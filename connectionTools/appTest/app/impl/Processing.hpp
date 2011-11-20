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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_PROCESSING_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_PROCESSING_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "../connectors/gen/Processing.hpp"
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
    class Processing
    {
        private:
            typedef Processing This;

        public:
            struct DataTypes
            {
                typedef const ProcMessageSCPtr& procMessage;
                typedef const BufferSCPtr& outBuffer;
                typedef const std::string& connectorName;
            };

            typedef connectors::gen::Processing<DataTypes> Connector;
            Connector connector;

        private:
            typedef boost::shared_ptr<boost::asio::deadline_timer> TimerSPtr;

            boost::asio::io_service &ioService;

            void sendResponse(const BufferSCPtr &buffer, const ProcMessageSCPtr &procMessage, const TimerSPtr &timer)
            {
                connector.events.messageProcessed(buffer, procMessage);
            }

        public:
            Processing(boost::asio::io_service &ioService) : ioService(ioService)
            {
                connector.bindActions(*this);
            }
//            void init() {}
//            void start(const CompletedFun &completedFun) {}
//            void finish(const CompletedFun &completedFun) {}

            void processMessage(const ProcMessageSCPtr &procMessage)
            {
                const BufferSCPtr &recvBuff = procMessage->getBuffer();
                BufferSPtr respBuff = boost::make_shared<Buffer>(recvBuff->size() + 1);

                *std::transform(recvBuff->begin(), recvBuff->end(), respBuff->begin(), &toupper) = '\n';

                TimerSPtr timer = boost::make_shared<boost::asio::deadline_timer>(boost::ref(ioService),
                        boost::posix_time::seconds(5));
                timer->async_wait(boost::bind(&Processing::sendResponse, this, respBuff, procMessage, timer));
            }
    };
}}}}}

#undef MT_CODEGEN_NSP
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
