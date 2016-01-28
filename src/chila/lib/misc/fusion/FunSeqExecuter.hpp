/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC_FUSION__FUNSEQEXECUTER_HPP
#define CHILA_LIB_MISC_FUSION__FUNSEQEXECUTER_HPP

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/invoke_function_object.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/preprocessor.hpp>
#include <boost/mpl/set.hpp>


#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename FunFSeq>
    struct FunSeqExecuter
    {
        typedef void result_type;

        template <typename ArgFSeq>
        struct Executer
        {
            ArgFSeq args;
            Executer(const ArgFSeq &args) : args(args) {}

            template <typename Fun>
            void operator()(const Fun &fun) const
            {
                boost::fusion::invoke_function_object(boost::unwrap_ref(fun), args);
            }
        };

        template <typename ArgFSeq>
        Executer<ArgFSeq> executer(const ArgFSeq &args) const
        {
            return Executer<ArgFSeq>(args);
        }

        FunFSeq seq;
        FunSeqExecuter(const FunFSeq &seq) : seq(seq) {}

        void operator()() const
        {
            boost::fusion::for_each(seq, executer(boost::fusion::make_vector()));
        }

        #define DEF_OPERATOR(z, argCount, data) \
            template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                                     \
            void operator()(BOOST_PP_ENUM_BINARY_PARAMS(argCount, const Arg, &arg)) const               \
            {                                                                                           \
                boost::fusion::for_each(seq,                                                            \
                        executer(boost::fusion::make_vector(BOOST_PP_ENUM_PARAMS(argCount, arg))));     \
            }


        BOOST_PP_REPEAT_FROM_TO(1, 49, DEF_OPERATOR, )
    };

    template <typename FunFSeq>
    inline FunSeqExecuter<FunFSeq> funSeqExecuter(const FunFSeq &functions)
    {
        return FunSeqExecuter<FunFSeq>(functions);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef DEF_OPERATOR


#endif
