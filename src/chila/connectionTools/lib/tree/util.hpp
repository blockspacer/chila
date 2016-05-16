/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__UTIL_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__UTIL_HPP

#include "fwd.hpp"
#include <chila/lib/misc/SinkInserter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <chila/lib/node/fwd.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/node/exceptions.hpp>
#include <chila/lib/xmlppUtils/util.hpp>
#include <string>
#include <chila/lib/misc/macrosExp.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    void sendXMLToStream(std::ostream &out, const connector::Connector &connector, unsigned index = 0);
    void sendXMLToStream(std::ostream &out, const cPerformer::ConnectionPerformer &cPerformer, unsigned index = 0);
//
    struct NspInserter final: public chila::lib::misc::SinkInserter<NspInserter>
    {
        const chila::lib::misc::Path &path;
        NspInserter(const chila::lib::misc::Path &path) : path(path) {}

        void write(std::ostream &out) const;
    };

    struct ArgListInserter final: public chila::lib::misc::SinkInserter<ArgListInserter>
    {
        const connector::Function &fun;
        const std::string &delim;

        ArgListInserter(const connector::Function &fun, const std::string &delim) : fun(fun), delim(delim) {}

        void write(std::ostream &out) const;
    };

    struct EvCalledInserter final: public chila::lib::misc::SinkInserter<EvCalledInserter>
    {
        const connector::Action &fun;
        const std::string &delim;

        EvCalledInserter(const connector::Action &fun, const std::string &delim) : fun(fun), delim(delim) {}

        void write(std::ostream &out) const;
    };

    struct PathInserter final: public chila::lib::misc::SinkInserter<PathInserter>
    {
        const chila::lib::misc::Path &path;
        const std::string &delim;

        PathInserter(const chila::lib::misc::Path &path, const std::string &delim) : delim(delim), path(path) {}

        void write(std::ostream &out) const;
    };

    Namespace &createNamespaceFromHere(Namespace &base, const chila::lib::misc::Path &path);

    StringVec getIdVec(const std::string &text, const char *sep);

    template <typename Group, typename Map, typename Instance>
    chila::lib::misc::Path getFullId(const Instance &object)
    {
        chila::lib::misc::Path ret = object.name();

        auto *ciMap = &(object.template parent<Map>());

        while (auto *group = dynamic_cast<const Group*>(
                    chila::lib::misc::checkNotNull(ciMap->parentPtr())))
        {
            ret.add(group->name());
            ciMap = &(group->template parent<Map>());
        }

        return ret.reverse();
    }

    chila::lib::misc::Path getFullId(const connector::Argument &object);
    chila::lib::misc::Path getFullId(const connector::Event &object);
    chila::lib::misc::Path getFullId(const connector::Action &object);
    chila::lib::misc::Path getFullId(const cPerformer::ConnectorInstance &object);

    void print(std::ostream &out, const ReqProvVector &vec, unsigned indent);

    ValueVec posibilites(const chila::lib::node::Node &node);

    cPerformer::ConnectorInstance &getCInstance(cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path);
    const cPerformer::ConnectorInstance &getCInstance(const cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path);

    cPerformer::AProviderCreator &getAPC(cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path);
    const cPerformer::AProviderCreator &getAPC(const cPerformer::ConnectionPerformer &cPerformer, const clMisc::Path &path);

    template <typename Group, typename Element, typename Map>
    Element &getGroupedElement(Map &map, clMisc::Path path)
    {
        auto *lastNode = &map;

        if (path.empty())
            BOOST_THROW_EXCEPTION(chila::lib::node::NodeNotFound());

        auto name = path.top();
        path.pop();

        for (auto &gName : path)
        {
            lastNode = &(lastNode->get(gName).template toType<Group>().elements());
        }

        return lastNode->get(name).template toType<Element>();
    }

    clMisc::Path getGroupedFullPath(const chila::lib::node::Node &element);

    inline std::string getImplName(const std::string &groupQualName)
    {
        return chila::lib::misc::Path(groupQualName, ":").getStringRep("_");
    }

    CInsVec getInitCInstances(const cPerformer::ConnectionPerformer &cPerformer);

    template <typename Group, typename Element, typename Map, typename Fun>
    void generateGrouped(unsigned indent,
                         const Map &map,
                         bool first,
                         const std::string &prefix,
                         const std::string &delim,
                         const Fun &fun)
    {
        for (const auto &elementBase : map)
        {
            if (const auto *element = dynamic_cast<const Element*>(&elementBase))
            {
                fun(indent, first, prefix, *element);
            }
            else if (const auto *group = dynamic_cast<const Group*>(&elementBase))
            {
                generateGrouped<Group, Element>
                (
                    indent,
                    group->elements(),
                    first, prefix + group->name() + delim,
                    delim, fun
                );
            }

            first = false;
        }
    }

    template <typename Parent, typename Group, typename InType> // Map
    ADD_CONST_IF(Parent) &getGroupParent(InType &inType)
    {
        auto *map = &inType;
        while (true)
        {
            auto *p = map->parentPtr();
            my_assert(p);

            if (auto *group = dynamic_cast<ADD_CONST_IF(Group)*>(p))
            {
                map = &(group->template parent<InType>());
            }
            else if (auto *cPerf = dynamic_cast<ADD_CONST_IF(Parent)*>(p))
            {
                return *cPerf;
            }
            else abort();
        }
    }

    template <typename Group, typename InType /* Map */>
    InType &getMainParent(InType &inType)
    {
        InType *curr = &inType;
        while (true)
        {
            auto *parent = chila::lib::misc::checkNotNull(curr->parentPtr());

            if (auto *tp = dynamic_cast<ADD_CONST_IF(Group)*>(parent))
            {
                curr = &(tp->template parent<InType>());
            }
            else return *curr;
        }
    }

