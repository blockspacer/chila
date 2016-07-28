/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.lib'
 *
 * 'chila.lib' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.lib' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.lib'. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ProgramOptions.hpp"
#include <iostream>
#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace po = boost::program_options;

    bool ProgramOptions::parse(int argc, char **argv) try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << opDesc << std::endl;
            return false;
        }

        return true;
    }
    catch(const std::exception &ex)
    {
        BOOST_THROW_EXCEPTION(ApplicationError(std::string("argument error: ") + ex.what()));
    }

}
MY_NSP_END
