/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
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
        void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, const Arg, &arg))              \
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
