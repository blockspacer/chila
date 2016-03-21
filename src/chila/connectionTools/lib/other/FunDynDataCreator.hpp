/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNDYNDATACREATOR_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNDYNDATACREATOR_HPP

    #include "FunDynData.hpp"
    #include <boost/hana/ext/boost/mpl/vector.hpp>

    #include "macrosExp.hpp"

    #define EX_SIZE decltype(boost::hana::length(typename FunctionMData::Arguments{}))::value

    #include "macros.fgen.hpp"

    MY_NSP_START
    {
        template <typename FunctionMData, unsigned argCount>
        struct FunDynDataCreatorImpl {};

        template <typename FunctionMData>
        struct FunDynDataCreator final: public FunDynDataCreatorImpl<FunctionMData, EX_SIZE>
        {
            FunDynDataCreator() : FunDynDataCreatorImpl<FunctionMData, EX_SIZE>() {}
        };
    }
    MY_NSP_END

    #include "macros.fgen.hpp"


    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 19)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/other/FunDynDataCreator.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_SIMPLE_TYPE_TS_SPEC
    #undef EX_SIZE

    #endif


#else

    #define argCount BOOST_PP_ITERATION()

    #include <chila/lib/misc/macrosExp.hpp>

    #define ARG_AT(pos) decltype(boost::hana::at(typename FunctionMData::Arguments{}, boost::hana::integral_constant<int, pos>{}))::type
    #define ARG_AT_ELEM(z, n, data) BOOST_PP_COMMA_IF(n) typename ARG_AT(n)::ParamType BOOST_PP_CAT(arg, n)
    #define ADD_TO_MAP(z, n, data) \
        ret.push(ARG_AT(n)::getName(), chila::lib::misc::refValHolder<typename ARG_AT(n)::ParamType>(BOOST_PP_CAT(arg, n)));

    #define argCount BOOST_PP_ITERATION()

    #include "macros.fgen.hpp"

    MY_NSP_START
    {
        template <typename FunctionMData>
        struct FunDynDataCreatorImpl<FunctionMData, argCount>
        {
            typedef FunDynData result_type;

            FunDynData operator()(BOOST_PP_REPEAT(argCount, ARG_AT_ELEM,)) const
            {
                FunDynData ret(FunctionMData::getName());

                BOOST_PP_REPEAT(argCount, ADD_TO_MAP,)

                return ret;
            }
        };

    }
    MY_NSP_END

    #include "macros.fgen.hpp"

    #undef ARG_AT
    #undef ARG_AT_ELEM
    #undef ADD_TO_MAP

#endif
