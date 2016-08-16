/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FileLoader.hpp"
#include <boost/range/adaptor/reversed.hpp>
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
#include <boost/exception/detail/exception_ptr.hpp>
#include <boost/exception/get_error_info.hpp>
#include "../../lib/actions.hpp"
#include "../../lib/ActionMap.hpp"
#include "../../lib/TextProperty.hpp"
#include <chila/connectionTools/lib/tree/ParseText.hpp>
#include <chila/connectionTools/lib/tree/util.hpp>
#include <boost/range/algorithm/transform.hpp>

#define MODULE_NAME FileLoader

#define go_to_ref_wpos_map_entry_elem(r, Type, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    {BOOST_PP_SEQ_ELEM(0, elem), [this](const clNode::Node &node, const ev_executer_type(performAction) &eventExecuter) \
    { \
        auto &typed = clMisc::dynamicCast<const Type&>(node); \
        goToReferencedNode(BOOST_PP_SEQ_ELEM(1, elem), eventExecuter); \
    }}



#define go_to_ref_wpos_map_entry(Type, elems) \
    {boost::typeindex::type_id<Type>(), \
    GoToRefWPosValMap \
    { \
        BOOST_PP_SEQ_FOR_EACH_I(go_to_ref_wpos_map_entry_elem, Type, elems) \
    }}

#define add_rename_action(Type) \
        if (auto *typedNode = clMisc::dcast<Type>(&node)) \
        { \
            actionMap->addAction<lib::actions::Rename>().current = node.name(); \
        }

