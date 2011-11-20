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

#ifndef CHILA_CONNECTIONTOOLS_BASEMODULECREATOR_CODEGENERATOR_HPP
#define	CHILA_CONNECTIONTOOLS_BASEMODULECREATOR_CODEGENERATOR_HPP

#include <chila/connectionTools/lib/tree/Connector.hpp>
#include <iostream>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define mtLibTree chila::connectionTools::lib::tree
#define libMisc chila::lib::misc


DEF_NAMESPACE(3, (chila,connectionTools,baseConnectorCreator))
{
    class CodeGenerator
    {
        private:
            const mtLibTree::Connector &connector;
            std::ostream &out;
            libMisc::Path modNspPath;

            void generateHeader();
            void generateFooter();

            void generateConnector();


            void generateSignature(const std::string &name, const mtLibTree::Signature &sig);
            void generateArgumentList(const mtLibTree::Function &fun);
            void generateFunctionCall(const std::string &prefix, const mtLibTree::Signature &sig);
            void getGuardRep(std::ostream &out);
            void getDelimRep(std::ostream &out, const char *delim);

        public:
            CodeGenerator(const mtLibTree::Connector &connector, std::ostream &out);

            void generate();
    };

}}}

#undef libMisc
#undef mtLibTree
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>

#endif
