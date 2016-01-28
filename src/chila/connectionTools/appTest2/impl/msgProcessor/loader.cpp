/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/connectionTools/loader/fwd.hpp>
#include "impl/connection/MessageProcessor.hpp"
#include <iostream>
#include <boost/asio/io_service.hpp>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <chila/lib/misc/util.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"

#include "nspDef.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccMsgProcessor = chila::connectionTools::appTest2::impl::msgProcessor;
namespace cclOther = chila::connectionTools::lib::other;

ccMsgProcessor::impl::connection::MessageProcessor::CProviderSPtr msgProcessor;

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher)
{
    std::cout << "messageProcessor" << std::endl;

    auto &ioService = chila::lib::misc::deref(ccLoader::getValue<boost::asio::io_service*>(dataMap, "service"));

    msgProcessor = ccMsgProcessor::impl::connection::MessageProcessor::create(ioService);

    cMap.add("messageProcessor", msgProcessor->getConnector());

    launcher.add(msgProcessor->getConnector());
}
