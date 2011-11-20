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

#include "util.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

DEF_NAMESPACE(3, (chila,lib,tinyXMLUtils))
{
    std::string getPath(const TiXmlElement &element)
    {
        std::string ret;
        for (const TiXmlNode *cur = &element; cur; cur = cur->Parent())
        {
            const TiXmlElement *e = cur->ToElement();
            if (!e) break;

            ret = "/" + (e->Value() + ret);
        }

        return ret;
    }

    const TiXmlElement &getElement(const TiXmlElement &element, const char *name) try
    {
        const TiXmlElement *ret = element.FirstChildElement(name);
        if (!ret)
            BOOST_THROW_EXCEPTION(MissingNode());

        return *ret;
    }
    catch (const boost::exception &ex)
    {
        ex << chila::lib::misc::ExceptionInfo::Row(element.Row())
           << chila::lib::misc::ExceptionInfo::Column(element.Column())
           << chila::lib::misc::ExceptionInfo::XPath(getPath(element) + "/" + name);
        throw;
    }

    std::string getTextOfElement(const TiXmlElement &element)
    {
        const TiXmlNode *node = element.FirstChild();
        if (!node) return "";

        const TiXmlText *text = node->ToText();
        if (!text) return "";

        return text->Value();
    }


}}}



