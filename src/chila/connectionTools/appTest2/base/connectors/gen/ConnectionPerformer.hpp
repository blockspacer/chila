/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/mpl/set.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/call_traits.hpp>
#include <boost/fusion/container/vector.hpp>
#include <chila/lib/misc/Path.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <chila/connectionTools/lib/codegen/convert.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define CREATE_ARG          CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_ARG
#define CREATE_APROVIDER    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_APROVIDER
#define PASS_ARG            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_PASS_ARG
#define EXECUTE_ACTION      CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_EXECUTE_ACTION
#define GET_ARGUMENT        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_GET_ARGUMENT


// ------------------------------- Argument aliases utility macros ------------------------------------
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARG_ALIAS_SEQ \
    (clientId) \
    (recvBuffer) \
    (sndBuffer) \
    (errorMsg) \
    (moduleName) \
    (procMessage)

// ----------------------------- ConnectorAliases utility macros ----------------------------------
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONN_ALIAS_SEQ \
    (Network)(Logger)(MessageProcessor)

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_Network \
    ((clientId)(clientId)) \
    ((recvBuffer)(recvBuffer)) \
    ((sndBuffer)(sndBuffer)) \
    ((errorMsg)(errorMsg)) \
    ((moduleName)(moduleName))

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_Logger \
    ((clientId)(clientId)) \
    ((recvBuffer)(recvBuffer)) \
    ((sndBuffer)(sndBuffer)) \
    ((errorMsg)(errorMsg)) \
    ((moduleName)(moduleName))

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_MessageProcessor \
    ((procMessage)(procMessage)) \
    ((result)(sndBuffer)) \
    ((moduleName)(moduleName))



// ----------------------------- ArgumentProvider utility macros ---------------------------------------
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__APCREATORS_SEQ \
    (networkNameProv)(processingNameProv)(procMessageCreator)(procMessageReaderPC)

// networkNameProv
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_RARG_SEQ_networkNameProv

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_PARG_SEQ_networkNameProv \
    (moduleName)

// processingNameProv
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_RARG_SEQ_processingNameProv

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_PARG_SEQ_processingNameProv \
    (moduleName)

// procMessageCreator
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_RARG_SEQ_procMessageCreator \
    (clientId)(recvBuffer)

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_PARG_SEQ_procMessageCreator \
    (procMessage)

// procMessageReaderPC
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_RARG_SEQ_procMessageReaderPC \
    (procMessage)

#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARGPROV_PARG_SEQ_procMessageReaderPC \
    (clientId)

// ----------------------------- Connector instances utility macros ---------------------------------------
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__CONN_INSTANCE_SEQ \
    ((Logger)(logger)) \
    ((MessageProcessor)(messageProcessor)) \
    ((Network)(network))

// -------------------------------------- Namespace start ----------------------------------------------
#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,appTest2,base,connectors,gen))
{
    using chila::connectionTools::lib::codegen::actionExecuter;

    template <typename ArgTypes, typename Connectors>
    struct ConnectionPerformer
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.appTest2.base.connectors.gen.ConnectionPerformer"; }

        // ArgAliases
        struct ArgAliases
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES(CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTORS_GEN__ARG_ALIAS_SEQ)
        };

        // network_started ---------------------------------------------------------------------------------------------------------
        struct Tag_network_started {};

        template
        <
            typename APC_networkNameProv,
            typename Action_logger_moduleStarted,
            typename Action_network_acceptClient
        >
        struct Ex_network_started
        {
            typedef void result_type;

            APC_networkNameProv apc_networkNameProv;
            Action_logger_moduleStarted act_logger_moduleStarted;
            Action_network_acceptClient act_network_acceptClient;

            Ex_network_started
            (
                const APC_networkNameProv &apc_networkNameProv,
                const Action_logger_moduleStarted &act_logger_moduleStarted,
                const Action_network_acceptClient &act_network_acceptClient
            ) :
                apc_networkNameProv(apc_networkNameProv),
                act_logger_moduleStarted(act_logger_moduleStarted),
                act_network_acceptClient(act_network_acceptClient)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    networkNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleStarted
                EXECUTE_ACTION
                (
                    logger, moduleStarted,
                    PASS_ARG(logger, moduleStarted, moduleName, GET_ARGUMENT(networkNameProv, moduleName))
                );

                // network.actions.acceptClient
                EXECUTE_ACTION
                (
                    network, acceptClient,
                );

            }
        };

        template
