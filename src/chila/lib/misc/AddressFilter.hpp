/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__ADDRESSFILTER_HPP
#define CHILA_LIB_MISC__ADDRESSFILTER_HPP

#include <boost/function.hpp>
#include <boost/asio.hpp>
#include "NetResolver.hpp"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/bind.hpp>
#include <set>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class AddressFilter
    {
        public:
            typedef std::set<std::string> StringSet;
            typedef std::set<boost::asio::ip::address> AddressSet;

            typedef std::function<void(const std::string &error)> HandlerFun;

            HandlerFun handler;

            AddressFilter(
                    boost::asio::io_service &ioService,
                    const boost::posix_time::time_duration &timeOut,
                    const HandlerFun &handler = HandlerFun()) :
                handler(handler), resolver(ioService, timeOut)
            {

            }

            void addAllowedHosts(const StringSet &hosts);

            const AddressSet &addresses() const { return addressSet; }

            bool allowed(const boost::asio::ip::address &address) { return addressSet.empty() || addressSet.count(address); }

        private:
            typedef NetResolver<boost::asio::ip::tcp::resolver> Resolver;
            Resolver resolver;
            AddressSet addressSet;
            StringSet hosts;

            StringSet::const_iterator it, end;

            void addOne();

            void resHandler(const std::string &host, const std::string &errorMsg, Resolver::ResolverType::iterator itEp);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"



#endif

