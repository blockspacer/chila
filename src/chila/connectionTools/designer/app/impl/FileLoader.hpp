/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FILELOADER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FILELOADER_HPP

#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/CPerformerCreator.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include "../../lib/AddPosibilities.hpp"
#include "connection/FileLoader.hpp"
#include "fwd.hpp"
#include <list>

#define MODULE_NAME FileLoader

#include "macros.fgen.hpp"

MY_NSP_START
{
    using StringSet = std::set<std::string>;
    using StringVec = std::vector<std::string>;

    struct Action
    {
        chila::lib::misc::Path path;
        boost::uint32_t nspCRC;

        Action(chila::lib::misc::Path path, boost::uint32_t nspCRC) : path(path), nspCRC(nspCRC) {}

        chila::lib::node::Node &referenced(cclTree::Namespace &nsp) const { return nsp.find(path); }

        virtual const char *name() const = 0;

        virtual ~Action() {}
    };

    FWDEC_SPTR(Action);


    class FileLoader final: public connection::FileLoader::CProvider
    {
        public:
            using Connector = connection::FileLoader::Connector;
            using ArgTypes = connection::FileLoader::ArgTypes;

            Connector connector;


            FileLoader(
                    boost::asio::io_service &ioService,
                    const ClmPathVec &flowCInstances,
                    const ClmPathSet &flowCInstancesDim,
                    bool showFunEvents);

            connection::FileLoader::Connector &getConnector() { return connector; }

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish);

            void MOD_ACTION_SIG(loadCPerformer);
            void MOD_ACTION_SIG(loadConnector);
            void MOD_ACTION_SIG(refreshTree);
//            void MOD_ACTION_SIG(nextNode);

            void MOD_ACTION_SIG(performAction);

            void MOD_ACTION_SIG(undo);
            void MOD_ACTION_SIG(redo);

            void MOD_ACTION_SIG(moveUp);
            void MOD_ACTION_SIG(moveDown);

            void MOD_ACTION_SIG(save);

            void MOD_ACTION_SIG(giveActionList);
            void MOD_ACTION_SIG(expandFlowNode);


            void MOD_ACTION_SIG(requestFlowNodes);
            void MOD_ACTION_SIG(showFNodeInfo);

            void MOD_ACTION_SIG(checkNodes) { check(eventExecuter); }

            void MOD_ACTION_SIG(requestDesignNode);

       private:
            static constexpr unsigned descLimit = 80;

            struct InsWalkedFNode;

            using CInstanceSet = std::set<const cclTree::cPerformer::ConnectorInstance*>;
            using FlowNodesMap = std::map<clMisc::Path, clMisc::Path>;
            FlowNodesMap fnMap;

            lib::AddPosibilities addPosibilities;
            ClmPathVec flowCInstances;

            ClmPathSet flowCInstancesDim;

            using CInsSet = std::set<const cclTree::cPerformer::ConnectorInstance*>;
            using PCInsMap = std::map<clMisc::Path, CInsSet>;
            PCInsMap pcInsMap;

            using ColorMap = std::map<boost::typeindex::type_index, std::string>;
            ColorMap colorMap;

            using FNodesToExpandMap = std::map<clMisc::Path, clMisc::Path>;
            FNodesToExpandMap fNodesToExpand;

            class TPathMap
            {
                public:
                    void insert(const clMisc::Path &nodePath, const clMisc::Path &treePath);
                    void eraseTreePath(const clMisc::Path &nodePath, bool onlyChildren = false);
                    const clMisc::Path &getNodePath(const clMisc::Path &treePath) const;
                    const clMisc::Path &getTreePath(const clMisc::Path &nodePath) const;
                    const clMisc::Path &findTreePath(const clMisc::Path &nodePath) const;
                    void clear() { nodeTreeMap.clear(); treeNodeMap.clear(); }

                private:
                    using Map = std::map<clMisc::Path, clMisc::Path>;
                    using ItMap = std::map<clMisc::Path, Map::iterator>;

                    Map treeNodeMap;
                    ItMap nodeTreeMap;

            } tPathMap;

            using ValueForFun = boost::function<std::string(const chila::lib::node::Node&)>;
            using ValueForMap = std::map<boost::typeindex::type_index, ValueForFun>;
            ValueForMap valueForMap;

            struct DeactivateUndo
            {
                FileLoader &loader;
                DeactivateUndo(FileLoader &loader) : loader(loader) { loader.undoActive = false; }
                ~DeactivateUndo() { loader.undoActive = true; }
            };

            struct FileData
            {
                boost::filesystem::path path;
                bool modified;
                FileData(const boost::filesystem::path &path) :
                    path(path), modified(false) {}
            };

            struct ConnectorData : public FileData
            {
                cclTree::connector::Connector *object;
                ConnectorData(const boost::filesystem::path &path, cclTree::connector::Connector *connector) :
                    FileData(path), object(connector) {}
            };

            struct CPData : public FileData
            {
                cclTree::cPerformer::ConnectionPerformer *object;
                CPData(const boost::filesystem::path &path, cclTree::cPerformer::ConnectionPerformer *cPerformer) :
                    FileData(path), object(cPerformer) {}
            };

            using ConnectorVector = std::vector<ConnectorData>;
            ConnectorVector connectors;

            using CPerfVec = std::vector<CPData>;

            CPerfVec cpVec;

            bool showFunEvents;

            boost::asio::io_service &ioService;
            cclTree::Namespace globalNsp;

            using UndoRedoAList = std::list<ActionSPtr>;
            UndoRedoAList actions;
            UndoRedoAList::iterator actionsCursor;

            bool undoActive;

            mutable unsigned showIndent;

            boost::uint32_t initialCRC;

            using NodeWalkVec = std::vector<const chila::lib::node::Node*>;

            NodeWalkVec nodeWalkVec;

            using PathSet = std::set<clMisc::Path>;

            clMisc::Path cutPathFrom;

            template <typename EventExecuter>
            void check(const EventExecuter &eventExecuter) const;

            template <typename EventExecuter>
            void sendArgErrorEvents(const chila::lib::misc::Path &path, const PathSet &set, const EventExecuter &eventExecuter) const;

            template <typename EventExecuter>
            void sendErrorEvents(const std::exception &ex, const EventExecuter &eventExecuter) const;


            template <typename Type>
            std::string addToVector(Type &node);

            void setNodeValue(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction));
            void removeNode(const chila::lib::misc::Path &treeNodePath, ev_executer_arg(performAction));
            void goToReferencedNode(const chila::lib::node::Node &node, ev_executer_arg(performAction));
            void addAction(const ActionSPtr &action);
            void renameNode(const chila::lib::misc::Path &nodePath, const std::string &value, ev_executer_arg(performAction));
            chila::lib::node::Node &addNodeInt(const chila::lib::misc::Path &treePath, const std::string &actionId, const std::string &value);
            void addNode(const chila::lib::misc::Path &path, const std::string &actionId, const std::string &value, ev_executer_arg(performAction));
            void loadContainerOfTyped(lib::ActionMap &actionMap, const chila::lib::node::Node &node);
            template <typename NodeMap>
            void loadGroup(lib::ActionMap &actionMap);
            cclTree::cPerformer::ConnectorInstance &getCInstance(const clMisc::Path &cInsPath);

            using MoveNodeFun = std::function<std::string(chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)>;

            template <typename EventExecuter>
            void moveNode(const chila::lib::misc::Path &treeNodePath, const EventExecuter &eventExecuter, const MoveNodeFun &fun);

            template <typename EventExecuter>
            void removeChildren(cclTree::NodeWithChildren &parent, const EventExecuter &eventExecuter);

            void walkFlowNodes(const clMisc::Path &flowNodePath,
                               const cclTree::cPerformer::ConnectorInstance &cInstance,
                               PathSet &walkedNodes,
                               const CInstanceSet &flowCInstancesDimNodes,
                               ev_executer_arg(requestFlowNodes));

            void walkFlowNodes(const clMisc::Path &flowNodePath,
                               const cclTree::cPerformer::EventCall &evCall,
                               PathSet &walkedNodes,
                               const CInstanceSet &flowCInstancesDimNodes,
                               ev_executer_arg(requestFlowNodes));

            void walkFlowNodes(const clMisc::Path &flowNodePath,
                               const cclTree::cPerformer::ActionInstance &aInstance,
                               PathSet &walkedNodes,
                               const CInstanceSet &flowCInstancesDimNodes,
                               ev_executer_arg(requestFlowNodes));

            void flowNodeFound(const clMisc::Path &flowNodePath,
                               const clMisc::Path &nodePath,
                               const std::string &value,
                               bool isExpandable,
                               ev_executer_arg(requestFlowNodes));

            template <typename ArgRefMap>
            void showDesc(
                const lib::TextPropertiesSPtr &titleProps,
                const lib::TextPropertiesSPtr &descProps,
                const lib::TextPropertiesSPtr &noDescProps,
                const clMisc::Path &path,
                const std::string &title,
                bool withArgs,
                const ArgRefMap &args,
                const std::string &desc,
                ev_executer_arg(showFNodeInfo));

            CInstanceSet getCInstancesHLNodes(const ClmPathSet &paths);

            template <typename EventExecuter>
            void walkNode(const clMisc::Path &parentNodePath, const clNode::Node &node, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void walkChildrenNodes(const clMisc::Path &treeNodePath, const clNode::Node &node, const EventExecuter &eventExecuter);

            std::string findColor(const boost::typeindex::type_index &index);

            template <typename Type>
            std::string getValueFor(const Type &node);

            std::string getValueFor(const chila::lib::node::Node &node);

            template <typename EventExecuter>
            void refreshDesignTreeAndMM(const clMisc::Path &nodePath, const EventExecuter &eventExecuter);

            void markModified(const clMisc::Path &nodePath);

            template <typename Group, typename Instance, typename Map>
            clMisc::Path getPathPortion(
                clMisc::Path::const_iterator &pathIt,
                const clMisc::Path::const_iterator &pathEnd,
                const Map & map);

            void loadPCInsMap(const chila::lib::node::NodeWithChildren &root);

            const CInsSet &getCInstances(const clMisc::Path &path) const;
            const CInsSet &getCInstances(const cclTree::cPerformer::ConnectorInstance &cInstance) const;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

