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

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__APPLICATIONSCREATOR_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_TREE__APPLICATIONSCREATOR_HPP

#include "fwd.hpp"
#include "CreatorBase.hpp"
#include <boost/filesystem.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class ApplicationCreator : public CreatorBase
    {
        private:
            Application &app;

            void parseArgumentAliases(Application &application, const TiXmlElement *aliasElem);
            void parseConnectorAliases(Application &application, const TiXmlElement *aliasesElem);
            void parseArgProviderCreators(Application &application, const TiXmlElement *creatorsElem);
            void parseConnectorInstances(Application &application, const TiXmlElement *instancesElem);


            static std::string parseAction(const std::string &actionStr, std::string &actionName);

            Application &create();

        public:
            ApplicationCreator(NspBase &nspBase, const boost::filesystem::path &file) :
                CreatorBase(nspBase, file), app(create()) {}

            Application &getApplication() const { return app; }
    };
}}}}

#undef DEF_NAMESPACE
#undef libMisc


#include <chila/lib/misc/macrosUndef.hpp>
#endif


