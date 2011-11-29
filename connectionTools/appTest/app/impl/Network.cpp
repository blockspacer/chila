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

#include "Network.hpp"
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include "Client.hpp"
#include <iostream>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    /** Starts the module. */
    void Network::start()
    {
        acceptor.open(listenEndPoint.protocol());
        acceptor.set_option(boost::asio::socket_base::reuse_address(true));
        acceptor.bind(listenEndPoint);
        acceptor.listen(10);

        acceptClient();

        connector.events.started();
    }

    /** Accepts a client. */
    void Network::acceptClient()
    {
        ClientSPtr client = boost::make_shared<Client>(boost::ref(acceptor.get_io_service()));
        client->accept(acceptor, boost::bind(&Network::acceptHandler, this, client, _1));
    }

    /** Accept's handler. */
    void Network::acceptHandler(const ClientSPtr &client, const boost::system::error_code &ec)
    {
        if (ec) BOOST_THROW_EXCEPTION(boost::system::system_error(ec));

        client->setId(findId());
        clients.insert(ClientMap::value_type(client->getId(), client));
        acceptClient();
        readMessage(client);

        connector.events.clientConnected.function(client->getId());
    }

    /** Reads a message. */
    void Network::readMessage(const ClientSPtr &client)
    {
        client->readMessage(boost::bind(&Network::readHandler, this, client, _1, _2));
    }

    /** Read's handler. */
    void Network::readHandler(const ClientSPtr &client, const BufferSCPtr &buffer,
        const boost::system::error_code &ec)
    {
        if (ec == boost::asio::error::connection_reset || ec == boost::asio::error::connection_aborted ||
                ec == boost::asio::error::eof)
        {
            clients.erase(client->getId());
            connector.events.clientDisconnected.function(client->getId());
            return;
        }
        else if (ec) BOOST_THROW_EXCEPTION(boost::system::system_error(ec));


        connector.events.msgReceived.function(client->getId(), buffer);

        readMessage(client);
    }


    /** Sends a message to a client. */
    void Network::sendMessage(unsigned clientId, const BufferSCPtr &buffer)
    {
        ClientSPtr client = clients.find(clientId)->second;
        client->writeMessage(buffer, boost::bind(&Network::writeHandler, this, client, _1, _2));
    }

    /** Read's handler. */
    void Network::writeHandler(const ClientSPtr &client, const boost::system::error_code &ec,
            unsigned bytesTransferred)
    {
        if (ec) BOOST_THROW_EXCEPTION(boost::system::system_error(ec));
    }


    /** Finds and id for a client. */
    unsigned Network::findId() const
    {
        long last = -1;
        BOOST_FOREACH(const ClientMap::value_type &vt, clients)
        {
            if (vt.first - last > 1)
                return last + 1;

            last = vt.first;
        }

        return last + 1;
    }

    connection::Network::CProviderSPtr connection::Network::create(boost::asio::io_service &ioService,
                    const boost::asio::ip::tcp::endpoint &listenEndPoint)
    {
        return boost::make_shared<app::impl::Network>(boost::ref(ioService), listenEndPoint);
    }
}}}}}