<
            typename APC_networkNameProv,
            typename Action_logger_moduleStarted,
            typename Action_network_acceptClient
        >
        inline static Ex_network_started
        <
            APC_networkNameProv,
            Action_logger_moduleStarted,
            Action_network_acceptClient
        >
        ex_network_started
        (
            const APC_networkNameProv &apc_networkNameProv,
            const Action_logger_moduleStarted &act_logger_moduleStarted,
            const Action_network_acceptClient &act_network_acceptClient
        )
        {
            return Ex_network_started
            <
                APC_networkNameProv,
                Action_logger_moduleStarted,
                Action_network_acceptClient
            >
            (
                apc_networkNameProv,
                act_logger_moduleStarted,
                act_network_acceptClient
            );
        }

        // network_clientConnected -------------------------------------------------------------------------------------------------
        struct Tag_network_clientConnected {};

        template
        <
            typename Action_logger_clientConnected,
            typename Action_network_acceptClient,
            typename Action_network_readMessage
        >
        struct Ex_network_clientConnected
        {
            typedef void result_type;

            Action_logger_clientConnected act_logger_clientConnected;
            Action_network_acceptClient act_network_acceptClient;
            Action_network_readMessage act_network_readMessage;

            Ex_network_clientConnected
            (
                const Action_logger_clientConnected &act_logger_clientConnected,
                const Action_network_acceptClient &act_network_acceptClient,
                const Action_network_readMessage &act_network_readMessage
            ) :
                act_logger_clientConnected(act_logger_clientConnected),
                act_network_acceptClient(act_network_acceptClient),
                act_network_readMessage(act_network_readMessage)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &clientId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(clientId, clientId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // logger.actions.clientConnected
                EXECUTE_ACTION
                (
                    logger, clientConnected,
                    PASS_ARG(logger, clientConnected, clientId, clientId)
                );

                // network.actions.acceptClient
                EXECUTE_ACTION
                (
                    network, acceptClient,
                );

                // network.actions.readMessage
                EXECUTE_ACTION
                (
                    network, readMessage,
                    PASS_ARG(network, readMessage, clientId, clientId)
                );

            }
        };

        template
<
            typename Action_logger_clientConnected,
            typename Action_network_acceptClient,
            typename Action_network_readMessage
        >
        inline static Ex_network_clientConnected
        <
            Action_logger_clientConnected,
            Action_network_acceptClient,
            Action_network_readMessage
        >
        ex_network_clientConnected
        (
            const Action_logger_clientConnected &act_logger_clientConnected,
            const Action_network_acceptClient &act_network_acceptClient,
            const Action_network_readMessage &act_network_readMessage
        )
        {
            return Ex_network_clientConnected
            <
                Action_logger_clientConnected,
                Action_network_acceptClient,
                Action_network_readMessage
            >
            (
                act_logger_clientConnected,
                act_network_acceptClient,
                act_network_readMessage
            );
        }

        // network_clientDisconnected ----------------------------------------------------------------------------------------------
        struct Tag_network_clientDisconnected {};

        template
        <
            typename Action_logger_clientDisconnected
        >
        struct Ex_network_clientDisconnected
        {
            typedef void result_type;

            Action_logger_clientDisconnected act_logger_clientDisconnected;

            Ex_network_clientDisconnected
            (
                const Action_logger_clientDisconnected &act_logger_clientDisconnected
            ) :
                act_logger_clientDisconnected(act_logger_clientDisconnected)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &clientId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(clientId, clientId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // logger.actions.clientDisconnected
                EXECUTE_ACTION
                (
                    logger, clientDisconnected,
                    PASS_ARG(logger, clientDisconnected, clientId, clientId)
                );

            }
        };

        template
