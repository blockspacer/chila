/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__NETWORK_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__NETWORK_HPP

#include <boost/asio.hpp>
#include "fwd.hpp"
#include "../../connectors/gen/Network.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>

#include <chila/lib/misc/macrosExp.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Network
    {
        enum MsgReadCriteriaEnum { MRCE_LENGTH, MRCE_NLCR } ;

        struct ArgTypes
        {
            using clientId          = unsigned;
            using recvBuffer        = Buffer;
            using sndBuffer         = CharVectorSCPtr;
            using errorMsg          = std::string;
            using endpoint          = boost::asio::ip::tcp::endpoint;
            using address           = boost::asio::ip::address;
            using host              = std::string;
        };

        DEF_CPROVIDER(Network);

        static CProviderUPtr create(const std::string &instanceName, boost::asio::io_service &ioserv,
                const std::string &host,
                const std::string &service,
                const boost::posix_time::time_duration &resolveTimeOut,
                const chila::lib::misc::StringSet &allowedHosts,
                unsigned bufferSize);
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_SPTR
#undef DEF_NAMESPACE

#endif
