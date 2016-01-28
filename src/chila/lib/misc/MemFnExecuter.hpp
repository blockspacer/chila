/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__MEMFNEXECUTER_HPP
#define CHILA_LIB_MISC__MEMFNEXECUTER_HPP

#include <boost/ref.hpp>
#include <boost/preprocessor.hpp>

#define TMPL_ARG(z, index, data) typename Arg##index
#define OP_DEC_ARG(z, index, data) const Arg##index &arg##index
#define OP_PASS_ARG(z, index, data) arg##index

#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename MemFn, typename Object>
    struct MemFnExecuter
    {
        typedef typename MemFn::result_type result_type;

        MemFn fun;
        Object object;

        MemFnExecuter(MemFn fun, Object object) : fun(fun), object(object) {}

        result_type operator()() const
        {
            return boost::unwrap_ref(this->fun)(boost::unwrap_ref(this->object));
        }

        #define DEF_OPERATOR(z, argCount, data)                                                         \
            template <BOOST_PP_ENUM(argCount, TMPL_ARG,)>                                             \
            result_type operator()(BOOST_PP_ENUM(argCount, OP_DEC_ARG,)) const                        \
            {                                                                                           \
                return this->fun(this->object, BOOST_PP_ENUM(argCount, OP_PASS_ARG,));    \
            }

        BOOST_PP_REPEAT_FROM_TO(1, 19, DEF_OPERATOR,)
    };

    template <typename MemFn, typename Object>
    inline MemFnExecuter<MemFn, Object> memFnExecuter(MemFn fun, Object object)
    {
        return MemFnExecuter<MemFn, Object>(fun, object);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"


#undef DEF_OPERATOR
#undef TMPL_ARG
#undef OP_DEC_ARG
#undef OP_PASS_ARG
#undef DEF_NAMESPACE


#endif

