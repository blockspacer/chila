/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP

#include "../../connectors/gen/ConnectionPerformer.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "Logger.hpp"
#include "Network.hpp"
#include "MessageProcessor.hpp"
#include "argProviders.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    struct CPerformerData
    {
        struct ArgTypes
        {
            using clientId      = unsigned;
            using recvBuffer    = BufferSCPtr;
            using sndBuffer     = BufferSCPtr;
            using errorMsg      = std::string;
            using moduleName    = std::string;
            using procMessage   = ProcMessageSCPtr;
        };

        struct Connectors
        {
            using Logger = connection::Logger::Connector;
            using Network = connection::Network::Connector;
            using MessageProcessor = connection::MessageProcessor::Connector;

            Logger &logger;
            Network &network;
            MessageProcessor &messageProcessor;

            Connectors
            (
                connection::Logger::Connector &logger,
                connection::Network::Connector &network,
                connection::MessageProcessor::Connector &messageProcessor
            ) : logger(logger),
                network(network) ,
                messageProcessor(messageProcessor)
            {}
        };

        using ConnectionPerformer = app::connectors::gen::ConnectionPerformer<ArgTypes, Connectors>;

        struct AppArgs
        {
            chila::connectionTools::lib::codegen::ConnectorMap &cMap;

            struct Providers
            {
                chila::lib::misc::Construct<MessageCreatorArgProvider<ConnectionPerformer::ArgAliases> > procMessageCreator;
                chila::lib::misc::Construct<MessageReaderArgProvider<ConnectionPerformer::ArgAliases> > procMessageReaderPC;

                ModuleNameProviderCreator<ConnectionPerformer::ArgAliases> networkNameProv, processingNameProv;

                Providers() : networkNameProv("Network"), processingNameProv("MessageProcessor") {}

            } providers;

            AppArgs(chila::connectionTools::lib::codegen::ConnectorMap &cMap) : cMap(cMap) {}
        };

        static void connect(chila::connectionTools::lib::codegen::ConnectorMap &cMap)
        {
            AppArgs args(cMap);
            ConnectionPerformer::connect(args);
        }
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
