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

#ifndef CHILA_LIB_MISC__EXCEPTIONS_HPP
#define CHILA_LIB_MISC__EXCEPTIONS_HPP

#include <boost/exception/all.hpp>

#include "macrosDef.hpp"
#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define DEF_EXCEPTION CHILA_LIB_MISC__DEF_EXCEPTION

DEF_NAMESPACE(3, (chila,lib,misc))
{
    DEF_EXCEPTION(ElementNotFound, "element not found");
    DEF_EXCEPTION(ElementAlreadyExists, "element already exists");
    DEF_EXCEPTION(TiXmlError, "XML error");

    struct ExceptionInfo
    {
        typedef boost::error_info<struct tag_description_info, std::string> Description;
        typedef boost::error_info<struct tag_row_info, unsigned> Row;
        typedef boost::error_info<struct tag_column_info, unsigned> Column;
        typedef boost::error_info<struct tag_xpath_info, std::string> XPath;
    };
}}}

#undef DEF_NAMESPACE
#undef DEF_EXCEPTION
#include "macrosUndef.hpp"

#endif
