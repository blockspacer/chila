/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "AddressFilter.hpp"
#include <boost/bind.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"


MY_NSP_START
{
    void AddressFilter::addAllowedHosts(const StringSet &hosts)
    {
        this->hosts = hosts;
        it = hosts.begin();
        end = hosts.end();

        addOne();
    }

    void AddressFilter::addOne()
    {
        if (it == end)
            handler("");
        else
            resolver.resolve(*it, "", boost::bind(&AddressFilter::resHandler, this, *it, _1, _2));

        ++it;
    }

    void AddressFilter::resHandler(const std::string &host, const std::string &errorMsg, Resolver::ResolverType::iterator itEp)
    {
        if (!errorMsg.empty())
            handler("error resolving '" + host + "':" + errorMsg);
        else
        {
            addressSet.insert(itEp->endpoint().address());
            addOne();
        }
    }
}
MY_NSP_END

