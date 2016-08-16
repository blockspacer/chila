/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.lib'
 *
 * 'chila.lib' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.lib' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.lib'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_LIB_MISC__FUNEXECSEQUENCE_HPP
#define CHILA_LIB_MISC__FUNEXECSEQUENCE_HPP

#include <boost/ref.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Fun0, typename Fun1>
    struct FunExecSequence
    {
        Fun0 fun0;
        Fun1 fun1;
        FunExecSequence(const Fun0 &fun0, const Fun1 &fun1) : fun0(fun0), fun1(fun1) {}

#define py_com_personal_lib_misc__def_operator(z, n, data) \
        BOOST_PP_IF(n, template<,)                                              \
        BOOST_PP_ENUM_PARAMS(n, typename Arg)                                   \
        BOOST_PP_IF(n, >,)                                                      \
        void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, Arg, &arg))              \
        {                                                                       \
            boost::unwrap_ref(fun0)(BOOST_PP_ENUM_PARAMS(n, arg));                                 \
            boost::unwrap_ref(fun1)(BOOST_PP_ENUM_PARAMS(n, arg));                                 \
        }

        BOOST_PP_REPEAT(50, py_com_personal_lib_misc__def_operator,);
    };

#undef py_com_personal_lib_misc__def_operator

    template <typename Fun0, typename Fun1>
    inline FunExecSequence<Fun0, Fun1> funExecSequence(const Fun0 &fun0, const Fun1 &fun1)
    {
        return FunExecSequence<Fun0, Fun1>(fun0, fun1);
    }

    template <typename FunFrom, typename FunTo>
    void composeFun(FunFrom &from, const FunTo &to)
    {
        if (from)
            from = funExecSequence(from, to);
        else
            from = to;
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
