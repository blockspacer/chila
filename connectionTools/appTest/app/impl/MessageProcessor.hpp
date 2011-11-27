/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    class MessageProcessor : public connection::MessageProcessor::CProvider
    {
        public:
            connection::MessageProcessor::Connector connector;

            MessageProcessor(boost::asio::io_service &ioService) : ioService(ioService)
            {
                connector.bindActions(*this);
            }

            connection::MessageProcessor::Connector &getConnector() { return connector; }

            void start()
            {
                connector.events.started();
            }

            void processMessage(const ProcMessageSCPtr &procMessage);

       private:
            typedef boost::shared_ptr<boost::asio::deadline_timer> TimerSPtr;
            boost::asio::io_service &ioService;

            void sendResponse(const BufferSCPtr &buffer, const ProcMessageSCPtr &procMessage, const TimerSPtr &timer)
            {
                connector.events.messageProcessed(buffer, procMessage);
            }
    };
}}}}}

#undef MT_CODEGEN_NSP
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif

