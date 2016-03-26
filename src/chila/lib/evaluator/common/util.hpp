/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_COMMON__UTIL_HPP
#define CHILA_LIB_EVALUATOR_COMMON__UTIL_HPP

#include "util.hpp"
#include <boost/mpl/vector.hpp>
#include <chila/lib/evaluator/expression/FunctorExecuterOperation.hpp>
#include <chila/lib/evaluator/expression/OperationProviderMap.hpp>
#include <chila/lib/evaluator/expression/VariableProviderMap.hpp>
#include <chila/lib/evaluator/expression/FunctionAdapter.hpp>
#include <boost/make_shared.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chila/lib/misc/Construct.hpp>
#include <boost/bind.hpp>
#include <set>
#include <boost/lexical_cast.hpp>
#include <chila/lib/evaluator/expression/defMacros.hpp>
#include "defMacros.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    template <bool isConstant, typename Function>
    inline void addProvider(expNSP::OperationProviderMap &providerMap, const std::string &name, Function fun)
    {
        typedef expNSP::FunctorExecuterOperation<Function, isConstant> FExOp;
        typedef expNSP::BaseOperationProvider<FExOp, Function> Provider;

        providerMap.add(name, std::make_shared<Provider>(name, fun));
    }

    #define BIND_PARAM(z, index, data) , BOOST_PP_CAT(_, BOOST_PP_INC(index))

    #define DEF_CONS_PROVIDER(z, argCount, data)    \
        template <bool isConstant, typename Ret, typename Type                                              \
            BOOST_PP_ENUM_TRAILING_PARAMS(argCount, typename Arg)>                                          \
        inline void addConstructProvider(expNSP::OperationProviderMap &providerMap, const std::string &name)\
        {                                                                                                   \
            addProvider<isConstant>(providerMap, name,                                                      \
                expNSP::functionAdapterWithRet<Ret                                                          \
                    BOOST_PP_ENUM_TRAILING_PARAMS(argCount, Arg)>(boost::bind                               \
                    (                                                                                       \
                        chila::lib::misc::Construct<Type>()                                                 \
                        BOOST_PP_REPEAT(argCount, BIND_PARAM,)                                              \
                    )));                                                                                    \
        }

    BOOST_PP_REPEAT(10, DEF_CONS_PROVIDER,)

    #undef DEF_CONS_PROVIDER
    #undef BIND_PARAM

    def_unary_op ( Negation,        - );
    def_unary_op ( Not,             ! );

    def_binary_op( Addition,        + );
    def_binary_op( Substraction,    - );
    def_binary_op( Multiplication,  * );
    def_binary_op( Division,        / );

    def_binary_op( LessThan,        <  );
    def_binary_op( GreaterThan,     >  );
    def_binary_op( LessEqThan,      <= );
    def_binary_op( GreaterEqThan,   >= );

    def_binary_op( Equals,          == );
    def_binary_op( Different,       != );

    def_binary_op( Conjunction,     && );
    def_binary_op( Disjunction,     || );


    template <typename Boolean, typename Arg>
    inline void addEquality(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "=",  Equals           <Boolean, Arg, Arg>());
        addProvider<true>(providerMap, "!=", Different        <Boolean, Arg, Arg>());
    }

    template <typename Ret, typename Arg0, typename Arg1>
    inline void addAdditionAndSubstraction(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "+",  Addition         <Ret, Arg0, Arg1>());
        addProvider<true>(providerMap, "-",  Substraction     <Ret, Arg0, Arg1>());
    }

    template <typename Boolean, typename Arg>
    inline void addRelational(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "<",  LessThan         <Boolean, Arg, Arg>());
        addProvider<true>(providerMap, ">",  GreaterThan      <Boolean, Arg, Arg>());
        addProvider<true>(providerMap, "<=", LessEqThan       <Boolean, Arg, Arg>());
        addProvider<true>(providerMap, ">=", GreaterEqThan    <Boolean, Arg, Arg>());

        addEquality<Boolean, Arg>(providerMap);
    }


//
//    void addOperations(expNSP::OperationProviderMap &providerMap)
//    {
//        addBooleanOperations(providerMap);
//        addNumericOperations(providerMap);
//        addStringOperations(providerMap);
//        addDateTimeOperations(providerMap);
//
//
//        addSetOperations<Numeric>(providerMap);
//        addSetOperations<String>(providerMap);
//    }


}
MY_NSP_END

#include "nspUndef.hpp"

#undef expNSP

#endif

