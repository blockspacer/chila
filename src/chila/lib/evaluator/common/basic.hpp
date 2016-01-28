/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_COMMON__BASIC_HPP
#define CHILA_LIB_EVALUATOR_COMMON__BASIC_HPP

#include "util.hpp"
#include "defMacros.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Boolean>
    void addBooleanOperations(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "not", Not             <Boolean,   Boolean>()        );

        addProvider<true>(providerMap, "or",   Disjunction     <Boolean,   Boolean,   Boolean>());
        addProvider<true>(providerMap, "and",   Conjunction     <Boolean,   Boolean,   Boolean>());

//        addProvider(providerMap, "?", BooleanConditional);
    }

    template <typename Boolean, typename Numeric>
    void addNumericOperations(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "-",  Negation         <Numeric, Numeric>()        );

        addAdditionAndSubstraction<Numeric, Numeric, Numeric>(providerMap);
        addProvider<true>(providerMap, "*",  Multiplication   <Numeric, Numeric, Numeric>());
        addProvider<true>(providerMap, "/",  Division         <Numeric, Numeric, Numeric>());

        addRelational<Boolean, Numeric>(providerMap);
    }

    template <typename Boolean, typename Numeric, typename String>
    void addStringOperations(expNSP::OperationProviderMap &providerMap)
    {
        addProvider<true>(providerMap, "+",  Addition         <String, String, String>());

        addRelational<Boolean, String>(providerMap);

        addProvider<true>(providerMap, "string", lexical_cast_op(String, Numeric));
    }

}
MY_NSP_END

#include "nspUndef.hpp"

#endif

