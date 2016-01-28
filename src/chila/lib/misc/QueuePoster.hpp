/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#warning Not tested


#ifndef CHILA_LIB_MISC__QUEUEPOSTER_HPP
#define CHILA_LIB_MISC__QUEUEPOSTER_HPP

#include <boost/bind.hpp>

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Queue, typename Fun>
    struct QueuePoster
    {
        typedef void result_type;
        typedef typename boost::unwrap_reference<Queue>::type UnwrapedQueue;
        typedef typename boost::unwrap_reference<Fun>::type UnwrapedFun;

        Fun fun;
        Queue queue;

        QueuePoster(Queue queue, Fun fun) : queue(queue), fun(fun) {}

        UnwrapedQueue &getQueue() { return boost::unwrap_ref(queue); }
        UnwrapedFun &getFun()     { return boost::unwrap_ref(fun); }

        #ifdef __clang__
            template <typename... Arg>
            void operator()(const Arg&... arg)
            {
                getQueue().post([=]{ getFun()(arg...); });
            }
        #else
            #define CHILA_LIB_MISC__DEF_OPER(z, n, data) \
                    BOOST_PP_IF(n, template <,) \
                        BOOST_PP_ENUM_PARAMS(n, typename Arg) \
                    BOOST_PP_IF(n, >,) \
                    void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, Arg, &&arg)) \
                    { \
                        getQueue().post([&]{ fun(BOOST_PP_ENUM_PARAMS(n, arg)); }); \
                    }

            BOOST_PP_REPEAT_FROM_TO(0, 49, CHILA_LIB_MISC__DEF_OPER,)

            #undef CHILA_LIB_MISC__DEF_OPER
        #endif
    };

    template <typename Queue, typename Fun>
    QueuePoster<Queue, Fun> queuePoster(Queue queue, Fun fun)
    {
        return QueuePoster<Queue, Fun>(queue, fun);
    }

    struct SetPostFun
    {
        template <typename Function>
        struct result_type
        {
            typedef chila::lib::misc::QueuePoster<boost::reference_wrapper<boost::asio::io_service>, Function> type;
        };

        boost::asio::io_service &queue;

        SetPostFun(boost::asio::io_service &queue) : queue(queue) {}

        template <typename Function>
        typename result_type<Function>::type operator()(const Function &function) const
        {
            return chila::lib::misc::queuePoster(boost::ref(queue), function);
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#undef CHILA_LIB_MISC__DEF_OPER

#endif