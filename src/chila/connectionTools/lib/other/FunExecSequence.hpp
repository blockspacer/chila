/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNEXECSEQUENCE_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNEXECSEQUENCE_HPP

#include <chila/lib/misc/FunExecSequence.hpp>

#include "macrosExp.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Fun1>
    struct FunExecSequence
    {
        template <typename Fun0>
        struct result_type
        {
            typedef chila::lib::misc::FunExecSequence<Fun0, Fun1> type;
        };

        Fun1 fun1;

        FunExecSequence(const Fun1 &fun1) : fun1(fun1) {}

        template <typename Fun0>
        typename result_type<Fun0>::type operator()(const Fun0 &fun0) const
        {
            return typename result_type<Fun0>::type(fun0, fun1);
        }
    };

    template <typename Fun1>
    inline FunExecSequence<Fun1> funExecSequence(const Fun1 &fun1)
    {
        return FunExecSequence<Fun1>(fun1);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
