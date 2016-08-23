/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__MAINWINDOW_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__MAINWINDOW_HPP



#include <boost/fusion/include/make_vector.hpp>
#include "fwd.hpp"
#include "connection/MainWindow.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/optional.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <boost/bind.hpp>
#include <ctype.h>
#include <list>

#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

MY_NSP_START
{
    class MainWindow final: public connection::MainWindow::CProvider
    {
        public:
            using Connector = connection::MainWindow::Connector;
            using ArgTypes = connection::MainWindow::ArgTypes;

            Connector connector;

            connection::MainWindow::Connector &getConnector() { return connector; }

            MainWindow(boost::asio::io_service &ioService, const boost::filesystem::path &gladeFile, bool showFunEvents);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish);

            void MOD_ACTION_SIG(waitEvent);

            void MOD_ACTION_SIG(addNode);
            void MOD_ACTION_SIG(removeNode);
            void MOD_ACTION_SIG(removeChildren);
            void MOD_ACTION_SIG(removeAllChildren);
            void MOD_ACTION_SIG(setNodeValue);
            void MOD_ACTION_SIG(showActions);
            void MOD_ACTION_SIG(renameNode);

            void MOD_ACTION_SIG(addOutputText);
            void MOD_ACTION_SIG(clearOutput);

            void MOD_ACTION_SIG(actionNotPerformed);

            void MOD_ACTION_SIG(selectNode);

            void MOD_ACTION_SIG(addFlowNode);
            void MOD_ACTION_SIG(noMoreFlowNodes);

            void MOD_ACTION_SIG(saveDesignTreeState);
            void MOD_ACTION_SIG(restoreDesignTreeState);

            ~MainWindow()
            {
                if (widgets.mainWindow) delete widgets.mainWindow;
            }

       private:
            using MenuMap = std::map<std::string, boost::any>;

            struct MenuMapData
            {
                MenuMap map;
                Gtk::Menu &menu;

                MenuMapData(Gtk::Menu &menu) : menu(menu) {}
            };

            boost::asio::io_service &ioService;

            Gtk::Main kit;
            Glib::RefPtr<Gtk::Builder> builder;

            using EventEx = Connector::Actions::MData_waitEvent::EventExecuter;
            using EventExSPtr = std::shared_ptr<EventEx>;
            EventExSPtr eventEx;

            std::shared_ptr<boost::asio::deadline_timer> timer;

            std::shared_ptr<Gtk::Menu> popupMenu;

            std::shared_ptr<Gtk::MessageDialog> errorDialog;

            struct ColumnRecord : public Gtk::TreeModel::ColumnRecord
            {
                Gtk::TreeModelColumn<Glib::ustring> value;
                Gtk::TreeModelColumn<chila::lib::misc::Path> id;

                ColumnRecord()
                {
                    add(id);
                    add(value);
                }
            };

            using NavigationList = std::list<chila::lib::misc::Path>;
            NavigationList navList;
            NavigationList::iterator navListCursor;

            struct RowData
            {
                std::string value;
                Gtk::TreeModel::Row row;

                RowData() {}
                RowData(const Gtk::TreeModel::Row &row) : row(row) {}
            };

            using RowMap = std::map<clMisc::Path, RowData>;
            using PathMap = std::map<clMisc::Path, RowMap::iterator>;

            struct
            {
                Gtk::Window *mainWindow;
                Gtk::Dialog *setValueDialog;
                Gtk::TreeView *designTree, *flowTree;
                Gtk::TextView *setValueTView, *outputText;
                Gtk::Toolbar *toolbar;
                Gtk::Notebook *notebook;
            } widgets;

            struct
            {
                Glib::RefPtr<Gtk::Action> undo, redo, goBack, goForward, save, moveUp, moveDown;
            } actions;

            struct TreeData
            {
                ColumnRecord columnRecord;
                Glib::RefPtr<Gtk::TreeStore> treeStore;
                RowMap rowMap;
                Gtk::TreeView *tree;

                TreeData() : tree(nullptr) {}
            } designData, flowData;

            Glib::RefPtr<Gtk::TextTag> lastTTagUnder;

            using PathSet = std::set<clMisc::Path>;
            PathSet expandedDesignNodes, expandedFlowNodes, flowNodesToExpand;

            clMisc::Path lastFlowSelection, lastDesignSelection;

            GdkEventButton lastEventButton;
            bool textOver, shouldRefreshFlow;


            sigc::connection dialogRespConn;

            mutable unsigned showIndent;

            bool showFunEvents;

            template <typename EventExecuter>
            void actionSelected(const chila::lib::misc::Path &nodePath, const lib::ActionSCPtr &action,
                const std::string &value, const EventExecuter &eventExecuter);

            void goToError();

            void addNavigation(const chila::lib::misc::Path &path);

            void selectNodePv(const chila::lib::misc::Path &nodePath, bool addNav, bool openNode);

            void initToolBar(ev_executer_arg(launcher_start));

            void setTimer();
            void timerExpired(const boost::system::error_code &ec);

            void updateTextTagUnder(const Glib::RefPtr<Gtk::TextTag> &currTag = Glib::RefPtr<Gtk::TextTag>());

            template <typename EventExecuter>
            void menuItem(GdkEvent *event, const chila::lib::misc::Path &nodePath, const lib::ActionSCPtr &action,
                const std::string &value, const EventExecuter &eventExecuter);

            void addMenuItems(const chila::lib::misc::Path &nodePath, const lib::ActionMap &actionMap,
                Gtk::Menu &parent, ev_executer_arg(showActions));
            void addPosibilities(
                const chila::lib::misc::Path &nodePath,
                Gtk::MenuItem &item,
                const lib::ActionWithPosSCPtr &action,
                const cclTree::ValueVec &valueMap,
                const std::string &value,
                ev_executer_arg(showActions));

            void appendFlowEmptyNode(const Gtk::TreeModel::Row &row);

            template <typename EventExecuter>
            void updateFlowSelection(const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void exandNodePath(const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void refreshFlowNodes(const EventExecuter &eventExecuter);

            void addNodePrv(
                TreeData &data,
                const clMisc::Path &nodePath,
                const std::string &value,
                bool appendEmpty);

            void saveDesignTreeStatePrv(const Gtk::TreeNodeChildren &children);

            clMisc::Path getSelectedNodePath(const TreeData &treeData);
            void selectTreeNode(const TreeData &treeData, const clMisc::Path &path);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

