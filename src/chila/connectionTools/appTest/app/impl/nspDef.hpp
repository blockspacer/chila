/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/misc/macrosExp.hpp>

#define MY_NSP chila,connectionTools,appTest,app,impl

#define MY_NSP_START      CHILA_LIB_MISC__DEF_NAMESPACE_VAR(MY_NSP)
#define MY_NSP_END    CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(MY_NSP)

#ifdef MODULE_NAME
    #define MOD_ACTION_SIG(action) CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(\
        CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, MODULE_NAME, action)
#endif

#define execute_event       CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT
#define execute_event_tn    CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN
#define call_ev_fatal         CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL

#define ev_executer_arg     CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_ARG
#define ev_executer_type    CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_TYPE

#define my_assert           CHILA_LIB_MISC__ASSERT