<
            typename Action_logger_clientDisconnected
        >
        inline static Ex_network_clientDisconnected
        <
            Action_logger_clientDisconnected
        >
        ex_network_clientDisconnected
        (
            const Action_logger_clientDisconnected &act_logger_clientDisconnected
        )
        {
            return Ex_network_clientDisconnected
            <
                Action_logger_clientDisconnected
            >
            (
                act_logger_clientDisconnected
            );
        }

        // network_connectionError -------------------------------------------------------------------------------------------------
        struct Tag_network_connectionError {};

        template
        <
            typename Action_logger_connectionError
        >
        struct Ex_network_connectionError
        {
            typedef void result_type;

            Action_logger_connectionError act_logger_connectionError;

            Ex_network_connectionError
            (
                const Action_logger_connectionError &act_logger_connectionError
            ) :
                act_logger_connectionError(act_logger_connectionError)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &clientId_in,
                const InArg1 &errorMsg_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(clientId, clientId);
                CREATE_ARG(errorMsg, errorMsg);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // logger.actions.connectionError
                EXECUTE_ACTION
                (
                    logger, connectionError,
                    PASS_ARG(logger, connectionError, clientId, clientId),
                    PASS_ARG(logger, connectionError, errorMsg, errorMsg)
                );

            }
        };

        template
<
            typename Action_logger_connectionError
        >
        inline static Ex_network_connectionError
        <
            Action_logger_connectionError
        >
        ex_network_connectionError
        (
            const Action_logger_connectionError &act_logger_connectionError
        )
        {
            return Ex_network_connectionError
            <
                Action_logger_connectionError
            >
            (
                act_logger_connectionError
            );
        }

        // network_msgReceived -----------------------------------------------------------------------------------------------------
        struct Tag_network_msgReceived {};

        template
        <
            typename APC_procMessageCreator,
            typename Action_logger_msgReceived,
            typename Action_messageProcessor_processMessage,
            typename Action_network_readMessage
        >
        struct Ex_network_msgReceived
        {
            typedef void result_type;

            APC_procMessageCreator apc_procMessageCreator;
            Action_logger_msgReceived act_logger_msgReceived;
            Action_messageProcessor_processMessage act_messageProcessor_processMessage;
            Action_network_readMessage act_network_readMessage;

            Ex_network_msgReceived
            (
                const APC_procMessageCreator &apc_procMessageCreator,
                const Action_logger_msgReceived &act_logger_msgReceived,
                const Action_messageProcessor_processMessage &act_messageProcessor_processMessage,
                const Action_network_readMessage &act_network_readMessage
            ) :
                apc_procMessageCreator(apc_procMessageCreator),
                act_logger_msgReceived(act_logger_msgReceived),
                act_messageProcessor_processMessage(act_messageProcessor_processMessage),
                act_network_readMessage(act_network_readMessage)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &clientId_in,
                const InArg1 &recvBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(clientId, clientId);
                CREATE_ARG(recvBuffer, recvBuffer);

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    procMessageCreator,
                    clientId,
                    recvBuffer
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.msgReceived
                EXECUTE_ACTION
                (
                    logger, msgReceived,
                    PASS_ARG(logger, msgReceived, clientId, clientId),
                    PASS_ARG(logger, msgReceived, recvBuffer, recvBuffer)
                );

                // messageProcessor.actions.processMessage
                EXECUTE_ACTION
                (
                    messageProcessor, processMessage,
                    PASS_ARG(messageProcessor, processMessage, procMessage, GET_ARGUMENT(procMessageCreator, procMessage))
                );

                // network.actions.readMessage
                EXECUTE_ACTION
                (
                    network, readMessage,
                    PASS_ARG(network, readMessage, clientId, clientId)
                );

            }
        };

        template
