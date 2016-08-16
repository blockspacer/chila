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

#include "dsv.hpp"

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <chila/lib/misc/macrosExp.hpp>



#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE
#define SHOW            CHILA_LIB_MISC__//SHOW
#define CLM_ASSERT      CHILA_LIB_MISC__ASSERT

DEF_NAMESPACE(3, (chila,lib,dsv))
{

    template <>
    void load(std::istream &in, bool &data, char delim)
    {
        char c;
        CLM_ASSERT(nextField(&c, &c + 1, in, delim) - &c == 1);
        if (c == '0')
            data = false;
        else if (c == '1')
            data = true;
        else
            BOOST_THROW_EXCEPTION(std::runtime_error("'c' must be '0' or '1"));
    }

    template <>
    void load(std::istream &in, unsigned &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }

    template <>
    void load(std::istream &in, unsigned long &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }

    template <>
    void load(std::istream &in, int &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }


    template <>
    void load(std::istream &in, std::string &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);
        data = std::string(buff, end - buff);
    }


}}}
