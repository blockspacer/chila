/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_LIB_EVALUATOR_EXPRESSION__EVALUABLE_VECTOR_HPP
    #define CHILA_LIB_EVALUATOR_EXPRESSION__EVALUABLE_VECTOR_HPP

    #include <boost/fusion/sequence/intrinsic/size.hpp>
    #include <boost/mpl/size.hpp>
    #include <boost/preprocessor.hpp>
    #include <boost/fusion/container/vector.hpp>
    #include <boost/mpl/vector.hpp>
    #include "expression.hpp"

    #include "nspDef.hpp"

    MY_NSP_START
    {
        template <typename MPLForwardSeq, unsigned argCount>
        struct MakeEvaluableVectorImpl {};

        template <typename MPLForwardSeq>
        struct MakeEvaluableVector :
            public MakeEvaluableVectorImpl< MPLForwardSeq, boost::mpl::size<MPLForwardSeq>::value >
        {
        };

        template <typename MPLForwardSeq, unsigned argCount>
        struct CallFunctionImpl {};

        template <typename EvalVector>
        struct CallFunction final: public CallFunctionImpl< EvalVector,
                boost::fusion::result_of::size<EvalVector>::value >
        {
            CallFunction(const EvalVector &args) :
                CallFunctionImpl< EvalVector, boost::fusion::result_of::size<EvalVector>::value >(args) {}
        };

        template <typename EvalVector>
        inline CallFunction<EvalVector> callFunction(const EvalVector &args)
        {
            return CallFunction<EvalVector>(args);
        }

    }
    MY_NSP_END

    #include "nspUndef.hpp"

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 10)
    #define BOOST_PP_FILENAME_1         <chila/lib/evaluator/expression/evaluable_vector.hpp>
    #include BOOST_PP_ITERATE()

    #endif

#else

    #include <boost/fusion/container/vector.hpp>

    #define argCount BOOST_PP_ITERATION()

    #define ARG_TYPE_AT(index) typename boost::mpl::at_c<MPLForwardSeq, index>::type
    #define EVALUABLE_TYPE_AT(index) Evaluable<ARG_TYPE_AT(index)>
    #define DEF_ARG(z, index, data) boost::shared_ptr< const EVALUABLE_TYPE_AT(index) >
    #define VALUE_AT(z, index, data) boost::fusion::at_c<index>(args)->evaluate(valueMap)

    CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,evaluator,expression)
    {

        template <typename MPLForwardSeq>
        struct MakeEvaluableVectorImpl<MPLForwardSeq, argCount>
        {
            typedef boost::fusion::vector<BOOST_PP_ENUM(argCount, DEF_ARG,)> type;
        };

        template <typename EvalVector>
        struct CallFunctionImpl<EvalVector, argCount>
        {
            const EvalVector &args;

            CallFunctionImpl(const EvalVector &args) : args(args) {}

            template <typename Function>
            typename Function::result_type operator()(Function fun, const ValueMap &valueMap) const
            {
                return fun(BOOST_PP_ENUM(argCount, VALUE_AT,));
            }
        };



    }
    MY_NSP_END

    #include "nspUndef.hpp"


    #undef VALUE_AT
    #undef ARG_TYPE_AT
    #undef EVALUABLE_TYPE_AT
    #undef DEF_ARG
    #undef argCount


#endif