#define add_rename_action_wg(Type) \
        if (auto *typedNode = clMisc::dcast<Type##Group>(&node)) \
        { \
            actionMap->addAction<lib::actions::Rename>().current = node.name(); \
        } \
        else if (auto *typedNode = clMisc::dcast<Type>(&node)) \
        { \
            actionMap->addAction<lib::actions::Rename>().current = node.name(); \
        }

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
                auto size = insDesc.find('\n');
                if (size == std::string::npos)
                    size = insDesc.size();

                out << mu_italic(mu_fcolor(MU_DGREEN, " - " << (limit == clMisc::MAX_UINT || limit >= size ? insDesc.substr(0, size) :
                                                                insDesc.substr(0, limit) + "...")));
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

            auto &fromNode = globalNsp().find(parent).toType<chila::lib::node::IContainerOfTyped>();
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

            if (globalNsp().find(parent).toTypePtr<NodeMap>())
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
    clMisc::Path::const_iterator getPathPortion(
            clMisc::Path::const_iterator pathIt,
            clMisc::Path::const_iterator pathEnd,
            const Map &map)
    {
        auto *curr = &map;
        while (pathIt != pathEnd)
        {
            auto &name = *pathIt++;

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

        return pathIt;
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
        globalNsps({cclTree::Namespace::create("")}),
        currNsp(globalNsps.begin()),
        savedNsp(currNsp),
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

            def_color(cPerformer::ArgVRefMap, DDMAGENTA),
            def_color(cPerformer::ArgVRef, DYELLOW),

            def_color(cPerformer::ConnectorRef, DDMAGENTA),
            def_color(cPerformer::CAArgAliasMap, DDMAGENTA),
            def_color(cPerformer::EventAliasMap, DDMAGENTA),
            def_color(cPerformer::ActionAliasMap, DDMAGENTA),

            def_color(cPerformer::CAArgAlias, DYELLOW),
            def_color(cPerformer::EventAlias, DYELLOW),
            def_color(cPerformer::ActionAlias, DYELLOW),

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

            value_for(cPerformer::EventAlias)
            {
                return str_stream(mu_fcolor(color, typed.name()) << writeDesc(typed.description().value));
            }}},

            value_for(cPerformer::ActionAlias)
            {
                return str_stream(mu_fcolor(color, typed.name()) << writeDesc(typed.description().value));
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
        },
        goToRefWPosMap
        {
            {
                go_to_ref_wpos_map_entry(cclTree::cPerformer::ActionInstance,
                    (("connInstance")(typed.connInstance()))
                    (("connAlias")(typed.connInstance().referenced().connAlias()))
                    (("connector")(typed.connInstance().referenced().connAlias().referenced().connector()))
                    (("action")(typed.action()))
                ),
                go_to_ref_wpos_map_entry(cclTree::cPerformer::CAArgAlias,
                    (("connArg")(typed))
                    (("cpArg")(typed.cpRef()))
                )
            }
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
        set_map_posibilities(cPerformer::EventAlias,                Map, WITH_POS, "");
        set_map_posibilities(cPerformer::ActionAlias,               Map, WITH_POS, "");
        set_map_posibilities(cPerformer::ArgVRef,                   Map, WITH_POS, "");
        set_map_posibilities(cPerformer::EventCall,                 Map, WITH_POS, "");
        set_map_posibilities(cPerformer::APCRef,                    Map, WITH_POS, "");
        addPosibilities.set<cclTree::cPerformer::ActionInstanceVec>("", lib::AddType::WITH_POS,
            [this](chila::lib::node::NodeWithChildren &node, const std::string &value) -> chila::lib::node::Node&
            {
                auto &aIns = node.toType<cclTree::cPerformer::ActionInstanceVec>().add();
                auto path = chila::lib::misc::Path(value, ":");

                auto &cInstance = node.parent<cclTree::cPerformer::EventCall>()
                        .parent<cclTree::cPerformer::EventCallMap>()
                        .parent<cclTree::cPerformer::ConnectorInstance>();

                auto &cInstanceMap = cclTree::getMainParent(cInstance.parent<cclTree::cPerformer::ConnectorInstanceMap>());


                auto pathPortionEnd = getPathPortion<cclTree::cPerformer::ConnectorInstanceGroup,
                                                  cclTree::cPerformer::ConnectorInstance>(path.cbegin(), path.cend(), cInstanceMap);

                aIns.connInstance().value = clMisc::Path(path.cbegin(), pathPortionEnd);
                aIns.action().value = clMisc::Path(pathPortionEnd, path.end());

                return aIns;
            });

        set_map_posibilities_ex(cPerformer::ArgumentMap, cPerformer::Argument,                              WITH_VAL, true, false, "instance");
        set_map_posibilities_ex(cPerformer::ArgumentMap, cPerformer::ArgumentGroup,                         WITH_VAL, true, false, "group");

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
                walkNode(prefix, treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter); \
        } \

#define wn_walk_ungrouped(Name) \
        wn_walk_map(Name) \

#define wn_walk_grouped(Name) \
        wn_walk_ungrouped(Name) \
        else if_is_mtl_node(Name##Group) \
        { \
            for (auto &child : typed->elements()) \
                walkNode(prefix, treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter); \
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

    std::pair<clMisc::Path, clMisc::Path> FileLoader::TPathMap::getExistingParentTreePath(const clMisc::Path &nodePath) const
    {
        auto np = nodePath;

        while (true)
        {
            auto it = nodeTreeMap.find(np);
            if (it != nodeTreeMap.end())
                return { it->second->first, np };

            np.pop();
        }

        BOOST_THROW_EXCEPTION(clMisc::ElementNotFound());
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
    void FileLoader::walkNode(const std::string &prefix, const clMisc::Path &parentNodePath, const clNode::Node &node, const EventExecuter &eventExecuter)
    {
        auto treeNodePath = parentNodePath;
        std::string newPrefix;
        auto *nsp = clMisc::dcast<cclTree::Namespace>(&node);

        if (nsp && nsp->size() == 1 && clMisc::dcast<cclTree::Namespace>(&nsp->front()))
        {
            std::string pTop;
            if (!parentNodePath.empty())
            {
                pTop = parentNodePath.top();
            }

            newPrefix = prefix + (prefix.empty() || node.name().empty() ? "" : ":") + node.name();
        }
        else
        {
            if (nsp)
            {
                if (!node.name().empty())
                    treeNodePath += (prefix + ":" + node.name());
            }
            else
            {
                treeNodePath += node.name();
            }

            tPathMap.insert(node.path(), treeNodePath);

            if (!treeNodePath.empty())
            {
                if (nsp)
                {
                    wn_node_found(clMisc::Path(prefix, ":").getStringRep(".") + "." + node.name());
                }
                else
                {
                    wn_node_found(getValueFor(node));
                }
            }
        }

        walkChildrenNodes(newPrefix, treeNodePath, node, eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::walkChildrenNodes(const std::string &prefix, const clMisc::Path &treeNodePath, const clNode::Node &node, const EventExecuter &eventExecuter)
    {
        if_is_mtl_node(Namespace)
        {
            for (auto &child : *typed)
                walkNode(prefix, treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter);
        }
        else if_is_mtl_node(connector::Connector)
        {
            walkNode(prefix, treeNodePath, typed->arguments(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->actions(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->events(), eventExecuter);
        }
        else wn_walk_grouped(connector::Argument)
        else wn_walk_grouped(connector::Event)
        else wn_walk_grouped(connector::Action)
        else wn_walk_map(connector::ArgRef)
        else wn_walk_map(connector::EventRef)
        else if_is_mtl_node(cPerformer::ConnectionPerformer)
        {
            walkNode(prefix, treeNodePath, typed->arguments(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->connectorAliases(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->aProvCreators(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->connInstances(), eventExecuter);
        }
        else wn_walk_grouped(cPerformer::Argument)
        else wn_walk_grouped(cPerformer::AProviderCreator)
        else wn_walk_map(cPerformer::ArgVRef)
        else wn_walk_ungrouped(cPerformer::ConnectorAlias)
        else wn_walk_grouped(cPerformer::ConnectorInstance)
        else wn_walk_map(cPerformer::CAArgAlias)
        else wn_walk_map(cPerformer::EventAlias)
        else wn_walk_map(cPerformer::ActionAlias)
        else wn_walk_grouped(cPerformer::ConnectorInstance)
        else wn_walk_map(cPerformer::APCRef)
        else wn_walk_ungrouped(cPerformer::EventCall)
        else if_is_mtl_node(cPerformer::ActionInstanceVec)
        {
            for (auto &child : *typed)
                walkNode(prefix, treeNodePath, clMisc::dynamicCast<clNode::Node>(child), eventExecuter);
        }

        if_is_mtl_node(connector::Action)
        {
            walkNode(prefix, treeNodePath, typed->arguments(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->events(), eventExecuter);
        }

        if_is_mtl_node(connector::Event)
        {
            walkNode(prefix, treeNodePath, typed->arguments(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::AProviderCreator)
        {
            walkNode(prefix, treeNodePath, typed->requires(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->provides(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::ConnectorAlias)
        {
            walkNode(prefix, treeNodePath, typed->connector(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->arguments(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->events(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->actions(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::ConnectorInstance)
        {
            walkNode(prefix, treeNodePath, typed->connAlias(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->events(), eventExecuter);
        }

        if_is_mtl_node(cPerformer::EventCall)
        {
            walkNode(prefix, treeNodePath, typed->aProvCreators(), eventExecuter);
            walkNode(prefix, treeNodePath, typed->actions(), eventExecuter);
        }
    }

    void FileLoader::MOD_ACTION_SIG(giveActionList)
    {
        lib::ActionMapSPtr actionMap = std::make_shared<lib::ActionMap>();

        auto ctNodePath = tPathMap.getNodePath(nodePath);
        auto &node = globalNsp().find(ctNodePath);

        node_if_dcast(const cclTree::Element, &node)
        {
            actionMap->addAction<lib::actions::SetDescription>().current = typedNode->description().value;
        }

        if (auto *typedNode = dynamic_cast< const cclTree :: cPerformer :: ConnectorRef *>( & node )) {
            actionMap->addAction<lib::actions:: SetValueWVal >().current = typedNode->value.getStringRep();
        }

        add_rename_action_wg(cclTree::connector::Argument)
        else add_rename_action_wg(cclTree::connector::Event)
        else add_rename_action_wg(cclTree::connector::Action)
        else add_rename_action_wg(cclTree::cPerformer::Argument)
        else add_rename_action(cclTree::cPerformer::ConnectorAlias)
        else add_rename_action(cclTree::cPerformer::CAArgAlias)
        else add_rename_action(cclTree::cPerformer::EventAlias)
        else add_rename_action(cclTree::cPerformer::ActionAlias)
        else add_rename_action_wg(cclTree::cPerformer::AProviderCreator)
        else add_rename_action_wg(cclTree::cPerformer::ConnectorInstance)

        cast_load_action_wp_typed(cclTree::cPerformer::ConnectorInstanceRef, SetValueWPos)
        cast_load_action_wp_typed(cclTree::cPerformer::CAArgAlias, SetValueWPos)
        cast_load_action_wp_typed(cclTree::cPerformer::ConnectorAliasRef, SetValueWPos)
        cast_load_action_wp_typed(cclTree::cPerformer::ActionRef, SetValueWPos)
        cast_load_action_wp_typed(chila::lib::node::TypedNode<bool>, SetValueWPos)
        cast_load_actions_cont_grouped(cclTree::connector::Argument, Map)
        cast_load_actions_cont_grouped(cclTree::connector::Event, Map)
        cast_load_actions_cont_grouped(cclTree::connector::Action, Map)
        cast_load_actions_cont(cclTree::connector::ArgRef, Map)
        cast_load_actions_cont(cclTree::connector::EventRef, Map)

        cast_load_actions_cont_grouped(cclTree::cPerformer::Argument, Map)
        cast_load_actions_cont(cclTree::cPerformer::ConnectorAlias, Map)
        cast_load_actions_cont(cclTree::cPerformer::CAArgAlias, Map)
        cast_load_actions_cont(cclTree::cPerformer::EventAlias, Map)
        cast_load_actions_cont(cclTree::cPerformer::ActionAlias, Map)
        cast_load_actions_cont(cclTree::cPerformer::ArgVRef, Map)
        cast_load_actions_cont_grouped(cclTree::cPerformer::AProviderCreator, Map)
        cast_load_actions_cont(cclTree::cPerformer::EventCall, Map)
        cast_load_actions_cont(cclTree::cPerformer::APCRef, Map)
        cast_load_actions_cont_grouped(cclTree::cPerformer::ConnectorInstance, Map)
        cast_load_actions_cont(cclTree::cPerformer::ActionInstance, Vec)


        auto typeIndex = boost::typeindex::type_id_runtime(node);
        auto mapIt = goToRefWPosMap.find(typeIndex);
        if (mapIt != goToRefWPosMap.end())
        {
            auto &vVec = actionMap->addAction<lib::actions::GoToReferencedWPos>().posibilities;
            auto &map = mapIt->second;

            boost::transform(map, std::back_inserter(vVec),
                [&](const GoToRefWPosValMap::value_type &vt)
                {
                    return cclTree::ValueEntry{vt.first};
                });
        }
        else node_if_dcast(const chila::lib::node::IReference, &node)
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

    bool FileLoader::checkRecovery(const boost::filesystem::path &path)
    {
        auto rPath = getRecoveryPath(path);
        if (boost::filesystem::exists(rPath))
        {
            if (clMisc::filesAreEqual(path, rPath))
            {
                boost::filesystem::remove(rPath);
            }
            else return true;
        }

        return false;
    }


    template <typename Type>
    void FileLoader::loadObject(const boost::filesystem::path &filePath, bool isRecovery)
    {
        auto recPath = getRecoveryPath(filePath);
        auto hasRec = isRecovery && boost::filesystem::exists(recPath);

        Type creator(globalNsp(), hasRec ? recPath : filePath);

        if (hasRec)
            recoveredFiles.push_back(filePath);

        fileDataVec.push_back(FileData{filePath, creator.create().path()});
    }

    bool FileLoader::checkRecFiles(const PathSet &files)
    {
        auto ret = false;
        for (auto &path : files)
        {
            if (checkRecovery(path))
                ret = true;
        }

        return ret;
    }

    void FileLoader::loadFilesPrv(const PathSet &cpFiles, const PathSet &connFiles, bool isRecovery)
    {
        for (auto &filePath : connFiles)
        {
            loadObject<cclTree::ConnectorCreator>(filePath, isRecovery);
        }

        for (auto &filePath : cpFiles)
        {
            loadObject<cclTree::CPerformerCreator>(filePath, isRecovery);
        }
    }

    void FileLoader::MOD_ACTION_SIG(loadFiles)
    {
        PathSet cpRFiles, connRFiles;
        auto ret0 = checkRecFiles(filesData.first);
        auto ret1 = checkRecFiles(filesData.second);

        loadFilesPrv(filesData.first, filesData.second, false);

        if (ret0 || ret1)
        {
            pushGlobalNsp(std::make_shared<cclTree::Namespace>());

            loadFilesPrv(filesData.first, filesData.second, true);

            globalNsp().takeSimilar(*globalNsps[0]);
        }
    }

    void FileLoader::MOD_ACTION_SIG(refreshTree)
    {
        refresh(eventExecuter);
    }

    void FileLoader::saveObject(const FileData &data, bool isRecovery)
    {
        std::ofstream out;

        out.exceptions(std::ios::badbit | std::ios::failbit);
        auto tmpName = isRecovery ? getRecoveryPath(data.filePath) : getTemporalPath(data.filePath);
        out.open(tmpName.c_str());
        auto remover = clMisc::atExit([&] { boost::filesystem::remove(tmpName); });

        auto &node = globalNsp().find(data.path);

        if (auto *typed = node.template toTypePtr<cclTree::cPerformer::ConnectionPerformer>())
            cclTree::sendXMLToStream(out, *typed);
        else if (auto *typed = node.template toTypePtr<cclTree::connector::Connector>())
            cclTree::sendXMLToStream(out, *typed);
        else
            abort();

        if (!isRecovery)
        {
            boost::filesystem::rename(tmpName, data.filePath);
        }

        remover.active = false;
    }

    void FileLoader::saveFiles(bool isRecovery)
    {
        for (auto &vt : modFiles)
        {
            saveObject(vt.second, isRecovery);
        }

        if (!isRecovery)
        {
            savedNsp = currNsp;
            updateModFiles();
        }

        cleanTmpFiles();
    }

    void FileLoader::cleanTmpFiles()
    {
        for (auto &fileData : fileDataVec)
        {
            auto recoveryPath = getRecoveryPath(fileData.filePath);
            if (modFiles.count(fileData.filePath) == 0 && boost::filesystem::exists(recoveryPath))
            {
                boost::filesystem::remove(recoveryPath);
            }
        }
    }

    void FileLoader::MOD_ACTION_SIG(save)
    {
        recoveredFiles.clear();
        saveFiles(false);
        check(eventExecuter);
    }

    void FileLoader::MOD_ACTION_SIG(moveUp)
    {
        moveNode(nodePath, eventExecuter,
            [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec) -> clNode::Node&
            {
                return parent.moveUp(name, isVec);
            });

        updateModFiles();
        saveFiles(true);
    }

    void FileLoader::MOD_ACTION_SIG(moveDown)
    {
        moveNode(nodePath, eventExecuter,
            [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec) -> clNode::Node&
            {
                return parent.moveDown(name, isVec);
            });

        updateModFiles();
        saveFiles(true);
    }

    chila::lib::node::Node &FileLoader::addNodeInt(const chila::lib::misc::Path &treePath, const std::string &actionId, const std::string &value)
    {
        auto nodePath = tPathMap.getNodePath(treePath);

        if (globalNsp().find(nodePath).toTypePtr<cclTree::Group>())
            nodePath.add("elements");

        auto &node = editNode(nodePath);

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

    void FileLoader::addNode(const chila::lib::misc::Path &path, const std::string &actionId, const std::string &value, ev_executer_arg(performAction))
    {
        auto &node = addNodeInt(path, actionId, clMisc::Path(value).getStringRep(":"));

        auto addedNodePath = node.path();;

        refresh(eventExecuter);

        execute_event(nodeSelected)(tPathMap.getTreePath(addedNodePath), false);

        check(eventExecuter);
        updateModFiles();
    }

    template <typename EventExecuter>
    void FileLoader::moveNode(const chila::lib::misc::Path &treeNodePath, const EventExecuter &eventExecuter, const MoveNodeFun &fun)
    {
        auto nodePath = tPathMap.getNodePath(treeNodePath);

        auto name = nodePath.top();
        auto parentPath = nodePath.parent();
        auto &parent = editNode(parentPath).toType<cclTree::NodeWithChildren>();
        auto &node = parent.child(name);

        bool isVec = dynamic_cast<const chila::lib::node::NodeVector*>(&parent);
        fun(parent, name, isVec);

        auto newTNPath = tPathMap.getTreePath(node.path());

        refresh(eventExecuter);
        execute_event_tn(nodeSelected)(newTNPath, false);

        check(eventExecuter);

        updateModFiles();
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
                bptr_cast(lib::actions::GoToReferencedWPos, action)
                {
                    auto dNodePath = tPathMap.getNodePath(nodePath);
                    auto &node = globalNsp().find(dNodePath);

                    auto typeIndex = boost::typeindex::type_id_runtime(node);
                    auto mapIt = goToRefWPosMap.find(typeIndex);
                    my_assert(mapIt != goToRefWPosMap.end());

                    const auto &goToRefWPosValMap = mapIt->second;

                    auto mapIt2 = goToRefWPosValMap.find(value);
                    my_assert(mapIt2 != goToRefWPosValMap.end());

                    mapIt2->second(node, eventExecuter);
                }
                else bptr_cast(lib::actions::GoToReferenced, action)
                {
                    auto dNodePath = tPathMap.getNodePath(nodePath);
                    auto &node = globalNsp().find(dNodePath);
                    goToReferencedNode(node, eventExecuter);
                }
                else bptr_cast(lib::actions::SetDesc, action)
                {
                    auto &dNodePath = tPathMap.getNodePath(nodePath);

                    setNodeValue(dNodePath + "description", value, eventExecuter);
                    auto &node = globalNsp().find(dNodePath);

                    execute_event(valueFound)(nodePath, getValueFor(node));
                }
                else bptr_cast(lib::actions::SetValue, action)
                {
                    auto ctNodePath = tPathMap.getNodePath(nodePath);
                    setNodeValue(ctNodePath, value, eventExecuter);
                    auto &node = globalNsp().find(ctNodePath);

                    execute_event(valueFound)(nodePath, getValueFor(node));
                }
                else bptr_cast(lib::actions::Rename, action)
                {
                    auto ctNodePath = tPathMap.getNodePath(nodePath);

                    auto toRep = clNode::getReferences(globalNsp(), ctNodePath);

                    auto toClone = toRep;
                    toClone.push_back(ctNodePath);

                    cloneNodes(toClone);

                    auto &node = globalNsp().find(ctNodePath);
                    auto &parent = node.parent<clNode::NodeMap>();

                    auto &newNode = parent.renameChild(node.name(), value);

                    replaceReferences(globalNsp(), toRep, newNode);
                    globalNsp().updateParents();

                    updateModFiles();
                    refresh(eventExecuter);
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
                        [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec) -> clNode::Node&
                        {
                            return parent.moveUp(name, isVec);
                        });
                }
                else bptr_cast(lib::actions::MoveDown, action)
                {
                    moveNode(nodePath, eventExecuter,
                        [&](chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec) -> clNode::Node&
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

                    auto fromNodePath = tPathMap.getNodePath(cutPathFrom);
                    auto fromParentPath = fromNodePath;
                    auto name = fromParentPath.pop();
                    auto toNodePath = tPathMap.getNodePath(nodePath);

                    auto tnPathClone = toNodePath;
                    tnPathClone.add(globalNsp().find(toNodePath).toTypePtr<cclTree::Group>() ? "elements" : "");

                    auto toRep = clNode::getReferences(globalNsp(), fromNodePath);

                    auto toClone = ClmPathVec({fromNodePath, tnPathClone});

                    toClone.insert(toClone.end(), toRep.begin(), toRep.end());

                    cloneNodes(toClone);

                    auto &fromParentNode = globalNsp().find(fromParentPath).toType<chila::lib::node::NodeWithChildren>();
                    auto &fromNodeIC = fromParentNode.toType<chila::lib::node::IContainerOfTyped>();
                    auto &toNode = globalNsp().find(toNodePath).toType<chila::lib::node::IContainerOfTyped>();

                    auto &node = toNode.takeChild(fromNodeIC, name);

                    replaceReferences(globalNsp(), toRep, node);

                    globalNsp().updateParents();

                    refresh(eventExecuter);

                    cutPathFrom.clear();

                    execute_event(nodeSelected)(nodePath, false);

                    check(eventExecuter);
                    updateModFiles();
                }
                else abort();
            }
            catch (const cclTree::Exception &ex)
            {
                execute_event(actionNotPerformed)(ex.what());
            }
            catch (const chila::lib::node::Exception &ex)
            {
                execute_event(actionNotPerformed)(ex.what());
            }

            saveFiles(true);
        });
    }

    void FileLoader::renameNode(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction))
    {
    }

    cclTree::Namespace &FileLoader::globalNsp()
    {
        my_assert(!globalNsps.empty());
        return clMisc::deref(*currNsp);
    }

    const cclTree::Namespace &FileLoader::globalNsp() const
    {
        my_assert(!globalNsps.empty());
        return clMisc::deref(*currNsp);
    }

    void FileLoader::pushGlobalNsp(const cclTree::NamespaceSPtr &nsp)
    {
        my_assert(currNsp != globalNsps.end());

        globalNsps.erase(currNsp + 1, globalNsps.end());
        globalNsps.push_back(nsp);
        currNsp = globalNsps.end() - 1;


    }

    clNode::Node &FileLoader::editNode(const chila::lib::misc::Path &nodePath)
    {
        auto cloneRet = globalNsp().find(nodePath).cloneAll();
        auto nsp = std::dynamic_pointer_cast<cclTree::Namespace>(cloneRet.first);
        nsp->updateParents();
        pushGlobalNsp(nsp);

        return cloneRet.second;
    }

    void FileLoader::cloneNodes(const ClmPathVec &paths)
    {
        auto lastNsp =  globalNsps.back();
        for (auto &path : paths)
        {
            lastNsp = std::dynamic_pointer_cast<cclTree::Namespace>(lastNsp->find(path).cloneAll().first);
            lastNsp->updateParents();
        }

        pushGlobalNsp(lastNsp);
    }


    void FileLoader::setNodeValue(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction))
    {
        auto &node = editNode(nodePath);

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

        updateModFiles();
//        refresh(eventExecuter);

        check(eventExecuter);
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

    void FileLoader::removeNode(const chila::lib::misc::Path &treeNodePath, ev_executer_arg(performAction))
    {
        try
        {
            auto nodePath = tPathMap.getNodePath(treeNodePath);

            auto &node = editNode(nodePath);
            auto &parent = node.parent();

            parent.remove(node.name());
        }
        catch (const cclTree::Exception &ex)
        {
            execute_event(actionNotPerformed)(ex.what());
        }
        catch (const chila::lib::node::Exception &ex)
        {
            execute_event(actionNotPerformed)(ex.what());
        }

        updateModFiles();
        refresh(eventExecuter);
        check(eventExecuter);
    }

    template <typename EventExecuter>
    void FileLoader::check(const EventExecuter &eventExecuter) try
    {
        execute_event_tn(clearOutput)();

        using TPColor = lib::textProperty::Color;

        auto redColor = makeProps(TPColor(75, 0, 0));

        for (auto &path : recoveredFiles)
        {
            execute_event_tn(outputText)(redColor, "Recovered: \"" + path.string() + "\"\n\n");
        }

        globalNsp().check();
        execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "no errors found");
    }
    catch (const cclTree::Exception &ex)
    {
        sendErrorEvents(ex, eventExecuter);
    }
    catch (const chila::lib::node::Exception &ex)
    {
        sendErrorEvents(ex, eventExecuter);
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
            auto showPath = [&](const clMisc::Path &path, const std::string &title)
            {
                auto treePath = tPathMap.findTreePath(path);
                auto tPathStr = treePath ? treePath.getStringRep() : path.getStringRep();

                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "- " + title + ": ");
                execute_event_tn(outputText)(makeProps(TPNPath(path), pathProps1),  tPathStr);
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
            };

            execute_event_tn(outputText)(errorProps, ex.what() + std::string("\n"));

            if (const auto *path = boost::get_error_info<chila::lib::misc::ExceptionInfo::Path>(ex))
            {
                showPath(*path, "path");
            }

            if (const auto *path = boost::get_error_info<cclTree::ErrorInfo::ReferencePath>(ex))
            {
                showPath(*path, "ref. path");
            }

            if (const auto *type = boost::get_error_info<chila::lib::misc::ExceptionInfo::TypeFrom>(ex))
            {
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "- type from: [" + type->pretty_name() + "]\n");
            }

            if (const auto *type = boost::get_error_info<chila::lib::misc::ExceptionInfo::ActualType>(ex))
            {
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "- actual type: [" + type->pretty_name() + "]\n");
            }

            if (const auto *type = boost::get_error_info<chila::lib::misc::ExceptionInfo::TypeTo>(ex))
            {
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "- type to: [" + type->pretty_name() + "]\n");
            }


            if (const auto *vec = boost::get_error_info<cclTree::ErrorInfo::ReqProvVec>(ex))
            {
                for (const auto &reqProv : *vec)
                {
                    auto treePath = tPathMap.findTreePath(reqProv.path);
                    auto tPathStr = treePath ? treePath.getStringRep() : reqProv.path.getStringRep();

                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "- ");
                    execute_event_tn(outputText)(makeProps(TPNPath(reqProv.path), pathProps1),  tPathStr);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n - requires: ");
                    sendArgErrorEvents(reqProv.path, reqProv.requires,                      eventExecuter);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n - provides: ");
                    sendArgErrorEvents(reqProv.path, reqProv.provides,                      eventExecuter);
                    execute_event_tn(outputText)(lib::TextPropertiesSPtr(),                 "\n");
                }
            }

            if (const auto *data = boost::get_error_info<cclTree::ErrorInfo::AInsVecInfo>(ex))
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

            if (const auto *data = boost::get_error_info<cclTree::ErrorInfo::DescToken>(ex))
            {
                execute_event_tn(outputText)(lib::TextPropertiesSPtr(), "- token: " + *data + "\n");
            }
        }
    }

    template <typename EventExecuter>
    void FileLoader::sendArgErrorEvents(const chila::lib::misc::Path &path, const ClmPathSet &set, const EventExecuter &eventExecuter) const
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

    void FileLoader::MOD_ACTION_SIG(requestDesignNode)
    {
        auto treePath = tPathMap.getTreePath(nodePath);
        execute_event(nodeSelected)(treePath, true);
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
        auto it = fnMap.find(nodePath);
        my_assert(it != fnMap.end());

        fNodesToExpand[it->second] = nodePath;
    }

    cclTree::cPerformer::ConnectorInstance &FileLoader::getCInstance(const clMisc::Path &cInsPath)
    {
        auto subPath = clMisc::Path(cInsPath.top(), ":");
        auto parent = cInsPath;
        parent.pop();

        auto &cPerformer = globalNsp().find(parent).toType<cclTree::cPerformer::ConnectionPerformer>();
        return cclTree::getCInstance(cPerformer, subPath);
    }

    struct FileLoader::InsWalkedFNode
    {
        ClmPathSet &walkedNodes;
        std::pair<ClmPathSet::iterator, bool> insRet;
        clMisc::Path nodePath;

        InsWalkedFNode(const clMisc::Path &nodePath, ClmPathSet &walkedNodes) :
            walkedNodes(walkedNodes),
            nodePath(nodePath),
            insRet(walkedNodes.insert(nodePath))
        {
        }

        operator bool() const
        {
            return insRet.second;
        }

        ~InsWalkedFNode()
        {
            if (insRet.second)
                walkedNodes.erase(insRet.first);
        }
    };

    void FileLoader::loadPCInsMap(const chila::lib::node::NodeWithChildren &root)
    {
        for (auto &node : root)
        {
            if (auto cIns = dynamic_cast<const cclTree::cPerformer::ConnectorInstance*>(&node))
            {
                auto path = cclTree::getGroupedPath(*cIns);

                pcInsMap[path].push_back(cIns);
            }
            else if (auto cIns = dynamic_cast<const chila::lib::node::NodeWithChildren*>(&node))
            {
                loadPCInsMap(*cIns);
            }
        }
    }

    std::string prefixSuffix(const std::string &prefix, const std::string &text, const std::string &suffix)
    {
        if (text.empty())
            return "";
        else
            return prefix + text + suffix;
    }

    std::string firstLine(const std::string &text)
    {
        return text.substr(0, text.find('\n'));
    }

    std::string FileLoader::flGetEnhancedDesc(const cclTree::cPerformer::ActionInstance &actionIns, bool singleLine)
    {
        std::string aAliasDesc;
        cclTree::CAliasVec cAliasVec;
        auto &action = actionIns.action().referenced();

        auto igPath = cclTree::getGroupedPath(actionIns.connInstance().referenced());
        auto cInstances = getCInstances(igPath);

        for (auto cIns : cInstances | boost::adaptors::reversed)
        {
            if (auto *acAlias = cclTree::getActionAlias(*cIns, actionIns))
                aAliasDesc = clMisc::getNonEmpty(aAliasDesc, acAlias->description().value);

            cAliasVec.push_back(boost::ref(cIns->connAlias().referenced()));
        }

        if (singleLine)
        {
            auto insDesc = clMisc::getNonEmpty(actionIns.description().value,
                                               aAliasDesc,
                                               actionIns.action().referenced().description().value);

            return firstLine(getEnhancedDesc(actionIns, cAliasVec, insDesc));
        }
        else
        {
            return prefixSuffix("- [actionIns]: ", getEnhancedDesc(actionIns, cAliasVec, actionIns.description().value), "\n\n")
                 + prefixSuffix("- [actionAlias]: ", getEnhancedDesc(actionIns, cAliasVec, aAliasDesc), "\n\n")
                 + prefixSuffix("- [action]: ", getEnhancedDesc(actionIns, cAliasVec, action.description().value), "");
        }
    }

    std::string FileLoader::flGetEnhancedDesc(const cclTree::cPerformer::EventCall &evCall, bool singleLine)
    {
        cclTree::CAliasVec cAliasVec;

        auto igPath = cclTree::getGroupedPath(evCall.parent<cclTree::cPerformer::EventCallMap>()
                                                    .parent<cclTree::cPerformer::ConnectorInstance>());
        auto cInstances = getCInstances(igPath);

        std::string evCallDesc, evAliasDesc;
        auto &event = evCall.referenced();

        for (auto cIns : cInstances | boost::adaptors::reversed)
        {
            auto *eCall = cIns->events().getPtr(evCall.name());
            auto *eventAlias = cclTree::getEventAlias(*cIns, evCall);

            evCallDesc = clMisc::getNonEmpty(evCallDesc, eCall ? eCall->description().value : "");
            evAliasDesc = clMisc::getNonEmpty(evAliasDesc, eventAlias ? eventAlias->description().value : "");

            cAliasVec.push_back(boost::ref(cIns->connAlias().referenced()));
        }

        if (singleLine)
        {
            auto desc = clMisc::getNonEmpty(evCallDesc, evAliasDesc, evCall.referenced().description().value);

            return firstLine(getEnhancedDesc(evCall, cAliasVec, desc));
        }
        else
        {
            return prefixSuffix("- [eventCall]: ", getEnhancedDesc(evCall, cAliasVec, evCallDesc), "\n\n")
                 + prefixSuffix("- [eventAlias]: ", getEnhancedDesc(evCall, cAliasVec, evAliasDesc), "\n\n")
                 + prefixSuffix("- [event]: ", getEnhancedDesc(evCall, cAliasVec, event.description().value), "");
        }
    }

    std::string FileLoader::flGetEnhancedDesc(const clMisc::Path &cInsPath, bool singleLine)
    {
        cclTree::CAliasVec cAliasVec;
        std::string cInsDesc, cAliasDesc;
        const cclTree::connector::Connector *connPtr = nullptr;

        auto &cInsVec = getCInstances(cInsPath);

        // Goes through all the connector instances conceptually referenced by the instance to obtain the description
        for (auto cIns : cInsVec)
        {
            auto &connAlias = cIns->connAlias().referenced();
            connPtr = &connAlias.connector().referenced();

            cInsDesc = clMisc::getNonEmpty(cIns->description().value, cInsDesc);
            cAliasDesc = clMisc::getNonEmpty(connAlias.description().value, cAliasDesc);

            cAliasVec.push_back(boost::ref(connAlias));
        }

        if (singleLine)
        {
            auto desc = clMisc::getNonEmpty(cInsDesc, cAliasDesc, clMisc::deref(connPtr).description().value);
            return firstLine(getEnhancedDesc(*connPtr, cAliasVec, desc));
        }
        else
        {
            auto &conn = clMisc::deref(connPtr);

            return prefixSuffix("- [connInstance]: ", getEnhancedDesc(conn, cAliasVec, cInsDesc), "\n\n")
                 + prefixSuffix("- [connAlias]: ", getEnhancedDesc(conn, cAliasVec, cAliasDesc), "\n\n")
                 + prefixSuffix("- [connector]: ", getEnhancedDesc(conn, cAliasVec, conn.description().value), "");
        }
    }

    void FileLoader::MOD_ACTION_SIG(requestFlowNodes)
    {
        ClmPathSet walkedNodes;

        fnMap.clear();

        // Loads 'pcInsMap'
        pcInsMap.clear();

        for (auto &fileData : fileDataVec)
        {
            loadPCInsMap(globalNsp().find(fileData.path).toType<clNode::NodeWithChildren>());
        }

        // Goes through all the flow instances marked for display
        for (auto &cInsPath : flowCInstances)
        {
            auto fnPath = cInsPath.getStringRep(":");
            auto desc = flGetEnhancedDesc(cInsPath, true);

            auto &cInsVec = getCInstances(cInsPath);

            // Goes through all the connector instances conceptually referenced by the instance
            for (auto cIns : cInsVec)
            {
                auto &connAlias = cIns->connAlias().referenced();
                auto &conn = connAlias.connector().referenced();

                cclTree::CAliasVec cAliasVec = {boost::ref(connAlias)};
                desc = getEnhancedDesc(*cIns, cAliasVec, desc);

                flowNodeFound
                (
                    fnPath,
                    cIns->path(),
                    str_stream(cInsPath << writeDesc(desc)),
                    true,
                    eventExecuter
                );

                const auto &flowCInstancesDimNodes = getCInstancesHLNodes(flowCInstancesDim);

                for (auto &eventCall : cIns->events())
                {
                    walkEvCallFNode(eventCall, fnPath, walkedNodes, flowCInstancesDimNodes, cInsVec, eventExecuter);
                }
            }
        }

        execute_event(noMoreFlowNodes)();
    }

    void FileLoader::walkEvCallFNode(const cclTree::cPerformer::EventCall &evCall,
                                     const clMisc::Path &flowNodePath,
                                     ClmPathSet &walkedNodes,
                                     const CInstanceSet &flowCInstancesDimNodes,
                                     const CInsVec &cInsVec,
                                     ev_executer_arg(requestFlowNodes))
    {
        std::string evCallDesc, evAliasDesc;
        auto id = evCall.name();
        auto fnPath = flowNodePath + id;
        auto nodePath = evCall.path();
        auto inserted = InsWalkedFNode(nodePath, walkedNodes);
        auto hasActions = inserted && !evCall.actions().empty();
        auto insDesc = inserted ? flGetEnhancedDesc(evCall, true) : "";


        flowNodeFound
        (
            fnPath,
            nodePath,
            str_stream(mu_fcolor(MU_DRED, "[event] " << id << (inserted ? " " : "... ")) << writeDesc(insDesc)),
            hasActions,
            eventExecuter
        );

        // If the event was not walked, do it
        if (inserted)
            walkFlowNodes(fnPath, evCall, walkedNodes, flowCInstancesDimNodes, eventExecuter);
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
                                   ClmPathSet &walkedNodes,
                                   const CInstanceSet &flowCInstancesDimNodes,
                                   ev_executer_arg(requestFlowNodes))
    {
        for (auto &actionIns : evCall.actions())
        {
            auto id = actionIns.connInstance().value.getStringRep(":") + "->" + actionIns.action().value.getStringRep(":");
            auto nodePath = actionIns.path();
            auto fnPath = flowNodePath + id;
            bool hasEvents = !actionIns.action().referenced().events().empty();

            auto insDesc = flGetEnhancedDesc(actionIns, true);

            auto cInsText = actionIns.connInstance().value.getStringRep(":");

            auto dim = flowCInstancesDimNodes.count(&actionIns.connInstance().referenced());

            auto cInsFText = dim ? cInsText : str_stream(mu_bold(cInsText));

            flowNodeFound
            (
                fnPath,
                nodePath,
                str_stream(mu_fcolor(MU_BLUE, "[action] "
                        << cInsFText
                        << "." << actionIns.action().value.getStringRep(":") << " ")
                        << writeDesc(insDesc)),
                hasEvents,
                eventExecuter
            );

            walkFlowNodes(fnPath, actionIns, walkedNodes, flowCInstancesDimNodes, eventExecuter);
        }
    }

    const FileLoader::CInsVec &FileLoader::getCInstances(const clMisc::Path &path) const
    {
        auto it = pcInsMap.find(path);
        my_assert(it != pcInsMap.end());
        return it->second;
    }

    const FileLoader::CInsVec &FileLoader::getCInstances(const cclTree::cPerformer::ConnectorInstance &cInstance) const
    {
        auto path = cclTree::getGroupedPath(cInstance);

        return getCInstances(path);
    }

    void FileLoader::walkFlowNodes(const clMisc::Path &flowNodePath,
                                   const cclTree::cPerformer::ActionInstance &aInstance,
                                   ClmPathSet &walkedNodes,
                                   const CInstanceSet &flowCInstancesDimNodes,
                                   ev_executer_arg(requestFlowNodes))
    {
        EvRefMap evRefMap;

        // Inserts the allowed events by the action
        for (auto &evRef : aInstance.action().referenced().events())
        {
            my_assert(evRefMap.insert({evRef.name(), &evRef}).second);
        }

        auto gPath = cclTree::getGroupedPath(aInstance.connInstance().referenced());
        auto &cInsVec = getCInstances(gPath);

        // Goes through all the action instances conceptually referenced by the 'aInstance'
        for (auto cInstance : getCInstances(aInstance.connInstance().value))
            // Goes through the events of the connector instance
            for (auto &evCall : cInstance->events())
            {
                auto it = evRefMap.find(evCall.name());

                if (it != evRefMap.end())
                {
                    // Removes the walked event
                    evRefMap.erase(it);

                    walkEvCallFNode(evCall, flowNodePath, walkedNodes, flowCInstancesDimNodes, cInsVec, eventExecuter);
                }
            }

        // Adds the remaining events
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
        using TPUnder = lib::textProperty::Underline;
        using TPNPath = lib::textProperty::NodePath;
        using TPScale = lib::textProperty::Scale;

        auto it = fnMap.find(nodePath);
        my_assert(it != fnMap.end());
        auto ctNodePath = it->second;

        const auto &node = globalNsp().find(ctNodePath);

        auto titleProps =  makeProps(TPBold());
        auto parenProps = lib::TextPropertiesSPtr();
        auto descProps = makeProps(TPColor(0, 50, 0));
        auto descErrorProps = makeProps(TPColor(50, 70, 50));
        auto noDescProps = makeProps(TPColor(70, 70, 70));
        auto typeProps =  makeProps(TPBold(), TPColor(0, 0, 70));

        auto showTitle = [&](const std::string &title)
        {
            execute_event(outputText)(makeProps(titleProps, TPUnder()), title + "\n");
        };

        auto showSubTitle = [&](const std::string &kind, const clMisc::Path &path, const std::string &title)
        {
            if (!kind.empty())
                execute_event(outputText)(typeProps, "- [" + kind + "] ");

            execute_event(outputText)(makeProps(titleProps, TPNPath(path)), title);
        };


        auto showArgs = [&](const chila::lib::node::NodeWithChildren &args)
        {
            execute_event(outputText)(parenProps, "(");
            bool first = true;
            for (auto &arg : args)
            {
                if (first) first = false;
                else execute_event(outputText)(parenProps, ", ");

                execute_event(outputText)(makeProps(TPNPath(arg.path())), arg.name());
            }
            execute_event(outputText)(parenProps, ")");
        };

        auto showAliasedArgs = [&](const cclTree::cPerformer::ConnectorInstance &cIns, const cclTree::connector::ArgRefMap &args)
        {
            auto &cAlias = cIns.connAlias().referenced();

            execute_event(outputText)(parenProps, "(");
            bool first = true;
            for (auto &arg : args)
            {
                if (first) first = false;
                else execute_event(outputText)(parenProps, ", ");

                auto &argRef = cAlias.arguments().get(arg.name()).cpRef();
                execute_event(outputText)(makeProps(TPNPath(argRef.refPath())), argRef.value.getStringRep(":"));
            }
            execute_event(outputText)(parenProps, ")");
        };

        auto showDesc = [&](const cclTree::Element &elem)
        {
            execute_event(outputText)(titleProps, ": ");

            auto &desc = elem.description().value;
            auto &node = dynamic_cast<const chila::lib::node::Node&>(elem);

            if (desc.empty())
                execute_event(outputText)(noDescProps, "(no description)\n\n");
            else
            {
                bool first = true;

                clMisc::writeParagraph(desc, 100, [&](const std::string &line)
                {
                    execute_event(outputText)(descProps, (first ? "" : "  "));
                    cclTree::ParseText parseText(line, node);

                    while(true) try
                    {
                        if (!parseText.parse())
                            break;

                        if (auto *foundNode = parseText.foundNode())
                        {
                            execute_event(outputText)(descProps, "'");
                            execute_event(outputText)(makeProps(TPNPath(foundNode->path()), descProps), parseText.tokenStr());
                            execute_event(outputText)(descProps, "'");
                        }
                        else
                        {
                            execute_event(outputText)(descProps, parseText.tokenStr());
                        }
                    }
                    catch (const cclTree::DescriptionParseError &ex)
                    {
                        execute_event(outputText)(descErrorProps, parseText.tokenStr());
                    }
                    catch (const cclTree::DescriptionParseInvalidReference &ex)
                    {
                        execute_event(outputText)(descErrorProps, "'");
                        execute_event(outputText)(descErrorProps, parseText.tokenStr());
                        execute_event(outputText)(descErrorProps, "'");
                    }

                    execute_event(outputText)(descProps, "\n");

                    first = false;
                });

                execute_event(outputText)(descProps, "\n");
            }
        };

        auto showNInfoCInstance = [&](const cclTree::cPerformer::ConnectorInstance &cInstance)
        {
            auto &cAlias = cInstance.connAlias().referenced();
            auto &conn = cAlias.connector().referenced();
            auto connInsTitle = cclTree::getGroupedPath(cInstance).getStringRep(":");

            showSubTitle("connInstance", cInstance.path(), connInsTitle);   showDesc(cInstance);
            showSubTitle("connAlias", cAlias.path(),       cAlias.name());  showDesc(cAlias);
        };

        auto showNInfoConnector = [&](const cclTree::cPerformer::ConnectorInstance &cInstance)
        {
            auto &cAlias = cInstance.connAlias().referenced();
            auto &conn = cAlias.connector().referenced();
            auto connPathTitle = cclTree::getGroupedPath(conn).getStringRep(":");

            showSubTitle("connector", conn.path(), connPathTitle);
            showDesc(conn);
        };

        execute_event(clearOutput)();
        if (auto *typed = dynamic_cast<const cclTree::cPerformer::ConnectorInstance*>(&node))
        {
            auto &conn = typed->connAlias().referenced().connector().referenced();

            auto &connDesc = conn.description().value;
            auto connPathTitle = cclTree::getGroupedPath(conn).getStringRep(":");

            auto gPath = cclTree::getGroupedPath(*typed);
            auto desc = flGetEnhancedDesc(gPath, false);

            showTitle("Description:");
            execute_event(outputText)(descProps, desc + "\n\n");

            auto cInstances = getCInstances(gPath);
            unsigned cInd = cInstances.size();
            for (auto cInstance : cInstances | boost::adaptors::reversed)
            {
                showTitle(cclTree::getGroupedFullPath(*cInstance).getStringRep());
                showNInfoCInstance(*cInstance);
            }

            showTitle(cclTree::getGroupedFullPath(conn).getStringRep());
            showNInfoConnector(*typed);
        }
        else if (auto *typed = dynamic_cast<const cclTree::connector::EventRef*>(&node))
        {
            auto &event = typed->referenced();
            auto connEvTitle = cclTree::getGroupedPath(event).getStringRep(":");

            showSubTitle("event", event.path(), connEvTitle);
            showArgs(event.arguments());
            showDesc(event);
        }
        else if (auto *typed = dynamic_cast<const cclTree::cPerformer::EventCall*>(&node))
        {
            auto &evCall = *typed;
            auto &cInstance = evCall.parent<cclTree::cPerformer::EventCallMap>()
                                    .parent<cclTree::cPerformer::ConnectorInstance>();
            auto &conn = cInstance.connAlias().referenced().connector().referenced();
            auto connTitle = cclTree::getGroupedFullPath(conn).getStringRep(":");

            auto &event = evCall.referenced();

            auto connEvTitle = cclTree::getGroupedPath(event).getStringRep(":");

            auto igPath = cclTree::getGroupedPath(cInstance);

            auto desc = flGetEnhancedDesc(evCall, false);

            showTitle("Description:");
            execute_event(outputText)(descProps, desc + "\n\n");


            auto cInstances = getCInstances(igPath);
            for (auto cIns : cInstances | boost::adaptors::reversed)
            {
                auto cInsTitle = cclTree::getGroupedFullPath(*cIns).getStringRep();
                showTitle(cInsTitle);

                auto &connAlias = cIns->connAlias().referenced();

                if (auto *eCall = cIns->events().getPtr(evCall.name()))
                {
                    showSubTitle("eventCall", eCall->path(),   eCall->name());
                    showAliasedArgs(*cIns, event.arguments());
                    showDesc(*eCall);

                    if (auto *evAlias = cclTree::getEventAlias(*eCall))
                    {
                        showSubTitle("evAlias", evAlias->path(), evAlias->name());
                        showAliasedArgs(*cIns, event.arguments());
                        showDesc(*evAlias);
                    }
                }

                showNInfoCInstance(*cIns);
            }

            showTitle(connTitle);

            showSubTitle("event", event.path(), connEvTitle);
            showArgs(event.arguments());
            showDesc(event);

            showNInfoConnector(cInstance);

            for (auto &apc : evCall.aProvCreators())
            {
                showSubTitle("apc", apc.path(), cclTree::getGroupedPath(apc).getStringRep(":"));
                showArgs(apc.referenced().requires());
                execute_event(outputText)(descProps, " -> ");
                showArgs(apc.referenced().provides());
                showDesc(apc.referenced());
            }
        }
        else if (auto *typed = dynamic_cast<const cclTree::cPerformer::ActionInstance*>(&node))
        {
            auto &aIns = *typed;
            auto &cInstance = aIns.connInstance().referenced();
            auto &action = aIns.action().referenced();

            auto &conn = cInstance.connAlias().referenced().connector().referenced();
            auto connTitle = cclTree::getGroupedFullPath(conn).getStringRep();

            auto aInsTitle = cclTree::getGroupedPath(action).getStringRep(":");
            auto connAcTitle = cclTree::getGroupedPath(aIns.action().referenced()).getStringRep();

            auto cInsTitle = cclTree::getGroupedFullPath(cInstance).getStringRep();

            auto desc = flGetEnhancedDesc(aIns, false);

            showTitle("Description:");
            execute_event(outputText)(descProps, desc + "\n\n");

            showTitle(cInsTitle);


            showSubTitle("actionInstance", aIns.path(),  aInsTitle);
            showAliasedArgs(cInstance, action.arguments());
            showDesc(aIns);

            showNInfoCInstance(cInstance);

            auto igPath = cclTree::getGroupedPath(cInstance);
            auto cInstances = getCInstances(igPath);
            for (auto cIns : cInstances | boost::adaptors::reversed)
            {
                if (auto *acAlias = cclTree::getActionAlias(*cIns, aIns))
                {
                    auto cInsTitle = cclTree::getGroupedFullPath(*acAlias).getStringRep();
                    auto &connAlias = acAlias->parent<cclTree::cPerformer::ActionAliasMap>()
                                              .parent<cclTree::cPerformer::ConnectorAlias>();

                    showTitle(cInsTitle);

                    showSubTitle("actionAlias", acAlias->path(), acAlias->name());
                    showDesc(*acAlias);

                    showSubTitle("connAlias", connAlias.path(), connAlias.name());
                    showDesc(connAlias);
                }
            }

            showTitle(connTitle);
            showSubTitle("action", action.path(), connAcTitle);
            showArgs(action.arguments());
            showDesc(action);

            showNInfoConnector(cInstance);
        }
    }

#define if_cast_action(Type) \
        if (std::shared_ptr<Type> action = std::dynamic_pointer_cast<Type>(*actionsCursor))

    void FileLoader::MOD_ACTION_SIG(undo)
    {
        if (currNsp != globalNsps.begin())
        {
            (*--currNsp)->updateParents();
            updateModFiles();
            refresh(eventExecuter);
            saveFiles(true);
        }
    }

    void FileLoader::MOD_ACTION_SIG(redo)
    {
        my_assert(currNsp != globalNsps.end());
        if (currNsp + 1 != globalNsps.end())
        {
            (*++currNsp)->updateParents();
            updateModFiles();
            refresh(eventExecuter);
            saveFiles(true);
        }
    }

    template <typename EventExecuter>
    void FileLoader::refresh(const EventExecuter &eventExecuter)
    {
        execute_event_tn(saveDesignTreeState)();
        execute_event_tn(removeAllChildren)();

        tPathMap.clear();
        walkNode("", "", globalNsp(), eventExecuter);
        check(eventExecuter);
        execute_event_tn(restoreDesignTreeState)();
    }

    void FileLoader::updateModFiles()
    {
        modFiles.clear();
        for (auto &fileData : fileDataVec)
        {
            auto &savedNode = (**savedNsp).find(fileData.path);
            auto &currNode = globalNsp().find(fileData.path);

            if (!savedNode.compare(currNode))
                modFiles.insert({fileData.filePath, fileData});
        }
    }
}
MY_NSP_END

