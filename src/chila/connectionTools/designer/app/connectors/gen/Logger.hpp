// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__LOGGER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/call_traits.hpp>
#include <boost/function.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <string>

#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <chila/connectionTools/lib/codegen/EventExecuter.hpp>
#include <chila/connectionTools/lib/codegen/Connector.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define MY_BIND_ACTION(name) \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name)
#define DEF_CONNECTOR_ARGUMENT CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENT
#define DEF_CONNECTOR_FUNCTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTION
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK

// Arguments defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ARGS_Logger \
    (moduleName) \
    (cToolsPath)

// Event defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_Logger \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_starting \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_started \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_deactivating \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_deactivated \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_finishing \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Logger_launcher_finished \


// Action defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_Logger \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (moduleStarted) \
    (moduleFinished) \
    (connectorLoaded) \
    (cPerformerLoaded)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_launcher_start \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_launcher_deactivate \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_launcher_finish \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_moduleStarted \
    (moduleName)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_moduleFinished \
    (moduleName)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_connectorLoaded \
    (cToolsPath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Logger_cPerformerLoaded \
    (cToolsPath)

// Actions' called events
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_launcher_start \
    (launcher_started)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_launcher_deactivate \
    (launcher_deactivated)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_launcher_finish \
    (launcher_finished)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_moduleStarted \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_moduleFinished \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_connectorLoaded \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Logger_cPerformerLoaded \



CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,designer,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct Logger final: public chila::connectionTools::lib::codegen::ConnectorImpl<Logger<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.designer.app.connectors.gen.Logger"; }

        typedef Logger Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, Logger)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, Logger)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, Logger)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, Logger)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, Logger)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, Logger) {}
        } actions;


        Logger() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(moduleStarted);
            MY_BIND_ACTION(moduleFinished);
            MY_BIND_ACTION(connectorLoaded);
            MY_BIND_ACTION(cPerformerLoaded);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
