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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_NETWORK_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_NETWORK_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "fwd.hpp"
#include "../connectors/gen/Network.hpp"
#include <boost/asio.hpp>
#include <map>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    class Network
    {
        private:
            typedef Network This;


        public:
            struct DataTypes
            {
                typedef unsigned clientId;
                typedef const BufferSCPtr &recvBuffer;
                typedef const BufferSCPtr &sndBuffer;
                typedef const std::string &errorMsg;
                typedef const std::string &moduleName;
            };

            typedef connectors::gen::Network<DataTypes> Connector;
            Connector connector;

        private:
            typedef std::map<unsigned, ClientSPtr> ClientMap;
            ClientMap clients;

            boost::asio::ip::tcp::endpoint listenEndPoint;
            boost::asio::ip::tcp::acceptor acceptor;

        public:
            Network(boost::asio::io_service &ioService,
                    const boost::asio::ip::tcp::endpoint &listenEndPoint) :
                acceptor(ioService), listenEndPoint(listenEndPoint)
            {
                connector.bindActions(*this);
            }

            void init();
            void start();
//            void finish(const CompletedFun &completedFun) {}

            void acceptClient();
            void acceptHandler(const ClientSPtr &client, const boost::system::error_code &ec);
            void readMessage(const ClientSPtr &client);
            void readHandler(const ClientSPtr &client, const BufferSCPtr &buffer,
                const boost::system::error_code &ec);
            unsigned findId() const;

            void sendMessage(unsigned clientId, const BufferSCPtr &sndBuffer);
            void writeHandler(const ClientSPtr &client, const boost::system::error_code &ec,
                unsigned bytesTransferred);
    };
}}}}}

#undef MT_CODEGEN_NSP
#undef DEF_NAMESPACE
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>
#include <chila/lib/misc/macrosUndef.hpp>
#endif
