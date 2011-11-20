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

#ifndef CHILA_CONNECTIONTOOLS_LIB_FUNCTION_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_FUNCTION_HPP

#include "fwd.hpp"
#include "FunctionArgument.hpp"
#include "ObjectContainer.hpp"
#include <boost/cast.hpp>
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class Function : public Object<Functions>, public virtual ObjectContainer
    {
        public:
            Function(Functions &container, const std::string &name, const std::string &description) :
                Object<Functions>(container, name), description(description) {}

            void setArguments(const StringVec &argNames)
            {
                unsigned i = 0;

                BOOST_FOREACH(const std::string &name, argNames)
                {
                    setObject(new FunctionArgument(*this, name, i++));
                }
            }

            unsigned getArgCount() const { return getObjectMap().size(); }

            OBJECT_GROUP_DEF_GETTERS(FunctionArgument, Argument)
            OBJECT_GROUP_DEF_ORDERED_VEC_GETTER(FunctionArgument, Arguments)

            void check() const { ObjectContainer::checkObjects(); }

            const std::string &getDescription() const { return description; }

        private:
            std::string description;
    };
}}}}

#undef libMisc
#undef DEF_NAMESPACE

#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosUndef.hpp>
#endif

