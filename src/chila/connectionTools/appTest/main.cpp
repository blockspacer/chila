/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "app/Main.hpp"
#include <iostream>
#include <boost/exception/all.hpp>

using namespace chila::connectionTools::appTest;


int main(int argc, char** argv) try
{
    boost::asio::io_service ioService;

    app::Main main(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1600));
    main.start();

    ioService.run();

    return EXIT_SUCCESS;
}
catch (const std::exception &ex)
{
    std::cout << boost::diagnostic_information(ex) << std::endl;
    return EXIT_FAILURE;
}
