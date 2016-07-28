/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */


#include <boost/asio/ip/basic_resolver.hpp>


#include <boost/algorithm/string/trim.hpp>
#include "Network.hpp"
#include <boost/asio/time_traits.hpp>

#include <chila/lib/misc/macrosExp.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>

#define MODULE_NAME Network


#include "macros.fgen.hpp"


MY_NSP_START
{
    void Network::MOD_ACTION_SIG(launcher_start)
    {
        set_state({ModuleState::STARTED});

        filter.handler = [this, eventExecuter](const std::string &error){ readyToAccept(error, eventExecuter); };

        resolver.resolve(host, service, [this, eventExecuter](const std::string &error, Resolver::ResolverType::iterator it)
        {
            if (error.empty())
            {
                listenEp = it->endpoint();
                filter.addAllowedHosts(allowedHosts);

                execute_event(endpointResolved)(listenEp);
            }
            else
            {
                execute_event(fatalError)("Could not resolve '" + host + ":" + service + "': " + error);
            }
        });
    }

    void Network::MOD_ACTION_SIG(launcher_deactivate)
    {
        acceptor.close();

        boost::mutex::scoped_lock lock(mutex);
        for (auto &vt : sessionMap)
        {
            shutdownSession(vt.second);
        }

        set_state({ModuleState::DEACTIVATED});

        lock.unlock();
        execute_event(launcher_deactivated)();
    }

    void Network::acceptClient(ev_executer_arg(launcher_start))
    {
        unsigned sessionId = nextSessionId++;
        SessionSPtr session = std::make_shared<Session>(boost::ref(ioService), sessionId, bufferSize, resolveTimeOut);

        boost::mutex::scoped_lock lock(mutex);
        ct_assert(sessionMap.insert({ sessionId, session }).second);
        lock.unlock();

        acceptor.async_accept(session->socket, [this, session, eventExecuter](const boost::system::error_code &err)
        {
            unsigned sessionId = session->id;
            if (err == boost::asio::error::connection_aborted ||
                err == boost::asio::error::connection_reset ||
                err == boost::asio::error::broken_pipe ||
                err == boost::asio::error::eof ||
                err == boost::asio::error::operation_aborted)
            {
                removeSession(sessionId);
            }
            else if (err)
            {
                std::cout << err << std::endl;
                BOOST_THROW_EXCEPTION(boost::system::system_error(err));
            }
            else
            {
                resolver.resolve(session->socket.remote_endpoint(),
                    [this, session, eventExecuter](const std::string &error, Resolver::ResolverType::iterator it)
                    {
                        if (error.empty())
                        {
                            // execute_event(endpointResolved(listenEp);
                //            std::cout << "resolved: " << it->host_name() << std::endl;
                            CHILA_LIB_MISC__SHOW(40, session->id);
                            execute_event(clientHostResolved)(session->id, it->host_name());
                        }
                        else
                        {
                            // warning
                        }
                    });

                CHILA_LIB_MISC__SHOW(40, sessionId);
                execute_event(clientAccepted)(sessionId, session->socket.remote_endpoint());
                read(session, eventExecuter);
                acceptClient(eventExecuter);
            }
        });
    }

    void Network::read(const SessionSPtr &session, ev_executer_arg(launcher_start))
    {
        session->socket.async_read_some(boost::asio::buffer(session->buffer, session->bufferSize), [this, session, eventExecuter]
            (const boost::system::error_code &err, size_t byteTransferred)
            {
                if (handleError(session, err, eventExecuter))
                {
                    execute_event(msgRead)(session->id, Buffer(session->buffer, byteTransferred));
                    read(session, eventExecuter);
                }
            });
    }

    void Network::MOD_ACTION_SIG(write) try
    {
        boost::mutex::scoped_lock lock(mutex);
        check_state(ModuleState::STARTED);

        auto it = sessionMap.find(clientId);
        ct_assert(it != sessionMap.end());

        SessionSPtr session = it->second;

        session->socket.async_write_some(boost::asio::buffer(*sndBuffer, (*sndBuffer).size()),
            [this, session, sndBuffer, eventExecuter](const boost::system::error_code &err, size_t bytes_transf)
            {
                if (handleError(session, err, eventExecuter))
                    execute_event(msgWritten)(session->id, sndBuffer);
                else
                    execute_event(responseDiscarded)(session->id, sndBuffer);
            });
    }
    catch (const chila::lib::misc::ElementNotFound &ex)
    {
        execute_event(responseDiscarded)(clientId, sndBuffer);
    }

    template <typename EventExecuter>
    bool Network::handleError(const SessionSPtr &session, const boost::system::error_code &err, const EventExecuter &eventExecuter)
    {
        if
        (
            err == boost::asio::error::operation_aborted ||
            err == boost::asio::error::connection_aborted ||
            err == boost::asio::error::connection_reset ||
            err == boost::asio::error::broken_pipe ||
            err == boost::asio::error::eof ||
            err == boost::asio::error::bad_descriptor
        )
        {
            if (!session->readCanceled)
            {
                removeSession(session->id);
                execute_event_tn(clientDisconnected)(session->id);
            }
            return false;
        }
        else if (err)
        {
            removeSession(session->id);
            shutdownSession(session);
            execute_event_tn(clientError)(session->id, boost::system::system_error(err).what());
            return false;
        }
        return true;
    }

    void Network::readyToAccept(const std::string &error, ev_executer_arg(launcher_start)) try
    {
        if (!error.empty())
        {
            execute_event(fatalError)("Error resolving allowed address: " + error);
        }
        else
        {
            for (const auto &address : filter.addresses())
            {
                execute_event(resolvedAllowedAddress)(address);
            }

            acceptor.open(listenEp.protocol());
            acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor.bind(listenEp);
            acceptor.listen();

            acceptClient(eventExecuter);
            execute_event(launcher_started)();
        }
    }
    catch (const boost::system::system_error &ex)
    {
        execute_event(fatalError)("Error listening clients: " + std::string(ex.what()));
    }

    void Network::MOD_ACTION_SIG(closeSession)
    {
        boost::mutex::scoped_lock lock(mutex);

        check_state(ModuleState::STARTED);
        auto it = sessionMap.find(clientId);
        ct_assert(it != sessionMap.end());

        lock.unlock();
        it->second->socket.close();
    }

    void Network::removeSession(unsigned sessionId)
    {
        boost::mutex::scoped_lock lock(mutex);
        sessionMap.erase(sessionId);
    }


    void Network::shutdownSession(const SessionSPtr &session)
    {
        if(session->socket.is_open())
        {
            session->shutdownRead();
        }
    }

    connection::Network::CProviderUPtr connection::Network::create
    (
        const std::string &instanceName,
        boost::asio::io_service &ioserv,
        const std::string &host,
        const std::string &service,
        const boost::posix_time::time_duration &resolveTimeOut,
        const chila::lib::misc::StringSet &allowedHosts,
        unsigned bufferSize
    )
    {
        return boost::make_unique<impl::Network>(
            instanceName,
            boost::ref(ioserv),
            host,
            service,
            resolveTimeOut,
            allowedHosts,
            bufferSize);
    }
}
MY_NSP_END

#include "macros.fgen.hpp"
