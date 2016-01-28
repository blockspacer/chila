/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL__NETWORK_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL__NETWORK_HPP

#include "connection/Network.hpp"
#include <boost/asio.hpp>
#include "fwd.hpp"
#include <boost/assign.hpp>
#include <chila/lib/misc/NetResolver.hpp>
#include <chila/lib/misc/AddressFilter.hpp>
#include <chila/connectionTools/lib/other/FunExecSequence.hpp>
#include <chila/connectionTools/lib/other/util.hpp>

#include <chila/connectionTools/lib/other/macrosExp.hpp>


#include "macros.fgen.hpp"

#define MODULE_NAME Network


MY_NSP_START
{
    using boost::asio::ip::tcp;

    class Network final: public connection::Network::CProvider
    {

        public:
            Network(
                const std::string &instanceName,
                boost::asio::io_service &ioserv,
                const std::string &host,
                const std::string &service,
                const boost::posix_time::time_duration &resolveTimeOut,
                const chila::lib::misc::StringSet &allowedHosts,
                unsigned bufferSize)
        :
                acceptor(ioserv),
                ioService(ioserv),
                resolver(ioserv, resolveTimeOut),
                filter(ioserv, resolveTimeOut),
                nextSessionId(0),
                reading(0),
                    CHILA_CONNECTIONTOOLS_LIB_OTHER__SAVEPARAMS(connection::Network::CProvider,
                      ((1)(host)("Host"))
                      ((1)(service)("Service"))
                      ((1)(allowedHosts)("Allowed Hosts"))
                      ((1)(resolveTimeOut)("Resolve Timeout"))
                      ((1)(bufferSize)("Buffer Size")))
                {
                    connector.bindActions(*this);
                }

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(write);
            void MOD_ACTION_SIG(closeSession);
            void MOD_ACTION_SIG(launcher_deactivate);
            void MOD_ACTION_SIG(launcher_finish) { set_state({ModuleState::FINISHED}); execute_event(launcher_finished)(); }


        private:
            typedef chila::lib::misc::NetResolver<boost::asio::ip::tcp::resolver> Resolver;

            using Buffer = connection::Buffer;

            boost::mutex mutex;
            tcp::acceptor acceptor;
            boost::asio::io_service &ioService;
            std::string host;
            std::string service;
            unsigned reading;
            boost::posix_time::time_duration resolveTimeOut;


            struct Session
            {
                unsigned id;
                tcp::socket socket;
                unsigned bufferSize;
                char *buffer;
                bool readCanceled;
                Resolver resolver;

                Session(boost::asio::io_service &ioService, int idsess, unsigned bufferSize,
                    const boost::posix_time::time_duration &resolveTimeOut) :
                    socket(ioService), id(idsess), bufferSize(bufferSize), readCanceled(false), resolver(ioService, resolveTimeOut)
                {
                    buffer = new char[bufferSize];
                }

                void shutdownRead()
                {
                    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_receive);
                    readCanceled = true;
                }

                ~Session()
                {
                    delete[] buffer;
                }
            };

            typedef boost::shared_ptr<Session> SessionSPtr;
            typedef std::map<unsigned, SessionSPtr> SessionMap;

            SessionMap sessionMap;

            Resolver resolver;

            chila::lib::misc::AddressFilter filter;

            chila::lib::misc::StringSet allowedHosts;
            unsigned nextSessionId;
            boost::asio::ip::tcp::endpoint listenEp;

            unsigned bufferSize;

            enum ReadWrite{ Read, Write};

            void read(const SessionSPtr &session, ev_executer_arg(launcher_start));
            void acceptClient(ev_executer_arg(launcher_start));

            void clientResolveHandler(unsigned clientId, const std::string &error, Resolver::ResolverType::iterator it);
            void readyToAccept(const std::string &error, ev_executer_arg(launcher_start));
            void shutdownSession(const SessionSPtr &session);

            template <typename EventExecuter>
            bool handleError(const SessionSPtr &session, const boost::system::error_code &err, const EventExecuter &eventExecuter);

            void removeSession(unsigned idSession);

    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#undef MOD_ACTION_SIG

#endif