#define def_get_main_parent(Name) \
    inline Name##Map &getMainParent(Name##Map &inType)   { return getMainParent<Name##Group>(inType); } \
    inline const Name##Map &getMainParent(const Name##Map &inType)   { return getMainParent<Name##Group>(inType); }

    def_get_main_parent(connector::Argument);
    def_get_main_parent(connector::Action);
    def_get_main_parent(connector::Event);

    def_get_main_parent(cPerformer::Argument);
    def_get_main_parent(cPerformer::AProviderCreator);
    def_get_main_parent(cPerformer::ConnectorInstance);

#undef def_get_main_parent

    template <typename Group, typename ParseElementFun, typename Map>
    void parseGrouped(Map &map, const xmlpp::Element &root, const std::string &tagName, const ParseElementFun &parseElementFun)
    {
        namespace xmlppUtils = chila::lib::xmlppUtils;

        xmlppUtils::iterateChildren(root, [&](const xmlpp::Element &element)
        {
            std::string elemValue = element.get_name();

            if (elemValue == tagName)
            {
                parseElementFun(map, element);
            }
            else if (elemValue == "group")
            {
                auto elementName = xmlppUtils::getAttribute<std::string>(element, "name");
                auto description = xmlppUtils::getAttribute<std::string>(element, "description", "");
                auto &group = map.template add<Group>(elementName);

                group.description().value = description;
                parseGrouped<Group>(group.elements(), element, tagName, parseElementFun);
            }
            else
            {
                chila::lib::xmlppUtils::throwException(chila::lib::xmlppUtils::InvalidTagName(), element);
            }
        });
    }

    clMisc::Path getGroupedPath(const chila::lib::node::Node &node);

    const cPerformer::EventAlias *getEventAlias(const cPerformer::EventCall &eventCall);
    const cPerformer::ActionAlias *getActionAlias(const cPerformer::ActionInstance &actionIns);
    const cPerformer::ActionAlias *getActionAlias(const cPerformer::ConnectorInstance &cInstance,
                                                  const cPerformer::ActionInstance &actionIns);
}
MY_NSP_END

#include "nspUndef.hpp"



#endif

