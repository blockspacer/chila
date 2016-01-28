/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP

#include <boost/fusion/include/make_set.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <chila/lib/misc/exceptions.hpp>

#define my_assert       CHILA_LIB_MISC__ASSERT
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXECUTE_EVENT(executer, event) \
    executer.execute<Connector::Events::MData_##event>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename _EventFSeq>
    class EventExecuter
    {
        public:
            using result_type = void;
            using EventFSeq = _EventFSeq;

            EventExecuter(const EventFSeq &eventFSeq) : eventFSeq(eventFSeq), executed(false) {}

            EventExecuter(const EventExecuter &rhs) : eventFSeq(rhs.eventFSeq), executed(false)
            {
                rhs.executed = true; // just to render it unusable
            }

//            EventExecuter(EventExecuter &&rhs) : eventFSeq(rhs.eventFSeq), executed(false)
//            {
//                my_assert(!rhs.executed);
//                rhs.executed = true; // just to render it unusable
//            }

            template <typename Event, typename ...Args>
            void execute(const Args&... args) const
            {
//                my_assert(!executed); // the whole "execute once" should be rethinked, maybe an execution order is preferable
//                executed = true;

                static_assert(boost::fusion::result_of::has_key<EventFSeq, Event&>::type::value, "event not found");

                auto &ev = boost::fusion::at_key<Event&>(eventFSeq);

                if (ev) ev(args...);
            }

        protected:
            const EventFSeq &eventFSeq;
            mutable bool executed;
    };


    template <typename EventFSeq>
    inline EventExecuter<EventFSeq> eventExecuter(const EventFSeq &eventFSeq)
    {
        return EventExecuter<EventFSeq>(eventFSeq);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#undef my_assert
#endif
