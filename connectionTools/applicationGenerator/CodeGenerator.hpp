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

#ifndef CHILA_CONNECTIONTOOLS_CONNECTIONSGENERATOR_CODEGENERATOR_HPP
#define CHILA_CONNECTIONTOOLS_CONNECTIONSGENERATOR_CODEGENERATOR_HPP

#include <chila/connectionTools/lib/tree/fwd.hpp>
#include <iostream>
#include <chila/lib/misc/macrosDef.hpp>

#define mtLibTree chila::connectionTools::lib::tree
#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,connectionTools,connectionsGenerator))
{
    class CodeGenerator
    {
        private:
            const mtLibTree::Application &app;
            std::ostream &out;

        public:
            CodeGenerator(const mtLibTree::Application &app, std::ostream &out) :
                app(app), out(out) {}

            void generate();

    };
}}}

#undef mtLibTree
#undef DEF_NAMESPACE
#endif
