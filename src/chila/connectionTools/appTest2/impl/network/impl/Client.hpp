/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_NETWORK_IMPL__CLIENT_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_NETWORK_IMPL__CLIENT_HPP

#include "fwd.hpp"
#include <limits>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    class Client
    {
        public:
            using ReadHandlerFun = boost::function<void(const BufferSCPtr&,
                    const boost::system::error_code&)>;
            using WriteHandlerFun = boost::function<void(const boost::system::error_code&,
                    unsigned bytesTransferred)>;

            Client(boost::asio::io_service &ioService) :
                id(std::numeric_limits<unsigned>::max()), socket(ioService) {}

            unsigned getId() const { return id; }
            void setId(unsigned id)
            {
                my_assert(this->id == std::numeric_limits<unsigned>::max());
                this->id = id;
            }

            template <typename Handler>
            void accept(boost::asio::ip::tcp::acceptor &acceptor, Handler handler)
            {
                acceptor.async_accept(socket, handler);
            }

            void readMessage(const ReadHandlerFun &readHandler)
            {
                auto buffer = std::make_shared<Buffer>(1024);

                async_read(socket, boost::asio::buffer(*buffer),
                    boost::bind(&Client::readCompletionCond, this, boost::ref(*buffer), _1, _2),
                    boost::bind(&Client::readHandler, this, buffer, readHandler, _1, _2));
            }

            void writeMessage(const BufferSCPtr &buffer, const WriteHandlerFun &writeHandler)
            {
                auto sndBuffer = std::make_shared<Buffer>(*buffer);
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

        private:
            boost::asio::ip::tcp::socket socket;
            unsigned id;
    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif
