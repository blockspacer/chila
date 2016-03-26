/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__MESSAGEPROCESSOR_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__MESSAGEPROCESSOR_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/MessageProcessor.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <ctype.h>


#define MODULE_NAME MessageProcessor

#include "nspDef.hpp"

MY_NSP_START
{
    class MessageProcessor final: public connection::MessageProcessor::CProvider
    {
        public:
            using Connector = connection::MessageProcessor::Connector;
            using ArgTypes = connection::MessageProcessor::ArgTypes;

            Connector connector;

            MessageProcessor(boost::asio::io_service &ioService) : ioService(ioService)
            {
                connector.bindActions(*this);
            }

            connection::MessageProcessor::Connector &getConnector() { return connector; }

            void MOD_ACTION_SIG(launcher_start)  { execute_event(launcher_started)();  }

            void MOD_ACTION_SIG(processMessage);

       private:
            using TimerSPtr=  std::shared_ptr<boost::asio::deadline_timer>;
            boost::asio::io_service &ioService;

            void sendResponse(const BufferSCPtr &buffer, const ProcMessageSCPtr &procMessage, const TimerSPtr &timer, ev_executer_arg(processMessage))
            {
                execute_event(messageProcessed)(buffer, procMessage);
            }
    };
}
MY_NSP_END

#include "nspUndef.hpp"
#endif

