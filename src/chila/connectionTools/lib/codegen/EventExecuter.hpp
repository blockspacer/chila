/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP

//#include <boost/fusion/include/make_set.hpp>
//#include <boost/fusion/include/has_key.hpp>
//#include <boost/fusion/include/at_key.hpp>
#include <chila/lib/misc/exceptions.hpp>

#define my_assert       CHILA_LIB_MISC__ASSERT
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXECUTE_EVENT(executer, event) \
    executer.execute<Connector::Events::MData_##event>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename _EventFSet>
    class EventExecuter
    {
        public:
            using result_type = void;
            using EventFSet = _EventFSet;

            EventExecuter(const EventFSet &eventFSet) : eventFSet(eventFSet), executed(false) {}

            EventExecuter(const EventExecuter &rhs) : eventFSet(rhs.eventFSet), executed(false)
            {
                rhs.executed = true; // just to render it unusable
            }

//            EventExecuter(EventExecuter &&rhs) : eventFSet(rhs.eventFSet), executed(false)
//            {
//                my_assert(!rhs.executed);
//                rhs.executed = true; // just to render it unusable
//            }

            template <typename Event, typename ...Args>
            void execute(const Args&... args) const
            {
//                my_assert(!executed); // the whole "execute once" should be rethinked, maybe an execution order is preferable
//                executed = true;

                abort();

//                static_assert(boost::fusion::result_of::has_key<EventFSet, Event&>::type::value, "event not found");
//
//                auto &ev = boost::fusion::at_key<Event&>(eventFSet);
//
//                if (ev) ev(args...);
            }

        protected:
            const EventFSet &eventFSet;
            mutable bool executed;
    };


    template <typename EventFSet>
    inline EventExecuter<EventFSet> eventExecuter(const EventFSet &eventFSet)
    {
        return EventExecuter<EventFSet>(eventFSet);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#undef my_assert
#endif
