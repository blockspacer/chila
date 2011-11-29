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

#include <iostream>
#include <chila/lib/misc/Construct.hpp>
#include "app/impl/Logging.hpp"
#include "app/impl/Network.hpp"
#include "app/impl/Processing.hpp"
#include "app/connectors/gen/Application.hpp"
#include "app/impl/argProviderCreators.hpp"

namespace appTest = chila::connectionTools::appTest;
namespace libMisc = chila::lib::misc;

struct Connectors
{
    typedef appTest::app::impl::Logging::Connector Logging;
    typedef appTest::app::impl::Network::Connector Network;
    typedef appTest::app::impl::Processing::Connector Processing;

    Logging &logging;
    Network &network;
    Processing &processing;

    Connectors(Logging &logging, Network &network, Processing &processing) :
        logging(logging), network(network), processing(processing) {}
};

typedef appTest::app::connectors::gen::Application<Connectors> MyApplication;

struct Args
{
    Connectors connectors;

    struct Providers
    {
        libMisc::Construct<appTest::app::impl::MessageCreatorArgProvider<MyApplication::ArgAliases> > procMessageCreator;
        libMisc::Construct<appTest::app::impl::MessageReaderArgProvider<MyApplication::ArgAliases> > procMessageReaderPC;

        typedef appTest::app::impl::ModuleNameProviderCreator<MyApplication::ArgAliases> ModuleNameProviderCreator;

        ModuleNameProviderCreator networkNameProv, processingNameProv;

        Providers() : networkNameProv("Network"), processingNameProv("Processing") {}

    } providers;

    Args(const Connectors &connectors) : connectors(connectors) {}
};


int main(int argc, char** argv)
{
    boost::asio::io_service ioService;

    appTest::app::impl::Network network(ioService,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1600));
    appTest::app::impl::Logging logging;
    appTest::app::impl::Processing processing(ioService);

    Args args(Connectors(logging.connector, network.connector, processing.connector));

    MyApplication::connect(args);

    network.init();
    network.start();

    ioService.run();

    return 0;
}

