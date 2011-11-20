/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CreatorBase.hpp"
#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    std::string CreatorBase::getElementPos(const TiXmlElement *elem)
    {
        return "[" + boost::lexical_cast<std::string>(elem->Row()) + ":" +
                     boost::lexical_cast<std::string>(elem->Column()) + "]";
    }

    void CreatorBase::checkTag(const TiXmlElement *elem, const char *expected) const
    {
        if (!elem)
            throw ConnectorCreationError("tag '" + getCurrPath() + "/" + expected + " expected");
        else if (strcmp(elem->Value(), expected))
            throw ConnectorCreationError("tag '" + getCurrPath() + "/" + expected + "' at " +
                    getElementPos(elem) + " expected, but '" + getCurrPath() + "/" +
                    elem->Value() + "' found");
    }

    const char *CreatorBase::getAttrAndCheck(const TiXmlElement *elem, const char *name) const
    {
        const char *ret = elem->Attribute(name);
        if (!ret) throwAttributeError(name, elem, "is missing");
        return ret;
    }



    void CreatorBase::throwAttributeError(const std::string &attributeName,
            const TiXmlElement *elem, const std::string &msg) const
    {
        throw ConnectorCreationError("attribute '" + attributeName + "' of " + getCurrPath() + " at " +
                getElementPos(elem) + "' " + msg);
    }

    /** Parses 'names' into 'nameVec'. */
    StringVec CreatorBase::getIdVec(const std::string &text, const char *sep)
    {
        StringVec ids;
        typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
        Tokenizer tokens(text, boost::char_separator<char>(sep));
        for (Tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
        {
            std::string name = *iter;
            boost::trim(name);
            ids.push_back(name);
        }

        return ids;
    }

    /** Returns the string representation of 'xmlPath'. */
    std::string CreatorBase::getCurrPath() const
    {
        std::string ret;
        BOOST_FOREACH(const std::string &name, currPath)
        {
            ret += "/" + name;
        }

        return ret;
    }

}}}}

