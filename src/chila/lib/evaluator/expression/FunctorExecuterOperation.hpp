/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_LIB_EVALUATOR_EXPRESSION__FUNCTOREXECUTEROPERATION_HPP
    #define CHILA_LIB_EVALUATOR_EXPRESSION__FUNCTOREXECUTEROPERATION_HPP

    #include <boost/mpl/size.hpp>
    #include <boost/mpl/at.hpp>
    #include <boost/preprocessor.hpp>
    #include "expression.hpp"

    #define ARG_VEC_SIZE boost::mpl::size<typename Function::argument_types>::value

    #include "nspDef.hpp"

    MY_NSP_START
    {
        template <typename Function, bool _isConstant, unsigned argCount>
        struct FunctorExecuterOperationImpl
        {
        };

        template <typename Function, bool _isConstant>
        struct FunctorExecuterOperation : public FunctorExecuterOperationImpl<Function, _isConstant, ARG_VEC_SIZE>
        {
            FunctorExecuterOperation(const std::string &name, Function fun, const ArgumentListSCPtr &argList) :
                FunctorExecuterOperationImpl<Function, _isConstant, ARG_VEC_SIZE>(name, fun, argList) {}
        };

    }
    MY_NSP_END

    #include "nspUndef.hpp"

    #define BOOST_PP_ITERATION_LIMITS   (0, 10)
    #define BOOST_PP_FILENAME_1         <chila/lib/evaluator/expression/FunctorExecuterOperation.hpp>
    #include BOOST_PP_ITERATE()

    #undef ARG_VEC_SIZE

    #endif

#else

    #define argCount BOOST_PP_ITERATION()

    #include "nspDef.hpp"

    MY_NSP_START
    {

        #define TMPL_PARAM(z, index, data) , typename _Arg##index

        #define EVAL_ARG(z, index, aList) arg##index->evaluate(valueMap)

        #define IS_COMP_ARG(z, index, data) \
            && std::dynamic_pointer_cast<const Arg##index##EvType>(aList[index])

//        #define SHOW_TYPE_ID(z, index, data) SHOW(typeid(aList[index].get()).name());

        #define TYPEDEF_ARG(z, index, data) \
            typedef typename boost::mpl::at_c<Arguments, index>::type Arg##index;

        #define TYPEDEF_EVALUABLE(z, index, data) \
            typedef Evaluable<Arg##index> Arg##index##EvType; CHILA_LIB_MISC__FWDEC_SPTR(Arg##index##EvType);

        #define DEC_VAR(z, index, data) Arg##index##EvTypeSCPtr arg##index;

        #define SET_VAR(z, index, aList) \
            if (!(arg##index = std::dynamic_pointer_cast<const Arg##index##EvType>(aList[index])))    \
                throw IncompatibleArgumentList();

        /** Defines an operation that executes a functor on the arguments. */
        template <typename Functor, bool _isConstant>
        struct FunctorExecuterOperationImpl<Functor, _isConstant, argCount>: public Operation,
            public Evaluable<typename Functor::result_type>
        {
            typedef typename Functor::result_type Ret;
            typedef typename Functor::argument_types Arguments;

            BOOST_PP_REPEAT(argCount, TYPEDEF_ARG,);
            BOOST_PP_REPEAT(argCount, TYPEDEF_EVALUABLE,);
            BOOST_PP_REPEAT(argCount, DEC_VAR,);

            Functor fun;

            FunctorExecuterOperationImpl(const std::string &name, Functor fun,
                    const ArgumentListSCPtr &argList) :
                Operation(name, argList), fun(fun)
            {
                my_assert(argList);
                if (argCount != argList->size())
                    throw IncompatibleArgumentList();

                BOOST_PP_REPEAT(argCount, SET_VAR, (*argList));
            }

            Ret evaluate(const ValueMap &valueMap) const
            {
                return fun(BOOST_PP_ENUM(argCount, EVAL_ARG,));
            }

            ValueSCPtr evaluateOnValue(const ValueMap &valueMap) const
            {
                return std::make_shared< ValueBase<Ret> >(evaluate(valueMap));
            }

            bool isConstant() const { return _isConstant; }
        };

        #undef ClassName
        #undef TMPL_PARAM
        #undef EVAL_ARG
        #undef IS_COMP_ARG
        #undef DEF_FUN_EXECUTER_OP
        #undef TYPEDEF_ARG
        #undef TYPEDEF_EVALUABLE
        #undef DEC_VAR
        #undef SET_VAR


    }
    MY_NSP_END

    #include "nspUndef.hpp"


#endif
