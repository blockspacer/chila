/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FileLoader.hpp"
#include <chila/connectionTools/lib/tree/types.hpp>
#include <chila/connectionTools/lib/tree/util.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include "../../lib/util.hpp"
#include <chila/lib/misc/util.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <fstream>
#include <boost/algorithm/string/case_conv.hpp>
#include "../../lib/actions.hpp"
#include "../../lib/ActionMap.hpp"
#include "../../lib/TextProperty.hpp"

#define MODULE_NAME FileLoader


#include "macros.fgen.hpp"

#define def_color(Type, COLOR) { boost::typeindex::type_id<cclTree::Type>(), MU_##COLOR }

MY_NSP_START
{
    struct writeDesc : public chila::lib::misc::SinkInserter<writeDesc>
    {
        const std::string &insDesc;
        unsigned limit;

        writeDesc(const std::string &insDesc, unsigned limit = clMisc::MAX_UINT) : insDesc(insDesc), limit(limit)
        {
        }

        void write(std::ostream &out) const
        {
            if (!insDesc.empty())
            {
                out << mu_italic(mu_fcolor(MU_DGREEN, " - " << (limit == clMisc::MAX_UINT ? insDesc :
                                                                limit < insDesc.size() ? insDesc.substr(0, limit) + "..." : insDesc)));
            }
        }
    };


    template <typename Type>
    void loadAction(lib::ActionMap &actionMap, const chila::lib::node::Node &node, const std::string &name = Type::title())
    {
        auto pos = cclTree::posibilites(node);

        Type &action = actionMap.template addAction<Type>();
        action.posibilities = cclTree::posibilites(node);
    }

    void FileLoader::loadContainerOfTyped(lib::ActionMap &actionMap, const chila::lib::node::Node &node)
    {
        auto pos = addPosibilities.posibilities(typeid(node).name());

        my_assert(pos.size());

        if (pos.size() == 1)
        {
            switch (pos.begin()->addType)
            {
                case lib::AddType::SIMPLE:   actionMap.addAction<lib::actions::Add>();           break;
                case lib::AddType::WITH_POS: loadAction<lib::actions::AddWPos>(actionMap, node); break;
                case lib::AddType::WITH_VAL: actionMap.addAction<lib::actions::AddWVal>();       break;
                default: abort();
            }
        }
        else
        {
            auto &aMap = actionMap.addMap("add");

            for (const auto &p : pos)
            {
                switch (p.addType)
                {
                    case lib::AddType::SIMPLE:   aMap.addAction<lib::actions::Add>(p.name);               break;
                    case lib::AddType::WITH_POS: loadAction<lib::actions::AddWPos>(aMap, node, p.name);   break;
                    case lib::AddType::WITH_VAL: aMap.addAction<lib::actions::AddWVal>(p.name);           break;
                    default: abort();
                }
            }
        }

        if (cutPathFrom)
        {
            auto parent = tPathMap.getNodePath(cutPathFrom);
            parent.pop();

            auto &fromNode = globalNsp.find(parent).toType<chila::lib::node::IContainerOfTyped>();
            auto &toNode = node.toType<chila::lib::node::IContainerOfTyped>();

            if (toNode.canTakeChildFrom(fromNode))
            {
                actionMap.addAction<lib::actions::Paste>();
            }
        }
    }

    template <typename NodeMap>
    void FileLoader::loadGroup(lib::ActionMap &actionMap)
    {
        if (cutPathFrom)
        {
            auto parent = cutPathFrom;
            parent.pop();

            if (globalNsp.find(parent).toTypePtr<NodeMap>())
            {
                actionMap.addAction<lib::actions::Paste>();
            }
        }
    }

#define set_map_posibilities_ex(ContType, ChildName, addType, withName, withVal, name) \
    addPosibilities.set<cclTree::ContType, cclTree::ChildName, withName, withVal>(lib::AddType::addType, name)

#define set_map_posibilities(ChildType, ContSuffix, addType, name) \
    set_map_posibilities_ex(ChildType##ContSuffix, ChildType, addType, true, false, name)

#define set_vec_posibilities(ChildType, ContSuffix, addType, withValue, name) \
    set_map_posibilities_ex(ChildType##ContSuffix, ChildType, addType, false, withValue, name)

#define wn_colored(node, exp) \
    mu_fcolor(findColor(boost::typeindex::type_id_runtime(node)), exp)

#define value_for(Type) \
    { boost::typeindex::type_id<cclTree::Type>(), [this](const chila::lib::node::Node &node) \
    { \
        auto color = findColor(boost::typeindex::type_id<cclTree::Type>()); \
        auto &typed = dynamic_cast<const cclTree::Type&>(node);

#define value_for_name_desc(Type) \
    value_for(Type) \
    { \
        return str_stream(mu_fcolor(color, typed.name()) << writeDesc(typed.description().value, descLimit)); \
    }}}

    template <typename Group, typename Instance, typename Map>
    clMisc::Path FileLoader::getPathPortion(
            clMisc::Path::const_iterator &pathIt,
            const clMisc::Path::const_iterator &pathEnd,
            const Map &map)
    {
        clMisc::Path ret;
        auto *curr = &map;
        while (pathIt != pathEnd)
        {
            auto &name = *pathIt++;

            ret += name;
            auto *child = clMisc::checkNotNull(curr->getPtr(name));

            if (auto *typed = child->template toTypePtr<Group>())
            {
                curr = &(typed->elements());
            }
            else if (auto *typed = child->template toTypePtr<Instance>())
            {
                break;
            }
            else abort();
        }

        return ret;
    }

    FileLoader::FileLoader(
            boost::asio::io_service &ioService,
            const ClmPathVec &flowCInstances,
            const ClmPathSet &flowCInstancesDim,
            bool showFunEvents) :
        ioService(ioService),
        actionsCursor(actions.end()),
        undoActive(true),
        showIndent(0),
        flowCInstances(flowCInstances),
        flowCInstancesDim(flowCInstancesDim),
        showFunEvents(showFunEvents),
        colorMap
        {
            def_color(connector::Connector, BLUE),
            def_color(connector::ArgumentMap, DBLUE),
            def_color(connector::EventMap, DBLUE),
            def_color(connector::ActionMap, DBLUE),

            def_color(connector::Argument, DDRED),
            def_color(connector::ArgumentGroup, DDRED),
            def_color(connector::Event, DDRED),
            def_color(connector::EventGroup, DDRED),
            def_color(connector::Action, DDRED),
            def_color(connector::ActionGroup, DDRED),

            def_color(connector::ArgRefMap, DDMAGENTA),
            def_color(connector::ArgRef, DYELLOW),

            def_color(connector::EventRefMap, DDMAGENTA),
            def_color(connector::EventRef, DYELLOW),

            def_color(cPerformer::ConnectionPerformer, BLUE),
            def_color(cPerformer::ArgumentMap, DBLUE),
            def_color(cPerformer::AProviderCreatorMap, DBLUE),
            def_color(cPerformer::ConnectorAliasMap, DBLUE),
            def_color(cPerformer::ConnectorInstanceMap, DBLUE),

            def_color(cPerformer::Argument, DDRED),
            def_color(cPerformer::ArgumentGroup, DDRED),
            def_color(cPerformer::AProviderCreator, DDRED),
            def_color(cPerformer::AProviderCreatorGroup, DDRED),
            def_color(cPerformer::ConnectorAlias, DDRED),
            def_color(cPerformer::ConnectorInstance, DDRED),
            def_color(cPerformer::ConnectorInstanceGroup, DDRED),

            def_color(cPerformer::ArgRefVMap, DDMAGENTA),
            def_color(cPerformer::ArgRefV, DYELLOW),

            def_color(cPerformer::ConnectorRef, DDMAGENTA),
            def_color(cPerformer::CAArgAliasMap, DDMAGENTA),
            def_color(cPerformer::EventAliasMap, DDMAGENTA),
            def_color(cPerformer::ActionAliasMap, DDMAGENTA),

            def_color(cPerformer::CAArgAlias, DYELLOW),

            def_color(cPerformer::EventCall, DDMAGENTA),
            def_color(cPerformer::ConnectorAliasRef, DYELLOW),
            def_color(cPerformer::EventCallMap, DYELLOW),

            def_color(cPerformer::APCRefMap, DDGREEN),
            def_color(cPerformer::ActionInstanceVec, DDGREEN),

            def_color(cPerformer::APCRef, DDBLUE),
            def_color(cPerformer::ActionInstance, DDBLUE)
        },
        valueForMap
        {
            value_for_name_desc(connector::Connector),
            value_for_name_desc(connector::Argument),
            value_for_name_desc(connector::ArgumentGroup),
            value_for_name_desc(connector::Event),
            value_for_name_desc(connector::EventGroup),
            value_for_name_desc(connector::Action),
            value_for_name_desc(connector::ActionGroup),
            value_for_name_desc(cPerformer::ConnectionPerformer),
            value_for_name_desc(cPerformer::Argument),
            value_for_name_desc(cPerformer::ArgumentGroup),
            value_for_name_desc(cPerformer::AProviderCreator),
            value_for_name_desc(cPerformer::AProviderCreatorGroup),
            value_for_name_desc(cPerformer::ConnectorAlias),
            value_for_name_desc(cPerformer::ConnectorInstance),
            value_for_name_desc(cPerformer::ConnectorInstanceGroup),
            value_for_name_desc(cPerformer::EventCall),

            value_for(cPerformer::CAArgAlias)
            {
                return str_stream(mu_fcolor(color, typed.name()) << ": " << typed.cpRef().value.getStringRep(":") << writeDesc(typed.description().value));
            }}},

            value_for(cPerformer::ConnectorAliasRef)
            {
                return str_stream(mu_fcolor(color,  "alias: ") << typed.value);
            }}},

            value_for(cPerformer::ConnectorRef)
            {
                return str_stream(mu_fcolor(color, "connector: ") << typed.value);
            }}},

            value_for(cPerformer::ActionInstance)
            {
                std::stringstream str;

                str << wn_colored(typed, typed.connInstance().value.getStringRep(":")
                    << "." << typed.action().value.getStringRep(":"));

                if (typed.determinesOrder().value)
                    str << mu_fcolor(MU_LGRAY, " (det. order)");

                return str_stream(str.str() << writeDesc(typed.description().value));
            }}}
        }
    {
        connector.bindActions(*this);


        set_map_posibilities_ex(connector::ArgumentMap, connector::Argument,                        WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(connector::ArgumentMap, connector::ArgumentGroup,                   WITH_VAL, true, false, "group");

        set_map_posibilities_ex(connector::EventMap, connector::Event,                              WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(connector::EventMap, connector::EventGroup,                         WITH_VAL, true, false, "group");

        set_map_posibilities_ex(connector::ActionMap, connector::Action,                              WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(connector::ActionMap, connector::ActionGroup,                         WITH_VAL, true, false, "group");

        set_map_posibilities(connector::ArgRef,     Map, WITH_POS, "");
        set_map_posibilities(connector::EventRef,   Map, WITH_POS, "");

        set_map_posibilities(cPerformer::ConnectorAlias,            Map, WITH_VAL, "");
        set_map_posibilities(cPerformer::CAArgAlias,                Map, WITH_POS, "");
        set_map_posibilities(cPerformer::ArgRefV,                   Map, WITH_POS, "");
        set_map_posibilities(cPerformer::EventCall,                 Map, WITH_POS, "");
        set_map_posibilities(cPerformer::APCRef,                    Map, WITH_POS, "");
//        set_vec_posibilities(cPerformer::ActionInstance,            Vec, WITH_POS, false, "");
        addPosibilities.set<cclTree::cPerformer::ActionInstanceVec>("", lib::AddType::WITH_POS,
            [this](chila::lib::node::NodeWithChildren &node, const std::string &value) -> chila::lib::node::Node&
            {
                auto &aIns = node.toType<cclTree::cPerformer::ActionInstanceVec>().add();
                auto path = chila::lib::misc::Path(value, ":");

                auto &cInstance = node.parent<cclTree::cPerformer::EventCall>()
                        .parent<cclTree::cPerformer::EventCallMap>()
                        .parent<cclTree::cPerformer::ConnectorInstance>();

                auto cInstanceGPath = cclTree::getGroupedPath<cclTree::cPerformer::ConnectorInstanceGroup,
                                                              cclTree::cPerformer::ConnectorInstanceMap>(cInstance);

                auto &cInstanceMap = cclTree::getMainParent(cInstance.parent<cclTree::cPerformer::ConnectorInstanceMap>());



                auto pathIt = path.cbegin();
                auto pathPortion = getPathPortion<cclTree::cPerformer::ConnectorInstanceGroup,
                                                  cclTree::cPerformer::ConnectorInstance>(pathIt, path.cend(), cInstanceMap);

                clMisc::Path pathValue;
                auto it0 = cInstanceGPath.begin(), it1 = pathPortion.begin();
                for (; it0 != cInstanceGPath.end() && it1 != pathPortion.end() && *it0 == *it1; ++it0, ++it1);

                for (; it1 != pathPortion.end(); ++it1)
                    pathValue += *it1;

                aIns.connInstance().value = pathValue;


                auto &actionMap = cclTree::getMainParent(
                    aIns.connInstance().referenced().connAlias().referenced().connector().referenced().actions());

                aIns.action().value = getPathPortion<cclTree::connector::ActionGroup,
                                                     cclTree::connector::Action>(pathIt, path.cend(), actionMap);

                return aIns;
            });

        set_map_posibilities_ex(cPerformer::ArgumentMap, cPerformer::Argument,                              WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::ArgumentMap, cPerformer::ArgumentGroup,                         WITH_VAL, true, false, "group");

        set_map_posibilities_ex(cPerformer::EventAliasMap, cPerformer::EventAlias,                          WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::EventAliasMap, cPerformer::EventAliasGroup,                     WITH_VAL, true, false, "group");

        set_map_posibilities_ex(cPerformer::ActionAliasMap, cPerformer::ActionAlias,                        WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::ActionAliasMap, cPerformer::ActionAliasGroup,                   WITH_VAL, true, false, "group");

        set_map_posibilities_ex(cPerformer::AProviderCreatorMap, cPerformer::AProviderCreator,              WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::AProviderCreatorMap, cPerformer::AProviderCreatorGroup,         WITH_VAL, true, false, "group");

        set_map_posibilities_ex(cPerformer::ConnectorInstanceMap, cPerformer::ConnectorInstance,        WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::ConnectorInstanceMap, cPerformer::ConnectorInstanceGroup,   WITH_VAL, true, false, "group");
    }

    std::string FileLoader::getValueFor(const chila::lib::node::Node &node)
    {
        auto it = valueForMap.find(boost::typeindex::type_id_runtime(node));
        if (it == valueForMap.end())
            return str_stream(wn_colored(node, node.name()));
        else
            return it->second(node);
    }

    template <typename Type>
    std::string FileLoader::getValueFor(const Type &node)
    {
        auto it = valueForMap.find(boost::typeindex::type_id<Type>());
        if (it == valueForMap.end())
            return str_stream(wn_colored(node, node.name()));
        else
            return it->second(node);
    }


    std::string makeTitle(std::string name)
    {
        my_assert(name.size());
        auto rng = boost::make_iterator_range(name.begin(), name.begin() + 1);
        boost::to_upper(rng);
        return name;
    }



#define wn_node_found(value) \
    execute_event_tn(nodeFound)(treeNodePath, value);

#define wn_walk_map(Name) \
        if_is_mtl_node(Name##Map) \
        { \
            for (auto &child : *typed) \
                walkNode(treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter); \
        } \

#define wn_walk_ungrouped(Name) \
        wn_walk_map(Name) \

#define wn_walk_grouped(Name) \
        wn_walk_ungrouped(Name) \
        else if_is_mtl_node(Name##Group) \
        { \
            for (auto &child : typed->elements()) \
                walkNode(treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter); \
        } \

    std::string FileLoader::findColor(const boost::typeindex::type_index &index)
    {
        auto it = colorMap.find(index);
        if (it == colorMap.end())
            return MU_BLACK;
        else
            return it->second;
    }

    std::string toGrouped(const std::string &name)
    {
        return clMisc::Path(name).getStringRep(":");
    }

    void FileLoader::TPathMap::insert(const clMisc::Path &nodePath, const clMisc::Path &treePath)
    {
        auto ret = treeNodeMap.insert({treePath, nodePath});
        my_assert(ret.second);

        my_assert(nodeTreeMap.insert({nodePath, ret.first}).second);
    }

    void FileLoader::TPathMap::eraseTreePath(const clMisc::Path &treePath, bool onlyChildren)
    {
        auto it = treeNodeMap.find(treePath);
        my_assert(it != treeNodeMap.end());
        if (onlyChildren)
            ++it;

        auto range = lib::getParentAndChildren(it, treeNodeMap.end(), treePath);

        for (auto &vt : range)
            my_assert(nodeTreeMap.erase(vt.second));

        treeNodeMap.erase(boost::begin(range), boost::end(range));
    }

    const clMisc::Path &FileLoader::TPathMap::getNodePath(const clMisc::Path &treePath) const
    {
        auto it = treeNodeMap.find(treePath);
        my_assert(it != treeNodeMap.end());
        return it->second;
    }


    const clMisc::Path &FileLoader::TPathMap::getTreePath(const clMisc::Path &nodePath) const
    {
        auto it = nodeTreeMap.find(nodePath);
        my_assert(it != nodeTreeMap.end());
        return it->second->first;
    }

    const clMisc::Path &FileLoader::TPathMap::findTreePath(const clMisc::Path &nodePath) const
    {
        static clMisc::Path empty;

        for (auto path = nodePath; !path.empty(); path = path.parent())
        {
            auto it = nodeTreeMap.find(path);
            if (it != nodeTreeMap.end())
                return it->second->first;
        }

        return empty;
    }

    template <typename EventExecuter>
    void FileLoader::walkNode(const clMisc::Path &parentNodePath, const clNode::Node &node, const EventExecuter &eventExecuter)
    {
        auto treeNodePath = parentNodePath;
        if (!node.name().empty())
            treeNodePath += node.name();

        tPathMap.insert(node.path(), treeNodePath);

        if (!treeNodePath.empty())
            wn_node_found(getValueFor(node));

        walkChildrenNodes(treeNodePath, node, eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::walkChildrenNodes(const clMisc::Path &treeNodePath, const clNode::Node &node, const EventExecuter &eventExecuter)
    {
        if_is_mtl_node(Namespace)
        {
            for (auto &child : *typed)
                walkNode(treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter);
        }
        else if_is_mtl_node(connector::Connector)
        {
            walkNode(treeNodePath, typed->arguments(), eventExecuter);
            walkNode(treeNodePath, typed->actions(), eventExecuter);
            walkNode(treeNodePath, typed->events(), eventExecuter);
        }
        else wn_walk_grouped(connector::Argument)
        else wn_walk_grouped(connector::Event)
        else wn_walk_grouped(connector::Action)
        else wn_walk_map(connector::ArgRef)
        else wn_walk_map(connector::EventRef)
        else if_is_mtl_node(cPerformer::ConnectionPerformer)
        {
            walkNode(treeNodePath, typed->arguments(), eventExecuter);
            walkNode(treeNodePath, typed->connectorAliases(), eventExecuter);
            walkNode(treeNodePath, typed->aProvCreators(), eventExecuter);
            walkNode(treeNodePath, typed->connInstances(), eventExecuter);
        }
        else wn_walk_grouped(cPerformer::Argument)
        else wn_walk_grouped(cPerformer::AProviderCreator)
        else wn_walk_map(cPerformer::ArgRefV)
        else wn_walk_ungrouped(cPerformer::ConnectorAlias)
        else wn_walk_grouped(cPerformer::ConnectorInstance)
        else wn_walk_map(cPerformer::CAArgAlias)
        else wn_walk_grouped(cPerformer::ConnectorInstance)
        else wn_walk_map(cPerformer::APCRef)
        else wn_walk_ungrouped(cPerformer::EventCall)
        else if_is_mtl_node(cPerformer::ActionInstanceVec)
        {
            for (auto &child : *typed)
                walkNode(treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter);
        }

        if_is_mtl_node(connector::Action)
        {
            walkNode(treeNodePath, typed->arguments(), eventExecuter);
            walkNode(treeNodePath, typed->events(), eventExecuter);
        }

        if_is_mtl_node(connector::Event)
        {
            walkNode(treeNodePath, typed->arguments(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::AProviderCreator)
        {
            walkNode(treeNodePath, typed->requires(), eventExecuter);
            walkNode(treeNodePath, typed->provides(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::ConnectorAlias)
        {
            walkNode(treeNodePath, typed->connector(), eventExecuter);
            walkNode(treeNodePath, typed->argAliases(), eventExecuter);
            walkNode(treeNodePath, typed->eventAliases(), eventExecuter);
            walkNode(treeNodePath, typed->actionAliases(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::ConnectorInstance)
        {
            walkNode(treeNodePath, typed->connAlias(), eventExecuter);
            walkNode(treeNodePath, typed->events(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::EventCall)
        {
            walkNode(treeNodePath, typed->aProvCreators(), eventExecuter);
            walkNode(treeNodePath, typed->actions(), eventExecuter);
        }
    }

    void FileLoader::MOD_ACTION_SIG(giveActionList)
    {
        lib::ActionMapSPtr actionMap = std::make_shared<lib::ActionMap>();

        auto ctNodePath = tPathMap.getNodePath(nodePath);
        auto &node = globalNsp.find(ctNodePath);

        node_if_dcast(const cclTree::Element, &node)
        {
            actionMap->addAction<lib::actions::SetDescription>().current = typedNode->description().value;
        }

        cast_load_action_np_typed(cclTree::cPerformer::ConnectorRef, SetValueWVal)
        else cast_load_action_wp_typed(cclTree::cPerformer::ConnectorInstanceRef, SetValueWPos)
        else cast_load_action_wp_typed(cclTree::cPerformer::CAArgAlias, SetValueWPos)
        else cast_load_action_wp_typed(cclTree::cPerformer::ConnectorAliasRef, SetValueWPos)
        else cast_load_action_wp_typed(cclTree::cPerformer::ActionRef, SetValueWPos)
        else cast_load_action_wp_typed(chila::lib::node::TypedNode<bool>, SetValueWPos)
        else cast_load_actions_cont_grouped(cclTree::connector::Argument, Map)
        else cast_load_actions_cont_grouped(cclTree::connector::Event, Map)
        else cast_load_actions_cont_grouped(cclTree::connector::Action, Map)
        else cast_load_actions_cont(cclTree::connector::ArgRef, Map)
        else cast_load_actions_cont(cclTree::connector::EventRef, Map)

        else cast_load_actions_cont_grouped(cclTree::cPerformer::Argument, Map)
        else cast_load_actions_cont(cclTree::cPerformer::ConnectorAlias, Map)
        else cast_load_actions_cont(cclTree::cPerformer::CAArgAlias, Map)
        else cast_load_actions_cont(cclTree::cPerformer::ArgRefV, Map)
        else cast_load_actions_cont(cclTree::cPerformer::EventAlias, Map)
        else cast_load_actions_cont(cclTree::cPerformer::ActionAlias, Map)
        else cast_load_actions_cont_grouped(cclTree::cPerformer::AProviderCreator, Map)
        else cast_load_actions_cont(cclTree::cPerformer::EventCall, Map)
        else cast_load_actions_cont(cclTree::cPerformer::APCRef, Map)
        else cast_load_actions_cont_grouped(cclTree::cPerformer::ConnectorInstance, Map)
        else cast_load_actions_cont(cclTree::cPerformer::ActionInstance, Vec)

        node_if_dcast(const cclTree::cPerformer::ActionInstance, &node)
        {
            actionMap->addAction<lib::actions::GoToReferenced>();
        }

        node_if_dcast(const chila::lib::node::IReference, &node)
        {
            actionMap->addAction<lib::actions::GoToReferenced>();
        }


        execute_event(actionListFound)(nodePath, actionMap);
    }

    void FileLoader::MOD_ACTION_SIG(launcher_start)
    {
        execute_event(launcher_started)();
    }

    void FileLoader::MOD_ACTION_SIG(launcher_finish)
    {
        execute_event(launcher_finished)();
    }

    void FileLoader::MOD_ACTION_SIG(loadConnector)
    {
        cclTree::ConnectorCreator creator(globalNsp, filePath);

        connectors.push_back(ConnectorData(filePath, &creator.create()));
    }

    void FileLoader::MOD_ACTION_SIG(loadCPerformer)
    {
        cclTree::CPerformerCreator creator(globalNsp, filePath);

        cpVec.push_back(CPData(filePath, &creator.create()));
    }

    void FileLoader::MOD_ACTION_SIG(refreshTree)
    {
        tPathMap.clear();
        walkNode("", globalNsp, eventExecuter);
        check(eventExecuter);
    }

    template <typename Data>
    void saveObject(Data &data)
    {
        std::ofstream out;

        out.exceptions(std::ios::badbit | std::ios::failbit);
        auto tmpName = data.path.string() + "~";
        out.open(tmpName.c_str());
        auto remover = clMisc::atExit([&] { boost::filesystem::remove(tmpName); });

        cclTree::sendXMLToStream(out, *(data.object));
        data.modified = false;

        boost::filesystem::rename(tmpName, data.path);
        remover.active = false;
    }

    void FileLoader::MOD_ACTION_SIG(save)
    {
        for (auto &cData : connectors) if (cData.modified)
        {
            saveObject(cData);
        }

        for (auto &cpData : cpVec) if (cpData.modified)
        {
            saveObject(cpData);
        }
    }

    void FileLoader::MOD_ACTION_SIG(moveUp)
    {
        moveNode(nodePath, eventExecuter,
            [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)
            {
                return parent.moveUp(name, isVec);
            });
    }

    void FileLoader::MOD_ACTION_SIG(moveDown)
    {
        moveNode(nodePath, eventExecuter,
            [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)
            {
                return parent.moveDown(name, isVec);
            });
    }

    chila::lib::node::Node &FileLoader::addNodeInt(const chila::lib::misc::Path &treePath, const std::string &actionId, const std::string &value)
    {
        auto nodePath = tPathMap.getNodePath(treePath);
        auto *nodePtr = &globalNsp.find(nodePath);

        if (nodePtr->toTypePtr<cclTree::Group>())
        {
            nodePtr = &globalNsp.find(nodePath + "elements");
        }

        auto &node = *nodePtr;

        auto posSize = addPosibilities.size(typeid(node).name());
        if (posSize == 1)
        {
            return addPosibilities.call(node.toType<chila::lib::node::NodeWithChildren>(), "", value);
        }
        else if (posSize > 1)
        {
            return addPosibilities.call(node.toType<chila::lib::node::NodeWithChildren>(), actionId, value);
        }
        else abort();

        return *static_cast<chila::lib::node::Node*>(nullptr);
    }

    template <typename EventExecuter>
    void FileLoader::refreshDesignTreeAndMM(const clMisc::Path &nodePath, const EventExecuter &eventExecuter)
    {
        execute_event_tn(saveDesignTreeState)();

        chila::lib::node::NodeWithChildren *pNode = nullptr;

        for (auto &cData : connectors)
        {
            if (nodePath.startsWith(cData.object->path()))
            {
                cData.modified = true;
                pNode = cData.object;
            }
        }

        for (auto &cpData : cpVec)
        {
            if (nodePath.startsWith(cpData.object->path()))
            {
                cpData.modified = true;
                pNode = cpData.object;
            }
        }

        my_assert(pNode);

        auto pNodePath = pNode->path();

        auto dNodePath = tPathMap.getTreePath(pNodePath);
        execute_event_tn(removeChildren)(dNodePath);

        tPathMap.eraseTreePath(dNodePath, true);

        walkChildrenNodes(dNodePath, *pNode, eventExecuter);

        execute_event_tn(restoreDesignTreeState)();
    }

    void FileLoader::markModified(const clMisc::Path &nodePath)
    {
        for (auto &cData : connectors)
        {
            cData.modified = cData.modified || nodePath.startsWith(cData.object->path());
        }

        for (auto &cpData : cpVec)
        {
            cpData.modified = cpData.modified || nodePath.startsWith(cpData.object->path());
        }
    }

    void FileLoader::addNode(const chila::lib::misc::Path &path, const std::string &actionId, const std::string &value, ev_executer_arg(performAction))
    {
        auto &node = addNodeInt(path, actionId, clMisc::Path(value).getStringRep(":"));

        auto addedNodePath = node.path();;

        refreshDesignTreeAndMM(addedNodePath, eventExecuter);

        execute_event(nodeSelected)(tPathMap.getTreePath(addedNodePath), false);

        check(eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::moveNode(const chila::lib::misc::Path &treeNodePath, const EventExecuter &eventExecuter, const MoveNodeFun &fun)
    {
        auto nodePath = tPathMap.getNodePath(treeNodePath);

        auto &node = globalNsp.find(nodePath);
        auto &parent = node.parent<cclTree::NodeWithChildren>();

        bool isVec = dynamic_cast<const chila::lib::node::NodeVector*>(&parent);
        fun(parent, node.name(), isVec);

        refreshDesignTreeAndMM(nodePath, eventExecuter);
        execute_event_tn(nodeSelected)(treeNodePath, false);

        check(eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::removeChildren(cclTree::NodeWithChildren &parent, const EventExecuter &eventExecuter)
    {
//        auto parentPath = parent.path();
//        tPathMap.erase(parentPath, true);
//
//        execute_event_tn(removeChildren)(parentPath);
    }

    void FileLoader::MOD_ACTION_SIG(performAction)
    {
        ioService.post([=]
        {
            try
            {
                bptr_cast(lib::actions::GoToReferenced, action)
                {
                    auto dNodePath = tPathMap.getNodePath(nodePath);
                    auto &node = globalNsp.find(dNodePath);

                    if (auto *typed = dynamic_cast<const cclTree::cPerformer::ActionInstance*>(&node))
                    {
                        goToReferencedNode(typed->action(), eventExecuter);
                    }
                    else
                    {
                        goToReferencedNode(node, eventExecuter);
                    }
                }
                else bptr_cast(lib::actions::SetDesc, action)
                {
                    auto &dNodePath = tPathMap.getNodePath(nodePath);
                    auto &node = globalNsp.find(dNodePath);

                    setNodeValue(dNodePath + "description", value, eventExecuter);
//                    refreshDesignTreeAndMM(dNodePath, eventExecuter);
                    execute_event(valueFound)(nodePath, getValueFor(node));
                }
                else bptr_cast(lib::actions::SetValue, action)
                {
                    auto &node = globalNsp.find(nodePath);
                    if (auto *typed = dynamic_cast<const cclTree::cPerformer::ConnectorInstanceRef*>(&node))
                    {
                        chila::lib::misc::Path val = value;
                        auto &from = typed->parent<cclTree::cPerformer::ActionInstance>()
                                           .parent<cclTree::cPerformer::ActionInstanceVec>()
                                           .parent<cclTree::cPerformer::EventCall>()
                                           .parent<cclTree::cPerformer::EventCallMap>()
                                           .parent<cclTree::cPerformer::ConnectorInstance>();

                        auto fromPath = cclTree::getFullId(from);
                        my_assert(!fromPath.empty());
                        fromPath.pop();

                        auto value = val.relative(fromPath).getStringRep();
                        setNodeValue(tPathMap.getNodePath(nodePath), value, eventExecuter);
                        execute_event(valueFound)(nodePath, getValueFor(node));
                    }
                    else
                    {
                        setNodeValue(tPathMap.getNodePath(nodePath), value, eventExecuter);
                        execute_event(valueFound)(nodePath, getValueFor(node));
                    }
                }
                else bptr_cast(lib::actions::AddElement, action)
                {
                    addNode(nodePath, action->id, value, eventExecuter);
                }
                else bptr_cast(lib::actions::Remove, action)
                {
                    removeNode(nodePath, eventExecuter);
                }
                else bptr_cast(lib::actions::MoveUp, action)
                {
                    moveNode(nodePath, eventExecuter,
                        [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)
                        {
                            return parent.moveUp(name, isVec);
                        });
                }
                else bptr_cast(lib::actions::MoveDown, action)
                {
                    moveNode(nodePath, eventExecuter,
                        [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)
                        {
                            return parent.moveDown(name, isVec);
                        });
                }
                else bptr_cast(lib::actions::Cut, action)
                {
                    cutPathFrom = nodePath;
                }
                else bptr_cast(lib::actions::Paste, action)
                {
                    my_assert(!cutPathFrom.empty());

                    auto fromParentPath = tPathMap.getNodePath(cutPathFrom);
                    auto name = fromParentPath.pop();
                    auto toNodePath = tPathMap.getNodePath(nodePath);


                    auto &fromParentNode = globalNsp.find(fromParentPath).toType<chila::lib::node::NodeWithChildren>();
                    auto &fromNodeIC = fromParentNode.toType<chila::lib::node::IContainerOfTyped>();
                    auto &toNode = globalNsp.find(toNodePath).toType<chila::lib::node::IContainerOfTyped>();

                    auto &node = toNode.takeChild(fromNodeIC, name);

                    refreshDesignTreeAndMM(fromParentPath, eventExecuter);
                    refreshDesignTreeAndMM(toNodePath, eventExecuter);

                    execute_event(nodeSelected)(nodePath, false);

                    check(eventExecuter);
                }
                else abort();
            }
            catch (const chila::lib::node::Exception &ex)
            {
                execute_event(actionNotPerformed)(ex.what());
            }
            catch (const cclTree::Exception &ex)
            {
                execute_event(actionNotPerformed)(ex.what());
            }
        });
    }

    void FileLoader::renameNode(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction))
    {
    }

    void FileLoader::setNodeValue(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction))
    {
        auto &node = globalNsp.find(nodePath);
        ActionSPtr action;

        node_if_dcast(chila::lib::node::TypedNode<std::string>, &node)
        {
            typedNode->value = value;
        }
        else node_if_dcast(chila::lib::node::TypedNode<bool>, &node)
        {
            typedNode->value = clMisc::textToBool(value);
        }
        else node_if_dcast(cclTree::cPerformer::CAArgAlias, &node)
        {
            typedNode->cpRef().value = clMisc::Path(value);
        }
        else node_if_dcast(cclTree::cPerformer::ActionRef, &node)
        {
            typedNode->value = clMisc::Path(value);
        }
        else node_if_dcast(chila::lib::node::TypedNode<chila::lib::misc::Path>, &node)
        {
            typedNode->value = clMisc::Path(value);
        }
        else abort();

        markModified(node.path());

        check(eventExecuter);
    }

    void FileLoader::removeNode(const chila::lib::misc::Path &treeNodePath, ev_executer_arg(performAction))
    {
        try
        {
            auto nodePath = tPathMap.getNodePath(treeNodePath);

            auto &node = globalNsp.find(nodePath);
            auto &parent = node.parent();
            auto parentPath = nodePath.parent();

            parent.remove(node.name());

            refreshDesignTreeAndMM(parentPath, eventExecuter);
        }
        catch (const chila::lib::node::Exception &ex)
        {
            execute_event(actionNotPerformed)(ex.what());
        }
        catch (const cclTree::Exception &ex)
        {
            execute_event(actionNotPerformed)(ex.what());
        }

        check(eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::check(const EventExecuter &eventExecuter) const try
    {
        execute_event_tn(clearOutput)();
        globalNsp.check();
        execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "no errors found");
    }
    catch (const chila::lib::node::Exception &ex)
    {
        sendErrorEvents(ex, eventExecuter);
    }
    catch (const cclTree::Exception &ex)
    {
        sendErrorEvents(ex, eventExecuter);
    }

    template <typename TProp>
    void addToProps(lib::TextProperties &dest, const TProp &prop)
    {
        dest.push_back(std::make_shared<TProp>(prop));
    }

    template <>
    void addToProps(lib::TextProperties &dest, const lib::TextPropertiesSPtr &props)
    {
        for (auto &prop : *props)
        {
            dest.push_back(prop);
        }
    }

    template <typename TProp, typename ...TProps>
    void addToProps(lib::TextProperties &dest, const TProp &prop, const TProps&... props)
    {
        addToProps(dest, prop);
        addToProps(dest, props...);
    }

    template <typename ...TProps>
    inline lib::TextPropertiesSPtr makeProps(const TProps& ...props)
    {
        auto ret = std::make_shared<lib::TextProperties>();

        addToProps(*ret, props...);

        return ret;
    }

    template <typename EventExecuter>
    void FileLoader::sendErrorEvents(const std::exception &ex, const EventExecuter &eventExecuter) const
    {
        using TPNPath = lib::textProperty::NodePath;
        using TPColor = lib::textProperty::Color;
        using TPUnder = lib::textProperty::Underline;

        auto pathProps1 = makeProps(TPColor(0, 0, 50));
        auto pathProps2 = makeProps(TPColor(0, 0, 0));
        auto errorProps = makeProps(TPColor(100, 0, 0));

        if (const chila::lib::node::CheckExceptionList *celEx = dynamic_cast<const chila::lib::node::CheckExceptionList*>(&ex))
        {
            for (const auto &childEx : celEx->exceptions)
            {
                sendErrorEvents(*childEx, eventExecuter);
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "\n");
            }
        }
        else
        {
            execute_event_tn(outputText)(errorProps, ex.what() + std::string("\n"));

            if (const chila::lib::misc::Path *path = boost::get_error_info<chila::lib::misc::ExceptionInfo::Path>(ex))
            {
                auto treePath = tPathMap.findTreePath(*path);
                auto tPathStr = treePath ? treePath.getStringRep() : path->getStringRep();

                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "- path: ");
                execute_event_tn(outputText)(makeProps(TPNPath(treePath), pathProps1),  tPathStr);
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
            }

            if (const chila::lib::misc::Path *path = boost::get_error_info<cclTree::ErrorInfo::ReferencePath>(ex))
            {
                auto treePath = tPathMap.findTreePath(*path);
                auto tPathStr = treePath ? treePath.getStringRep() : path->getStringRep();

                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "- ref. path: ");
                execute_event_tn(outputText)(makeProps(TPNPath(treePath), pathProps1),  tPathStr);
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
            }

            if (const cclTree::ReqProvVector *vec = boost::get_error_info<cclTree::ErrorInfo::ReqProvVec>(ex))
            {
                for (const auto &reqProv : *vec)
                {
                    auto treePath = tPathMap.findTreePath(reqProv.path);
                    auto tPathStr = treePath ? treePath.getStringRep() : reqProv.path.getStringRep();

                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "- ");
                    execute_event_tn(outputText)(makeProps(TPNPath(treePath), pathProps1),  tPathStr);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n - requires: ");
                    sendArgErrorEvents(reqProv.path, reqProv.requires,                      eventExecuter);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n - provides: ");
                    sendArgErrorEvents(reqProv.path, reqProv.provides,                      eventExecuter);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
                }
            }

            if (const cclTree::AInsVec *data = boost::get_error_info<cclTree::ErrorInfo::AInsVecInfo>(ex))
            {
                for (auto *aIns : *data)
                {
                    auto &aInstance = chila::lib::misc::deref(aIns);
                    auto cInstance = cclTree::getFullId(aInstance.connInstance().referenced()).getStringRep(":");
                    auto actionName = aInstance.action().value;

                    auto aInsPath = aInstance.path();
                    auto treePath = tPathMap.findTreePath(aInsPath);
                    auto tPathStr = treePath ? treePath.getStringRep() : aInsPath.getStringRep();

                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "  - ");
                    execute_event_tn(outputText)(makeProps(TPNPath(treePath), pathProps1),  cInstance + "." + actionName.getStringRep(":"));
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
                }
            }
        }
    }

    template <typename EventExecuter>
    void FileLoader::sendArgErrorEvents(const chila::lib::misc::Path &path, const PathSet &set, const EventExecuter &eventExecuter) const
    {
        bool first = true;
        for (const auto &str : set)
        {
            if (first) first = false;
            else execute_event_tn(outputText)(lib::TextPropertiesSPtr(), ", ");

            execute_event_tn(outputText)(lib::TextPropertiesSPtr(), str.getStringRep(":"));
        }
    }

    void FileLoader::goToReferencedNode(const chila::lib::node::Node &node, ev_executer_arg(performAction)) try
    {
        auto &typed = node.toType<chila::lib::node::IReference>();

        execute_event(nodeSelected)(tPathMap.getTreePath(typed.refPath()), true);
    }
    catch (const cclTree::Exception &ex)
    {
        execute_event(actionNotPerformed)(ex.what());
    }
    catch (const chila::lib::node::Exception &ex)
    {
        execute_event(actionNotPerformed)(ex.what());
    }



    connection::FileLoader::CProviderSPtr connection::FileLoader::create(
        boost::asio::io_service &ioService,
        const ClmPathVec &flowCInstances,
        const ClmPathSet &flowCInstancesDim,
        bool showFunEvents)
    {
        return std::make_shared<app::impl::FileLoader>(
            boost::ref(ioService),
            boost::cref(flowCInstances),
            boost::cref(flowCInstancesDim),
            showFunEvents);
    }

    void FileLoader::addAction(const ActionSPtr &action)
    {
        if (!undoActive) return;
        actions.erase(actionsCursor, actions.end());
        actions.push_back(action);
        actionsCursor = actions.end();
    }

    void FileLoader::MOD_ACTION_SIG(expandFlowNode)
    {
//        fNodesToExpand[nodePath] = treeNodePath;
    }

    cclTree::cPerformer::ConnectorInstance &FileLoader::getCInstance(const clMisc::Path &cInsPath)
    {
        auto subPath = clMisc::Path(cInsPath.top(), ":");
        auto parent = cInsPath;
        parent.pop();

        auto &cPerformer = globalNsp.find(parent).toType<cclTree::cPerformer::ConnectionPerformer>();
        return cclTree::getCInstance(cPerformer, subPath);
    }

    void FileLoader::MOD_ACTION_SIG(requestFlowNodes)
    {
        PathSet walkedNodes;
        fnMap.clear();

        for (const auto &cInsPath : flowCInstances)
        {
            auto &node = getCInstance(cInsPath);
            auto nodePath = node.path();

            chila::lib::misc::Path fnPath = nodePath.getStringRep(":");

            flowNodeFound
            (
                fnPath,
                nodePath,
                str_stream(cInsPath),
                true,
                eventExecuter
            );

            walkFlowNodes(fnPath, node, walkedNodes, getCInstancesHLNodes(flowCInstancesDim), eventExecuter);
        }

        execute_event(noMoreFlowNodes)();
    }

    void FileLoader::walkFlowNodes(const clMisc::Path &flowNodePath,
                                   const cclTree::cPerformer::ConnectorInstance &cInstance,
                                   PathSet &walkedNodes,
                                   const CInstanceSet &flowCInstancesDimNodes,
                                   ev_executer_arg(requestFlowNodes))
    {
        for (auto &eventCall : cInstance.events())
        {
            auto id = eventCall.name();
            auto nodePath = eventCall.path();
            auto fnPath = flowNodePath + id;
            auto inserted = insertWalkedFNode(fnPath, nodePath, walkedNodes);
            auto hasActions = inserted && !eventCall.actions().empty();
            auto insDesc = inserted ? eventCall.description().value : "";

            flowNodeFound
            (
                fnPath,
                eventCall.path(),
                str_stream(mu_fcolor(MU_DRED, "[event]" << " " << id << (inserted ? " " : "... ") << writeDesc(insDesc))),
                hasActions,
                eventExecuter
            );

            if (inserted)
                walkFlowNodes(fnPath, eventCall, walkedNodes, flowCInstancesDimNodes, eventExecuter);
        }
    }

    FileLoader::CInstanceSet FileLoader::getCInstancesHLNodes(const ClmPathSet &paths)
    {
        FileLoader::CInstanceSet ret;

        for (auto &path : paths)
        {
            auto &cInstance = getCInstance(path);
            my_assert(ret.insert(&cInstance).second);
        }

        return ret;
    }

    void FileLoader::walkFlowNodes(const clMisc::Path &flowNodePath,
                                   const cclTree::cPerformer::EventCall &evCall,
                                   PathSet &walkedNodes,
                                   const CInstanceSet &flowCInstancesDimNodes,
                                   ev_executer_arg(requestFlowNodes))
    {
        for (auto &actionIns : evCall.actions())
        {
            auto id = actionIns.connInstance().value.getStringRep(":") + "->" + actionIns.action().value.getStringRep(":");
            auto nodePath = actionIns.path();
            auto fnPath = flowNodePath + id;
            bool hasEvents = !actionIns.action().referenced().events().empty();

            auto insDesc = actionIns.description().value.empty() ?
                actionIns.action().referenced().description().value : actionIns.description().value;
            auto cInsText = actionIns.connInstance().value.getStringRep(":");

            auto dim = flowCInstancesDimNodes.count(&actionIns.connInstance().referenced());

            auto cInsFText = dim ? cInsText : str_stream(mu_bold(cInsText));

            flowNodeFound
            (
                fnPath,
                nodePath,
                str_stream(mu_fcolor(MU_BLUE, "[action] "
                        << cInsFText
                        << "." << actionIns.action().value << " ")
                        << writeDesc(insDesc)),
                hasEvents,
                eventExecuter
            );

            walkFlowNodes(fnPath, actionIns, walkedNodes, flowCInstancesDimNodes, eventExecuter);
        }
    }

    bool FileLoader::insertWalkedFNode(const clMisc::Path &flowNodePath, const clMisc::Path &nodePath, PathSet &walkedNodes)
    {
        auto it = fNodesToExpand.find(nodePath);

        return (it == fNodesToExpand.end() || it->second == flowNodePath) && walkedNodes.insert(nodePath).second;
    }

    void FileLoader::walkFlowNodes(const clMisc::Path &flowNodePath,
                                   const cclTree::cPerformer::ActionInstance &aInstance,
                                   PathSet &walkedNodes,
                                   const CInstanceSet &flowCInstancesDimNodes,
                                   ev_executer_arg(requestFlowNodes))
    {
        using EvRefMap = std::map<std::string, const cclTree::connector::EventRef*>;
        EvRefMap evRefMap;

        for (auto &evRef : aInstance.action().referenced().events())
        {
            my_assert(evRefMap.insert({evRef.name(), &evRef}).second);
        }

        for (auto &evCall : aInstance.connInstance().referenced().events())
        {
            auto it = evRefMap.find(evCall.name());

            if (it != evRefMap.end())
            {
                auto &connEv = it->second->referenced();

                auto id = evCall.name();
                auto fnPath = flowNodePath + id;
                auto nodePath = evCall.path();
                auto inserted = insertWalkedFNode(fnPath, nodePath, walkedNodes);
                auto hasActions = inserted && !evCall.actions().empty();
                auto insDesc = inserted ? (evCall.description().value.empty() ? connEv.description().value : evCall.description().value) : "";

                flowNodeFound
                (
                    fnPath,
                    nodePath,
                    str_stream(mu_fcolor(MU_DRED, "[event]" << " " << id << (inserted ? " " : "... ")) << writeDesc(insDesc)),
                    hasActions,
                    eventExecuter
                );

                evRefMap.erase(it);

                if (inserted)
                    walkFlowNodes(fnPath, evCall, walkedNodes, flowCInstancesDimNodes, eventExecuter);
            }
        }

        for (auto &vt : evRefMap)
        {
            auto &event = *vt.second;
            auto id = event.name();
            auto fnPath = flowNodePath + id;

            flowNodeFound
            (
                fnPath,
                event.path(),
                str_stream(mu_fcolor(MU_LRED, "[event]" << " " << id)),
                false,
                eventExecuter
            );
        }
    }

    void FileLoader::flowNodeFound(const clMisc::Path &flowNodePath,
                                   const clMisc::Path &nodePath,
                                   const std::string &value,
                                   bool isExpandable,
                                   ev_executer_arg(requestFlowNodes))
    {
        fnMap[flowNodePath] = nodePath;

        execute_event(flowNodeFound)
        (
            flowNodePath,
            value,
            isExpandable
        );
    }


    void FileLoader::MOD_ACTION_SIG(showFNodeInfo)
    {
        using TPColor = lib::textProperty::Color;
        using TPBold = lib::textProperty::Bold;
        using TPNPath = lib::textProperty::NodePath;

        auto it = fnMap.find(nodePath);
        assert(it != fnMap.end());
        auto ctNodePath = it->second;

        const auto &node = globalNsp.find(ctNodePath);

        auto titleProps =  makeProps(TPBold());
        auto descProps = lib::TextPropertiesSPtr();
        auto noDescProps = makeProps(TPColor(70, 70, 70));

        auto showTitle = [&](const clMisc::Path &path, const std::string &title)
        {
            execute_event(outputText)(descProps, "- ");
            execute_event(outputText)(makeProps(titleProps, TPNPath(path)), title);
        };

        auto showArgs = [&](const chila::lib::node::NodeWithChildren &args)
        {
            execute_event(outputText)(descProps, "(");
            bool first = true;
            for (auto &arg : args)
            {
                if (first) first = false;
                else execute_event(outputText)(descProps, ", ");

                execute_event(outputText)(makeProps(TPNPath(arg.path())), arg.name());
            }
            execute_event(outputText)(descProps, ")");
        };

        auto showAliasedArgs = [&](const cclTree::cPerformer::ConnectorInstance &cIns, const cclTree::connector::ArgRefMap &args)
        {
            auto &cAlias = cIns.connAlias().referenced();

            execute_event(outputText)(descProps, "(");
            bool first = true;
            for (auto &arg : args)
            {
                if (first) first = false;
                else execute_event(outputText)(descProps, ", ");

                auto &argRef = cAlias.argAliases().get(arg.name()).cpRef();
                execute_event(outputText)(makeProps(TPNPath(argRef.refPath())), argRef.value.getStringRep(":"));
            }
            execute_event(outputText)(descProps, ")");
        };

        auto showDesc = [&](const std::string &desc)
        {
            execute_event(outputText)(titleProps, ": ");

            if (desc.empty())
                execute_event(outputText)(noDescProps, "(no description)\n\n");
            else
            {
                if (desc.size() > 100)
                    execute_event(outputText)(descProps, "\n");

                execute_event(outputText)(descProps, desc + ".\n\n");
            }
        };

        execute_event(clearOutput)();
        if (auto *typed = dynamic_cast<const cclTree::cPerformer::ConnectorInstance*>(&node))
        {
            auto &cAlias = typed->connAlias().referenced();
            auto &connector = cAlias.connector().referenced();

            auto &connDesc = connector.description().value;
            auto &connAliasDesc = cAlias.description().value;
            auto connPathTitle = connector.path().getStringRep();


            showTitle(typed->path(),     typed->name()); showDesc(typed->description().value);
            showTitle(cAlias.path(),     cAlias.name()); showDesc(connAliasDesc);
            showTitle(connector.path(),  connPathTitle); showDesc(connDesc);
        }
        else if (auto *typed = dynamic_cast<const cclTree::connector::EventRef*>(&node))
        {
            auto &connector = typed->parent<cclTree::connector::EventRefMap>()
                                    .parent<cclTree::connector::Action>()
                                    .parent<cclTree::connector::ActionMap>()
                                    .parent<cclTree::connector::Connector>();

            auto connEvTitle = connector.path().getStringRep() + "." + typed->name();

            showTitle(typed->refPath(), connEvTitle);
            showArgs(typed->referenced().arguments());
            showDesc(typed->referenced().description().value);
        }
        else if (auto *typed = dynamic_cast<const cclTree::cPerformer::EventCall*>(&node))
        {
            auto &cInstance = typed->parent<cclTree::cPerformer::EventCallMap>()
                                    .parent<cclTree::cPerformer::ConnectorInstance>();

            auto &event = typed->referenced();

            auto evCallTitle = cInstance.name() + "." + typed->name();
            auto connEvTitle = cInstance.connAlias().value + "." + typed->name();

            showTitle(typed->path(),   evCallTitle);  showAliasedArgs(cInstance, event.arguments()); showDesc(typed->description().value);
            showTitle(typed->refPath(), connEvTitle); showArgs(event.arguments());                   showDesc(typed->referenced().description().value);

            for (auto &apc : typed->aProvCreators())
            {
                showTitle(apc.path(), apc.name());
                showArgs(apc.referenced().requires());
                execute_event(outputText)(descProps, " -> ");
                showArgs(apc.referenced().provides());
                showDesc(apc.referenced().description().value);
            }
        }
        else if (auto *typed = dynamic_cast<const cclTree::cPerformer::ActionInstance*>(&node))
        {
            auto &cInstance = typed->connInstance().referenced();
            auto &cAlias = cInstance.connAlias().referenced();
            auto &connector = cAlias.connector().referenced();

            auto &connAction = typed->action().referenced();

            auto &connDesc = connector.description().value;
            auto &connAliasDesc = cAlias.description().value;
            auto &connActionDesc = connAction.description().value;
            auto &acInsDesc = typed->description().value;
            auto &connInsDesc = cInstance.description().value;

            auto aInsTitle = cInstance.name() + "." + typed->action().value.getStringRep(":");
            auto connAcTitle = cAlias.name() + "." + typed->action().value.getStringRep(":");
            auto connPathTitle = connector.path().getStringRep();
            auto connInsTitle = cInstance.name();

            showTitle(typed->path(),     aInsTitle);     showAliasedArgs(cInstance, connAction.arguments()); showDesc(acInsDesc);
            showTitle(cInstance.path(),  connInsTitle);                                                      showDesc(connInsDesc);
            showTitle(connAction.path(), connAcTitle);   showArgs(connAction.arguments());                   showDesc(connActionDesc);
            showTitle(cAlias.path(),     cAlias.name());                                                     showDesc(connAliasDesc);
            showTitle(connector.path(),  connPathTitle);                                                     showDesc(connDesc);
        }
    }


#define if_cast_action(Type) \
        if (std::shared_ptr<Type> action = std::dynamic_pointer_cast<Type>(*actionsCursor))

    void FileLoader::MOD_ACTION_SIG(undo)
    {
    }

    void FileLoader::MOD_ACTION_SIG(redo)
    {
    }


}
MY_NSP_END

