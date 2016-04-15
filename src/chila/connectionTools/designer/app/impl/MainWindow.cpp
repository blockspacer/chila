/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <gdkmm-2.4/gdkmm/window.h>
#include <gdkmm-2.4/gdkmm/cursor.h>
#include "MainWindow.hpp"
#include <stdlib.h>
#include <algorithm>
#include <boost/preprocessor.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <chila/lib/misc/util.hpp>
#include <boost/cast.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "../../lib/actions.hpp"
#include "../../lib/TextProperty.hpp"
#include <boost/range/adaptors.hpp>
#include <boost/range.hpp>
#include "../../lib/util.hpp"
#include <boost/algorithm/string.hpp>

#include <chila/lib/misc/QueuePoster.hpp>

#include <chila/lib/misc/macrosExp.hpp>
#include <gtkmm-2.4/gtkmm/treeiter.h>
#include <pangomm-1.4/pangomm/fontdescription.h>
#include <pangomm-1.4/pangomm/attributes.h>
#include <gtk-2.0/gdk/gdkevents.h>
#include <sigc++-2.0/sigc++/connection.h>
#include <gtkmm-2.4/gtkmm/selectiondata.h>
#include <gtkmm-2.4/gtkmm/action.h>

#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

MY_NSP_START
{
    MainWindow::MainWindow(boost::asio::io_service &ioService, const boost::filesystem::path &gladeFile, bool showFunEvents) try :
        ioService(ioService),
        kit(0, NULL),
        builder(Gtk::Builder::create_from_file(gladeFile.string())),
        navListCursor(navList.end()),
        showIndent(0),
        showFunEvents(showFunEvents),
        textOver(false),
        shouldRefreshFlow(true)
    {
        connector.bindActions(*this);

        my_get_widget(mainWindow);
        my_get_widget(designTree);
        my_get_widget(flowTree);
        my_get_widget(setValueDialog);
        my_get_widget(setValueTView);
        my_get_widget(outputText);
        my_get_widget(toolbar);
        my_get_widget(notebook);

        my_get_action(undo);
        my_get_action(redo);
        my_get_action(goBack);
        my_get_action(goForward);
        my_get_action(save);
        my_get_action(moveUp);
        my_get_action(moveDown);

        designData.tree = widgets.designTree;
        flowData.tree = widgets.flowTree;
    }
    catch (const Gtk::BuilderError &ex)
    {
        std::cerr << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    void MainWindow::initToolBar(ev_executer_arg(launcher_start))
    {
        add_toolbar_button(save);
        add_toolbar_button(moveUp);
        add_toolbar_button(moveDown);

//        add_toolbar_button(undo);
//        add_toolbar_button(redo);
//        add_toolbar_button(goBack);
//        add_toolbar_button(goForward);

        widgets.toolbar->show_all();
    }

    Gtk::MenuItem *findChild(Gtk::Menu &parent, const std::string &name)
    {
        for (auto &child : parent.items())
        {
            if (child.get_name() == name)
                return &child;
        }

        return nullptr;
    }

    void MainWindow::addMenuItems(const chila::lib::misc::Path &nodePath, const lib::ActionMap &actionMap,
            Gtk::Menu &parent, ev_executer_arg(showActions))
    {
        for (const auto &vt : actionMap)
        {
            const auto &name = vt.first;
            const auto &value = vt.second;

            if (auto *child = findChild(parent, name))
            {
                if (auto map = std::dynamic_pointer_cast<const lib::ActionMap>(value))
                {
                    addMenuItems(nodePath, *map, *chila::lib::misc::checkNotNull(child->get_submenu()), eventExecuter);
                }
                else abort();
            }
            else
            {
                auto &item = *Gtk::manage(new Gtk::MenuItem(name));
                parent.append(item);
                if (auto action = std::dynamic_pointer_cast<const lib::ActionWithPos>(value))
                {
                    addPosibilities(nodePath, item, action, action->posibilities, "", eventExecuter);
                }
                else if (auto action = std::dynamic_pointer_cast<const lib::Action>(value))
                {
                    item.signal_event().connect_notify(
                        [this, nodePath, action, eventExecuter](GdkEvent *event)
                        {
                            menuItem(event, nodePath, action, "", eventExecuter);
                        });
                }
                else if (auto map = std::dynamic_pointer_cast<const lib::ActionMap>(value))
                {
                    auto &sm = *Gtk::manage(new Gtk::Menu());
                    item.set_submenu(sm);

                    addMenuItems(nodePath, *map, sm, eventExecuter);
                }
                else abort();
            }
        }
    }

    void MainWindow::addPosibilities(
        const chila::lib::misc::Path &nodePath,
        Gtk::MenuItem &item,
        const lib::ActionWithPosSCPtr &action,
        const cclTree::ValueVec &valueVec,
        const std::string &value,
        ev_executer_arg(showActions))
    {
        auto &sm = *Gtk::manage(new Gtk::Menu());
        item.set_submenu(sm);

        for (const auto &entry : valueVec)
        {
            auto &posItem = *Gtk::manage(new Gtk::MenuItem(entry.value));
            sm.append(posItem);
            auto val = value.empty() ? entry.value : value + "." + entry.value;

            if (entry.subValues.empty())
            {
                posItem.signal_event().connect_notify([this, nodePath, action, val, eventExecuter](GdkEvent *event)
                {
                    menuItem(event, nodePath, action, val, eventExecuter);
                });
            }
            else
            {
                addPosibilities(nodePath, posItem, action, entry.subValues, val, eventExecuter);
            }
        }
    }

    void MainWindow::MOD_ACTION_SIG(showActions)
    {
        MenuMap menuMap;

        if (!actionList->empty())
        {
            popupMenu = std::make_shared<Gtk::Menu>();
            addMenuItems(nodePath, *actionList, *popupMenu, eventExecuter);

            popupMenu->show_all();
            popupMenu->popup(lastEventButton.button, lastEventButton.time);
        }
    }

    // workaround 'item->signal_activate' not working for submenu items issue
    template <typename EventExecuter>
    void MainWindow::menuItem(GdkEvent *event, const chila::lib::misc::Path &nodePath, const lib::ActionSCPtr &action,
            const std::string &value, const EventExecuter &eventExecuter)
    {
        if (event->type == GDK_BUTTON_RELEASE)
            actionSelected(nodePath, action, value, eventExecuter);
    }

    template <typename EventExecuter>
    void MainWindow::actionSelected(const chila::lib::misc::Path &nodePath, const lib::ActionSCPtr &action,
            const std::string &value, const EventExecuter &eventExecuter)
    {
        if (auto awv = std::dynamic_pointer_cast<const lib::ActionWithValue>(action))
        {
            widgets.setValueTView->get_buffer()->set_text(awv->current);

            if (dialogRespConn)
                dialogRespConn.disconnect();

            dialogRespConn = widgets.setValueDialog->signal_response().connect_notify(
                [=](int response)
                {
                    widgets.setValueDialog->hide();

                    if (response == 0)
                    {
                        std::string text = widgets.setValueTView->get_buffer()->get_text();
                        boost::trim(text);
                        execute_event_tn(actionRequest)(nodePath, lib::ActionSCPtr(action), text);
                    }
                });

            widgets.setValueDialog->show();
        }
        else
        {
            execute_event_tn(actionRequest)(nodePath, lib::ActionSCPtr(action), value);
        }
    }

    void MainWindow::MOD_ACTION_SIG(renameNode)
    {
//        auto it = designData.pathMap.find(nodePath);
//        my_assert(it != designData.pathMap.end());
//
//        auto rowDataTmp = it->second->second;
//        designData.rowMap.erase(it);
//
//        rowDataTmp.value = nodeId;
//        rowDataTmp.row[designData.columnRecord.value] = nodeId;
//
//        auto newPath = nodePath;
//        newPath.pop();
//        newPath += nodeId;
//
//        my_assert(designData.rowMap.insert(RowMap::value_type(newPath, rowDataTmp)).second);
    }

    void MainWindow::MOD_ACTION_SIG(addNode)
    {
        addNodePrv(designData, nodePath, value, false);
    }

    void MainWindow::MOD_ACTION_SIG(removeNode)
    {
        auto it = designData.rowMap.find(nodePath);
        my_assert(it != designData.rowMap.end());

        auto &rowData = it->second;

        designData.treeStore->erase(rowData.row);

        auto range = lib::getParentAndChildren(it, designData.rowMap.end(), nodePath);

        designData.rowMap.erase(boost::begin(range), boost::end(range));

        shouldRefreshFlow = true;
    }

    void MainWindow::MOD_ACTION_SIG(removeChildren)
    {
        auto it = designData.rowMap.find(nodePath);
        my_assert(it != designData.rowMap.end());

        auto pRow = it->second.row;;
        auto range = lib::getParentAndChildren(++it, designData.rowMap.end(), nodePath);
        designData.rowMap.erase(boost::begin(range), boost::end(range));

        auto children = pRow->children();
        auto end = children.end();

        for (auto it = children.begin(); it != end; it = designData.treeStore->erase(it));

        shouldRefreshFlow = true;
    }

    void MainWindow::MOD_ACTION_SIG(setNodeValue)
    {
        auto it = designData.rowMap.find(nodePath);
        my_assert(it != designData.rowMap.end());
        auto &data = it->second;
        data.value = value;

        data.row[designData.columnRecord.value] = value;

        shouldRefreshFlow = true;
    }

    template <typename EventExecuter>
    void MainWindow::updateFlowSelection(const EventExecuter &eventExecuter)
    {
        auto it = widgets.flowTree->get_selection()->get_selected();
        if (!it) return;

        auto &row = *it;

        auto nodePath = (chila::lib::misc::Path) row[flowData.columnRecord.id];

        lastFlowSelection = nodePath;

        execute_event_tn(flowNodeSelected)(nodePath);
    };

    template <typename EventExecuter>
    void MainWindow::exandNodePath(const EventExecuter &eventExecuter)
    {
        auto it = widgets.flowTree->get_selection()->get_selected();
        if (!it) return;

        auto &row = *it;

        lastFlowSelection = row[flowData.columnRecord.id];

        auto nodePath = (chila::lib::misc::Path) row[flowData.columnRecord.id];

        execute_event_tn(expandFlowNode)(nodePath);

        expandedFlowNodes.insert(nodePath);

        refreshFlowNodes(eventExecuter);
    };


    void MainWindow::MOD_ACTION_SIG(launcher_start)
    {
        designData.treeStore = Gtk::TreeStore::create(designData.columnRecord);
        widgets.designTree->set_model(designData.treeStore);

        auto *renderer = Gtk::manage(new Gtk::CellRendererText());
        renderer->property_font() = "monospace";
        auto *tvColumn = Gtk::manage(new Gtk::TreeView::Column("value", *renderer));
        tvColumn->add_attribute(renderer->property_markup(), designData.columnRecord.value);
        widgets.designTree->append_column(*tvColumn);

        flowData.treeStore = Gtk::TreeStore::create(flowData.columnRecord);
        widgets.flowTree->set_model(flowData.treeStore);
        auto *flowRenderer = Gtk::manage(new Gtk::CellRendererText());
        auto *ftvColumn = Gtk::manage(new Gtk::TreeView::Column("value", *flowRenderer));
        ftvColumn->add_attribute(flowRenderer->property_markup(), flowData.columnRecord.value);
        widgets.flowTree->append_column(*ftvColumn);

        widgets.outputText->modify_font(Pango::FontDescription("monospace"));

        widgets.setValueTView->modify_font(Pango::FontDescription("monospace"));

        widgets.outputText->signal_event().connect_notify(
             [this](GdkEvent *event)
             {
                if (event->type == GDK_MOTION_NOTIFY)
                {
                    if (textOver)
                        textOver = false;
                    else
                        updateTextTagUnder();
                }
             });

        widgets.designTree->signal_button_release_event().connect_notify(
            [this, eventExecuter](GdkEventButton *event)
            {
                auto it = widgets.designTree->get_selection()->get_selected();
                if (!it) return;

                auto &row = *it;

                auto path = (chila::lib::misc::Path) row[designData.columnRecord.id];

                my_assert(!path.empty());

                if (event->button == 3)
                {
                    lastEventButton = *event;

                    execute_event(actionListRequired)(path);
                }
            });

        widgets.flowTree->signal_row_expanded().connect_notify(
            [this, eventExecuter](const Gtk::TreeModel::iterator &it, const Gtk::TreeModel::Path &rowPath)
            {
                const Gtk::TreeModel::Row &row = *it;

                clMisc::Path path = row[flowData.columnRecord.id];
                my_assert(expandedFlowNodes.insert(path).second);
            });

        widgets.flowTree->signal_row_collapsed().connect_notify(
            [this, eventExecuter](const Gtk::TreeModel::iterator &it, const Gtk::TreeModel::Path &rowPath)
            {
                const Gtk::TreeModel::Row &row = *it;

                clMisc::Path id = row[flowData.columnRecord.id];

                auto begin = expandedFlowNodes.find(id), end = begin;
                my_assert(begin != expandedFlowNodes.end());

                for (++end; end != expandedFlowNodes.end() && end->startsWith(id); ++end);

                expandedFlowNodes.erase(begin, end);
            });

        widgets.flowTree->signal_button_release_event().connect_notify(
            [this, eventExecuter](GdkEventButton *event)
            {
                switch (event->button)
                {
                    case 1:
                        updateFlowSelection(eventExecuter);
                        break;

                    case 3:
                        CHILA_LIB_MISC__SHOW(40, "yes");
                        exandNodePath(eventExecuter);
                        break;

                    default:
                        break;
                }
            });

        widgets.flowTree->signal_row_activated().connect_notify(
            [this, eventExecuter](const Gtk::TreeModel::Path &path, const Gtk::TreeView::Column*)
            {
//                const Gtk::TreeModel::Row &row = *flowData.treeStore->get_iter(path);
//                clMisc::Path designNodePath = row[flowData.columnRecord.related];
//
//                auto fit = flowData.rowMap.find(designNodePath);
//                my_assert(fit != flowData.rowMap.end());
//
//                auto &toRow = fit->second.row;
//                widgets.flowTree->expand_to_path(flowData.treeStore->get_path(toRow));
//                widgets.flowTree->get_selection()->select(toRow);
//                updateFlowSelection(eventExecuter);
            });

        widgets.notebook->signal_switch_page().connect_notify(
            [this, eventExecuter](GtkNotebookPage *widget, guint pageNum)
            {
                widgets.outputText->get_buffer()->set_text("");

                switch(pageNum)
                {
                    case 0:
                        widgets.outputText->set_wrap_mode(Gtk::WRAP_NONE);
                        execute_event(checkNodes)();
                        break;

                    case 1:
                        widgets.outputText->set_wrap_mode(Gtk::WRAP_WORD);
                        if (shouldRefreshFlow)
                        {
                            refreshFlowNodes(eventExecuter);
                        }
                        else
                        {
                            updateFlowSelection(eventExecuter);
                        }
                        break;

                    default:
                        abort();
                        break;
                }
            });

        auto getSelectedNodePath = [this]()
        {
            auto it = widgets.designTree->get_selection()->get_selected();
            if (!it) return chila::lib::misc::Path();

            auto &row = *it;

            return (chila::lib::misc::Path) row[designData.columnRecord.id];
        };

        actions.save->signal_activate().connect_notify([this, eventExecuter] { execute_event(saveRequest)(); });
        actions.moveUp->signal_activate().connect_notify([this, getSelectedNodePath, eventExecuter]
        {
            execute_event(moveUpRequest)(getSelectedNodePath());
        });

        actions.moveDown->signal_activate().connect_notify([this, getSelectedNodePath, eventExecuter]
        {
            execute_event(moveDownRequest)(getSelectedNodePath());
        });

        widgets.mainWindow->signal_hide().connect_notify(boost::bind(boost::ref(connector.actions.launcher_finish)));

        initToolBar(eventExecuter);


        widgets.mainWindow->show_all();

        execute_event(launcher_started)();
    }

    void MainWindow::MOD_ACTION_SIG(saveDesignTreeState)
    {
        expandedDesignNodes.clear();

        saveDesignTreeStatePrv(widgets.designTree->get_model()->children());
    }

    void MainWindow::saveDesignTreeStatePrv(const Gtk::TreeNodeChildren &children)
    {
        auto &tree = *widgets.designTree;
        auto model = tree.get_model();

        for (auto &row : children)
        {
            if (tree.row_expanded(model->get_path(row))) // TODO Maybe it's better looking for the 'visibe' childs
            {
                auto rowChildren = row->children();

                expandedDesignNodes.insert(row[designData.columnRecord.id]);
                saveDesignTreeStatePrv(rowChildren);
            }
        }
    }


    void MainWindow::MOD_ACTION_SIG(restoreDesignTreeState)
    {
        auto &tree = *widgets.designTree;
        auto model = tree.get_model();

        for (auto &path : expandedDesignNodes)
        {
            auto it = designData.rowMap.find(path);
            if (it != designData.rowMap.end())
            {
                tree.expand_to_path(model->get_path(it->second.row));
            }
        }
    }


    template <typename EventExecuter>
    void MainWindow::refreshFlowNodes(const EventExecuter &eventExecuter)
    {
        shouldRefreshFlow = false;
        flowData.treeStore->clear();

        flowNodesToExpand = expandedFlowNodes;
        expandedFlowNodes.clear();
        flowData.rowMap.clear();
        execute_event_tn(flowNodesRequired)();
    }

    void MainWindow::MOD_ACTION_SIG(waitEvent)
    {
        timer = std::make_shared<boost::asio::deadline_timer>(boost::ref(ioService));
        setTimer();

        eventEx = std::make_shared<EventEx>(eventExecuter);
    }

    void MainWindow::setTimer()
    {
        if (!timer) return;

        static boost::function<void(const boost::system::error_code &)> fun(
            boost::bind(&MainWindow::timerExpired, this, _1));
        timer->expires_from_now(boost::posix_time::milliseconds(10));
        timer->async_wait(fun);
    }

    void MainWindow::timerExpired(const boost::system::error_code &ec)
    {
        if (ec) return;

        while (kit.events_pending())
            kit.iteration(false);

        setTimer();
    }

    void MainWindow::MOD_ACTION_SIG(launcher_finish)
    {
        timer.reset();

        execute_event(launcher_finished)();
    }

    connection::MainWindow::CProviderSPtr connection::MainWindow::create(boost::asio::io_service &ioService,
        const boost::filesystem::path &gladeFile, bool showFunEvents)
    {
        return std::make_shared<app::impl::MainWindow>(boost::ref(ioService), gladeFile, showFunEvents);
    }

    void MainWindow::MOD_ACTION_SIG(actionNotPerformed)
    {
        errorDialog = std::make_shared<Gtk::MessageDialog>(boost::ref(*widgets.mainWindow),
                errorText, true, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);

        errorDialog->signal_response().connect([this](int response) { errorDialog->hide(); });
        errorDialog->show();
    }

    void MainWindow::updateTextTagUnder(const Glib::RefPtr<Gtk::TextTag> &currTag)
    {
        static Gdk::Cursor handCursor(Gdk::CursorType::HAND1);
        static Gdk::Cursor textCursor(Gdk::CursorType::LAST_CURSOR );

        if (lastTTagUnder)
            lastTTagUnder->property_underline() = Pango::UNDERLINE_NONE;

        if (currTag)
        {
            currTag->property_underline() = Pango::UNDERLINE_SINGLE;
            widgets.outputText->get_window(Gtk::TextWindowType::TEXT_WINDOW_TEXT)->set_cursor(handCursor);
        }
        else
        {
            widgets.outputText->get_window(Gtk::TextWindowType::TEXT_WINDOW_TEXT)->set_cursor(textCursor);
        }

        lastTTagUnder = currTag;
    }

    void MainWindow::MOD_ACTION_SIG(addOutputText)
    {
        auto buffer = widgets.outputText->get_buffer();

        if (textProperties)
        {
            auto tag = Gtk::TextTag::create();
            for (auto &prop : *textProperties)
            {
                if (auto *typed = dynamic_cast<const lib::textProperty::NodePath*>(prop.get()))
                {
                    auto &path = typed->path;

                    tag->signal_event().connect_notify(
                        [this, path, tag](const Glib::RefPtr<Glib::Object> &object, GdkEvent *event, const Gtk::TextIter &it)
                        {
                            switch (event->type)
                            {
                                case GDK_BUTTON_PRESS:
                                    selectNodePv(path, true, true);
                                    break;

                                case GDK_MOTION_NOTIFY:
                                    updateTextTagUnder(tag);
                                    textOver = true;
                                    break;

                                default:
                                    break;
                            }
                        });
                }
                else if (auto *typed = dynamic_cast<const lib::textProperty::Color*>(prop.get()))
                {
                    Gdk::Color color;
                    color.set_rgb_p(typed->red / 100, typed->green / 100, typed->blue / 100);
                    tag->property_foreground_gdk() = color;
                }
                else if (auto *typed = dynamic_cast<const lib::textProperty::Underline*>(prop.get()))
                {
                    tag->property_underline() = Pango::UNDERLINE_SINGLE;
                }
                else if (auto *typed = dynamic_cast<const lib::textProperty::Italic*>(prop.get()))
                {
                    tag->property_style() = Pango::STYLE_ITALIC;
                }
                else if (auto *typed = dynamic_cast<const lib::textProperty::Bold*>(prop.get()))
                {
                    tag->property_weight() = Pango::WEIGHT_BOLD;
                }
            }

            buffer->get_tag_table()->add(tag);
            buffer->insert_with_tag(buffer->end(), outputText, tag);
        }
        else
        {
            buffer->insert(buffer->end(), outputText);
        }

        widgets.outputText->queue_draw();
    }

    void MainWindow::MOD_ACTION_SIG(clearOutput)
    {
        auto buffer = widgets.outputText->get_buffer();
        buffer->set_text("");
        widgets.outputText->queue_draw();

    }

    void MainWindow::MOD_ACTION_SIG(selectNode)
    {
        selectNodePv(nodePath, true, openNode);
    }

    void MainWindow::selectNodePv(const chila::lib::misc::Path &nodePath, bool addNav, bool openNode)
    {
        widgets.notebook->set_current_page(0);

        auto it = designData.rowMap.find(nodePath);
        my_assert(it != designData.rowMap.end());

        auto &rowData = it->second;

        Gtk::TreePath tPath(rowData.row);
        Gtk::TreePath tpPath(rowData.row.parent());

        widgets.designTree->expand_to_path(openNode ? tPath : tpPath);
        widgets.designTree->set_cursor(tPath);
    }

    void MainWindow::addNavigation(const chila::lib::misc::Path &path)
    {
        if (navListCursor != navList.end())
        {
            if (*navListCursor == path) return;
            navList.erase(++navListCursor, navList.end());
        }

        navList.push_back(path);
        navListCursor = navList.end();
        --navListCursor;
    }

    void MainWindow::appendFlowEmptyNode(const Gtk::TreeModel::Row &row)
    {
        auto expRow = *(flowData.treeStore->append(row.children()));
        expRow[flowData.columnRecord.id] = ":empty:";
        expRow[flowData.columnRecord.value] = "empty";
    }

    void MainWindow::MOD_ACTION_SIG(addFlowNode)
    {
        addNodePrv(flowData, nodePath, value, isExpandable);
    }

    void MainWindow::addNodePrv(
            TreeData &data,
            const clMisc::Path &nodePath,
            const std::string &value,
            bool appendEmpty)
    {
        Gtk::TreeModel::Row row;
        auto parentPath = nodePath;
        auto id = parentPath.top();
        parentPath.pop();

        if (parentPath.empty())
        {
            row = *(data.treeStore->append());
        }
        else
        {
            auto it = data.rowMap.find(parentPath);
            my_assert(it != data.rowMap.end());

            auto &pRow = it->second.row;

//            if (position == std::numeric_limits<unsigned>::max())
//            {
//                row = *(designData.treeStore->append(it->second.row.children()));
//            }
//            else
//            {
//                auto children = it->second.row.children().begin();
//                std::advance(children, position);
//                row = *(designData.treeStore->insert(children));
//            }

            // Remove any "empty" node
            if (pRow.children().size() == 1)
            {
                auto &child = *pRow.children().begin();

                if (clMisc::Path(child[data.columnRecord.id]) == ":empty:")
                    row = *child;
            }

            if (!row)
                row = *(data.treeStore->append(pRow.children()));
        }

        if (appendEmpty)
            appendFlowEmptyNode(row);

        row[data.columnRecord.id] = nodePath;
        row[data.columnRecord.value] = value;

        auto insRet = data.rowMap.insert({nodePath, row});
        my_assert(insRet.second);

        data.tree->queue_draw();
    }

    void MainWindow::MOD_ACTION_SIG(noMoreFlowNodes)
    {
        if (!flowNodesToExpand.empty())
        {
            for (auto &path : flowNodesToExpand)
            {
                auto it = flowData.rowMap.find(path);
                if (it != flowData.rowMap.end())
                {
                    widgets.flowTree->expand_row(flowData.treeStore->get_path(it->second.row), false);
                }
            }

            flowNodesToExpand.clear();
        }

        if (!lastFlowSelection.empty())
        {
            auto it = flowData.rowMap.find(lastFlowSelection);
            if (it != flowData.rowMap.end())
            {
                auto &row = it->second.row;

                widgets.flowTree->get_selection()->select(row);

                updateFlowSelection(eventExecuter);
            }
        }
    }
}
MY_NSP_END

