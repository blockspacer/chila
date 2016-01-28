/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__LOGGER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/call_traits.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <string>

#include <boost/mpl/set.hpp>
#include <chila/connectionTools/lib/codegen/ActionImplExecuter.hpp>
#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <chila/connectionTools/lib/codegen/EventExecuter.hpp>
#include <chila/connectionTools/lib/codegen/Connector.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define MY_BIND_ACTION(name, argCount) \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name, argCount)
#define DEF_CONNECTOR_ARGUMENT CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENT
#define DEF_CONNECTOR_FUNCTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTION
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK

// Arguments defines
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ARGS_Logger \
    (clientId)(recvBuffer)(sndBuffer)(errorMsg)(moduleName)


// Event defines
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENTS_Logger \
    (dummy)(starting)(started)(deactivating)(deactivated) \
    (finishing)(finished)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_dummy \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_starting \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_started \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_deactivating \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_deactivated \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_finishing \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_finished \


// Action defines
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTIONS_Logger \
    (start)(deactivate)(finish)(moduleStarted)(clientConnected) \
    (clientDisconnected)(connectionError)(msgReceived)(msgProcessed)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_start \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_deactivate \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_finish \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_moduleStarted \
    (moduleName)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_clientConnected \
    (clientId)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_clientDisconnected \
    (clientId)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_connectionError \
    (clientId)(errorMsg)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_msgReceived \
    (clientId)(recvBuffer)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_msgProcessed \
    (clientId)(sndBuffer)


// Actions' called events
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_start \
    (started)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_deactivate \
    (deactivated)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_finish \
    (finished)

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_moduleStarted \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_clientConnected \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_clientDisconnected \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_connectionError \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_msgReceived \

#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_msgProcessed \


CHILA_LIB_MISC__DEF_NAMESPACE(7, (chila,connectionTools,appTest2,impl,logger,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct Logger final: public chila::connectionTools::lib::codegen::ConnectorImpl<Logger<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.appTest2.impl.logger.connectors.gen.Logger"; }

        typedef Logger Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, Logger)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, EVENT, Logger)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, EVENT, Logger)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, ACTION, Logger)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, ACTION, Logger)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_CONNECTORS_GEN, Logger) {}
        } actions;


        Logger() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(start, 0);
            MY_BIND_ACTION(deactivate, 0);
            MY_BIND_ACTION(finish, 0);
            MY_BIND_ACTION(moduleStarted, 1);
            MY_BIND_ACTION(clientConnected, 1);
            MY_BIND_ACTION(clientDisconnected, 1);
            MY_BIND_ACTION(connectionError, 2);
            MY_BIND_ACTION(msgReceived, 2);
            MY_BIND_ACTION(msgProcessed, 2);
        }
    };
}}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
