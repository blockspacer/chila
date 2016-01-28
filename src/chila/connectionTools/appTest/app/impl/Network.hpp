/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__NETWORK_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__NETWORK_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/Network.hpp"
#include <boost/asio.hpp>
#include <map>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define MODULE_NAME Network

#include "nspDef.hpp"

MY_NSP_START
{
    class Network final: public connection::Network::CProvider
    {
        public:
            using Connector = connection::Network::Connector;
            using ArgTypes = connection::Network::ArgTypes;

            Connector connector;

            Network(boost::asio::io_service &ioService,
                    const boost::asio::ip::tcp::endpoint &listenEndPoint) :
                acceptor(ioService), listenEndPoint(listenEndPoint)
            {
                connector.bindActions(*this);
            }

            connection::Network::Connector &getConnector() { return connector; }

            void MOD_ACTION_SIG(launcher_start);

            void MOD_ACTION_SIG(acceptClient);
            void MOD_ACTION_SIG(readMessage);

            unsigned findId() const;

            void MOD_ACTION_SIG(sendMessage);


        private:
            boost::asio::ip::tcp::acceptor acceptor;
            boost::asio::ip::tcp::endpoint listenEndPoint;

            using ClientMap = std::map<unsigned, ClientSPtr>;
            ClientMap clients;

            void acceptHandler(const ClientSPtr &client, const boost::system::error_code &ec, ev_executer_arg(acceptClient));

            void readHandler(const ClientSPtr &client, const BufferSCPtr &buffer,
                const boost::system::error_code &ec, ev_executer_arg(readMessage));

            void writeHandler(const ClientSPtr &client, const boost::system::error_code &ec,
                unsigned bytesTransferred, ev_executer_arg(sendMessage));

    };
}
MY_NSP_END

#include "nspUndef.hpp"
#endif
