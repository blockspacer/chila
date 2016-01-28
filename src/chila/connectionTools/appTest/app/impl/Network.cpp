/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Network.hpp"
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include "Client.hpp"
#include <iostream>
#include <chila/connectionTools/lib/codegen/EventExecuter.hpp>


#define MODULE_NAME Network

#include "nspDef.hpp"

MY_NSP_START
{
    /** Starts the module. */
    void Network::MOD_ACTION_SIG(launcher_start)
    {
        acceptor.open(listenEndPoint.protocol());
        acceptor.set_option(boost::asio::socket_base::reuse_address(true));
        acceptor.bind(listenEndPoint);
        acceptor.listen(10);

        execute_event(launcher_started)();
    }

    /** Accepts a client. */
    void Network::MOD_ACTION_SIG(acceptClient)
    {
        ClientSPtr client = boost::make_shared<Client>(boost::ref(acceptor.get_io_service()));
        client->accept(acceptor, boost::bind(&Network::acceptHandler, this, client, _1, eventExecuter));
    }

    /** Accept's handler. */
    void Network::acceptHandler(const ClientSPtr &client, const boost::system::error_code &ec, ev_executer_arg(acceptClient))
    {
        if (ec) BOOST_THROW_EXCEPTION(boost::system::system_error(ec));

        client->setId(findId());
        clients.insert(ClientMap::value_type(client->getId(), client));

        execute_event(clientConnected)(client->getId());
    }

    /** Reads a message. */
    void Network::MOD_ACTION_SIG(readMessage)
    {
        ClientMap::iterator it = clients.find(clientId);
        my_assert(it != clients.end());

        ClientSPtr &client = it->second;

        client->readMessage(boost::bind(&Network::readHandler, this, client, _1, _2, eventExecuter));
    }

    /** Read's handler. */
    void Network::readHandler(const ClientSPtr &client, const BufferSCPtr &buffer,
        const boost::system::error_code &ec, ev_executer_arg(readMessage))
    {
        if (ec)
        {
            clients.erase(client->getId());

            if (ec == boost::asio::error::connection_reset || ec == boost::asio::error::connection_aborted ||
                    ec == boost::asio::error::eof)
            {
                execute_event(clientDisconnected)(client->getId());
            }
            else
            {
                execute_event(connectionError)(client->getId(), boost::system::system_error(ec).what());
            }
        }
        else
        {
              execute_event(msgReceived)(client->getId(), buffer);
        }
    }


    /** Sends a message to a client. */
    void Network::MOD_ACTION_SIG(sendMessage)
    {
        ClientSPtr client = clients.find(clientId)->second;
        client->writeMessage(sndBuffer, boost::bind(&Network::writeHandler, this, client, _1, _2, eventExecuter));
    }

    /** Read's handler. */
    void Network::writeHandler(const ClientSPtr &client, const boost::system::error_code &ec,
            unsigned bytesTransferred, ev_executer_arg(sendMessage))
    {
        if (ec)
        {
            clients.erase(client->getId());
            execute_event(connectionError)(client->getId(), boost::system::system_error(ec).what());
        }
    }


    /** Finds and id for a client. */
    unsigned Network::findId() const
    {
        long last = -1;
        for (const auto &vt : clients)
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

}
MY_NSP_END

