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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CREATORBASE_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_CREATORBASE_HPP

#include "fwd.hpp"
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <tinyXPath/tinyxmlfwd.h>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class CreatorBase
    {
        protected:
            typedef std::vector<const char*> XmlPath;

            struct PushPath
            {
                XmlPath &xmlPath;
                PushPath(XmlPath &xmlPath, const char *name) : xmlPath(xmlPath)
                {
                    xmlPath.push_back(name);
                }

                ~PushPath() { xmlPath.pop_back(); }
            };


            boost::filesystem::path file;
            NspBase &nspBase;

            XmlPath currPath;

            void throwAttributeError(const std::string &attributeName,
                    const TiXmlElement *elem, const std::string &msg) const;

            void checkTag(const TiXmlElement *elem, const char *expected) const;
            static StringVec getIdVec(const std::string &text, const char *sep);

            std::string getCurrPath() const;
            static std::string getElementPos(const TiXmlElement *elem);

            const char *getAttrAndCheck(const TiXmlElement *elem, const char *name) const;

        public:
            CreatorBase(NspBase &nspBase, const boost::filesystem::path &file) :
                file(file), nspBase(nspBase) {}
    };
}}}}


#undef libMisc
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif


