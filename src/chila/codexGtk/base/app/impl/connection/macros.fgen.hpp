#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codexGtk/base/app/impl/connection/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codexGtk,base,app,impl,connection)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codexGtk,base,app,impl,connection)

    #define execute_event \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT

    #define execute_event_tn \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN

    #define call_ev_fatal \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL

    #define call_ev_fatal_tn \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_TN

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
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, MODULE_NAME, action)

    #define APROV_DEF_PROVIDER_BASE_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov)

    #define APROV_DEF_PROVIDER_BASE_FOR_WC(prov, customArgs) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR_WC(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov, customArgs)

    #define APROV_CONS_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov)

    #define APROV_PASS_REQ_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FOR(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov)

    #define APROV_DEF_CREATOR_WITH_ARGS(prov, argSeq) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov, argSeq)

    #define APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(prov) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov)

    #define APROVIDER_DEC \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC

    #define DEF_APC_ENCAPSULATOR_CR(creatorName, readerName, EncType) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CR(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, creatorName, readerName, EncType)

    #define APROVIDER_DEC_EX(prov, customArgs) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(CHILA_CODEX_BASE_APP_CONNECTORS_GEN, prov, customArgs)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define NSP \
        CHILA_CODEX_BASE_APP_CONNECTORS_GEN

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define FWDEC_SPTR \
        CHILA_LIB_MISC__FWDEC_SPTR

    #define dec_my_cons_prov \
        PY_COM_PERSONAL_APPLICATION_LIB__DEC_CONS_PROV

    #define dec_custom_prov \
        PY_COM_PERSONAL_APPLICATION_LIB__DEC_CUSTOM_PROV

    #define module_args_ex \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(CHILA_CODEX_BASE_APP_IMPL_CONNECTION, MODULE_NAME)

    #define DEF_CPROVIDER(ConnectorName) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_CPROVIDER(connectors::gen::ConnectorName<ArgTypes>)

    #define my_get_connector(Type) \
        Type::CProvider::Connector

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef execute_event
    #undef execute_event_tn
    #undef call_ev_fatal
    #undef call_ev_fatal_tn
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
    #undef NSP
    #undef app_assert
    #undef FWDEC_SPTR
    #undef dec_my_cons_prov
    #undef dec_custom_prov
    #undef module_args_ex
    #undef DEF_CPROVIDER
    #undef my_get_connector

#endif

