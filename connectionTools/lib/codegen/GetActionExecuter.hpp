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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_GETACTIONEXECUTER_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_CODEGEN_GETACTIONEXECUTER_HPP

#include "AProviderStacker.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
{
    template <typename event, typename action, typename GenFVec, typename FunToProvide>
    struct GetActionExecuter
    {
        GenFVec genFVec;
        FunToProvide funToProvide;

        GetActionExecuter(const GenFVec &genFVec, FunToProvide funToProvide) :
            genFVec(genFVec), funToProvide(funToProvide) {}

        template <typename ActionFunctor>
        void operator()(ActionFunctor aFun)
        {
            funToProvide(InArgMapCreator<event>::argSynthetizer(aProviderStacker(
                genFVec, argMapExecuter<action>(aFun))));
        }
    };

    template <typename event, typename action, typename GenFVec, typename FunToProvide>
    inline GetActionExecuter<event, action, GenFVec, FunToProvide>
        getActionExecuter(const GenFVec &genFVec, FunToProvide funToProvide)
    {
        return GetActionExecuter<event, action, GenFVec, FunToProvide>(genFVec, funToProvide);
    }
}}}}

#undef DEF_NAMESPACE 
#include <chila/lib/misc/macrosDef.hpp>
#endif

