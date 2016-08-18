/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.codegen'
 *
 * 'chila.connectionTools.lib.codegen' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.codegen' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.codegen'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNCTIONSIGCREATOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNCTIONSIGCREATOR_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/function.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename Arguments, unsigned ArgCount>
    struct FunctionSigCreatorImpl {};

    template <typename Arguments>
    struct FunctionSigCreator : FunctionSigCreatorImpl<Arguments, boost::mpl::size<Arguments>::value>
    {
    };

    #define DEF_ARG(z, n, data) \
        typename boost::mpl::at_c<Arguments, n>::type::ParamType

    #define DEF_FUN_CREATOR(z, argCount, data)                                                  \
        template <typename Arguments>                                                         \
        struct FunctionSigCreatorImpl<Arguments, argCount>                                    \
        {                                                                                       \
            using Type = void(BOOST_PP_ENUM(argCount, DEF_ARG,));      \
        };

    BOOST_PP_REPEAT(19, DEF_FUN_CREATOR,)
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

