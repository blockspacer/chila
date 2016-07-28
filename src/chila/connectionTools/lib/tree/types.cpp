/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "types.hpp"
#include "exceptions.hpp"
#include <chila/lib/node/util.hpp>
#include <chila/lib/misc/util.hpp>
#include <type_traits>
#include "util.hpp"
#include <boost/make_unique.hpp>

#include "nspDef.hpp"

#define my_assert           CHILA_LIB_MISC__ASSERT

#define catch_add_refpath \
        catch (Exception &ex) \
        { \
            throw ex << ErrorInfo::ReferencePath(path()); \
        } \
        catch (chila::lib::node::Exception &ex) \
        { \
            throw ex << ErrorInfo::ReferencePath(path()); \
        }

#define def_referenced(RefType, based, val) \
        RefType::Type &RefType::referenced() try             { return base(based).get(val); } catch_add_refpath \
        const RefType::Type &RefType::referenced() const try { return base(based).get(val); } catch_add_refpath

#define def_referenced_grouped(RefType, based, Group, val) \
        RefType::Type &RefType::referenced() try \
        { \
            return getGroupedElement<Group, RefType::Type>(base(based), val); \
        } \
        catch_add_refpath \
        \
        const RefType::Type &RefType::referenced() const try \
        { \
            return getGroupedElement<const Group, const RefType::Type>(base(based), val); \
        } \
        catch_add_refpath


