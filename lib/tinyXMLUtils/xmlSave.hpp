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

#ifndef CHILA_LIB_TINYXMLUTILS__XMLSAVE_HPP
#define CHILA_LIB_TINYXMLUTILS__XMLSAVE_HPP

#include "util.hpp"
#include <list>
#include <set>
#include <map>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,lib,tinyXMLUtils,xmlSave))
{
    template <typename Source>
    std::auto_ptr<TiXmlElement> get(const Source &element, const char *name);

    template <typename Key, typename Type>
    inline void add(TiXmlElement &element, const typename std::pair<Key, Type> &p, const char *name)
    {
        element.LinkEndChild(get<Type>(p.second, name).release());
    }

    template <typename Type>
    inline void add(TiXmlElement &element, const Type &object, const char *name)
    {
        element.LinkEndChild(get<Type>(object, name).release());
    }

    template <typename ListType>
    void addElements(TiXmlElement &element, const ListType &list, const char *childName)
    {
        BOOST_FOREACH(const typename ListType::value_type &vt, list)
        {
            add(element, vt, childName);
        }
    }

    template <typename ListType>
    std::auto_ptr<TiXmlElement> getCollection(const ListType &list, const char *name, const char *childName)
    {
        std::auto_ptr<TiXmlElement> ret(new TiXmlElement(name));
        addElements(*ret, list, childName);

        return ret;
    }

    template <typename ListType>
    void addCollection(TiXmlElement &element, const ListType &list, const char *name, const char *childName)
    {
        element.LinkEndChild(getCollection(list, name, childName).release());
    }

}}}}


#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
