/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "app/impl/connection/CPerformerData.hpp"
#include <chila/connectionTools/loader/fwd.hpp>
#include <iostream>
#include "app/App.hpp"

#include "macros.fgen.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccText = chila::codex::text;
namespace cclOther = chila::connectionTools::lib::other;
namespace po = boost::program_options;
namespace clMisc = chila::lib::misc;

po::variables_map vm;
unsigned port;

ccText::app::AppSPtr app;

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect)
{
    std::cout << "chila.codex.text:loadConnectors..." << std::endl;

    if (!app)
        app = boost::make_shared<ccText::app::App>();

    app->connect(cMap, dataMap, launcher, preLoaderConnect);
}
