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

#ifndef CHILA_CONNECTIONTOOLS_LIB_FUNCTIONS_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_FUNCTIONS_HPP

#include "fwd.hpp"
#include <iostream>
#include "ObjectContainer.hpp"
#include "Function.hpp"
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class Functions : public Object<Connector>,  public virtual ObjectContainer
    {
        public:
            Functions(Connector &container, const std::string &name) :
                Object<Connector>(container, name){}

            void setFunction(const std::string &name, const StringVec &argNames, const std::string &description)
            {
                std::auto_ptr<Function> fun(new Function(*this, name, description));
                fun->setArguments(argNames);
                setObject(fun);
            }

            OBJECT_GROUP_DEF_GETTERS(Function, Function)
            OBJECT_GROUP_DEF_VEC_GETTER(Function, Functions)

            void check() const { ObjectContainer::checkObjects(); }
    };
}}}}

#undef DEF_NAMESPACE
#undef libMisc

#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosUndef.hpp>
#endif

