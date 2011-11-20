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

#ifndef CHILA_CONNECTIONTOOLS_DOCGENERATOR_APPLICATIONGENERATOR_HPP
#define	CHILA_CONNECTIONTOOLS_DOCGENERATOR_APPLICATIONGENERATOR_HPP

#include <chila/connectionTools/lib/tree/Connector.hpp>
#include <boost/function.hpp>
#include <iostream>
#include "GeneratorBase.hpp"
#include <boost/filesystem/path.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define mtLibTree chila::connectionTools::lib::tree

DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
{
    class ApplicationGenerator : public GeneratorBase
    {
        public:
            typedef std::vector<boost::filesystem::path> ConnectorFiles;

            ApplicationGenerator(const mtLibTree::Application &application, std::ostream &out,
                    const std::string &title, const ConnectorFiles &connectorFiles) :
                GeneratorBase(out, application), application(application), title(title), connectorFiles(connectorFiles) {}

            void generate();

        private:
            const mtLibTree::Application &application;
            const std::string title;
            const ConnectorFiles connectorFiles;

            void generateArgAliases();
            void generateConnectorAliases();
            void generateArgProviderCreators();
            void generateConnectorInstances();
    };

}}}

#undef mtLibTree
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>

#endif
