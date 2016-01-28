/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_HPP
#define CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/MainWindow.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <ctype.h>
#include <boost/variant.hpp>
#include "../../../common/ModActions.hpp"


#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

#define CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_ACTIONS \
    (file_new) \
    (file_open) \
    (file_save) \
    (file_saveAs) \
    (file_quit) \
    (edit_undo) \
    (edit_redo) \
    (edit_findReplace)

#define DEF_ACTIONS_ELEM(r, data, elem) Glib::RefPtr<Gtk::Action> BOOST_PP_CAT(action_, elem);

MY_NSP_START
{
    class MainWindow final: public connection::MainWindow::CProvider
    {
        public:
            using PostFun = connection::MainWindow::PostFun;

            MainWindow(module_args_ex);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish);

            void MOD_ACTION_SIG(notebook_openNewTab);
            void MOD_ACTION_SIG(notebook_selectTab);
            void MOD_ACTION_SIG(notebook_tabContentsModified);
            void MOD_ACTION_SIG(notebook_tabContentsAreOriginal);
            void MOD_ACTION_SIG(notebook_tabDataChanged);
            void MOD_ACTION_SIG(notebook_closeTab);
            void MOD_ACTION_SIG(setPresent) { objects.mainWindow->present(); }
            void MOD_ACTION_SIG(addAction);
            void MOD_ACTION_SIG(clearActions) { }



        private:
            CHILA_LIB_MISC__NAMED_TUPLE
            (
                Data, 0,
                ((std::string)(text))
                ((std::string)(toolTip))
                ((Gtk::Label&)(label))
                ((Gtk::Widget&)(widget))
            );

            using TabIdSCPtr = connection::MainWindow::TabIdSCPtr;
            using DataMap = std::map<TabIdSCPtr, Data>;
            using DataItMap = std::map<Gtk::Widget*, DataMap::iterator>;
            using GtkActionPtr = Glib::RefPtr<Gtk::Action>;

            struct ActionMap
            {
                using Map = std::map<std::string, boost::variant
                <
                    Gtk::MenuItem*,
                    boost::recursive_wrapper<ActionMap>
                >>;

                Gtk::MenuShell *menuShell;
                Map map;

                ActionMap(Gtk::MenuShell *menuShell = nullptr) : menuShell(menuShell) {}
            };

            boost::asio::io_service &ioService;
            DataMap dataMap;
            DataItMap dataItMap;
            PostFun postFun;
            ActionMap actions;
            ccCommon::ModActions modActions;

            Glib::RefPtr<Gtk::Builder> &builder;

            struct
            {
                Gtk::Window *mainWindow;
                Gtk::Notebook *notebook;
                Gtk::Button *projectButton;
                Gtk::MenuBar *menuBar;
                Glib::RefPtr<Gtk::AccelGroup> aGroup;

                BOOST_PP_SEQ_FOR_EACH(DEF_ACTIONS_ELEM,, CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_ACTIONS)
            } objects;

            void clearNotebookPages();

            void setTabText(Data &data, Pango::Weight weight);
            TabIdSCPtr getCurrentTabId() const;
            Gtk::MenuItem &crateSubMenu(const std::string &label);
            Gtk::MenuItem &createActionMItem(const Glib::RefPtr<Gtk::Action> &action);

            template <typename EventExecuter>
            void addActionPrv(const ccCommon::ActionDataList &actionDataList, const GtkActionPtr &action, const EventExecuter &eventExecuter);

    };
}
MY_NSP_END

#undef def_nb_tabid_action
#undef DEF_ACTIONS_ELEM
#include "macros.fgen.hpp"
#endif

