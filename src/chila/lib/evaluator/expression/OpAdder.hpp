/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_LIB_EVALUATOR_EXPRESSION__OPADDER_HPP
    #define CHILA_LIB_EVALUATOR_EXPRESSION__OPADDER_HPP


    #include "nspDef.hpp"

    MY_NSP_START
    {
        template <typename Fun, unsigned argCount>
        struct OpAdderImpl {};

        template <typename Fun>
        struct OpAdder {};
    }
    MY_NSP_END

    #include "nspUndef.hpp"
    #endif

#else

    #define argCount BOOST_PP_ITERATION()

    DEF_NAMESPACE6(py,com,personal,lib,evaluator,expression)
    {
        struct OpAdder
    }
    MY_NSP_END

    #include "nspUndef.hpp"


#endif
