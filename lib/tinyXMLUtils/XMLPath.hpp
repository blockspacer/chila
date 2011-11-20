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

#ifndef CHILA_LIB_TINYXMLUTILS_XMLPATH_HPP
#define CHILA_LIB_TINYXMLUTILS_XMLPATH_HPP

#include <string>
#include <vector>
#include <tinyXPath/tinyxml.h>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,tinyXMLUtils))
{
    class XMLPath
    {
        public:
            struct Push
            {
                XMLPath &path;
                Push(XMLPath &path, const std::string &name) : path(path)
                {
                    path.push(name);
                }

                ~Push() { path.pop(); }
            };

            XMLPath(unsigned reserveSize = 8) : isAttr(false)
            {
                nameVec.reserve(reserveSize);
            }

            void push(const std::string &name, bool isAttribute = false)
            {
                assert(isAttr && !nameVec.empty() || !isAttr);
                this->isAttr = isAttribute;
                nameVec.push_back(name);
            }

            void pop()
            {
                nameVec.pop_back();
                isAttr = false;
            }

            bool isAttribute() const { return isAttr; }

            void checkTag(const TiXmlElement *elem, const char *expected) const;
            std::string getStringRep(const std::string &delim = "/") const;

            const char *getAttrAndCheck(const TiXmlElement *elem, const char *name) const;

        private:
            bool isAttr;
            typedef std::vector<std::string> NameVec;
            NameVec nameVec;
    };


}}}


#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
