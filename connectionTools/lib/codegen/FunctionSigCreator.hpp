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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_CALLBACKSIGCREATOR_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_CODEGEN_CALLBACKSIGCREATOR_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/function.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
{

    template <typename FunMetadata, unsigned ArgCount>
    struct FunctionSigCreatorImpl {};

    template <typename FunMetadata>
    struct FunctionSigCreator : FunctionSigCreatorImpl<FunMetadata, boost::mpl::size<typename FunMetadata::Arguments>::value>
    {
    };

    #define DEF_ARG(z, n, data) \
        typename boost::mpl::at_c<typename FunMetadata::Arguments, n>::type::DataType

    #define DEF_FUN_CREATOR(z, argCount, data)                                                  \
        template <typename FunMetadata>                                                         \
        struct FunctionSigCreatorImpl<FunMetadata, argCount>                                    \
        {                                                                                       \
            typedef typename FunMetadata::Result(Type)(BOOST_PP_ENUM(argCount, DEF_ARG,));      \
        };

    BOOST_PP_REPEAT(10, DEF_FUN_CREATOR,)
}}}}

#include <chila/lib/misc/macrosUndef.hpp>
#undef DEF_NAMESPACE
#endif

