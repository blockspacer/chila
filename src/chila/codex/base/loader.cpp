/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "app/impl/connection/CPerformerData.hpp"
#include <chila/connectionTools/loader/fwd.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include "app/App.hpp"


#include "macros.fgen.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccBase = chila::codex::base;
namespace cclOther = chila::connectionTools::lib::other;
namespace po = boost::program_options;
namespace clMisc = chila::lib::misc;

po::variables_map vm;
unsigned port;

ccBase::app::AppSPtr app;
boost::shared_ptr<QApplication> qApplication;

boost::filesystem::path initApp(int &argc, char** argv, cclOther::DataMap &dataMap)
{
    qApplication = boost::make_shared<QApplication>(argc, argv);

    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("base-lib", po::value<std::string>(), "base library")
        ("loader-config", po::value<std::string>(), "application configuration file (defaults to 'loaderConfig.xml')")
        ("install-dir,i", po::value<std::string>(), "Instalation directory")
        ("help,h", "produce help message");

    popDesc.add("base-lib", 1);

    try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::cout << "Loading base data..." << std::endl;

    auto installDir = clMisc::getProgramOption<std::string>(vm, "install-dir", ".");
    app = boost::make_shared<ccBase::app::App>(installDir, dataMap, *qApplication);

    boost::filesystem::path loaderConfig = clMisc::getProgramOption<std::string>(vm, "loader-config", "loaderConfig.xml");

    return loaderConfig.is_relative() ? installDir / loaderConfig : loaderConfig;
}

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect)
{
    std::cout << "chila.codex.base:loadConnectors..." << std::endl;

    app->connect(cMap, dataMap, launcher, preLoaderConnect);
}

void startApplication(ccLoader::ConnectorMap &cMap)
{
    std::cout << "Starting application..." << port << std::endl;
    app->start();
}
