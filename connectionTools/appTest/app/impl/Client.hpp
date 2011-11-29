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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_CLIENT_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_CLIENT_HPP

#include "fwd.hpp"
#include <limits>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    class Client
    {
        private:
            boost::asio::ip::tcp::socket socket;
            unsigned id;

        public:
            typedef boost::function<void(const BufferSCPtr&,
                    const boost::system::error_code&)> ReadHandlerFun;
            typedef boost::function<void(const boost::system::error_code&,
                    unsigned bytesTransferred)> WriteHandlerFun;

            Client(boost::asio::io_service &ioService) :
                id(std::numeric_limits<unsigned>::max()), socket(ioService) {}

            unsigned getId() const { return id; }
            unsigned setId(unsigned id)
            {
                assert(this->id == std::numeric_limits<unsigned>::max());
                this->id = id;
            }

            template <typename Handler>
            void accept(boost::asio::ip::tcp::acceptor &acceptor, Handler handler)
            {
                acceptor.async_accept(socket, handler);
            }

            void readMessage(const ReadHandlerFun &readHandler)
            {
                BufferSPtr buffer = boost::make_shared<Buffer>(1024);

                async_read(socket, boost::asio::buffer(*buffer),
                    boost::bind(&Client::readCompletionCond, this, boost::ref(*buffer), _1, _2),
                    boost::bind(&Client::readHandler, this, buffer, readHandler, _1, _2));
            }

            void writeMessage(const BufferSCPtr &buffer, const WriteHandlerFun &writeHandler)
            {
                BufferSPtr sndBuffer = boost::make_shared<Buffer>(*buffer);
                sndBuffer->push_back('\n');

                async_write(socket, boost::asio::buffer(*sndBuffer),
                        boost::bind(&Client::writeHandler, this, writeHandler, sndBuffer, _1, _2));
            }

            std::size_t readCompletionCond(const Buffer &buffer, const boost::system::error_code &ec,
                std::size_t bytes_transferred) const
            {
                if (ec) return 0;

                if (bytes_transferred && buffer.at(bytes_transferred - 1) == '\n')
                    return 0;
                else
                    return buffer.size() - bytes_transferred;
            }

            void readHandler(const BufferSPtr &buffer, const ReadHandlerFun &readHandler,
                const boost::system::error_code &ec, std::size_t bytes_transferred)
            {
                if (bytes_transferred) buffer->resize(bytes_transferred - 2);
                readHandler(buffer, ec);
            }

            void writeHandler(const WriteHandlerFun &writeHandler, const BufferSCPtr &buffer,
                const boost::system::error_code &ec, std::size_t bytes_transferred)
            {
                writeHandler(ec, bytes_transferred);
            }
    };

}}}}}

#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
