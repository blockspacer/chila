/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTION__CPERFORMERDATA_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE_CONNECTION__CPERFORMERDATA_HPP

#include "../connectors/gen/ConnectionPerformer.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "../../impl/logger/impl/connection/Logger.hpp"
#include "../../impl/network/impl/connection/Network.hpp"
#include "../../impl/msgProcessor/impl/connection/MessageProcessor.hpp"
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
            using Logger = appTest2::impl::logger::impl::connection::Logger::Connector;
            using Network = appTest2::impl::network::impl::connection::Network::Connector;
            using MessageProcessor = appTest2::impl::msgProcessor::impl::connection::MessageProcessor::Connector;

            Logger &logger;
            Network &network;
            MessageProcessor &messageProcessor;

            Connectors
            (
                appTest2::impl::logger::impl::connection::Logger::Connector &logger,
                appTest2::impl::network::impl::connection::Network::Connector &network,
                appTest2::impl::msgProcessor::impl::connection::MessageProcessor::Connector &messageProcessor
            ) : logger(logger),
                network(network) ,
                messageProcessor(messageProcessor)
            {}
        };

        using ConnectionPerformer = connectors::gen::ConnectionPerformer<ArgTypes, Connectors>;

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
