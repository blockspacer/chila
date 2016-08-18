#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/designer/app/impl/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,designer,app,impl)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,designer,app,impl)

    #define execute_event \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT

    #define execute_event_tn \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN

    #define call_ev_fatal \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL

    #define ct_assert \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT

    #define ct_assert_tn \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT_TN

    #define ev_executer_arg \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_ARG

    #define ev_executer_type \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_TYPE

    #define catch_inv_state_tf \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CATCH_INV_STATE_TF

    #define check_state(...) \
        catch_inv_state_tf( checkState({__VA_ARGS__},           __func__, __FILE__, __LINE__) )

    #define check_state_lm(mutex, ...) \
        catch_inv_state_tf( checkStateLM(mutex, {__VA_ARGS__},  __func__, __FILE__, __LINE__) )

    #define set_state(state) \
        catch_inv_state_tf( setState(state,                     __func__, __FILE__, __LINE__) )

    #define set_state_lm(mutex, state) \
        catch_inv_state_tf( setState(mutex, state,              __func__, __FILE__, __LINE__) )

    #define MOD_ACTION_SIG(action) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, MODULE_NAME, action)

    #define APROV_DEF_PROVIDER_BASE_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov)

    #define APROV_DEF_PROVIDER_BASE_FOR_WC(prov, customArgs) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR_WC(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov, customArgs)

    #define APROV_CONS_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov)

    #define APROV_PASS_REQ_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FOR(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov)

    #define APROV_DEF_CREATOR_WITH_ARGS(prov, argSeq) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov, argSeq)

    #define APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov)

    #define APROVIDER_DEC \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC

    #define DEF_APC_ENCAPSULATOR_CR(creatorName, readerName, EncType) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CR(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, creatorName, readerName, EncType)

    #define APROVIDER_DEC_EX(prov, customArgs) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, prov, customArgs)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define LAST_NODE \
        std::numeric_limits<unsigned>::max()

    #define if_is_mtl_node(Name) \
        if (auto *typed = dynamic_cast<const cclTree::Name*>(&node))

    #define catch_inv_state_tf \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CATCH_INV_STATE_TF

    #define check_state(...) \
        catch_inv_state_tf( checkState({__VA_ARGS__},           __func__, __FILE__, __LINE__) )

    #define check_state_lm(mutex, ...) \
        catch_inv_state_tf( checkStateLM(mutex, {__VA_ARGS__},  __func__, __FILE__, __LINE__) )

    #define set_state(state) \
        catch_inv_state_tf( setState(state,                     __func__, __FILE__, __LINE__) )

    #define set_state_lm(mutex, state) \
        catch_inv_state_tf( setState(mutex, state,              __func__, __FILE__, __LINE__) )

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define ipss \
        PY_COM_PERSONAL_LIB_MISC__IPSS

    #define ipss_end \
        PY_COM_PERSONAL_LIB_MISC__IPSS_END

    #define FWDEC_SPTR \
        CHILA_LIB_MISC__FWDEC_SPTR

    #define str_stream(exp) \
        CHILA_LIB_MISC__STRINGSTREAM("<span font=\"monospace\">" << exp << "</span>")

    #define node_if_dcast(Type, node) \
        if (auto *typedNode = dynamic_cast<Type*>(node))

    #define bptr_cast(Type, data) \
        if (auto typedNode = std::dynamic_pointer_cast<const Type>(data))

    #define show_error_info(out, Type, name, extended) \
                             if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex))                         out << "- " << name << ": " << (extended ? " \
        " : "[") << *value << (extended ? "" : "] \
        ") << std::flush;

    #define create_action(Name) \
        std::make_shared<lib::actions::Name>()

    #define create_action_wp(Name, ...) \
        std::make_shared<lib::actions::Name>(__VA_ARGS__)

    #define cast_load_action_wp_typed(Type, Action) \
                             node_if_dcast(const Type, &node)                     {                         loadAction<lib::actions::Action>(*actionMap, node);                     }

    #define cast_load_action_np_typed(Type, Action) \
                             node_if_dcast(const Type, &node)                     {                         actionMap->addAction<lib::actions::Action>().current = typedNode->value;                     }

    #define cast_load_actions_cont(Type, ContSuffix) \
                             node_if_dcast(const Type##ContSuffix, &node)                     {                         loadContainerOfTyped(*actionMap, node);                     }                     else node_if_dcast(const Type, &node)                     {                         actionMap->addAction<lib::actions::Remove>();                         actionMap->addAction<lib::actions::MoveUp>();                         actionMap->addAction<lib::actions::MoveDown>();                         actionMap->addAction<lib::actions::Cut>();                     }

    #define cast_load_actions_cont_grouped(Type, ContSuffix) \
                             node_if_dcast(const Type##ContSuffix, &node)                     {                         loadContainerOfTyped(*actionMap, node);                     }                     else node_if_dcast(const Type##Group, &node)                     {                         loadContainerOfTyped(*actionMap, typedNode->elements());                         actionMap->addAction<lib::actions::Remove>();                         actionMap->addAction<lib::actions::MoveUp>();                         actionMap->addAction<lib::actions::MoveDown>();                         actionMap->addAction<lib::actions::Cut>();                     }                     else node_if_dcast(const Type, &node)                     {                         actionMap->addAction<lib::actions::Remove>();                         actionMap->addAction<lib::actions::MoveUp>();                         actionMap->addAction<lib::actions::MoveDown>();                         actionMap->addAction<lib::actions::Cut>();                     }

    #define mu_cdata(exp) \
        "<![CDATA[" << exp << "]]>"

    #define mu_bold(exp) \
        "<b>" << exp << "</b>"

    #define mu_italic(exp) \
        "<i>" << exp << "</i>"

    #define mu_fcolor(color, exp) \
        "<span foreground=\"" << color << "\">" << exp << "</span>"

    #define MU_LLGRAY \
        "#a0a0a0"

    #define MU_LGRAY \
        "#808080"

    #define MU_DGREEN \
        "#008000"

    #define MU_DDGREEN \
        "#004000"

    #define MU_DBLUE \
        "#000080"

    #define MU_DDBLUE \
        "#000040"

    #define MU_BLUE \
        "#0000ff"

    #define MU_LBLUE \
        "#8080ff"

    #define MU_DYELLOW \
        "#808000"

    #define MU_DDYELLOW \
        "#404000"

    #define MU_DRED \
        "#c00000"

    #define MU_DMAGENTA \
        "#c000c0"

    #define MU_DDMAGENTA \
        "#800080"

    #define MU_DDRED \
        "#800000"

    #define MU_LRED \
        "#ff8080"

    #define MU_BLACK \
        "#000000"

    #define my_get_widget(name) \
        builder->get_widget(BOOST_PP_STRINGIZE(name), widgets.name);                      my_assert(widgets.name)

    #define post_to_queue_bind_na(method) \
        chila::lib::misc::queuePoster(boost::ref(ioService), boost::bind(&MainWindow::method, this))

    #define post_to_queue_bind_wa(method, ...) \
        chila::lib::misc::queuePoster(boost::ref(ioService), boost::bind(&MainWindow::method, this, __VA_ARGS__))

    #define my_get_action(name) \
        actions.name = Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object(#name "Action"));                     my_assert(actions.name);

    #define add_toolbar_button(name) \
        {                         Gtk::ToolButton *button = Gtk::manage(new Gtk::ToolButton(actions.name->get_stock_id()));                         button->signal_clicked().connect_notify([this, eventExecuter]{ actions.name->activate(); });                         widgets.toolbar->append(*button);                      }

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef execute_event
    #undef execute_event_tn
    #undef call_ev_fatal
    #undef ct_assert
    #undef ct_assert_tn
    #undef ev_executer_arg
    #undef ev_executer_type
    #undef catch_inv_state_tf
    #undef check_state
    #undef check_state_lm
    #undef set_state
    #undef set_state_lm
    #undef MOD_ACTION_SIG
    #undef APROV_DEF_PROVIDER_BASE_FOR
    #undef APROV_DEF_PROVIDER_BASE_FOR_WC
    #undef APROV_CONS_PARAMS_FOR
    #undef APROV_PASS_REQ_PARAMS_FOR
    #undef APROV_DEF_CREATOR_WITH_ARGS
    #undef APROV_COMMA_IF_HAS_CONS_PARAMS_FOR
    #undef APROVIDER_DEC
    #undef DEF_APC_ENCAPSULATOR_CR
    #undef APROVIDER_DEC_EX
    #undef my_assert
    #undef LAST_NODE
    #undef if_is_mtl_node
    #undef catch_inv_state_tf
    #undef check_state
    #undef check_state_lm
    #undef set_state
    #undef set_state_lm
    #undef my_assert
    #undef ipss
    #undef ipss_end
    #undef FWDEC_SPTR
    #undef str_stream
    #undef node_if_dcast
    #undef bptr_cast
    #undef show_error_info
    #undef create_action
    #undef create_action_wp
    #undef cast_load_action_wp_typed
    #undef cast_load_action_np_typed
    #undef cast_load_actions_cont
    #undef cast_load_actions_cont_grouped
    #undef mu_cdata
    #undef mu_bold
    #undef mu_italic
    #undef mu_fcolor
    #undef MU_LLGRAY
    #undef MU_LGRAY
    #undef MU_DGREEN
    #undef MU_DDGREEN
    #undef MU_DBLUE
    #undef MU_DDBLUE
    #undef MU_BLUE
    #undef MU_LBLUE
    #undef MU_DYELLOW
    #undef MU_DDYELLOW
    #undef MU_DRED
    #undef MU_DMAGENTA
    #undef MU_DDMAGENTA
    #undef MU_DDRED
    #undef MU_LRED
    #undef MU_BLACK
    #undef my_get_widget
    #undef post_to_queue_bind_na
    #undef post_to_queue_bind_wa
    #undef my_get_action
    #undef add_toolbar_button
    #undef MODULE_NAME

#endif

