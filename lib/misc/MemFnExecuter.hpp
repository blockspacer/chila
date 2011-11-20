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

#ifndef CHILA__LIB_MISC_MEMFNEXECUTER_HPP
#define	CHILA__LIB_MISC_MEMFNEXECUTER_HPP

#include <boost/ref.hpp>
#include <boost/preprocessor.hpp>

#define TMPL_ARG(z, index, data) typename Arg##index
#define OP_DEC_ARG(z, index, data) const Arg##index &arg##index
#define OP_PASS_ARG(z, index, data) arg##index

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{

    template <typename MemFn, typename Object>
    struct MemFnExecuter
    {
        typedef typename MemFn::result_type result_type;

        MemFn fun;
        Object object;

        MemFnExecuter(MemFn fun, Object object) : fun(fun), object(object) {}

        result_type operator()() const
        {
            return this->fun(this->object);
        }

        #define DEF_OPERATOR(z, argCount, data)                                                         \
            template <BOOST_PP_ENUM(argCount, TMPL_ARG,)>                                             \
            result_type operator()(BOOST_PP_ENUM(argCount, OP_DEC_ARG,)) const                        \
            {                                                                                           \
                return this->fun(this->object, BOOST_PP_ENUM(argCount, OP_PASS_ARG,));    \
            }

        BOOST_PP_REPEAT_FROM_TO(1, 9, DEF_OPERATOR,)
    };

    template <typename MemFn, typename Object>
    inline MemFnExecuter<MemFn, Object> memFnExecuter(MemFn fun, Object object)
    {
        return MemFnExecuter<MemFn, Object>(fun, object);
    }

}}}


#undef DEF_OPERATOR
#undef TMPL_ARG
#undef OP_DEC_ARG
#undef OP_PASS_ARG
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