<
            typename APC_procMessageCreator,
            typename Action_logger_msgReceived,
            typename Action_messageProcessor_processMessage,
            typename Action_network_readMessage
        >
        inline static Ex_network_msgReceived
        <
            APC_procMessageCreator,
            Action_logger_msgReceived,
            Action_messageProcessor_processMessage,
            Action_network_readMessage
        >
        ex_network_msgReceived
        (
            const APC_procMessageCreator &apc_procMessageCreator,
            const Action_logger_msgReceived &act_logger_msgReceived,
            const Action_messageProcessor_processMessage &act_messageProcessor_processMessage,
            const Action_network_readMessage &act_network_readMessage
        )
        {
            return Ex_network_msgReceived
            <
                APC_procMessageCreator,
                Action_logger_msgReceived,
                Action_messageProcessor_processMessage,
                Action_network_readMessage
            >
            (
                apc_procMessageCreator,
                act_logger_msgReceived,
                act_messageProcessor_processMessage,
                act_network_readMessage
            );
        }

        // messageProcessor_started ------------------------------------------------------------------------------------------------
        struct Tag_messageProcessor_started {};

        template
        <
            typename APC_processingNameProv,
            typename Action_logger_moduleStarted
        >
        struct Ex_messageProcessor_started
        {
            typedef void result_type;

            APC_processingNameProv apc_processingNameProv;
            Action_logger_moduleStarted act_logger_moduleStarted;

            Ex_messageProcessor_started
            (
                const APC_processingNameProv &apc_processingNameProv,
                const Action_logger_moduleStarted &act_logger_moduleStarted
            ) :
                apc_processingNameProv(apc_processingNameProv),
                act_logger_moduleStarted(act_logger_moduleStarted)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    processingNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleStarted
                EXECUTE_ACTION
                (
                    logger, moduleStarted,
                    PASS_ARG(logger, moduleStarted, moduleName, GET_ARGUMENT(processingNameProv, moduleName))
                );

            }
        };

        template
<
            typename APC_processingNameProv,
            typename Action_logger_moduleStarted
        >
        inline static Ex_messageProcessor_started
        <
            APC_processingNameProv,
            Action_logger_moduleStarted
        >
        ex_messageProcessor_started
        (
            const APC_processingNameProv &apc_processingNameProv,
            const Action_logger_moduleStarted &act_logger_moduleStarted
        )
        {
            return Ex_messageProcessor_started
            <
                APC_processingNameProv,
                Action_logger_moduleStarted
            >
            (
                apc_processingNameProv,
                act_logger_moduleStarted
            );
        }

        // messageProcessor_messageProcessed ---------------------------------------------------------------------------------------
        struct Tag_messageProcessor_messageProcessed {};

        template
        <
            typename APC_procMessageReaderPC,
            typename Action_logger_msgProcessed,
            typename Action_network_sendMessage
        >
        struct Ex_messageProcessor_messageProcessed
        {
            typedef void result_type;

            APC_procMessageReaderPC apc_procMessageReaderPC;
            Action_logger_msgProcessed act_logger_msgProcessed;
            Action_network_sendMessage act_network_sendMessage;

            Ex_messageProcessor_messageProcessed
            (
                const APC_procMessageReaderPC &apc_procMessageReaderPC,
                const Action_logger_msgProcessed &act_logger_msgProcessed,
                const Action_network_sendMessage &act_network_sendMessage
            ) :
                apc_procMessageReaderPC(apc_procMessageReaderPC),
                act_logger_msgProcessed(act_logger_msgProcessed),
                act_network_sendMessage(act_network_sendMessage)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &result_in,
                const InArg1 &procMessage_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(procMessage, procMessage);
                CREATE_ARG(result, sndBuffer);

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    procMessageReaderPC,
                    procMessage
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.msgProcessed
                EXECUTE_ACTION
                (
                    logger, msgProcessed,
                    PASS_ARG(logger, msgProcessed, clientId, GET_ARGUMENT(procMessageReaderPC, clientId)),
                    PASS_ARG(logger, msgProcessed, sndBuffer, sndBuffer)
                );

                // network.actions.sendMessage
                EXECUTE_ACTION
                (
                    network, sendMessage,
                    PASS_ARG(network, sendMessage, clientId, GET_ARGUMENT(procMessageReaderPC, clientId)),
                    PASS_ARG(network, sendMessage, sndBuffer, sndBuffer)
                );

            }
        };

        template
