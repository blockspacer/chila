/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "fwd.hpp"
#include <iostream>
#include <chila/lib/misc/RepeatText.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>
#include "types.hpp"
#include "exceptions.hpp"
#include <type_traits>
#include <boost/range/adaptors.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <libxml++/libxml++.h>
#include <chila/lib/misc/InPlaceStrStream.hpp>
#include <chila/lib/xmlppUtils/util.hpp>

#define ins_first(what) \
        if (first) first = false; \
        else out << what;

#define INDENT repeatText(indent, "    ")

#include "nspDef.hpp"

MY_NSP_START
{
    using chila::lib::misc::repeatText;
    using chila::lib::misc::quoted;
    using chila::lib::misc::xmlEscape;
    using chila::lib::misc::StringSet;

    namespace xmlppUtils = chila::lib::xmlppUtils;

    struct field final: public chila::lib::misc::SinkInserter<field>
    {
        using result_type = std::ostream;

        std::string value;
        unsigned maxLen;

        field(const std::string &value, unsigned maxLen) : value(value), maxLen(maxLen) {}

        void write(std::ostream &out) const
        {
            my_assert(maxLen >= value.size());
            out << value << chila::lib::misc::repeatText(maxLen - value.size(), " ");
        }
    };

    inline field qField(const std::string &value, unsigned maxLen)
    {
        return field("\"" + value + "\"", maxLen + 2);
    }

    void writeHeaderComment(xmlpp::Element &root, const std::string &comment, unsigned indent, bool newLine)
    {
        if (newLine)
            root.add_child_text("\n");

        xmlppUtils::writeIndent(root, indent);
        root.add_child_comment(" " + comment + " ");
    }

    template <typename Group, typename Element, typename Map, typename StreamElementFun>
    void sendToStreamGrouped(xmlpp::Element &root, const Map &map, unsigned indent, const StreamElementFun &streamElement)
    {
        for (auto &element : map)
        {
            if (auto *typed = dynamic_cast<const Element*>(&element))
            {
                streamElement(root, *typed, indent);
            }
            else if (auto *typed = dynamic_cast<const Group*>(&element))
            {
                add_element_wf(root, "group", groupElem)
                {
                    groupElem.set_attribute("name", typed->name());
                    groupElem.set_attribute("description", typed->description().value);
                    sendToStreamGrouped<Group, Element>(groupElem, typed->elements(), indent, streamElement);
                });
            }
            else abort();
        }
    }

    // ============================================= Connector =======================================================

    std::string firstUppercase(std::string data)
    {
        data.at(0) -= ('a' - 'A');
        return data;
    }

    namespace connector
    {
        /** Generates an argument list. */
        std::ostream &operator<<(std::ostream &out, const ArgRefMap &args)
        {
            bool first = true;
            for (const auto &funArg : args)
            {
                ins_first(", ");
                out << funArg.name();
            }

            return out;
        }

        /** Generates an argument list. */
        std::ostream &operator<<(std::ostream &out, const EventRefMap &events)
        {
            bool first = true;
            for (const auto &event : events)
            {
                ins_first(", ");
                out << event.name();
            }

            return out;
        }
    }

    void writeFunEvents(xmlpp::Element &funElem, const connector::Action &action)
    {
        if (!action.events().empty())
            funElem.set_attribute("events", my_ipss_exp(action.events()));
    }

    void writeFunEvents(xmlpp::Element &funElem, const connector::Event &action) {}

    void sendToStream(xmlpp::Element &root, const connector::ArgumentMap &arguments, unsigned indent = 0)
    {
        writeHeaderComment(root, "Arguments", indent, false);

        add_element_wf(root, "arguments", argumentsElem)
        {
            sendToStreamGrouped<connector::ArgumentGroup, connector::Argument>(argumentsElem, arguments, indent,
                [](xmlpp::Element &root, const connector::Argument &arg, unsigned indent)
                {
                    add_element_wf(root, "arg", child)
                    {
                        child.set_attribute("name", arg.name());
                        child.set_attribute("description", my_ipss_exp(xmlEscape(arg.description().value)));
                    });
                });
        });

    }

    template <typename Function, typename FunctionGroup, typename Map>
    void sendToStreamFMap(xmlpp::Element &root, const Map &functions, const std::string &name, unsigned indent = 0)
    {
        writeHeaderComment(root, " " + firstUppercase(name) + "s ", indent, false);

        add_element_wf(root, name + "s", functionsElem)
        {
            sendToStreamGrouped<FunctionGroup, Function>(functionsElem, functions, indent,
                [&](xmlpp::Element &root, const Function &fun, unsigned indent)
                {
                    add_element_wf(root, name, child)
                    {
                        child.set_attribute("name", fun.name());
                        child.set_attribute("arguments", my_ipss_exp(fun.arguments()));
                        child.set_attribute("description", my_ipss_exp(xmlEscape(fun.description().value)));

                        writeFunEvents(child, fun);
                    });
                });
        });
    }

    void sendXMLToStream(std::ostream &out, const connector::Connector &connector, unsigned indent)
    {
        xmlpp::Document doc;
        auto &root = chila::lib::misc::deref(doc.create_root_node("connector"));

        root.set_attribute("name", my_ipss_exp(connector.path()));
        root.set_attribute("description", my_ipss_exp(xmlEscape(connector.description().value)));

        sendToStream(root, connector.arguments(), indent + 1);
        sendToStreamFMap<connector::Event, connector::EventGroup>(root, connector.events(), "event", indent + 1);
        sendToStreamFMap<connector::Action, connector::ActionGroup>(root, connector.actions(), "action", indent + 1);

        xmlppUtils::writeIndent(root, indent);

        doc.write_to_stream(out);
    }


    // =========================================== ConnectionPerformer =====================================================
    void sendToStream(xmlpp::Element &root, const cPerformer::ArgumentMap &args, unsigned indent = 0);
    void sendToStream(xmlpp::Element &root, const cPerformer::ConnectorAliasMap &cAliases, unsigned indent = 0);
    void sendToStream(xmlpp::Element &root, const cPerformer::AProviderCreatorMap &apCreators, unsigned indent = 0);
    void sendToStream(xmlpp::Element &root, const cPerformer::ConnectorInstanceMap &cInstances, unsigned indent = 0);

    namespace cPerformer
    {
        std::ostream &operator<<(std::ostream &out, const cPerformer::APCRefMap &apcRefs)
        {
            bool first = true;
            for (const auto &apcRef : apcRefs)
            {
                ins_first(",\n                                      ");
                out << apcRef.name();
            }
            return out;
        }

        std::ostream &operator<<(std::ostream &out, const cPerformer::ArgRefVMap &apcArgAliasRefs)
        {
            bool first = true;
            for (const auto &apcArgAliasRef : apcArgAliasRefs)
            {
                ins_first(", ");
                out << clMisc::Path(apcArgAliasRef.name()).getStringRep(":");
            }

            return out;
        }
    }


    void sendXMLToStream(std::ostream &out, const cPerformer::ConnectionPerformer &cPerformer, unsigned indent)
    {
        xmlpp::Document doc;
        auto &root = chila::lib::misc::deref(doc.create_root_node("cPerformer"));
        root.set_attribute("name", my_ipss_exp(cPerformer.path()));
        root.set_attribute("description", cPerformer.description().value);

        sendToStream(root, cPerformer.arguments(), indent + 1);
        sendToStream(root, cPerformer.connectorAliases(), indent + 1);
        sendToStream(root, cPerformer.aProvCreators(), indent + 1);
        sendToStream(root, cPerformer.connInstances(), indent + 1);

        xmlppUtils::writeIndent(root, indent);
        doc.write_to_stream(out);
    }

    void sendToStream(xmlpp::Element &root, const cPerformer::ArgumentMap &args, unsigned indent)
    {
        writeHeaderComment(root, "Arguments", indent, false);

        add_element_wf(root, "arguments", argumentsElem)
        {
            sendToStreamGrouped<cPerformer::ArgumentGroup, cPerformer::Argument>(argumentsElem, args, indent,
                [](xmlpp::Element &root, const cPerformer::Argument &arg, unsigned indent)
                {
                    add_element_wf(root, "argument", child)
                    {
                        child.set_attribute("name", arg.name());
                        child.set_attribute("unique", my_ipss_exp(clMisc::boolToText(arg.unique().value)));
                        child.set_attribute("description", my_ipss_exp(xmlEscape(arg.description().value)));
                    });
                });
        });
    }

    template <typename Alias>
    void printCPName(xmlpp::Element &childElem, const Alias &aliasRef, int)
    {
    }


    template <typename Alias>
    void printCPName(xmlpp::Element &childElem, const Alias &aliasRef, long)
    {
        childElem.set_attribute("cpName", chila::lib::misc::Path(aliasRef.cpRef().value).getStringRep(":"));
    }

    template <typename WithCPInt, typename Aliases>
    void printAliases(xmlpp::Element &root, const Aliases &aliases, const std::string &rootName, const std::string &childName, unsigned indent)
    {
        add_element_wf(root, rootName, rootElem)
        {
            for (const auto &aliasRef : aliases)
            {
                add_element_wf(rootElem, childName, childElem)
                {
                    childElem.set_attribute("name", aliasRef.name());
                    printCPName(childElem, aliasRef, WithCPInt{});
                    childElem.set_attribute("description", aliasRef.description().value);
                });
            }
        });
    }

    void sendToStream(xmlpp::Element &root, const cPerformer::ConnectorAliasMap &cAliases, unsigned indent)
    {
        writeHeaderComment(root, "Connector Aliases", indent, true);

        add_element_wf(root, "connectorAliases", cAliasesElem)
        {
            for (const auto &alias : cAliases)
            {
                add_element_wf(cAliasesElem, "alias", cAliasElem)
                {
                    cAliasElem.set_attribute("name", alias.name());
                    cAliasElem.set_attribute("connectorPath", alias.connector().value.getStringRep());
                    cAliasElem.set_attribute("description", my_ipss_exp(xmlEscape(alias.description().value)));

                    printAliases<long>(cAliasElem, alias.argAliases(), "arguments", "argument", indent);
                    printAliases<int>(cAliasElem, alias.eventAliases(), "events", "event", indent);
                    printAliases<int>(cAliasElem, alias.actionAliases(), "actions", "action", indent);
                });
            }
        });
    }

    void sendToStream(xmlpp::Element &root, const cPerformer::AProviderCreatorMap &apCreators, unsigned indent)
    {
        writeHeaderComment(root, "Argument Provider Creators", indent, true);

        add_element_wf(root, "argumentProviderCreators", apCreatorsElem)
        {
            sendToStreamGrouped<cPerformer::AProviderCreatorGroup, cPerformer::AProviderCreator>(apCreatorsElem, apCreators, indent,
                [](xmlpp::Element &root, const cPerformer::AProviderCreator &apc, unsigned indent)
                {
                    add_element_wf(root, "creator", apcElem)
                    {
                        apcElem.set_attribute("name", apc.name());
                        apcElem.set_attribute("requires", my_ipss_exp(apc.requires()));
                        apcElem.set_attribute("provides", my_ipss_exp(apc.provides()));
                    });
                });
        });
    }

    void sendToStream(xmlpp::Element &root, const cPerformer::ConnectorInstanceMap &cInstances, unsigned indent)
    {
        writeHeaderComment(root, "Connector Instances", indent, true);

        add_element_wf(root, "connectors", connectorsElem)
        {
            sendToStreamGrouped<cPerformer::ConnectorInstanceGroup, cPerformer::ConnectorInstance>(connectorsElem, cInstances, indent,
                [](xmlpp::Element &root, const cPerformer::ConnectorInstance &instance, unsigned indent)
                {
                    add_element_wf(root, "instance", instanceElem)
                    {
                        instanceElem.set_attribute("name", instance.name());
                        instanceElem.set_attribute("connectorAlias", my_ipss_exp(instance.connAlias().value));
                        instanceElem.set_attribute("description", my_ipss_exp(xmlEscape(instance.description().value)));

                        for (const auto &eventCall : instance.events())
                        {
                            auto apcEmpty = eventCall.aProvCreators().empty(),
                                 acEmpty = eventCall.actions().empty();

                            add_element_wf(instanceElem, "event", eventElem)
                            {
                                eventElem.set_attribute("name", eventCall.name());
                                eventElem.set_attribute("description", my_ipss_exp(xmlEscape(eventCall.description().value)));

                                add_element_wf(eventElem, "aProviderCreators", apCreatorsElem)
                                {
                                    for (auto &apc : eventCall.aProvCreators())
                                    {
                                        add_element_wf(apCreatorsElem, "apc", apcElem)
                                        {
                                            apcElem.set_attribute("name", apc.name());
                                        });
                                    }
                                });

                                add_element_wf(eventElem, "actions", actionsElem)
                                {
                                    for (auto &action : eventCall.actions())
                                    {
                                        add_element_wf(actionsElem, "action", actionElem)
                                        {
                                            actionElem.set_attribute("connector", action.connInstance().value.getStringRep(":"));
                                            actionElem.set_attribute("name", action.action().value.getStringRep(":"));
                                            actionElem.set_attribute("determinesOrder", clMisc::boolToText(action.determinesOrder().value));
                                            actionElem.set_attribute("description", my_ipss_exp(xmlEscape(action.description().value)));
                                        });
                                    }
                                });
                            });
                        }
                    });
                });
        });
    }


    void NspInserter::write(std::ostream &out) const
    {
        bool first = true;
        for (const auto &name : path.getNames())
        {
            if (first) first = false;
            else out << "_";

            boost::to_upper_copy(std::ostream_iterator<char,char>(out),
                    std::make_pair(name.begin(), name.end()));
        }
    }

    void ArgListInserter::write(std::ostream &out) const
    {
        bool first = true;
        for (const auto &funArg : fun.arguments())
        {
            auto pName = getFullId(funArg.referenced()).getStringRep("_");

            if (delim.empty())
            {
                out << "(" << pName << ")";
            }
            else
            {
                if (first) first = false;
                else out << ", ";

                out << pName;
            }
        }
    }

    void EvCalledInserter::write(std::ostream &out) const
    {
        bool first = true;
        for (const auto &eRef : fun.events())
        {
            auto fullId = getFullId(eRef.referenced()).getStringRep("_");

            if (delim.empty())
            {
                out << "(" << fullId << ")";
            }
            else
            {
                if (first) first = false;
                else out << ", ";

                out << fullId;
            }
        }
    }

    void PathInserter::write(std::ostream &out) const
    {
        bool first = true;
        for (const auto &name : path.getNames())
        {
            if (first) first = false;
            else out << delim;

            out << name;
        }
    }

    Namespace &createNamespaceFromHere(Namespace &base, const chila::lib::misc::Path &path)
    {
        Namespace *last = &base;
        NspElement *node;
        my_assert(!path.empty());

        bool found = true;
        for (const auto &name : path.getNames())
        {
            if (found && (node = last->getPtr(name)))
            {
                last = dynamic_cast<Namespace*>(node);
                my_assert(last);
            }
            else
            {
                found = false;
                last = &(last->add<Namespace>(name));
            }
        }

        return *last;
    }

    /** Parses 'names' into 'nameVec'. */
    StringVec getIdVec(const std::string &text, const char *sep)
    {
        StringVec ids;
        using Tokenizer = boost::tokenizer< boost::char_separator<char> >;
        Tokenizer tokens(text, boost::char_separator<char>(sep));
        for (auto name : tokens)
        {
            boost::trim(name);
            ids.push_back(name);
        }

        return ids;
    }

    std::ostream &operator<<(std::ostream &out, const PathSet &set)
    {
        bool first = true;
        for (const auto &str : set)
        {
            if (first) first = false;
            else out << ", ";

            out << str;
        }

        return out;
    }

    void print(std::ostream &out, const ReqProvVector &vec, unsigned indent)
    {
        for (const auto &reqProv : vec)
        {
            out << INDENT << "- " << reqProv.path.getStringRep() << "\n"
                << INDENT << "  - requires: " << reqProv.requires << "\n"
                << INDENT << "  - provides: " << reqProv.provides << std::endl;
        }
    }

    template <typename Type>
    ValueVec posibilities(const chila::lib::node::ContainerOfTyped<Type> &node)
    {
        ValueVec ret;

        for (const auto &base : Type::base(node))
        {
            ret.push_back(base.name());
        }

        return ret;
    }

    auto noLeafFun = [](ValueEntry &entry, const chila::lib::node::Node &node) {};

    template <typename Group, typename Map, typename LeafFun>
    ValueVec ciMapPos(const Map &map, const LeafFun &leafFun)
    {
        ValueVec valueMap;

        for (const auto &node : map)
        {
            valueMap.push_back(node.name());

            auto &entry = valueMap.back();

            if (const auto *typed = dynamic_cast<const Group*>(&node))
            {
                entry.subValues = ciMapPos<Group>(typed->elements(), leafFun);
            }
            else
            {
                leafFun(entry, node);
            }

        }

        return valueMap;
    }


    ValueVec posibilities(const connector::ArgRefMap &node)
    {
        return ciMapPos<connector::ArgumentGroup>(connector::ArgRef::base(node), noLeafFun);
    }

    ValueVec posibilities(const connector::EventRefMap &node)
    {
        return ciMapPos<connector::EventGroup>(connector::EventRef::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::EventCallMap &node)
    {
        return ciMapPos<connector::EventGroup>(cPerformer::EventCall::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::CAArgAliasMap &node)
    {
        return ciMapPos<connector::ArgumentGroup>(cPerformer::CAArgAlias::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::EventAliasMap &node)
    {
        return ciMapPos<connector::EventGroup>(cPerformer::EventAlias::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::ActionAliasMap &node)
    {
        return ciMapPos<connector::ActionGroup>(cPerformer::ActionAlias::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::ArgRefVMap &node)
    {
        return ciMapPos<cPerformer::ArgumentGroup>(cPerformer::ArgRefV::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::CAArgAlias &node)
    {
        return ciMapPos<cPerformer::ArgumentGroup>(cPerformer::ArgRefT::base(node.cpRef()), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::APCRefMap &node)
    {
        return ciMapPos<cPerformer::AProviderCreatorGroup>(cPerformer::APCRef::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::ActionRef &node)
    {
        return ciMapPos<connector::ActionGroup>(cPerformer::ActionRef::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::ConnectorInstanceRef &node)
    {
        return ciMapPos<cPerformer::ConnectorInstanceGroup>(cPerformer::ConnectorInstanceRef::base(node), noLeafFun);
    }

    ValueVec posibilities(const cPerformer::ActionInstanceVec &node)
    {
        auto &cInsMap = getMainParent<cPerformer::ConnectorInstanceGroup>(
            node.parent<cPerformer::EventCall>()
                .parent<cPerformer::EventCallMap>()
                .parent<cPerformer::ConnectorInstance>()
                .parent<cPerformer::ConnectorInstanceMap>());

        CHILA_LIB_MISC__SHOW(40, cInsMap.path());

        return ciMapPos<cPerformer::ConnectorInstanceGroup>(cInsMap,
            [&](ValueEntry &entry, const chila::lib::node::Node &node)
            {
                auto &cInstance = node.toType<cPerformer::ConnectorInstance>();
                auto &actionMap = cInstance.connAlias().referenced().connector().referenced().actions();

                entry.subValues = ciMapPos<connector::ActionGroup>(actionMap, noLeafFun);
            });
    }


    ValueVec posibilities(const chila::lib::node::TypedNode<bool> &node)
    {
        return { ValueEntry("true"), ValueEntry("false") };
    }

    template <typename Type>
    typename std::enable_if<std::is_base_of<chila::lib::node::IReference, Type>::value, ValueVec>::type
        posibilities(const Type &node)
    {
        ValueVec ret;

        for (const auto &base : Type::base(node))
        {
            ret.push_back(base.name());
        }

        return ret;
    }

#define ret_posibilites(Type) \
        if (const auto *typed = dynamic_cast<const Type*>(&node)) \
        { \
            return posibilities(*typed); \
        }

    ValueVec posibilites(const chila::lib::node::Node &node)
    {
        ret_posibilites(connector::ArgRefMap)
        ret_posibilites(connector::EventRefMap)
        ret_posibilites(cPerformer::CAArgAliasMap)
        ret_posibilites(cPerformer::CAArgAlias)
        ret_posibilites(cPerformer::EventAliasMap)
        ret_posibilites(cPerformer::ActionAliasMap)
        ret_posibilites(cPerformer::ArgRefVMap)
        ret_posibilites(cPerformer::APCRef)
        ret_posibilites(cPerformer::APCRefMap)
        ret_posibilites(cPerformer::ConnectorInstanceRef)
        ret_posibilites(cPerformer::ActionRef)
        ret_posibilites(cPerformer::ConnectorAliasRef)
        ret_posibilites(cPerformer::EventCallMap)
        ret_posibilites(cPerformer::ActionInstanceVec)
        ret_posibilites(chila::lib::node::TypedNode<bool>)


        return ValueVec();
    }

    cPerformer::ConnectorInstance &getCInstance(cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path) try
    {
        return getGroupedElement<cPerformer::ConnectorInstanceGroup, cPerformer::ConnectorInstance>(cPerformer.connInstances(), path);
    }
    catch (const chila::lib::node::NodeNotFound &ex)
    {
        BOOST_THROW_EXCEPTION(ConnectorInstanceNotFound() << clMisc::ExceptionInfo::Path(path));
    }

    const cPerformer::ConnectorInstance &getCInstance(const cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path) try
    {
        return getGroupedElement<const cPerformer::ConnectorInstanceGroup, const cPerformer::ConnectorInstance>(cPerformer.connInstances(), path);
    }
    catch (const chila::lib::node::NodeNotFound &ex)
    {
        BOOST_THROW_EXCEPTION(ConnectorInstanceNotFound() << clMisc::ExceptionInfo::Path(path));
    }

    cPerformer::AProviderCreator &getAProviderCreator(cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path) try
    {
        return getGroupedElement<cPerformer::AProviderCreatorGroup, cPerformer::AProviderCreator>(cPerformer.aProvCreators(), path);
    }
    catch (const chila::lib::node::NodeNotFound &ex)
    {
        BOOST_THROW_EXCEPTION(AProviderCreatorNotFound() << clMisc::ExceptionInfo::Path(path));
    }

    const cPerformer::AProviderCreator &getAProviderCreator(const cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path) try
    {
        return getGroupedElement<const cPerformer::AProviderCreatorGroup, const cPerformer::AProviderCreator>(cPerformer.aProvCreators(), path);
    }
    catch (const chila::lib::node::NodeNotFound &ex)
    {
        BOOST_THROW_EXCEPTION(AProviderCreatorNotFound() << clMisc::ExceptionInfo::Path(path));
    }

    using AInsSet = std::set<const cPerformer::ActionInstance*>;
    using CInsReqData = std::map<const cPerformer::ConnectorInstance*, AInsSet>;

    AInsSet getRequiredAInstances(const cPerformer::ConnectorInstance &cInstance)
    {
        AInsSet ret;

        for (auto &eventIns : cInstance.events())
        {
            for (auto &actionIns : eventIns.actions())
            {
                if (actionIns.determinesOrder())
                {
                    ret.insert(&actionIns);
                }
            }
        }

        return ret;
    }

    void getReqData(CInsReqData &reqData, const cPerformer::ConnectorInstanceMap &map)
    {
        for (auto &cInstanceBase : map)
        {
            if (auto *instance = dynamic_cast<const cPerformer::ConnectorInstance*>(&cInstanceBase))
            {
                my_assert(reqData.insert({instance, getRequiredAInstances(*instance)}).second);
            }
            else if (auto *group = dynamic_cast<const cPerformer::ConnectorInstanceGroup*>(&cInstanceBase))
            {
                getReqData(reqData, group->elements());
            }
        }
    }

    bool requires(const cPerformer::ConnectorInstance *cInstance,
                  const cPerformer::ConnectorInstance *reqCInstance,
                  const CInsReqData &reqData,
                  AInsVec &stack)
    {
        auto it = reqData.find(cInstance);
        my_assert(it != reqData.end());

//        CHILA_LIB_MISC__SHOW(40, cInstance->path());

        for (auto *reqAIns : it->second)
        {
//            CHILA_LIB_MISC__SHOW(40, reqAIns->path());

            auto *reqCIns = &reqAIns->connInstance().referenced();
            bool found = std::find_if(stack.begin(), stack.end(),
                    [&, reqCIns](const cPerformer::ActionInstance *lhs)
                    { return &lhs->connInstance().referenced() == reqCIns; }) != stack.end();

            stack.push_back(reqAIns);

            if (found)
            {
                BOOST_THROW_EXCEPTION(CInstanceReqCycle()
                        << clMisc::ExceptionInfo::Path(reqCIns->path())
                        << ErrorInfo::AInsVecInfo(stack));
            }
            else if (reqCIns == reqCInstance)
            {
                return true;
            }
            else if (requires(reqCIns, reqCInstance, reqData, stack))
            {
                return true;
            }

            stack.pop_back();
        }

        return false;
    }

#define def_get_full_id(Name) \
    chila::lib::misc::Path getFullId(const Name &object) \
    { \
        return getFullId<Name##Group, Name##Map>(object); \
    }

    def_get_full_id(connector::Argument)
    def_get_full_id(connector::Event)
    def_get_full_id(connector::Action)
    def_get_full_id(cPerformer::ConnectorInstance)

#undef def_get_full_id


    struct CInstanceLess
    {
        const CInsReqData &reqData;
        CInstanceLess(const CInsReqData &reqData) : reqData(reqData) {}

        bool operator()(const cPerformer::ConnectorInstance *lhs,
                       const cPerformer::ConnectorInstance *rhs) const
        {
            AInsVec stack;

            return requires(rhs, lhs, reqData, stack) ? true :
                  (requires(lhs, rhs, reqData, stack) ? false : getFullId(*lhs) < getFullId(*rhs));
        }
    };

    using CInsInitSet = std::set<const cPerformer::ConnectorInstance*, CInstanceLess>;

    // Returns the ordered vector of connector instances based on the requirements from one another, which is determined
    // by the 'determinesOrder' attribute of the connector's action.
    CInsVec getInitCInstances(const cPerformer::ConnectionPerformer &cPerformer)
    {
        CInsReqData required;
        CInsInitSet sorted{CInstanceLess(required)};

        getReqData(required, cPerformer.connInstances());

        for (auto &vt : required)
        {
            my_assert(sorted.insert(vt.first).second);
        }

        return CInsVec(sorted.begin(), sorted.end());
    }

    std::pair<clMisc::Path, const chila::lib::node::Node*> getGroupedPathPrv(const chila::lib::node::Node &node)
    {
        clMisc::Path ret = node.name();
        auto *curr = &node;
        while (auto parentMap = curr->parentPtr<chila::lib::node::NodeMap>())
        {
            if (auto parentGroup = parentMap->parentPtr<Group>())
            {
                ret = dynamic_cast<const chila::lib::node::Node&>(*parentGroup).name() + ret;
                curr = curr->parentPtr()->parentPtr();
            }
            else break;
        }

        return {ret, curr};
    }

    clMisc::Path getGroupedPath(const chila::lib::node::Node &node)
    {
        return getGroupedPathPrv(node).first;
    }

    clMisc::Path getGroupedFullPath(const chila::lib::node::Node &node)
    {
        clMisc::Path ret;

        for (auto curr = &node; curr; curr = curr->parentPtr())
        {
            clMisc::Path gPath;

            std::tie(gPath, curr) = getGroupedPathPrv(*curr);
            ret = gPath.getStringRep(":") + ret;
        }

        return ret;
    }

    const cPerformer::EventAlias *getEventAlias(const cPerformer::EventCall &eventCall)
    {
        auto &cInstance = eventCall.parent<const cPerformer::EventCallMap>()
                                   .parent<const cPerformer::ConnectorInstance>();

        auto &connAlias = cInstance.connAlias().referenced();
        auto gfPath = getGroupedPath(eventCall.referenced());
        return connAlias.eventAliases().getPtr(gfPath.getStringRep(":"));
    }

    const cPerformer::EventAlias *getEventAlias(const cPerformer::ConnectorInstance &cInstance,
                                                const cPerformer::EventCall &eventCall)
    {
        auto &connAlias = cInstance.connAlias().referenced();
        auto gfPath = getGroupedPath(eventCall.referenced());
        return connAlias.eventAliases().getPtr(gfPath.getStringRep(":"));
    }

    const cPerformer::ActionAlias *getActionAlias(const cPerformer::ActionInstance &actionIns)
    {
        auto &connAlias = actionIns.connInstance().referenced().connAlias().referenced();
        auto gfPath = getGroupedPath(actionIns.action().referenced());
        return connAlias.actionAliases().getPtr(gfPath.getStringRep(":"));
    }

    const cPerformer::ActionAlias *getActionAlias(const cPerformer::ConnectorInstance &cInstance,
                                                  const cPerformer::ActionInstance &actionIns)
    {
        auto &connAlias = cInstance.connAlias().referenced();
        auto gfPath = getGroupedPath(actionIns.action().referenced());
        return connAlias.actionAliases().getPtr(gfPath.getStringRep(":"));
    }
}
MY_NSP_END
