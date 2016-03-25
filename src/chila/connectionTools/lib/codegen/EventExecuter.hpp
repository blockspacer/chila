/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EVENTEXECUTER_HPP

#include <chila/lib/misc/exceptions.hpp>

#define my_assert       CHILA_LIB_MISC__ASSERT
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXECUTE_EVENT(executer, event) \
    executer.execute<Connector::Events::MData_##event>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename _EventHMap>
    class EventExecuter
    {
        public:
            using result_type = void;
            using EventHMap = _EventHMap;

            EventExecuter(const EventHMap &eventHMap) : eventHMap(eventHMap), executed(false) {}

            EventExecuter(const EventExecuter &rhs) : eventHMap(rhs.eventHMap), executed(false)
            {
                rhs.executed = true; // just to render it unusable
            }

//            EventExecuter(EventExecuter &&rhs) : eventHMap(rhs.eventHMap), executed(false)
//            {
//                my_assert(!rhs.executed);
//                rhs.executed = true; // just to render it unusable
//            }

            template <typename Event, typename ...Args>
            void execute(const Args&... args) const
            {
//                my_assert(!executed); // the whole "execute once" should be rethinked, maybe an execution order is preferable
//                executed = true;

//                abort();

//                static_assert(boost::fusion::result_of::has_key<EventHMap, Event&>::type::value, "event not found");
//
                auto &ev = boost::unwrap_ref(eventHMap[boost::hana::type_c<boost::reference_wrapper<Event>>]);

                if (ev) ev(args...);
            }

        protected:
            const EventHMap &eventHMap;
            mutable bool executed;
    };


    template <typename EventHMap>
    inline EventExecuter<EventHMap> eventExecuter(const EventHMap &eventHMap)
    {
        return EventExecuter<EventHMap>(eventHMap);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#undef my_assert
#endif
