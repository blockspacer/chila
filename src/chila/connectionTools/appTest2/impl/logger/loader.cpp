/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/connectionTools/loader/fwd.hpp>
#include "impl/connection/Logger.hpp"
#include <iostream>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccLogger = chila::connectionTools::appTest2::impl::logger;
namespace cclOther = chila::connectionTools::lib::other;

ccLogger::impl::connection::Logger::CProviderSPtr logger;

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher)
{
    std::cout << "test" << std::endl;

    logger = ccLogger::impl::connection::Logger::create();

    cMap.add("logger", logger->getConnector());

    launcher.add(logger->getConnector());
}
