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

#include "impl/connection/ApplicationData.hpp"
#include "Main.hpp"

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#include <chila/lib/misc/macrosDef.hpp>

#define cast_cprovider(Type, ptr) boost::dynamic_pointer_cast<app::impl::connection::Type::CProvider>(ptr)

DEF_NAMESPACE(4, (chila,connectionTools,appTest,app))
{
    Main::Main
    (
        boost::asio::io_service &ioService,
        const boost::asio::ip::tcp::endpoint &listenEndPoint
    ) :
        network(app::impl::connection::Network::create(ioService, listenEndPoint)),
        logger(app::impl::connection::Logger::create()),
        messageProcessor(app::impl::connection::MessageProcessor::create(ioService))
    {
        typedef app::impl::connection::ApplicationData::AppArgs AppArgs;

        app::impl::connection::ApplicationData appData;
        appData.connect(AppArgs(AppArgs::Connectors
        (
            cast_cprovider(Logger, logger)->getConnector(),
            cast_cprovider(Network, network)->getConnector(),
            cast_cprovider(MessageProcessor, messageProcessor)->getConnector()
        )));
    }

    void Main::start()
    {
        cast_cprovider(Network, network)->getConnector().actions.start();
    }

}}}}
