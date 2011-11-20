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

#include "XMLPath.hpp"
#include "exception.hpp"
#include <boost/foreach.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,tinyXMLUtils))
{
    void XMLPath::checkTag(const TiXmlElement *elem, const char *expected) const
    {
        XMLPath exPath(*this);
        exPath.push(expected);
        if (!elem)
        {
            throw XMLPathExpectedError(exPath);
        }
        else if (::strcmp(elem->Value(), expected))
        {
            XMLPath fndPath(*this);
            fndPath.push(elem->Value());
            throw XMLPathExpectedButFoundError(exPath, fndPath, elem->Row(), elem->Column());
        }
    }

    std::string XMLPath::getStringRep(const std::string &delim) const
    {
        std::string ret;
        NameVec::const_iterator last = nameVec.end() - 1;
        for (NameVec::const_iterator it = nameVec.begin(); it != nameVec.end(); ++it)
        {
            ret += delim + ((it == last && isAttr) ? "@" : "") + *it;
        }

        return ret;
    }

    const char *XMLPath::getAttrAndCheck(const TiXmlElement *elem, const char *name) const
    {
        const char *ret = elem->Attribute(name);
        if (!ret)
        {
            XMLPath exPath(*this);
            exPath.push(name, true);
            throw XMLPathExpectedError(exPath);
        }

        return ret;
    }
}}}
