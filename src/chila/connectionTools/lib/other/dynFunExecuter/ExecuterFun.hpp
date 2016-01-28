/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__EXECUTERFUN_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__EXECUTERFUN_HPP


    #include <boost/mpl/size.hpp>
    #include <boost/lexical_cast.hpp>
    #include <chila/lib/misc/exceptions.hpp>

    #define EX_SIZE boost::mpl::size<typename FunctionMData::Arguments>::value
    #include "macros.fgen.hpp"

    MY_NSP_START
    {
        template <typename FunctionMData, unsigned argCount>
        struct ExecuterFunImpl {};

        template <typename FunctionMData>
        struct ExecuterFun final: public ExecuterFunImpl<FunctionMData, EX_SIZE>
        {
            ExecuterFun(const FunctionMData &fun) : ExecuterFunImpl<FunctionMData, EX_SIZE>(fun) {}
        };

        template <typename FunctionMData>
        inline ExecuterFun<FunctionMData> dfExecuterFun(const FunctionMData &fun)
        {
            return ExecuterFun<FunctionMData>(fun);
        }
    }
    MY_NSP_END

    #include "macros.fgen.hpp"


    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 19)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/other/dynFunExecuter/ExecuterFun.hpp>
    #include BOOST_PP_ITERATE()

    #undef EX_SIZE

    #endif


#else

    #define argCount BOOST_PP_ITERATION()

    #define ARG_AT(pos) boost::mpl::at_c<typename FunctionMData::Arguments, pos>::type
    #define ARG_AT_ELEM(z, n, data) BOOST_PP_COMMA_IF(n) getArg<typename ARG_AT(n)>(arguments)

    #include "macros.fgen.hpp"

    MY_NSP_START
    {
        template <typename FunctionMData>
        struct ExecuterFunImpl<FunctionMData, argCount>
        {
            const FunctionMData &fun;

            ExecuterFunImpl(const FunctionMData &fun) : fun(fun) {}

            void operator()(const ArgumentStrMap &arguments) const
            {
                fun(BOOST_PP_REPEAT(argCount, ARG_AT_ELEM,));
            }

            template <typename MData>
            typename MData::Type getArg(const ArgumentStrMap &arguments) const
            {
                auto it = arguments.find(MData::getName());
                my_assert(it != arguments.end());

                return boost::lexical_cast<typename MData::Type>(it->second);
            }
        };

    }
    MY_NSP_END

    #include "macros.fgen.hpp"

    #undef ARG_AT
    #undef ARG_AT_ELEM

#endif
