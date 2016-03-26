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
        const BufferSCPtr &recvBuff = procMessage->getBuffer();
        BufferSPtr respBuff = std::make_shared<Buffer>(recvBuff->size());

        *std::transform(recvBuff->begin(), recvBuff->end(), respBuff->begin(), &toupper);

        TimerSPtr timer = std::make_shared<boost::asio::deadline_timer>(boost::ref(ioService),
                boost::posix_time::seconds(5));
        timer->async_wait(boost::bind(&MessageProcessor::sendResponse, this, respBuff, procMessage, timer, eventExecuter));
    }

    connection::MessageProcessor::CProviderSPtr connection::MessageProcessor::create(boost::asio::io_service &ioService)
    {
        return std::make_shared<app::impl::MessageProcessor>(boost::ref(ioService));
    }
}
MY_NSP_END
