/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FILELOADER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FILELOADER_HPP

#include <chila/connectionTools/lib/codegen/ActionExecuter.hpp>

#include <boost/fusion/include/make_vector.hpp>
#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/CPerformerCreator.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include "../../lib/AddPosibilities.hpp"
#include "connection/FileLoader.hpp"
#include "fwd.hpp"
#include <list>
#include <boost/range/algorithm/remove_if.hpp>

#define MODULE_NAME FileLoader

#include "macros.fgen.hpp"

MY_NSP_START
{
    using StringSet = std::set<std::string>;
    using StringVec = std::vector<std::string>;
    using PathSet = std::set<boost::filesystem::path>;
    using PathVec = std::vector<boost::filesystem::path>;

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

            void MOD_ACTION_SIG(loadFiles);
            void MOD_ACTION_SIG(refreshTree);

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

            using GoToRefWPosFun = std::function<void(const clNode::Node&, const ev_executer_type(performAction)&)>;
            using GoToRefWPosValMap = std::map<std::string, GoToRefWPosFun>;
            using GoToRefWPosMap = std::map<boost::typeindex::type_index, GoToRefWPosValMap>;

            GoToRefWPosMap goToRefWPosMap;

            lib::AddPosibilities addPosibilities;
            ClmPathVec flowCInstances;

            ClmPathSet flowCInstancesDim;

            PathVec recoveredFiles;

            using CInsVec = std::vector<const cclTree::cPerformer::ConnectorInstance*>;
            using PCInsMap = std::map<clMisc::Path, CInsVec>;
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
                    std::pair<clMisc::Path, clMisc::Path> getExistingParentTreePath(const clMisc::Path &nodePath) const;
                    const clMisc::Path &findTreePath(const clMisc::Path &nodePath) const;
                    void clear() { nodeTreeMap.clear(); treeNodeMap.clear(); }

                private:
                    using Map = std::map<clMisc::Path, clMisc::Path>;
                    using ItMap = std::map<clMisc::Path, Map::iterator>;

                    Map treeNodeMap;
                    ItMap nodeTreeMap;

            } tPathMap;

            using ValueForFun = std::function<std::string(const chila::lib::node::Node&)>;
            using ValueForMap = std::map<boost::typeindex::type_index, ValueForFun>;
            ValueForMap valueForMap;

            using NspVec = std::deque<cclTree::NamespaceSPtr>;
            NspVec globalNsps;
            using NspVecIt = NspVec::iterator;
            NspVecIt currNsp, savedNsp;

            struct FileData
            {
                boost::filesystem::path filePath;
                clMisc::Path path;
                FileData(const boost::filesystem::path &filePath, const clMisc::Path &path) :
                    filePath(filePath), path(path) {}
            };

            using FileDataVec = std::vector<FileData>;
            FileDataVec fileDataVec;

            using PathFileDataMap = std::map<boost::filesystem::path, FileData>;

            using ClmPathNodeMap = std::map<clMisc::Path, const clNode::Node*>;
            PathFileDataMap modFiles;

            bool showFunEvents;

            boost::asio::io_service &ioService;

            using UndoRedoAList = std::list<ActionSPtr>;
            UndoRedoAList actions;
            UndoRedoAList::iterator actionsCursor;

            bool undoActive;

            mutable unsigned showIndent;

            boost::uint32_t initialCRC;

            using NodeWalkVec = std::vector<const chila::lib::node::Node*>;

            NodeWalkVec nodeWalkVec;

            using EvRefMap = std::map<std::string, const cclTree::connector::EventRef*>;

            clMisc::Path cutPathFrom;

            template <typename EventExecuter>
            void check(const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void sendArgErrorEvents(const chila::lib::misc::Path &path, const ClmPathSet &set, const EventExecuter &eventExecuter) const;

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

            using MoveNodeFun = std::function<clNode::Node&(chila::lib::node::NodeWithChildren &parent, const std::string &name, bool isVec)>;

            template <typename EventExecuter>
            void moveNode(const chila::lib::misc::Path &treeNodePath, const EventExecuter &eventExecuter, const MoveNodeFun &fun);

            template <typename EventExecuter>
            void removeChildren(cclTree::NodeWithChildren &parent, const EventExecuter &eventExecuter);

//            void walkFlowNodes(const clMisc::Path &flowNodePath,
//                               const cclTree::cPerformer::ConnectorInstance &cInstance,
//                               const CInsVec &cInsVec,
//                               ClmPathSet &walkedNodes,
//                               const CInstanceSet &flowCInstancesDimNodes,
//                               ev_executer_arg(requestFlowNodes));

            void walkFlowNodes(const clMisc::Path &flowNodePath,
                               const cclTree::cPerformer::EventCall &evCall,
                               ClmPathSet &walkedNodes,
                               const CInstanceSet &flowCInstancesDimNodes,
                               ev_executer_arg(requestFlowNodes));

            void walkFlowNodes(const clMisc::Path &flowNodePath,
                               const cclTree::cPerformer::ActionInstance &aInstance,
                               ClmPathSet &walkedNodes,
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
            void walkNode(const std::string &prefix, const clMisc::Path &parentNodePath, const clNode::Node &node, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void walkChildrenNodes(const std::string &prefix, const clMisc::Path &treeNodePath, const clNode::Node &node, const EventExecuter &eventExecuter);

            std::string findColor(const boost::typeindex::type_index &index);

            template <typename Type>
            std::string getValueFor(const Type &node);

            std::string getValueFor(const chila::lib::node::Node &node);

            void loadPCInsMap(const chila::lib::node::NodeWithChildren &root);

            const CInsVec &getCInstances(const clMisc::Path &path) const;
            const CInsVec &getCInstances(const cclTree::cPerformer::ConnectorInstance &cInstance) const;

            void walkEvCallFNode(const cclTree::cPerformer::EventCall &evCall,
                                 const clMisc::Path &flowNodePath,
                                 ClmPathSet &walkedNodes,
                                 const CInstanceSet &flowCInstancesDimNodes,
                                 const CInsVec &cInsVec,
                                 ev_executer_arg(requestFlowNodes));

            std::string flGetEnhancedDesc(const cclTree::cPerformer::ActionInstance &actionIns, bool singleLine);
            std::string flGetEnhancedDesc(const cclTree::cPerformer::EventCall &evCall, bool singleLine);
            std::string flGetEnhancedDesc(const clMisc::Path &cInsPath, bool singleLine);

            void pushGlobalNsp(const cclTree::NamespaceSPtr &nsp);
            clNode::Node &editNode(const chila::lib::misc::Path &nodePath);

            cclTree::Namespace &globalNsp();
            const cclTree::Namespace &globalNsp() const;

            template <typename EventExecuter>
            void refresh(const EventExecuter &eventExecuter);

            void saveObject(const FileData &data, bool isRecovery);

            void cloneNodes(const ClmPathVec &paths);

            void saveFiles(bool isRecovery);

//            PathFileDataMap findModifiedFiles();

            void updateModFiles();
            void cleanTmpFiles();

            static boost::filesystem::path appendExtension(const boost::filesystem::path &path, const std::string &extension)
            {
                return path.parent_path() / (path.filename().string() + "." + extension);
            }

            static boost::filesystem::path getRecoveryPath(const boost::filesystem::path &path)
            {
                return appendExtension(path, "recovery~");
            }

            static boost::filesystem::path getTemporalPath(const boost::filesystem::path &path)
            {
                return appendExtension(path, "~");
            }

            template <typename Type>
            void loadObject(const boost::filesystem::path &filePath, bool isRecovery);

            void loadFilesPrv(const PathSet &cpFiles, const PathSet &connFiles, bool isRecovery);

            static bool checkRecFiles(const PathSet &files);

            static bool checkRecovery(const boost::filesystem::path &path);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

