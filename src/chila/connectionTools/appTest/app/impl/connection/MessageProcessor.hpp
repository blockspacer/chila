/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__MESSAGEPROCESSOR_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__MESSAGEPROCESSOR_HPP

#include "fwd.hpp"
#include "../../connectors/gen/MessageProcessor.hpp"
#include <boost/asio/io_service.hpp>
#include "../fwd.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    struct MessageProcessor
    {
        struct ArgTypes
        {
            using procMessage   = ProcMessageSCPtr;
            using result        = BufferSCPtr;
            using moduleName    = std::string;
        };

        using Connector = connectors::gen::MessageProcessor<ArgTypes>;

        struct CProvider: public connection::CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create(boost::asio::io_service &ioService);
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