<
            typename APC_procMessageReaderPC,
            typename Action_logger_msgProcessed,
            typename Action_network_sendMessage
        >
        inline static Ex_messageProcessor_messageProcessed
        <
            APC_procMessageReaderPC,
            Action_logger_msgProcessed,
            Action_network_sendMessage
        >
        ex_messageProcessor_messageProcessed
        (
            const APC_procMessageReaderPC &apc_procMessageReaderPC,
            const Action_logger_msgProcessed &act_logger_msgProcessed,
            const Action_network_sendMessage &act_network_sendMessage
        )
        {
            return Ex_messageProcessor_messageProcessed
            <
                APC_procMessageReaderPC,
                Action_logger_msgProcessed,
                Action_network_sendMessage
            >
            (
                apc_procMessageReaderPC,
                act_logger_msgProcessed,
                act_network_sendMessage
            );
        }

        // ConnInstances -----------------------------------------------------------------------------------------------------------
        struct ConnInstances
        {
            typename Connectors::Network &network;
            typename Connectors::MessageProcessor &messageProcessor;
            typename Connectors::Logger &logger;

            ConnInstances(const chila::connectionTools::lib::codegen::ConnectorMap &cMap) :
                network(cMap.get<typename Connectors::Network>("network")),
                messageProcessor(cMap.get<typename Connectors::MessageProcessor>("messageProcessor")),
                logger(cMap.get<typename Connectors::Logger>("logger"))
            {}
        };

        // network -----------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_network(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.network.events.started
                = ex_network_started
            (
                providers.networkNameProv
                ,
                actionExecuter<Tag_network_started, 0>(cInstances.logger.actions.moduleStarted),
                actionExecuter<Tag_network_started, 1>(cInstances.network.actions.acceptClient)
            );
            cInstances.network.events.clientConnected
                = ex_network_clientConnected
            (
                actionExecuter<Tag_network_clientConnected, 0>(cInstances.logger.actions.clientConnected),
                actionExecuter<Tag_network_clientConnected, 1>(cInstances.network.actions.acceptClient),
                actionExecuter<Tag_network_clientConnected, 2>(cInstances.network.actions.readMessage)
            );
            cInstances.network.events.clientDisconnected
                = ex_network_clientDisconnected
            (
                actionExecuter<Tag_network_clientDisconnected, 0>(cInstances.logger.actions.clientDisconnected)
            );
            cInstances.network.events.connectionError
                = ex_network_connectionError
            (
                actionExecuter<Tag_network_connectionError, 0>(cInstances.logger.actions.connectionError)
            );
            cInstances.network.events.msgReceived
                = ex_network_msgReceived
            (
                providers.procMessageCreator
                ,
                actionExecuter<Tag_network_msgReceived, 0>(cInstances.logger.actions.msgReceived),
                actionExecuter<Tag_network_msgReceived, 1>(cInstances.messageProcessor.actions.processMessage),
                actionExecuter<Tag_network_msgReceived, 2>(cInstances.network.actions.readMessage)
            );
        }

        // messageProcessor --------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_messageProcessor(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.messageProcessor.events.started
                = ex_messageProcessor_started
            (
                providers.processingNameProv
                ,
                actionExecuter<Tag_messageProcessor_started, 0>(cInstances.logger.actions.moduleStarted)
            );
            cInstances.messageProcessor.events.messageProcessed
                = ex_messageProcessor_messageProcessed
            (
                providers.procMessageReaderPC
                ,
                actionExecuter<Tag_messageProcessor_messageProcessed, 0>(cInstances.logger.actions.msgProcessed),
                actionExecuter<Tag_messageProcessor_messageProcessed, 1>(cInstances.network.actions.sendMessage)
            );
        }

        // logger ------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_logger(ConnInstances &cInstances, const Providers &providers)
        {
        }

        template <typename Args>
        static void connect(const Args &args)
        {
            ConnInstances cInstances(args.cMap);

            connect_network(cInstances, args.providers);
            connect_messageProcessor(cInstances, args.providers);
            connect_logger(cInstances, args.providers);
        }
    };

}}}}}}



#undef APROVIDER_CREATOR
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK
#undef MAKE_ACTION_VEC
#undef CREATE_ARG
#undef CREATE_APROVIDER
#undef EXECUTE_ACTION
#undef PASS_ARG
#undef GET_ARGUMENT
#endif
