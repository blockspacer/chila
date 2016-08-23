/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__MESSAGEPROCESSOR_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__MESSAGEPROCESSOR_HPP

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
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ARGS_MessageProcessor \
    (procMessage)(result)(moduleName)


// Event defines
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_MessageProcessor \
    (started)(messageProcessed)

#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MessageProcessor_started \

#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MessageProcessor_messageProcessed \
    (result)(procMessage)


// Action defines
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_MessageProcessor \
    (start)(processMessage)

#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MessageProcessor_start \

#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MessageProcessor_processMessage \
    (procMessage)


// Actions' called events
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MessageProcessor_start \
    (started)

#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MessageProcessor_processMessage \
    (messageProcessed)


CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct MessageProcessor final: public chila::connectionTools::lib::codegen::ConnectorImpl<MessageProcessor<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.appTest.app.connectors.gen.MessageProcessor"; }

        typedef MessageProcessor Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, MessageProcessor)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, EVENT, MessageProcessor)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, EVENT, MessageProcessor)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, ACTION, MessageProcessor)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, ACTION, MessageProcessor)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN, MessageProcessor) {}
        } actions;


        MessageProcessor() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(start, 0);
            MY_BIND_ACTION(processMessage, 1);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
