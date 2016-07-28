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

#ifndef CHILA_LIB_MISC__PROGRAMOPTIONS_HPP
#define CHILA_LIB_MISC__PROGRAMOPTIONS_HPP

#include "fwd.hpp"
#include "exceptions.hpp"
#include <boost/program_options.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class ProgramOptions
    {
        public:
            boost::program_options::positional_options_description popDesc;
            boost::program_options::options_description opDesc;

            ProgramOptions() : opDesc("Allowed options") {}

            bool parse(int argc, char **argv);

            template <typename Type>
            Type getProgramOption(const std::string &name);

            template <typename Type>
            Type getProgramOption(const std::string &name, const Type &defVal);

        private:
            boost::program_options::variables_map vm;

    };

    template <typename Type>
    Type ProgramOptions::getProgramOption(const std::string &name)
    {
        if (vm.count(name))
        {
            return vm[name].as<Type>();
        }
        else
        {
            BOOST_THROW_EXCEPTION(ApplicationError("error: '" + name + "' argument is missing."));
        }
    }

    template <typename Type>
    Type ProgramOptions::getProgramOption(const std::string &name, const Type &defVal)
    {
        if (vm.count(name))
        {
            return vm[name].as<Type>();
        }
        else
        {
            return defVal;
        }
    }

}
MY_NSP_END


#include "macros.fgen.hpp"


#endif
