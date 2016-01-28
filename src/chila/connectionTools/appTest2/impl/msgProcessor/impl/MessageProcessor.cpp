/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "MessageProcessor.hpp"
#include <boost/make_shared.hpp>


#define MODULE_NAME MessageProcessor

#include "nspDef.hpp"

MY_NSP_START
{
    void MessageProcessor::MOD_ACTION_SIG(processMessage)
    {
        auto recvBuff = procMessage->getBuffer();
        auto respBuff = boost::make_shared<Buffer>(recvBuff->size());

        *std::transform(recvBuff->begin(), recvBuff->end(), respBuff->begin(), &toupper);

        TimerSPtr timer = boost::make_shared<boost::asio::deadline_timer>(boost::ref(ioService),
                boost::posix_time::seconds(5));

        timer->async_wait([this, eventExecuter, respBuff, procMessage, timer](const boost::system::error_code &ec)
        {
            if (!ec)
                execute_event(messageProcessed)(respBuff, procMessage);
        });
    }

    connection::MessageProcessor::CProviderSPtr connection::MessageProcessor::create(boost::asio::io_service &ioService)
    {
        return boost::make_shared<impl::MessageProcessor>(boost::ref(ioService));
    }
}
MY_NSP_END
