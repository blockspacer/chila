/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN_APPLICATION_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN_APPLICATION_HPP

#include <boost/mpl/map.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <chila/connectionTools/lib/codegen/util.hpp>
#include <chila/connectionTools/lib/codegen/ArgumentProviderCreator.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define APROVIDER_CREATOR CHILA_CONNECTIONTOOLS_LIB_CODEGEN__APROVIDER_CREATOR
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK
#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include <chila/lib/misc/macrosDef.hpp>

DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,connectors,gen))
{
    template <typename Connectors>
    struct Application
    {
        // ArgAliases
        struct ArgAliases
        {
            DEF_ARG_ALIAS(clientId);
            DEF_ARG_ALIAS(errorMsg);
            DEF_ARG_ALIAS(moduleName);
            DEF_ARG_ALIAS(procMessage);
            DEF_ARG_ALIAS(recvBuffer);
            DEF_ARG_ALIAS(sndBuffer);
        };

        // Logger
        struct LoggerDesc
        {
            typedef typename Connectors::Logger Connector;

            // arg --> alias
            typedef boost::mpl::map
            <
                DEF_ARG_ALIAS_LINK(clientId, clientId),
                DEF_ARG_ALIAS_LINK(errorMsg, errorMsg),
                DEF_ARG_ALIAS_LINK(moduleName, moduleName),
                DEF_ARG_ALIAS_LINK(recvBuffer, recvBuffer),
                DEF_ARG_ALIAS_LINK(sndBuffer, sndBuffer)
            > ArgAliasLinks;
        };

        // MessageProcessor
        struct MessageProcessorDesc
        {
            typedef typename Connectors::MessageProcessor Connector;

            // arg --> alias
            typedef boost::mpl::map
            <
                DEF_ARG_ALIAS_LINK(moduleName, moduleName),
                DEF_ARG_ALIAS_LINK(procMessage, procMessage),
                DEF_ARG_ALIAS_LINK(result, sndBuffer)
            > ArgAliasLinks;
        };

        // Network
        struct NetworkDesc
        {
            typedef typename Connectors::Network Connector;

            // arg --> alias
            typedef boost::mpl::map
            <
                DEF_ARG_ALIAS_LINK(clientId, clientId),
                DEF_ARG_ALIAS_LINK(errorMsg, errorMsg),
                DEF_ARG_ALIAS_LINK(moduleName, moduleName),
                DEF_ARG_ALIAS_LINK(recvBuffer, recvBuffer),
                DEF_ARG_ALIAS_LINK(sndBuffer, sndBuffer)
            > ArgAliasLinks;
        };

        // ConnectorDescMap
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename Connectors::Logger, LoggerDesc>,
            boost::mpl::pair<typename Connectors::MessageProcessor, MessageProcessorDesc>,
            boost::mpl::pair<typename Connectors::Network, NetworkDesc>
        > ConnectorDescMap;

        // networkNameProv
        #define networkNameProvDef APROVIDER_CREATOR \
        (                                                             \
            args.providers.networkNameProv,                                          \
            ,                                                         \
            (moduleName)                                              \
        )

        // procMessageCreator
        #define procMessageCreatorDef APROVIDER_CREATOR \
        (                                                             \
            args.providers.procMessageCreator,                                       \
            (clientId)(recvBuffer),                                   \
            (procMessage)                                             \
        )

        // procMessageReaderPC
        #define procMessageReaderPCDef APROVIDER_CREATOR \
        (                                                             \
            args.providers.procMessageReaderPC,                                      \
            (procMessage),                                            \
            (clientId)                                                \
        )

        // processingNameProv
        #define processingNameProvDef APROVIDER_CREATOR \
        (                                                             \
            args.providers.processingNameProv,                                       \
            ,                                                         \
            (moduleName)                                              \
        )

        template <typename Args>
        static void connect(const Args &args)
        {
            // logger
            // messageProcessor
            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.messageProcessor.events.messageProcessed,
                boost::fusion::make_vector(procMessageReaderPCDef),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.msgProcessed,
                    args.connectors.network.actions.sendMessage
                )
            );

            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.messageProcessor.events.started,
                boost::fusion::make_vector(processingNameProvDef),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.moduleStarted
                )
            );

            // network
            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.network.events.clientConnected,
                boost::fusion::make_vector(),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.clientConnected
                )
            );

            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.network.events.clientDisconnected,
                boost::fusion::make_vector(),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.clientDisconnected
                )
            );

            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.network.events.msgReceived,
                boost::fusion::make_vector(procMessageCreatorDef),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.msgReceived,
                    args.connectors.messageProcessor.actions.processMessage
                )
            );

            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>
            (
                args.connectors.network.events.started,
                boost::fusion::make_vector(networkNameProvDef),
                boost::fusion::make_vector
                (
                    args.connectors.logger.actions.moduleStarted,
                    args.connectors.messageProcessor.actions.start
                )
            );

        }
        #undef networkNameProvDef
        #undef procMessageCreatorDef
        #undef procMessageReaderPCDef
        #undef processingNameProvDef
    };
}}}}}}

#include <chila/lib/misc/macrosUndef.hpp>
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>

#undef DEF_NAMESPACE
#undef APROVIDER_CREATOR
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK
#undef MT_CODEGEN_NSP

#endif
