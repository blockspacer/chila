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

#ifndef CHILA_LIB_MISC__UTIL_HPP
#define CHILA_LIB_MISC__UTIL_HPP

#include "exceptions.hpp"
#include <tinyXPath/tinyxml.h>

#include "macrosDef.hpp"
#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{
    inline void check(const TiXmlDocument &doc)
    {
        if(doc.Error())
            BOOST_THROW_EXCEPTION(TiXmlError() << ExceptionInfo::Description(doc.ErrorDesc())
                                               << ExceptionInfo::Row(doc.ErrorRow())
                                               << ExceptionInfo::Column(doc.ErrorCol()));
    }
}}}

#undef DEF_NAMESPACE
#include "macrosUndef.hpp"

#endif
