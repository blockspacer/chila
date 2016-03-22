/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__NULLFUNCTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__NULLFUNCTIONS_HPP

#include "fwd.hpp"
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/hana.hpp>

#include <boost/call_traits.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename FunctionsFSeq>
    void nullFunctions(const FunctionsFSeq &functions)
    {
        boost::hana::for_each(functions, [&](auto &funMData)
        {
            funMData.passFunAndSet([](auto function)
            {
                return [](auto ...arg){};
            });
        });
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
