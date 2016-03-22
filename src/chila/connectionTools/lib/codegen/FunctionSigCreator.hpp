/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNCTIONSIGCREATOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNCTIONSIGCREATOR_HPP

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/function.hpp>
#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/vector.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename Arguments, unsigned ArgCount>
    struct FunctionSigCreatorImpl {};

    template <typename Arguments>
    struct FunctionSigCreator : FunctionSigCreatorImpl<Arguments, decltype(boost::hana::length(Arguments{}))::value>
    {
    };

    #define DEF_ARG(z, n, data) \
        typename decltype(boost::hana::traits::remove_reference(boost::hana::at(Arguments{}, boost::hana::int_c<n>)))::type::ParamType

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

