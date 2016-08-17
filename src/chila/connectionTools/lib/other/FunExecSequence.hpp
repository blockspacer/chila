/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNEXECSEQUENCE_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNEXECSEQUENCE_HPP



#include "macrosExp.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Fun1>
    inline auto funExecSequence(const Fun1 &fun1)
    {
        return [fun1](const auto &fun0)
        {
            return chila::lib::misc::funExecSequence(fun0, fun1);
        };
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
