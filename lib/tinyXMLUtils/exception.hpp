/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_LIB_TINYXMLUTILS_EXCEPTION_HPP
#define CHILA_LIB_TINYXMLUTILS_EXCEPTION_HPP

#include "XMLPath.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define DEF_EXCEPTION CHILA_LIB_MISC__DEF_EXCEPTION

DEF_NAMESPACE(3, (chila,lib,tinyXMLUtils))
{
    struct XMLPathError : public boost::exception, public std::exception
    {
        ~XMLPathError() throw() {}
    };


    struct XMLPathExpectedError : public XMLPathError
    {
        const XMLPath expected;
        const std::string whatMsg;

        XMLPathExpectedError(const XMLPath &expected) : expected(expected),
            whatMsg("'" + expected.getStringRep() + " expected"){}

        const char *what() const throw() { return whatMsg.c_str(); }

        ~XMLPathExpectedError() throw() {}
    };

    struct XMLPathExpectedButFoundError : public XMLPathExpectedError
    {
        const XMLPath found;
        const std::string whatMsg;
        unsigned row, column;

        XMLPathExpectedButFoundError(const XMLPath &expected, const XMLPath &found, unsigned row, unsigned column) :
            XMLPathExpectedError(expected), row(row), column(column), found(found),
            whatMsg("'" + expected.getStringRep() + "' at [" + boost::lexical_cast<std::string>(row) + ":" +
                boost::lexical_cast<std::string>(column) + "]" +
                " expected, but '" + found.getStringRep() + "' found")
        {}

        const char *what() const throw() { return whatMsg.c_str(); }

        ~XMLPathExpectedButFoundError() throw() {}
    };


    DEF_EXCEPTION(MissingNode, "missing node");
    DEF_EXCEPTION(NoText, "no text");
    DEF_EXCEPTION(ErrorReadingValue, "error reading value");

}}}


#undef DEF_NAMESPACE
#undef DEF_EXCEPTION
#include <chila/lib/misc/macrosUndef.hpp>
#endif
