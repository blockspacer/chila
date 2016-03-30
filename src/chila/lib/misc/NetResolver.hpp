/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__NETRESOLVER_HPP
#define CHILA_LIB_MISC__NETRESOLVER_HPP

#include <boost/asio.hpp>
#include <memory>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "macros.fgen.hpp"


MY_NSP_START
{
    template <typename _ResolverType>
    class NetResolver
    {
        public:
            typedef _ResolverType ResolverType;

            typedef boost::function<void(const std::string &error, typename ResolverType::iterator it)> ResolverHandlerFun;

            NetResolver(boost::asio::io_service &ioService, const boost::posix_time::time_duration &timeOut) :
                resolver(ioService), timeOut(timeOut) {}


            void resolve(const std::string &host, const std::string &service, const ResolverHandlerFun &handler);
            void resolve(const boost::asio::ip::tcp::endpoint &ep, const ResolverHandlerFun &handler);

        private:
            typedef std::shared_ptr<boost::asio::deadline_timer> TimerSPtr;
            boost::posix_time::time_duration timeOut;
            ResolverType resolver;
            TimerSPtr timer;

            void resolveHandler(const ResolverHandlerFun &handler, const boost::system::error_code &ec, typename ResolverType::iterator it);
            void timerHandler(const ResolverHandlerFun &handler, const boost::system::error_code &ec);
    };

    template <typename ResolverType>
    void NetResolver<ResolverType>::resolve(const std::string &host, const std::string &service,
            const ResolverHandlerFun &handler)
    {
        timer = std::make_shared<boost::asio::deadline_timer>(boost::ref(resolver.get_io_service()), timeOut);
        timer->async_wait(boost::bind(&NetResolver<ResolverType>::timerHandler, this, handler, _1));

        if (host == "*")
        {
            resolver.async_resolve(boost::asio::ip::tcp::resolver::query(boost::asio::ip::tcp::v4(), service),
                boost::bind(&NetResolver<ResolverType>::resolveHandler, this, handler, _1, _2));
        }
        else
        {
            resolver.async_resolve(boost::asio::ip::tcp::resolver::query(host, service),
                boost::bind(&NetResolver<ResolverType>::resolveHandler, this, handler, _1, _2));
        }
    }

    template <typename ResolverType>
    void NetResolver<ResolverType>::resolve(const boost::asio::ip::tcp::endpoint &ep, const ResolverHandlerFun &handler)
    {
        timer = std::make_shared<boost::asio::deadline_timer>(boost::ref(resolver.get_io_service()), timeOut);
        timer->async_wait(boost::bind(&NetResolver<ResolverType>::timerHandler, this, handler, _1));

        resolver.async_resolve(ep, boost::bind(&NetResolver<ResolverType>::resolveHandler, this, handler, _1, _2));
    }

    template <typename ResolverType>
    void NetResolver<ResolverType>::resolveHandler(const NetResolver<ResolverType>::ResolverHandlerFun &handler,
            const boost::system::error_code &ec, typename ResolverType::iterator it)
    {
        timer.reset();

        if (ec)
        {
            handler(boost::system::system_error(ec).what(), typename ResolverType::iterator());
        }
        else if (it == typename ResolverType::iterator())
        {
            handler("empty list", it);

        }
        else
            handler("", it);
    }

    template <typename ResolverType>
    void NetResolver<ResolverType>::timerHandler(const NetResolver<ResolverType>::ResolverHandlerFun &handler, const boost::system::error_code &ec)
    {
        if (!ec) handler("time out", typename ResolverType::iterator());
    }
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

