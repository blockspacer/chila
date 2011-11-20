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

#ifndef CHILA_LIB_TINYXMLUTILS__XMLLOAD_HPP
#define CHILA_LIB_TINYXMLUTILS__XMLLOAD_HPP

#include "util.hpp"
#include <list>
#include <set>
#include <map>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

DEF_NAMESPACE(4, (chila,lib,tinyXMLUtils,xmlLoad))
{
    template <typename Type, typename Source>
    Type get(const Source &element);

    template <typename Type>
    inline Type getFromString(const std::string &text) try
    {
        return boost::lexical_cast<Type>(text);
    }
    catch (const boost::bad_lexical_cast &ex)
    {
        BOOST_THROW_EXCEPTION(ErrorReadingValue());
    }

    template <typename Key, typename Type>
    inline void add(std::map<Key, Type> &map, const typename std::map<Key, Type>::value_type &vt)
    {
        if (!map.insert(vt).second)
            throw chila::lib::misc::ElementAlreadyExists();
    }

    template <typename Type>
    inline void add(std::set<Type> &set, const Type &object)
    {
        if (!set.insert(object).second)
            throw chila::lib::misc::ElementAlreadyExists();
    }

    template <typename Type>
    inline void add(std::list<Type> &list, const Type &object)
    {
        list.push_back(object);
    }

    template <typename ListType>
    ListType getCollection(const TiXmlElement &element, const char *tagName)
    {
        ListType ret;
        for (const TiXmlElement *cur = element.FirstChildElement(tagName); cur; cur = cur->NextSiblingElement(tagName))
            add(ret, get<typename ListType::value_type>(*cur));

        return ret;
    }

    template <typename Type>
    inline Type getFromElement(const TiXmlElement &element, const char *tagName)
    {
        return get<Type>(getElement(element, tagName));
    }

    template <typename Type>
    inline Type getFromAttribute(const TiXmlElement &element, const char *attrName) try
    {
        return getFromString<Type>(getAttribute(element, attrName));
    }
    catch (const ErrorReadingValue &ex)
    {
        ex << chila::lib::misc::ExceptionInfo::Row(element.Row())
           << chila::lib::misc::ExceptionInfo::Column(element.Column())
           << chila::lib::misc::ExceptionInfo::XPath(getPath(element) + "/@" + attrName);
        throw;
    }

    template <typename ListType>
    inline ListType getCollectionFromElement(const TiXmlElement &element, const char *tagName, const char *childTagName)
    {
        return getCollection<ListType>(getElement(element, tagName), childTagName);
    }

}}}}

#undef libMisc
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
