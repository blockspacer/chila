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

#ifndef CHILA_CONNECTION_TOOLS_APPTEST_APP_IMPL_CONNECTION__APPLICATION_HPP
#define CHILA_CONNECTION_TOOLS_APPTEST_APP_IMPL_CONNECTION__APPLICATION_HPP

#include "../../connectors/gen/Application.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "Logger.hpp"
#include "Network.hpp"
#include "MessageProcessor.hpp"
#include "argProviders.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,impl,connection))
{
    struct ApplicationData
    {
        struct Connectors
        {
            typedef connection::Logger::Connector Logger;
            typedef connection::Network::Connector Network;
            typedef connection::MessageProcessor::Connector MessageProcessor;
        };

        typedef app::connectors::gen::Application<Connectors> Application;

        struct AppArgs
        {
            struct Connectors
            {
                connection::Logger::Connector &logger;
                connection::Network::Connector &network;
                connection::MessageProcessor::Connector &messageProcessor;

                Connectors
                (
                    connection::Logger::Connector &logger,
                    connection::Network::Connector &network,
                    connection::MessageProcessor::Connector &messageProcessor
                ) : logger(logger),
                    network(network) ,
                    messageProcessor(messageProcessor)
                {}
            } connectors;

            struct Providers
            {
                chila::lib::misc::Construct<MessageCreatorArgProvider<Application::ArgAliases> > procMessageCreator;
                chila::lib::misc::Construct<MessageReaderArgProvider<Application::ArgAliases> > procMessageReaderPC;

                ModuleNameProviderCreator<Application::ArgAliases> networkNameProv, processingNameProv;

                Providers() : networkNameProv("Network"), processingNameProv("MessageProcessor") {}

            } providers;

            AppArgs(const AppArgs::Connectors &connectors) : connectors(connectors) {}
        };

        void connect(const AppArgs &args) const;
    };
}}}}}}

#undef DEF_NAMESPACE

#endif
