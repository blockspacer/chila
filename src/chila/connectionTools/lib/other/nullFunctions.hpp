/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__NULLFUNCTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__NULLFUNCTIONS_HPP

#include "fwd.hpp"
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/call_traits.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct NullFunction
    {
        template <typename FunctionMData>
        struct NullFunFPS
        {
            struct NullFun
            {
                typedef void result_type;

                template <typename... Arg>
                void operator()(const Arg&... arg) const {}
            };

            typedef NullFun result_type;

            result_type operator()(const typename FunctionMData::Function &function) const
            {
                return NullFun();
            }
        };

        template <typename FunctionMData>
        void operator()(FunctionMData &funMData) const
        {
            funMData.passFunAndSet(NullFunFPS<FunctionMData>());
        }
    };

    template <typename FunctionsFSeq>
    void nullFunctions(const FunctionsFSeq &functions)
    {
        boost::fusion::for_each(functions, NullFunction());
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
