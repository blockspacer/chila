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

#ifndef CHILA_CONNECTIONTOOLS_LIB_MODULECREATOR_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_MODULECREATOR_HPP

#include "fwd.hpp"
#include "CreatorBase.hpp"
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <tinyXPath/tinyxmlfwd.h>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class ConnectorCreator : public CreatorBase
    {
        private:
            typedef boost::function<void(const std::string &name, const StringVec &argNames,
                    const std::string &description)> AddFunction;

            XmlPath currPath;

            void getSignature(const TiXmlElement *root, StringVec &argNames);

            void loadFunctions(const TiXmlElement *root, Connector &connector,
                    const AddFunction &addFun, const char *tagName);

            void loadArguments(const TiXmlElement *root, Connector &connector);

            Connector &mod;

            Connector &create();


        public:
            ConnectorCreator(NspBase &nspBase, const boost::filesystem::path &file) :
                CreatorBase(nspBase, file), mod(create()) {}

            Connector &getConnector() const { return mod; }
    };
}}}}


#undef libMisc
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif


