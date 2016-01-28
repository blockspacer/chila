/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/connectionTools/loader/fwd.hpp>
#include "impl/connection/Network.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccNetwork = chila::connectionTools::appTest2::impl::network;
namespace cclOther = chila::connectionTools::lib::other;

ccNetwork::impl::connection::Network::CProviderSPtr network;

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher)
{
    std::cout << "network" << std::endl;

    auto &ioService = chila::lib::misc::deref(ccLoader::getValue<boost::asio::io_service*>(dataMap, "service"));
    auto listenEndPoint = ccLoader::getValue<boost::asio::ip::tcp::endpoint>(dataMap, "listenEndPoint");

    network = ccNetwork::impl::connection::Network::create(ioService, listenEndPoint);

    cMap.add("network", network->getConnector());

    launcher.add(network->getConnector());
}
