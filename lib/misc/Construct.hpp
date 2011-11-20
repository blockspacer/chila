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

#ifndef CHILA_LIB_MISC_CONSTRUCT_H
#define CHILA_LIB_MISC_CONSTRUCT_H

#include <boost/ref.hpp>
#include <boost/preprocessor.hpp>

#include <chila/lib/misc/macrosDef.hpp>


#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{
    template <typename Type>
    struct Construct
    {
        typedef Type result_type;

        Type operator()() const { return Type(); }

        #define OP_DEC_ARG(z, index, data) const Arg##index &arg##index
        #define OP_PASS_ARG(z, index, data) boost::unwrap_ref(arg##index)

        #define DEF_OPERATOR(z, argCount, data)                                     \
            template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                 \
            result_type operator()(BOOST_PP_ENUM(argCount, OP_DEC_ARG,)) const      \
            {                                                                       \
                return Type(BOOST_PP_ENUM(argCount, OP_PASS_ARG,));                 \
            }

        BOOST_PP_REPEAT_FROM_TO(1, 10, DEF_OPERATOR,)

        #undef OP_DEC_ARG
        #undef OP_PASS_ARG
        #undef DEF_OPERATOR
    };

}}}

#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>


#endif

