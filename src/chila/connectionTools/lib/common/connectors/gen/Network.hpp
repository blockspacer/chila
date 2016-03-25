// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__NETWORK_HPP
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__NETWORK_HPP

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
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ARGS_Network \
    (clientId) \
    (recvBuffer) \
    (sndBuffer) \
    (errorMsg) \
    (endpoint) \
    (address) \
    (host)

// Event defines
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENTS_Network \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (clientAccepted) \
    (msgRead) \
    (msgWritten) \
    (responseDiscarded) \
    (clientError) \
    (clientDisconnected) \
    (endpointResolved) \
    (fatalError) \
    (resolvedAllowedAddress) \
    (clientHostResolved)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_starting \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_started \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_deactivating \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_deactivated \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_finishing \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_launcher_finished \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_clientAccepted \
    (clientId)(endpoint)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_msgRead \
    (clientId)(recvBuffer)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_msgWritten \
    (clientId)(sndBuffer)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_responseDiscarded \
    (clientId)(sndBuffer)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_clientError \
    (clientId)(errorMsg)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_clientDisconnected \
    (clientId)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_endpointResolved \
    (endpoint)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_fatalError \
    (errorMsg)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_resolvedAllowedAddress \
    (address)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_Network_clientHostResolved \
    (clientId)(host)

// Action defines
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTIONS_Network \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (write) \
    (closeSession)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Network_launcher_start \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Network_launcher_deactivate \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Network_launcher_finish \

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Network_write \
    (clientId)(sndBuffer)
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_Network_closeSession \
    (clientId)

// Actions' called events
#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Network_launcher_start \
    (launcher_started)(resolvedAllowedAddress)(fatalError)(endpointResolved)(clientHostResolved)(clientAccepted)(clientDisconnected)(clientError)(msgRead)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Network_launcher_deactivate \
    (launcher_deactivated)(fatalError)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Network_launcher_finish \
    (launcher_finished)(fatalError)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Network_write \
    (msgWritten)(responseDiscarded)(clientDisconnected)(clientError)(fatalError)

#define CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_Network_closeSession \
    (fatalError)


CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,lib,common,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct Network final: public chila::connectionTools::lib::codegen::ConnectorImpl<Network<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.lib.common.connectors.gen.Network"; }

        typedef Network Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, Network)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, EVENT, Network)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, EVENT, Network)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, ACTION, Network)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, ACTION, Network)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_LIB_COMMON_CONNECTORS_GEN, Network) {}
        } actions;


        Network() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(write);
            MY_BIND_ACTION(closeSession);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
