/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONIMPLEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONIMPLEXECUTER_HPP

#include "EventExecuter.hpp"
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename MemFn, typename Object, typename EventFSeq>
    struct ActionImplExecuter
    {
        public:
            using result_type = void;

            ActionImplExecuter(const ActionImplExecuter&) = default;

            ActionImplExecuter(const MemFn &fun, Object &object, const EventFSeq &eventFSeq) :
                eventFSeq(eventFSeq), object(object), fun(fun) {}

            template <typename ...Args>
            void operator()(const Args&... arg)
            {
                this->fun(this->object, arg..., eventExecuter(eventFSeq));
            }


        private:
            const EventFSeq &eventFSeq;
            MemFn fun;
            Object &object;
    };

    template <typename MemFn, typename Object, typename EventFSeq>
    inline ActionImplExecuter<MemFn, Object, EventFSeq> actionImplExecuter(const MemFn &fun, Object &object, const EventFSeq &eventFSeq)
    {
        return ActionImplExecuter<MemFn, Object, EventFSeq>(fun, object, eventFSeq);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
