/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "connection/CPerformerData.hpp"
#include <chila/connectionTools/loader/fwd.hpp>
#include <iostream>
#include <boost/asio/io_service.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"
#include <boost/program_options.hpp>

#include "nspDef.hpp"

namespace ccLoader = chila::connectionTools::loader;
namespace ccaBase = chila::connectionTools::appTest2::base;
namespace cclOther = chila::connectionTools::lib::other;
namespace po = boost::program_options;
namespace clMisc = chila::lib::misc;

boost::asio::io_service ioService;
po::variables_map vm;
unsigned port;

boost::filesystem::path initApp(int argc, char** argv, cclOther::DataMap &dataMap)
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("base-lib", po::value<std::string>(), "base library")
        ("loader-config", po::value<std::string>(), "application configuration file (defaults to 'loaderConfig.xml')")
        ("port,p", po::value<unsigned>(), "listening port")
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

    port = clMisc::getProgramOption<unsigned>(vm, "port");

    std::cout << "Loading base data..." << std::endl;

    my_assert(dataMap.insert({"service", &ioService}).second);
    my_assert(dataMap.insert({"listenEndPoint", boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)}).second);

    return clMisc::getProgramOption<std::string>(vm, "loader-config", "loaderConfig.xml");
}

void loadConnectors(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher)
{
    std::cout << "Connecting modules..." << std::endl;

    ccaBase::connection::CPerformerData::connect(cMap);
}

void startApplication(ccLoader::ConnectorMap &cMap)
{
    std::cout << "Listening on port " << port << std::endl;
    ioService.run();
}
