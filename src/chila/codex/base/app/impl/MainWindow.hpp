/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
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
#include <QAction>
#include "../../../common/ModActions.hpp"
#include <chila/lib/qt/fwd.hpp>


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
            void MOD_ACTION_SIG(setPresent) { /*objects.mainWindow->present(); */}
            void MOD_ACTION_SIG(addAction);
            void MOD_ACTION_SIG(addSeparator);
            void MOD_ACTION_SIG(clearActions) { }

        private:
            QQuickWindow &window;
            ccCommon::ModActions modActions;

            struct
            {
                clQt::SigConnUPtr winClosing, tabSwitched;
            } qtSigConns;

            QVariant action;

            CHILA_LIB_MISC__NAMED_TUPLE
            (
                Data, 0,
                ((std::string)(text))
                ((std::string)(toolTip))
                ((QObject&)(tab))
            );

            using TabIdSCPtr = connection::MainWindow::TabIdSCPtr;
            using DataMap = std::map<TabIdSCPtr, Data>;
            using DataItMap = std::map<QObject*, DataMap::iterator>;

            DataMap dataMap;
            DataItMap dataItMap;

    };
}
MY_NSP_END

#undef def_nb_tabid_action
#undef DEF_ACTIONS_ELEM
#include "macros.fgen.hpp"
#endif

