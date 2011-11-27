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

#include "app/Main.hpp"
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
