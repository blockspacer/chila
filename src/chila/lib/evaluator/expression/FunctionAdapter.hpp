/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_LIB_EVALUATOR_EXPRESSION__FUNCTIONADAPTER_HPP
    #define CHILA_LIB_EVALUATOR_EXPRESSION__FUNCTIONADAPTER_HPP

    #include <boost/preprocessor.hpp>

    #define MAX_ARGS 10

    #define TMPL_ARG(z, index, data) , typename Arg##index = no_arg

    struct no_arg {};

    #include "nspDef.hpp"

    MY_NSP_START
    {
        template <typename Function, typename Ret BOOST_PP_REPEAT(BOOST_PP_INC(MAX_ARGS), TMPL_ARG,)>
        struct FunctionAdapter {};

    }
    MY_NSP_END

    #include "nspUndef.hpp"

    #undef TMPL_ARG

    #define BOOST_PP_ITERATION_LIMITS   (0, MAX_ARGS)
    #define BOOST_PP_FILENAME_1         <chila/lib/evaluator/expression/FunctionAdapter.hpp>
    #include BOOST_PP_ITERATE()

    #undef MAX_ARGS
    #include "undefMacros.hpp"
    #endif

#else

    #define argCount BOOST_PP_ITERATION()
    #define TMPL_ARG(z, index, data) , typename Arg##index
    #define TMPL_ARG_PASSED(z, index, data) , Arg##index
    #define TMPL_ARG_DEFAULT(z, index, data) , no_arg
    #define ARG_LIMIT BOOST_PP_DEC(MAX_ARGS)
    #define TMPL_ARG_PASSED_TO_VEC(z, index, data) Arg##index
    #define OP_ARG_PASSED_TO_VEC(z, index, data) const Arg##index &arg##index

    #include "nspDef.hpp"

    MY_NSP_START
    {
        template <typename Function, typename Ret BOOST_PP_REPEAT(argCount, TMPL_ARG,)>
        struct FunctionAdapter<Function, Ret BOOST_PP_REPEAT(argCount, TMPL_ARG_PASSED,)
            BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_PP_INC(MAX_ARGS), argCount), TMPL_ARG_DEFAULT,)>
        {
            typedef Ret result_type;
            typedef boost::mpl::vector<BOOST_PP_ENUM(argCount, TMPL_ARG_PASSED_TO_VEC,)> argument_types;

            Function fun;

            FunctionAdapter(Function fun) : fun(fun) {}

            result_type operator()(BOOST_PP_ENUM(argCount, OP_ARG_PASSED_TO_VEC,)) const
            {
                return fun(BOOST_PP_ENUM_PARAMS(argCount, arg));
            }
        };

        template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg) BOOST_PP_COMMA_IF(argCount) typename Function>
        inline FunctionAdapter<Function, typename Function::result_type
            BOOST_PP_COMMA_IF(argCount) BOOST_PP_ENUM_PARAMS(argCount, Arg)> functionAdapter(Function fun)
        {
            return FunctionAdapter<Function, typename Function::result_type
                BOOST_PP_COMMA_IF(argCount) BOOST_PP_ENUM_PARAMS(argCount, Arg)>(fun);
        }

        template <typename Ret, BOOST_PP_ENUM_PARAMS(argCount, typename Arg)
            BOOST_PP_COMMA_IF(argCount) typename Function>
        inline FunctionAdapter<Function, Ret BOOST_PP_COMMA_IF(argCount) BOOST_PP_ENUM_PARAMS(argCount, Arg)>
            functionAdapterWithRet(Function fun)
        {
            return FunctionAdapter<Function, Ret
                BOOST_PP_COMMA_IF(argCount) BOOST_PP_ENUM_PARAMS(argCount, Arg)>(fun);
        }

    }
    MY_NSP_END

    #include "nspUndef.hpp"

    #undef argCount

#endif
