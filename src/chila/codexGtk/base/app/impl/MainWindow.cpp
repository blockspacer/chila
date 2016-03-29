/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "MainWindow.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <chila/lib/misc/util.hpp>
#include <pangomm-1.4/pangomm/attributes.h>
#include <pangomm-1.4/pangomm/fontdescription.h>
#include <chila/lib/gtkmm/util.hpp>

#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

#define connect_action(name) \
        BOOST_PP_CAT(objects.action_, name)->signal_activate().connect_notify([this, eventExecuter] \
        { \
            postFun(BOOST_PP_STRINGIZE(BOOST_PP_CAT(action_, name)->signal_activate()), [this, eventExecuter] \
            { \
                execute_event(actionExecuted)(clMisc::Path(BOOST_PP_STRINGIZE(name), "_").getStringRep()); \
            }); \
        });

#define FUN_ACTIONS_ELEM(r, fun, elem) fun(elem);

#define my_get_action(name) my_get_object(Action, BOOST_PP_CAT(action_, name))

MY_NSP_START
{
    MainWindow::MainWindow(module_args_ex) :
        connection::MainWindow::CProvider(instanceName),
        ioService(ioService),
        postFun(postFun),
        builder(builder)
    {
        my_get_widget(mainWindow);
        my_get_widget(notebook);
        my_get_widget(projectButton);
        my_get_widget(menuBar);
        my_get_object(AccelGroup, aGroup);

        BOOST_PP_SEQ_FOR_EACH(FUN_ACTIONS_ELEM, my_get_action, CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_ACTIONS)

        actions.menuShell = objects.menuBar;

        ccCommon::ActionDataList fileAList = { { "file", "File" } };

        modActions.createAction(fileAList, "new",       "New",          "New file.",            Gtk::Stock::NEW,        { 'n', Gdk::CONTROL_MASK });
        modActions.createAction(fileAList, "open",      "Open",         "Open file.",           Gtk::Stock::OPEN,       { 'o', Gdk::CONTROL_MASK });
        modActions.createAction(fileAList, "save",      "Save",         "Save file.",           Gtk::Stock::SAVE,       { 's', Gdk::CONTROL_MASK });
        modActions.createAction(fileAList, "saveAs",    "Save As",      "Save file as.");
        modActions.createAction(fileAList, "close",     "Close",        "Close file.",          Gtk::Stock::CLOSE);
        modActions.createAction(fileAList, "closeAll",  "Close All",    "Close all files.",     Gtk::Stock::CLOSE);
        modActions.createAction(fileAList, "saveAll",   "Save All",     "Save all files.",      Gtk::Stock::SAVE,       { 's', Gdk::CONTROL_MASK | Gdk::SHIFT_MASK });
        modActions.createSeparator(fileAList);
        modActions.createAction(fileAList, "quit",      "Quit", "Quit program.",        Gtk::Stock::QUIT,       { 'q', Gdk::CONTROL_MASK });

        connector.bindActions(*this);
    }

    void MainWindow::MOD_ACTION_SIG(launcher_start)
    {
        clearNotebookPages();

        objects.mainWindow->signal_hide().connect_notify([this, eventExecuter]
        {
            postFun("mainWindow->signal_hide()", [this, eventExecuter]
            {
                execute_event(exitActionActivated)();
            });
        });

        objects.projectButton->signal_clicked().connect_notify([this, eventExecuter]
        {
            postFun("projectButton->signal_clicked()", [this, eventExecuter]
            {
                execute_event(projectButtonPressed)();
            });
        });

        BOOST_PP_SEQ_FOR_EACH(FUN_ACTIONS_ELEM, connect_action, CHILA_CODEX_BASE_APP_IMPL__MAINWINDOW_ACTIONS)

        for (const auto &actionData : modActions.dataList)
            addActionPrv(actionData.aList, actionData.action, eventExecuter);

        objects.mainWindow->set_size_request(800, 600);
        objects.mainWindow->show_all();

        execute_event(launcher_started)();
    }

    void MainWindow::MOD_ACTION_SIG(launcher_finish)
    {
        execute_event(launcher_finished)();
    }

    void MainWindow::MOD_ACTION_SIG(notebook_openNewTab)
    {
        auto &tab = clMisc::deref(notebook_tabWidget);

        auto &hBox = clGtkmm::makeManagedRef<Gtk::HBox>();
        auto &closeButton = clGtkmm::makeManagedRef<Gtk::Button>();
        auto &closeButtonImg = clGtkmm::makeManagedRef<Gtk::Image>(Gtk::Stock::CLOSE, Gtk::BuiltinIconSize::ICON_SIZE_MENU);
        closeButton.set_image(closeButtonImg);
        closeButton.set_tooltip_text("Close tab");
        closeButton.set_relief(Gtk::ReliefStyle::RELIEF_NONE);
        closeButton.signal_pressed().connect_notify([this, notebook_tabId, &tab, eventExecuter]
        {
            postFun("closeButton.signal_pressed()", [this, notebook_tabId, &tab, eventExecuter]
            {
                execute_event(notebook_closingTab)(notebook_tabId);
            });
        });

        auto &label = clGtkmm::makeManagedRef<Gtk::Label>(notebook_tabName + "  ");
        label.set_tooltip_text(notebook_tabTooltip);

        hBox.add(label);
        hBox.add(closeButton);

        tab.show_all();
        hBox.show_all();

        objects.notebook->signal_switch_page().connect_notify([this, eventExecuter](Gtk::Widget *widget, guint page)
        {
            postFun("objects.notebook->signal_switch_page()", [this, widget, eventExecuter]
            {
                auto it = dataItMap.find(widget);
                ct_assert(it != dataItMap.end());
                execute_event(notebook_tabSelected)(it->second->first);
            });
        });

        auto ret = dataMap.insert({notebook_tabId, {notebook_tabName, notebook_tabTooltip, label, tab}});
        ct_assert(ret.second);
        ct_assert(dataItMap.insert({&tab, ret.first}).second);

        objects.notebook->append_page(tab, hBox);
        objects.notebook->set_tab_reorderable(tab, true);
        objects.notebook->set_current_page(-1);
        objects.notebook->show_all();
    }

    void MainWindow::MOD_ACTION_SIG(notebook_closeTab)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;

        objects.notebook->remove_page(data.widget);
        ct_assert(dataItMap.erase(&data.widget));
    }

    void MainWindow::MOD_ACTION_SIG(notebook_tabDataChanged)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        data.text = notebook_tabName;
        data.toolTip = notebook_tabTooltip;

        setTabText(data, Pango::Weight::WEIGHT_NORMAL);
    }

    void MainWindow::MOD_ACTION_SIG(notebook_selectTab)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto pageNum = objects.notebook->page_num(it->second.widget);
        ct_assert(pageNum >= 0);
        objects.notebook->set_current_page(pageNum);
    }

    MainWindow::TabIdSCPtr MainWindow::getCurrentTabId() const
    {
        auto currWidget = objects.notebook->get_focus_child();
        my_assert(currWidget);
        auto it = dataItMap.find(currWidget);
        my_assert(it != dataItMap.end());

        return it->second->first;
    }

    void MainWindow::MOD_ACTION_SIG(notebook_tabContentsModified)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        setTabText(data, Pango::Weight::WEIGHT_BOLD);

    }

    void MainWindow::MOD_ACTION_SIG(notebook_tabContentsAreOriginal)
    {
        auto it = dataMap.find(notebook_tabId);
        ct_assert(it != dataMap.end());

        auto &data = it->second;
        setTabText(data, Pango::Weight::WEIGHT_NORMAL);
    }

    void MainWindow::setTabText(Data &data, Pango::Weight weight)
    {
        auto attrList = Pango::AttrList();
        Pango::Attribute attr(Pango::Attribute::create_attr_weight(weight));
        attrList.insert(attr);
        data.label.property_label() = data.text + "  ";
        data.label.property_tooltip_text() = data.toolTip;
        data.label.property_attributes() = attrList;
    }

    void MainWindow::clearNotebookPages()
    {
        auto pageCount = objects.notebook->get_n_pages();
        for (auto i = 0; i < pageCount; ++i)
        {
            objects.notebook->remove_page(0);
        }
    }

    Gtk::MenuItem &MainWindow::crateSubMenu(const std::string &label)
    {
        auto &menuItem = clGtkmm::makeManagedRef<Gtk::MenuItem>();
        menuItem.set_label(label);
        auto &menu = clGtkmm::makeManagedRef<Gtk::Menu>();

        menuItem.set_submenu(menu);
        menuItem.show();

        return menuItem;
    }

    Gtk::MenuItem &MainWindow::createActionMItem(const Glib::RefPtr<Gtk::Action> &action)
    {
        auto &menuItem = clGtkmm::makeManagedRef<Gtk::MenuItem>();
        action->set_accel_group(objects.aGroup);
        menuItem.set_related_action(action);

        menuItem.show();

        return menuItem;
    }

    void MainWindow::MOD_ACTION_SIG(addAction)
    {
        addActionPrv(actionDataList, action, eventExecuter);
    }

    template <typename EventExecuter>
    void MainWindow::addActionPrv(const ccCommon::ActionDataList &actionDataList, const GtkActionPtr &action, const EventExecuter &eventExecuter)
    {
        ct_assert_tn(actionDataList.size());

        ActionMap *lastAMap = &actions;
        clMisc::Path aPath;

        for (const auto &actionData : actionDataList)
        {
            auto it = lastAMap->map.find(actionData.name);
            if (it == lastAMap->map.end())
            {
                auto &menuItem = crateSubMenu(actionData.label);

                auto ret = lastAMap->map.insert( { actionData.name, ActionMap(menuItem.get_submenu()) } );
                ct_assert_tn(ret.second);

                lastAMap->menuShell->append(menuItem);
                it = ret.first;
            }

            lastAMap = &boost::get<ActionMap>(it->second);
            aPath += actionData.name;
        }

        if (!action)
        {
            auto &menuItem = clGtkmm::makeManagedRef<Gtk::SeparatorMenuItem>();
            lastAMap->menuShell->append(menuItem);
            menuItem.show();
        }
        else
        {
            auto name = action->get_name();
            auto &menuItem = createActionMItem(action);
            lastAMap->menuShell->append(menuItem);
            aPath.add(name);

            auto strPath = aPath.getStringRep();

            action->signal_activate().connect_notify([this, strPath, eventExecuter]
            {
                postFun("signal '" + strPath + "' activated:", [this, strPath, eventExecuter]
                {
                    execute_event_tn(actionExecuted)(strPath);
                });
            });

            ct_assert_tn(lastAMap->map.insert({ name, &menuItem }).second);
        }
    }


    connection::MainWindow::CProviderUPtr connection::MainWindow::create(module_args_ex)
    {
        return std::make_unique<impl::MainWindow>(module_pass_args_ex);
    }
}
MY_NSP_END
