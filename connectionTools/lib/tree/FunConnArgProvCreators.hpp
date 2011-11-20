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

#ifndef CHILA_CONNECTIONTOOLS_LIB_FUNCONNARGPROVCREATORS_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_FUNCONNARGPROVCREATORS_HPP

#include "fwd.hpp"
#include "FunConnArgProvCreator.hpp"
#include "ObjectContainer.hpp"
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    struct FunConnArgProvCreators : public Object<FunctionConnection>, public ObjectContainer
    {
        FunConnArgProvCreators(FunctionConnection &container, const std::string &name) :
            Object<FunctionConnection>(container, name) {}

        void setCreator(const std::string &name, unsigned pos)
        {
            setObject(new FunConnArgProvCreator(*this, name, pos));
        }

        OBJECT_GROUP_DEF_GETTERS(FunConnArgProvCreator, Creator)
        OBJECT_GROUP_DEF_ORDERED_VEC_GETTER(FunConnArgProvCreator, Creators)
    };
}}}}

#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

