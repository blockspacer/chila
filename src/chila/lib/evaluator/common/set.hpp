/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_COMMON__SET_HPP
#define CHILA_LIB_EVALUATOR_COMMON__SET_HPP

#include "util.hpp"
#include "defMacros.hpp"


#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Type>
    struct CreateSet
    {
        typedef std::set<Type> Set;
        typedef boost::shared_ptr<Set> SetSPtr;
        typedef boost::shared_ptr<const Set> SetSCPtr;
        typedef SetSCPtr result_type;

        SetSCPtr operator()() const { return boost::make_shared<Set>(); }

        #define SET_INSERT(z, index, argCount) ret->insert(arg##index);

        #define DEF_OP(z, argCount, data) \
            template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                             \
            SetSCPtr operator()(BOOST_PP_ENUM_BINARY_PARAMS(argCount, const Arg, &arg)) const   \
            {                                                                                   \
                SetSPtr ret = boost::make_shared<Set>();                                        \
                BOOST_PP_REPEAT(argCount, SET_INSERT,)                                          \
                return ret;                                                                     \
            }

        BOOST_PP_REPEAT_FROM_TO(1, 10, DEF_OP,)

        #undef DEF_OP
        #undef SET_INSERT
    };

    template <typename Boolean, typename Type>
    struct IsMemberOfSet
    {
        typedef std::set<Type> Set;
        typedef boost::shared_ptr<const Set> SetSCPtr;

        typedef Boolean result_type;

        Boolean operator()(const SetSCPtr &set, const Type &element) const
        {
            return set->find(element) != set->end();
        }
    };

    template <typename Boolean, typename Type>
    void addSetOperations(expNSP::OperationProviderMap &providerMap)
    {
        typedef std::set<Type> Set;
        typedef boost::shared_ptr<const Set> SetSCPtr;

        // ----------------------------------- Construction ------------------------------------------------
        addProvider<true>(providerMap, "set", adapt_fun_0(SetSCPtr)(CreateSet<Type>()));

        #define TYPE(z, index, data) Type

        #define ADD_CONS_PROVIDER(z, argCount, data)                                            \
            addProvider<true>(providerMap, "set",                                               \
                adapt_fun_n(SetSCPtr, BOOST_PP_ENUM(argCount, TYPE,))(CreateSet<Type>()));

        BOOST_PP_REPEAT_FROM_TO(1, 10, ADD_CONS_PROVIDER,)

        #undef TYPE
        #undef ADD_CONS_PROVIDER

        // -------------------------------------- Other ----------------------------------------------------

        addProvider<true>(providerMap, "is_member",
            adapt_fun_n(Boolean, SetSCPtr, Type)(IsMemberOfSet<Boolean, Type>()));
    }
}
MY_NSP_END

#include "nspUndef.hpp"


#endif

