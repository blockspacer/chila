/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON__UTIL_HPP
#define CHILA_CONNECTIONTOOLS_COMMON__UTIL_HPP

#include "common/impl/connection/Forwarder.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{

    struct ForwarderQPoster
    {
        using result_type = void;
        boost::asio::io_service &queue;

        ForwarderQPoster(boost::asio::io_service &queue) : queue(queue) {}

        template <typename EventExecuter, typename Object>
        void operator()(const EventExecuter &eventExecuter, const Object &object) const
        {
            queue.post([eventExecuter, object]
            {
                eventExecuter.template execute<common::impl::connection::Forwarder::CProvider::Connector::Events::MData_forwarded>(object);
            });
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
