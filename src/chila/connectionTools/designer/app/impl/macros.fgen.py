#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         ccloUtil.getCToolsMacros('CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN') + \
           [['my_assert',                       'CHILA_LIB_MISC__ASSERT'],
            ['LAST_NODE',                       'std::numeric_limits<unsigned>::max()'],
            ['if_is_mtl_node(Name)',            'if (auto *typed = dynamic_cast<const cclTree::Name*>(&node))'],
            ['catch_inv_state_tf',              'CHILA_CONNECTIONTOOLS_LIB_OTHER__CATCH_INV_STATE_TF'],
            ['check_state(...)',                'catch_inv_state_tf( checkState({__VA_ARGS__},           __func__, __FILE__, __LINE__) )'],
            ['check_state_lm(mutex, ...)',      'catch_inv_state_tf( checkStateLM(mutex, {__VA_ARGS__},  __func__, __FILE__, __LINE__) )'],
            ['set_state(state)',                'catch_inv_state_tf( setState(state,                     __func__, __FILE__, __LINE__) )'],
            ['set_state_lm(mutex, state)',      'catch_inv_state_tf( setState(mutex, state,              __func__, __FILE__, __LINE__) )'],
            ['my_assert',                       'CHILA_LIB_MISC__ASSERT'],
            ['ipss',                            'PY_COM_PERSONAL_LIB_MISC__IPSS'],
            ['ipss_end',                        'PY_COM_PERSONAL_LIB_MISC__IPSS_END'],
            ['FWDEC_SPTR',                      'CHILA_LIB_MISC__FWDEC_SPTR'],

            ['str_stream(exp)',                 'CHILA_LIB_MISC__STRINGSTREAM("<span font=\\"monospace\\">" << exp << "</span>")'],

            ['node_if_dcast(Type, node)',       'if (auto *typedNode = dynamic_cast<Type*>(node))'],

            ['bptr_cast(Type, data)',           'if (boost::shared_ptr<const Type> typedNode = boost::dynamic_pointer_cast<const Type>(data))'],

            ['show_error_info(out, Type, name, extended)',' \
                    if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
                        out << "- " << name << ": " << (extended ? "\n" : "[") << *value << (extended ? "" : "]\n") << std::flush;'],

            ['create_action(Name)',             'boost::make_shared<lib::actions::Name>()'],
            ['create_action_wp(Name, ...)',     'boost::make_shared<lib::actions::Name>(__VA_ARGS__)'],

            ['cast_load_action_wp_typed(Type, Action)',' \
                    node_if_dcast(const Type, &node) \
                    { \
                        loadAction<lib::actions::Action>(*actionMap, node); \
                    }'],

            ['cast_load_action_np_typed(Type, Action)',' \
                    node_if_dcast(const Type, &node) \
                    { \
                        actionMap->addAction<lib::actions::Action>(); \
                    }'],

            ['cast_load_actions_cont(Type, ContSuffix)',' \
                    node_if_dcast(const Type##ContSuffix, &node) \
                    { \
                        loadContainerOfTyped(*actionMap, node); \
                    } \
                    else node_if_dcast(const Type, &node) \
                    { \
                        actionMap->addAction<lib::actions::Remove>(); \
                        actionMap->addAction<lib::actions::MoveUp>(); \
                        actionMap->addAction<lib::actions::MoveDown>(); \
                        actionMap->addAction<lib::actions::Cut>(); \
                    }'],

            ['cast_load_actions_cont_grouped(Type, ContSuffix)',' \
                    node_if_dcast(const Type##ContSuffix, &node) \
                    { \
                        loadContainerOfTyped(*actionMap, node); \
                    } \
                    else node_if_dcast(const Type##Group, &node) \
                    { \
                        loadContainerOfTyped(*actionMap, typedNode->elements()); \
                        actionMap->addAction<lib::actions::Remove>(); \
                        actionMap->addAction<lib::actions::MoveUp>(); \
                        actionMap->addAction<lib::actions::MoveDown>(); \
                        actionMap->addAction<lib::actions::Cut>(); \
                    } \
                    else node_if_dcast(const Type, &node) \
                    { \
                        actionMap->addAction<lib::actions::Remove>(); \
                        actionMap->addAction<lib::actions::MoveUp>(); \
                        actionMap->addAction<lib::actions::MoveDown>(); \
                        actionMap->addAction<lib::actions::Cut>(); \
                    }'],

            ['mu_cdata(exp)',           '"<![CDATA[" << exp << "]]>"'],
            ['mu_bold(exp)',            '"<b>" << exp << "</b>"'],
            ['mu_italic(exp)',          '"<i>" << exp << "</i>"'],
            ['mu_fcolor(color, exp)',   '"<span foreground=\\"" << color << "\\">" << exp << "</span>"'],

            ['MU_LLGRAY',   '"#a0a0a0"'],
            ['MU_LGRAY',    '"#808080"'],
            ['MU_DGREEN',   '"#008000"'],
            ['MU_DDGREEN',  '"#004000"'],
            ['MU_DBLUE',    '"#000080"'],
            ['MU_DDBLUE',   '"#000040"'],
            ['MU_BLUE',     '"#0000ff"'],
            ['MU_LBLUE',    '"#8080ff"'],
            ['MU_DYELLOW',  '"#808000"'],
            ['MU_DDYELLOW', '"#404000"'],
            ['MU_DRED',     '"#c00000"'],
            ['MU_DMAGENTA', '"#c000c0"'],
            ['MU_DDMAGENTA','"#800080"'],
            ['MU_DDRED',    '"#800000"'],
            ['MU_LRED',     '"#ff8080"'],
            ['MU_BLACK',    '"#000000"'],

            ['my_get_widget(name)',
                    'builder->get_widget(BOOST_PP_STRINGIZE(name), widgets.name); \
                     my_assert(widgets.name)'],

            ['post_to_queue_bind_na(method)',
                    'chila::lib::misc::queuePoster(boost::ref(ioService), boost::bind(&MainWindow::method, this))'],

            ['post_to_queue_bind_wa(method, ...)',
                    'chila::lib::misc::queuePoster(boost::ref(ioService), boost::bind(&MainWindow::method, this, __VA_ARGS__))'],

            ['my_get_action(name)',
                    'actions.name = Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object(#name "Action")); \
                    my_assert(actions.name);'],

            ['add_toolbar_button(name)',
                    '{ \
                        Gtk::ToolButton *button = Gtk::manage(new Gtk::ToolButton(actions.name->get_stock_id())); \
                        button->signal_clicked().connect_notify([this, eventExecuter]{ actions.name->activate(); }); \
                        widgets.toolbar->append(*button); \
                     }']]

clmUtil.generateMacrosDefUndef(macros, [], ['MODULE_NAME'])