MY_NSP_START
{
    template <typename Container, typename Element, typename InType>
    ADD_CONST_IF(Container) &getFrom(InType &node)
    {
        if (auto *typed = dynamic_cast<ADD_CONST_IF(Container)*>(&node))
        {
            return *typed;
        }
        else if (auto *typed = dynamic_cast<ADD_CONST_IF(Element)*>(&node))
        {
            return typed->template parent<Container>();
        }
        else abort();
    }

    void Element::check(chila::lib::node::CheckData *data) const
    {
        checkDesc(*this);
    }

    namespace connector
    {
        // ArgRef --------------------------------------------------------------------------------------------------------
        ArgumentMap &ArgRef::base(Node &ref)
        {
            auto *map = ref.parent<Function>().parentPtr();

            if (auto *typed = dynamic_cast<EventMap*>(map))
            {
                return getGroupParent<Connector, EventGroup>(*typed).arguments();
            }
            else if (auto *typed = dynamic_cast<ActionMap*>(map))
            {
                return getGroupParent<Connector, ActionGroup>(*typed).arguments();
            }
            else abort();
        }

        const ArgumentMap &ArgRef::base(const Node &ref)
        {
            auto *map = ref.parent<Function>().parentPtr();

            if (auto *typed = dynamic_cast<const EventMap*>(map))
            {
                return getGroupParent<Connector, EventGroup>(*typed).arguments();
            }
            else if (auto *typed = dynamic_cast<const ActionMap*>(map))
            {
                return getGroupParent<Connector, ActionGroup>(*typed).arguments();
            }
            else abort();
        }

        def_referenced_grouped(ArgRef, parent<ArgRefMap>(), ArgumentGroup, clMisc::Path(name(), ":"))

        // EventRef --------------------------------------------------------------------------------------------------------
        EventMap &EventRef::base(Node &ref)
        {
            return getGroupParent<Connector, ActionGroup>(
                   ref.parent<Action>()
                      .parent<ActionMap>()).events();
        }

        const EventMap &EventRef::base(const Node &ref)
        {
            return getGroupParent<Connector, ActionGroup>(
                   ref.parent<Action>()
                      .parent<ActionMap>()).events();
        }


        def_referenced_grouped(EventRef, parent<EventRefMap>(), EventGroup, clMisc::Path(name(), ":"))
    }



    namespace cPerformer
    {
        // ArgRefV --------------------------------------------------------------------------------------------------------
        ArgumentMap &ArgRefV::base(Node &ref)
        {
            return getGroupParent<ConnectionPerformer, AProviderCreatorGroup>(ref.parent<AProviderCreator>()
                                                           .parent<AProviderCreatorMap>()).arguments();
        }

        const ArgumentMap &ArgRefV::base(const Node &ref)
        {
            return getGroupParent<ConnectionPerformer, AProviderCreatorGroup>(ref.parent<AProviderCreator>()
                                                           .parent<AProviderCreatorMap>()).arguments();
        }

        def_referenced_grouped(ArgRefV, parent<ArgRefVMap>(), ArgumentGroup, clMisc::Path(name(), ":"))

        // ArgRefT --------------------------------------------------------------------------------------------------------
        ArgumentMap &ArgRefT::base(Node &ref)
        {
            return ref.parent<CAArgAlias>()
                      .parent<CAArgAliasMap>()
                      .parent<ConnectorAlias>()
                      .parent<ConnectorAliasMap>()
                      .parent<ConnectionPerformer>().arguments();
        }

        const ArgumentMap &ArgRefT::base(const Node &ref)
        {
            return ref.parent<CAArgAlias>()
                      .parent<CAArgAliasMap>()
                      .parent<ConnectorAlias>()
                      .parent<ConnectorAliasMap>()
                      .parent<ConnectionPerformer>().arguments();
        }

        def_referenced_grouped(ArgRefT, *this, ArgumentGroup, value)

        // CAArgAlias --------------------------------------------------------------------------------------------------------
        connector::ArgumentMap &CAArgAlias::base(Node &ref)
        {
            return ref.parent<ConnectorAlias>().connector().referenced().arguments();
        }


        const connector::ArgumentMap &CAArgAlias::base(const Node &ref)
        {
            return ref.parent<ConnectorAlias>().connector().referenced().arguments();
        }

        def_referenced_grouped(CAArgAlias, parent<CAArgAliasMap>(), connector::ArgumentGroup, clMisc::Path(name(), ":"))

        // EventAlias --------------------------------------------------------------------------------------------------------
        connector::EventMap &EventAlias::base(Node &ref)
        {
            return ref.parent<ConnectorAlias>()
                      .connector().referenced().events();
        }


        const connector::EventMap &EventAlias::base(const Node &ref)
        {
            return ref.parent<ConnectorAlias>()
                      .connector().referenced().events();
        }

        def_referenced_grouped(EventAlias, parent<EventAliasMap>(), connector::EventGroup, clMisc::Path(name(), ":"))

        // ActionAlias --------------------------------------------------------------------------------------------------------
        connector::ActionMap &ActionAlias::base(Node &ref)
        {
            return ref.parent<ConnectorAlias>()
                      .connector().referenced().actions();
        }


        const connector::ActionMap &ActionAlias::base(const Node &ref)
        {
            return ref.parent<ConnectorAlias>()
                      .connector().referenced().actions();
        }

        def_referenced_grouped(ActionAlias, parent<ActionAliasMap>(), connector::ActionGroup, clMisc::Path(name(), ":"))

        // ConnectorRef --------------------------------------------------------------------------------------------------------
        Namespace &ConnectorRef::base(Node &ref)
        {
            return ref.parent<ConnectorAliasMap>()
                      .parent<ConnectionPerformer>()
                      .parent<Namespace>();
        }

        const Namespace &ConnectorRef::base(const Node &ref)
        {
            return ref.parent<ConnectorAliasMap>()
                      .parent<ConnectionPerformer>()
                      .parent<Namespace>();
        }

        connector::Connector &ConnectorRef::referenced() try
        {
            my_assert(parentPtr());
            if (value.empty())
                BOOST_THROW_EXCEPTION(ConnectorNotFound());

            return base(*parentPtr()).find(value).toType<connector::Connector>();
        }
        catch_add_refpath

        const connector::Connector &ConnectorRef::referenced() const try
        {
            my_assert(parentPtr());
            if (value.empty())
                BOOST_THROW_EXCEPTION(ConnectorNotFound());

            return base(*parentPtr()).find(value).toType<connector::Connector>();
        }
        catch_add_refpath

        // ConnectorAliasRef --------------------------------------------------------------------------------------------------------
        ConnectorAliasMap &ConnectorAliasRef::base(Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(ref.parent<ConnectorInstance>()
                                                            .parent<ConnectorInstanceMap>()).connectorAliases();
        }

        const ConnectorAliasMap &ConnectorAliasRef::base(const Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(ref.parent<ConnectorInstance>()
                                                            .parent<ConnectorInstanceMap>()).connectorAliases();
        }

        def_referenced(ConnectorAliasRef, *this, value)

        // APCRef --------------------------------------------------------------------------------------------------------
        AProviderCreatorMap &APCRef::base(Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(getFrom<APCRefMap, APCRef>(ref)
                                                        .parent<EventCall>()
                                                        .parent<EventCallMap>()
                                                        .parent<ConnectorInstance>()
                                                        .parent<ConnectorInstanceMap>()).aProvCreators();
        }

        const AProviderCreatorMap &APCRef::base(const Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(getFrom<APCRefMap, APCRef>(ref)
                                                        .parent<EventCall>()
                                                        .parent<EventCallMap>()
                                                        .parent<ConnectorInstance>()
                                                        .parent<ConnectorInstanceMap>()).aProvCreators();
        }

        def_referenced_grouped(APCRef, *this, AProviderCreatorGroup, clMisc::Path(name(), ":"))

        // ActionRef --------------------------------------------------------------------------------------------------------
        connector::ActionMap &ActionRef::base(Node &ref)
        {
            return ref.parent<ActionInstance>()
                      .connInstance().referenced()
                      .connAlias().referenced()
                      .connector().referenced().actions();
        }

        const connector::ActionMap &ActionRef::base(const Node &ref)
        {
            return ref.parent<ActionInstance>()
                      .connInstance().referenced()
                      .connAlias().referenced()
                      .connector().referenced().actions();
        }

        def_referenced_grouped(ActionRef, *this, connector::ActionGroup, value)

        // EventCall --------------------------------------------------------------------------------------------------------
        connector::EventMap &EventCall::base(Node &ref)
        {
            return ref.parent<ConnectorInstance>()
                      .connAlias().referenced().connector().referenced().events();
        }

        const connector::EventMap &EventCall::base(const Node &ref)
        {
            return ref.parent<ConnectorInstance>()
                      .connAlias().referenced().connector().referenced().events();
        }

        def_referenced_grouped(EventCall, parent<EventCallMap>(), connector::EventGroup, clMisc::Path(name(), ":"))

        // ConnectorInstanceRef --------------------------------------------------------------------------------------------------------
        ConnectorInstanceMap &ConnectorInstanceRef::base(Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(ref.parent<ActionInstance>()
                                                            .parent<ActionInstanceVec>()
                                                            .parent<EventCall>()
                                                            .parent<EventCallMap>()
                                                            .parent<ConnectorInstance>()
                                                            .parent<ConnectorInstanceMap>()).connInstances();
        }

        const ConnectorInstanceMap &ConnectorInstanceRef::base(const Node &ref)
        {
            return getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(ref.parent<ActionInstance>()
                                                            .parent<ActionInstanceVec>()
                                                            .parent<EventCall>()
                                                            .parent<EventCallMap>()
                                                            .parent<ConnectorInstance>()
                                                            .parent<ConnectorInstanceMap>()).connInstances();
        }

        template <typename InType> // ConnectorInstanceRef
        ADD_CONST_IF(ConnectorInstance) &ConnectorInstanceRef_referenced(InType &ciRef)
        {
            if (ciRef.value.empty())
            {
                BOOST_THROW_EXCEPTION(ConnectorInstanceNotFound());
            }

            auto &cInsMap = ConnectorInstanceRef::base(ciRef);

            return getGroupedElement<ADD_CONST_IF(ConnectorInstanceGroup), ADD_CONST_IF(ConnectorInstance)>(cInsMap, ciRef.value);
        }

        ConnectorInstance &ConnectorInstanceRef::referenced() try
        {
            return ConnectorInstanceRef_referenced(*this);
        }
        catch_add_refpath

        const ConnectorInstance &ConnectorInstanceRef::referenced() const try
        {
            return ConnectorInstanceRef_referenced(*this);
        }
        catch_add_refpath


        // ActionInstance --------------------------------------------------------------------------------------------------------
        const cPerformer::Argument &aliasOf(const ConnectorInstance &instance, const std::string &arg)
        {
            return instance.connAlias().referenced().arguments().get(arg).cpRef().referenced();
        }

        void loadSet(const ConnectorInstance &instance, PathSet &set, const connector::Function &fun)
        {
            chila::lib::node::CheckExceptionList eList;

            for (const auto &arg : fun.arguments()) chila::lib::node::checkAndAdd(eList, [&]
            {
                auto &alias = instance.connAlias().referenced().arguments().get(arg).cpRef().value;
                set.insert(alias); // TODO Test if putting 2 argRef pointing to the same cp-arg is catched as a 2 provided args
            });

            if (!eList.exceptions.empty()) BOOST_THROW_EXCEPTION(eList);
        }


        void load(const ActionInstance &aInstance, ReqProvVector &rpVec)
        {
            chila::lib::node::CheckExceptionList eList;

            const auto &eCall = aInstance.parent<ActionInstanceVec>().parent<EventCall>();

            // Adds the event's provided arguments
            ReqProv evReqProv(eCall.path(), "");

            chila::lib::node::checkAndAdd(eList, [&]
            {
                loadSet(eCall.parent<EventCallMap>().parent<ConnectorInstance>(), evReqProv.provides, eCall.referenced());
            });

            rpVec.push_back(evReqProv);

            // Goes through all the APCs
            for (const auto &apcRef : eCall.aProvCreators()) chila::lib::node::checkAndAdd(eList, [&]
            {
                const auto &apc = apcRef.referenced();
                ReqProv reqProv(apc.path(), clMisc::Path(apcRef.name(), ":"));

                // Adds the required arguments of the APC
                for (const auto &argRef : apc.requires())
                {
                    my_assert(reqProv.requires.insert(clMisc::Path(argRef.name(), ":")).second);
                }

                // Adds the provided arguments of the APC
                for (const auto &argRef : apc.provides())
                {
                    my_assert(reqProv.provides.insert(clMisc::Path(argRef.name(), ":")).second);
                }
                rpVec.push_back(reqProv);
            });

            // Adds the action's required arguments
            ReqProv acReqProv(aInstance.path(), "");

            chila::lib::node::checkAndAdd(eList, [&]
            {
                loadSet(aInstance.connInstance().referenced(), acReqProv.requires, aInstance.action().referenced());
            });

            rpVec.push_back(acReqProv);

            if (!eList.exceptions.empty()) BOOST_THROW_EXCEPTION(eList);
        }

        chila::lib::node::CheckDataUPtr EventAlias::createCheckData(chila::lib::node::CheckData *data) const
        {
            return boost::make_unique<chila::lib::node::CheckData>(*data);
        }

        void EventAlias::myCheck(chila::lib::node::CheckData *data) const
        {
            if (description().value.empty())
                throw chila::lib::node::ExceptionWrapper(DescriptionIsEmpty()
                    << chila::lib::misc::ExceptionInfo::Path(path()));
        }

        chila::lib::node::CheckDataUPtr ActionAlias::createCheckData(chila::lib::node::CheckData *data) const
        {
            return boost::make_unique<chila::lib::node::CheckData>(*data);
        }

        void ActionAlias::myCheck(chila::lib::node::CheckData *data) const
        {
            if (description().value.empty())
                throw chila::lib::node::ExceptionWrapper(DescriptionIsEmpty()
                    << chila::lib::misc::ExceptionInfo::Path(path()));
        }

        struct EventCallCheckData : public chila::lib::node::CheckData
        {
            using PathSet = std::set<chila::lib::misc::Path>;
            using RequiredMap = std::map<chila::lib::misc::Path, unsigned>;

            PathSet apcs;
            RequiredMap required;
        };

        chila::lib::node::CheckDataUPtr EventCall::createCheckData(chila::lib::node::CheckData *data) const
        {
            auto ret = boost::make_unique<EventCallCheckData>();
            for (auto &apcRef : aProvCreators())
                my_assert(ret->apcs.insert(clMisc::Path(apcRef.name(), ":")).second);

            return rvalue_cast(ret);
        }

        void EventCall::myCheck(chila::lib::node::CheckData *data) const
        {
            auto &checkData = dynamic_cast<EventCallCheckData&>(chila::lib::misc::deref(data));

            chila::lib::node::CheckExceptionList eList;

            for (auto &apc : checkData.apcs) chila::lib::node::checkAndAdd(eList, [&]
            {
                auto apcsPath = aProvCreators().path();
                chila::lib::node::checkAndAdd(eList, [&]
                {
                    throw chila::lib::node::ExceptionWrapper(ArgumentProviderCreatorNotUsed(apc.getStringRep(":"))
                        << chila::lib::misc::ExceptionInfo::Path(apcsPath + apc.getStringRep(":")));
                });
            });

            for (auto &vt : checkData.required) if (vt.second > 1) chila::lib::node::checkAndAdd(eList, [&]
            {
                const auto &arguments = getGroupParent<ConnectionPerformer, ConnectorInstanceGroup>(parent<EventCallMap>()
                                                                       .parent<ConnectorInstance>()
                                                                       .parent<ConnectorInstanceMap>()).arguments();

                auto &argName = vt.first;
                auto &arg = getGroupedElement<const ArgumentGroup, const Argument>(arguments, argName);

                if (arg.unique().value)
                {
                    chila::lib::node::checkAndAdd(eList, [&]
                    {
                        throw chila::lib::node::ExceptionWrapper(UniqueArgumentRequiredMoreThanOnce(arg.name())
                            << chila::lib::misc::ExceptionInfo::Path(path())
                            << ErrorInfo::ReferencePath(arg.path()));
                    });
                }
            });

            if (!eList.exceptions.empty()) BOOST_THROW_EXCEPTION(eList);
        }

        void ActionInstance::check(chila::lib::node::CheckData *data) const
        {
            chila::lib::node::CheckExceptionList eList;

            auto &checkData = dynamic_cast<EventCallCheckData&>(chila::lib::misc::deref(data));

            ReqProvVector rpVec;

            chila::lib::node::checkAndAdd(eList, [&]
            {
                NodeWithChildren::check();
            });

            chila::lib::node::checkAndAdd(eList, [&]
            {
                Element::check();
            });

            chila::lib::node::checkAndAdd(eList, [&]
            {
                load(*this, rpVec);
            });

            std::set<clMisc::Path> provArgs;
            for (auto &reqProv : rpVec)
            {
                for (auto &provArg : reqProv.provides)
                {
                    if (!provArgs.insert(provArg).second) chila::lib::node::checkAndAdd(eList, [&]
                    {
                        throw chila::lib::node::ExceptionWrapper(ArgumentProvidedManyTimes(provArg)
                            << chila::lib::misc::ExceptionInfo::Path(path())
                            << ErrorInfo::ReqProvVec(rpVec));
                    });
                }
            }

            for (unsigned reqIndex = 1; reqIndex < rpVec.size(); ++reqIndex)
            {
                for (const auto &reqArg : rpVec[reqIndex].requires) chila::lib::node::checkAndAdd(eList, [&]
                {
                    // Only register the required arguments for the actions for uniqueness
                    if (reqIndex == rpVec.size() - 1)
                        ++checkData.required[reqArg];

                    bool found = false;
                    for (unsigned provIndex = 0; provIndex < reqIndex; ++provIndex)
                    {
                        auto &entry = rpVec[provIndex];
                        const auto &provides = entry.provides;
                        if (provides.count(reqArg))
                        {
                            if (found)
                            {
                                throw chila::lib::node::ExceptionWrapper(RequiredArgumentProvidedManyTimes(reqArg) // <-- this is redundant
                                    << chila::lib::misc::ExceptionInfo::Path(path())
                                    << ErrorInfo::ReqProvVec(rpVec));
                            }
                            else
                            {
                                found = true;

                                if (provIndex) // index > 1 means it's an APC
                                    checkData.apcs.erase(entry.apcName);
                            }
                        }
                    }

                    if (!found)
                    {
                        throw chila::lib::node::ExceptionWrapper(RequiredArgumentNotFound(reqArg)
                            << chila::lib::misc::ExceptionInfo::Path(path())
                            << ErrorInfo::ReqProvVec(rpVec));
                    }
                });
            }

            if (!eList.exceptions.empty()) BOOST_THROW_EXCEPTION(eList);
        }

        void ConnectionPerformer::check(chila::lib::node::CheckData *data) const
        {
            chila::lib::node::CheckExceptionList eList;

            chila::lib::node::checkAndAdd(eList, [&]
            {
                Element::check(data);
            });

            chila::lib::node::checkAndAdd(eList, [&]
            {
                NodeWithChildren::check(data);
            });

            if (!eList.exceptions.empty()) throw eList;
        }
    }
}
MY_NSP_END

