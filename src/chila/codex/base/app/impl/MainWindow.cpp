/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/qt/SigConn.hpp>
#include "MainWindow.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/type_traits.hpp>

#include <chila/lib/misc/util.hpp>
#include <chila/lib/qt/util.hpp>
#include <boost/type_traits/remove_reference.hpp>

#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

#define lqt_connect_signal(name, cList, args)  \
    qtSigConns.name = CHILA_LIB_QT__CONNECT_SIGNAL(window, name, cList, args)

#define FUN_ACTIONS_ELEM(r, fun, elem) fun(elem);

#define my_get_action(name) my_get_object(Action, BOOST_PP_CAT(action_, name))



MY_NSP_START
{
    template <typename ...Pair>
    QJsonArray createPath(const std::pair<std::string, std::string> &item, const Pair&... items);

    QJsonObject createJSAction(const std::string &name, const std::string &text, const std::string &shortcut);

    MainWindow::MainWindow(module_args_ex) :
        connection::MainWindow::CProvider(instanceName),
        window(window),
        modActions(window)
    {
        ccCommon::ActionPathDataList fileAList = { { "file", "File" } };

        modActions.addAction(fileAList, "new",       "&New",          "New file.",           "StandardKey.New");
        modActions.addAction(fileAList, "open",      "&Open",         "Open file.",          "StandardKey.Open");
        modActions.addAction(fileAList, "save",      "&Save",         "Save file.",          "StandardKey.Save");
        modActions.addAction(fileAList, "saveAs",    "Save &As",      "Save file as.",       "StandardKey.SaveAs");
        modActions.addAction(fileAList, "saveAll",   "Sa&ve All",     "Save all files.",     "StandardKey.SaveAll");
        modActions.addAction(fileAList, "close",     "&Close",        "Close file.",         "StandardKey.Close");
        modActions.addAction(fileAList, "closeAll",  "&Close All",    "Close all files.",    "''");
        modActions.addSeparator(fileAList);
        modActions.addAction(fileAList, "quit",      "&Quit",         "Quit program.",       "StandardKey.Quit");

        connector.bindActions(*this);
    }

    void MainWindow::MOD_ACTION_SIG(launcher_start)
    {
        modActions.actionExecutedFun = [this, eventExecuter](const clMisc::Path &path)
        {
            execute_event(actionExecuted)(path);
        };

        lqt_connect_signal(winClosing, (this)(eventExecuter), )
        {
            execute_event(exitActionActivated)();
        });

        lqt_connect_signal(tabSwitched, (this)(eventExecuter), (tabVar))
        {

            auto tab = clMisc::checkNotNull(tabVar.value<QObject*>());

            auto it = dataItMap.find(tab);
            ct_assert(it != dataItMap.end());

            execute_event(notebook_tabSelected)(it->second->first);
        });

        execute_event(launcher_started)();
    }

    void MainWindow::MOD_ACTION_SIG(launcher_finish)
    {
        execute_event(launcher_finished)();
    }

    void MainWindow::MOD_ACTION_SIG(notebook_openNewTab)
    {
        auto tabVar = clQt::invokeMethod(window, "addTab", notebook_tabName, clMisc::deref(notebook_tabWidget));

        auto &tab = clMisc::deref(tabVar.value<QObject*>());
        auto ret = dataMap.insert({notebook_tabId, {notebook_tabName, notebook_tabTooltip, tab}});
        ct_assert(ret.second);
        ct_assert(dataItMap.insert({&tab, ret.first}).second);

        auto item = clMisc::checkNotNull(tab.property("item").value<QObject*>());

        execute_event(notebook_tabAdded)(notebook_tabId, item);
    }

    void MainWindow::MOD_ACTION_SIG(notebook_closeTab)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        auto &tab = data.tab;

        ct_assert(dataItMap.erase(&tab));
        dataMap.erase(it);

        clQt::invokeMethod(window, "removeTab", tab);
    }



    void MainWindow::MOD_ACTION_SIG(notebook_tabDataChanged)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &tab = it->second.tab;
        auto &data = it->second;

        data.text = notebook_tabName;
        data.toolTip = notebook_tabTooltip;
        tab.setProperty("title", QString(notebook_tabName.c_str()));
    }

    void MainWindow::MOD_ACTION_SIG(notebook_selectTab)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto disabler = qtSigConns.tabSwitched->disabler();
        clQt::invokeMethod(window, "selectTab", it->second.tab);
    }

    void MainWindow::MOD_ACTION_SIG(notebook_tabContentsModified)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        data.tab.setProperty("title", QString((data.text + " *").c_str()));

    }

    void MainWindow::MOD_ACTION_SIG(notebook_tabContentsAreOriginal)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        data.tab.setProperty("title", QString((data.text).c_str()));
    }

    void MainWindow::MOD_ACTION_SIG(addAction)
    {
        modActions.addAction(actionPathDataList, actionData.name, actionData.label, actionData.tooltip, actionData.shortcutKey);
    }

    void MainWindow::MOD_ACTION_SIG(addSeparator)
    {
        modActions.addSeparator(actionPathDataList);
    }

    connection::MainWindow::CProviderUPtr connection::MainWindow::create(module_args_ex)
    {
        return boost::make_unique<impl::MainWindow>(module_pass_args_ex);
    }
}
MY_NSP_END
