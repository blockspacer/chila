/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_IMPL_CONNECTION__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_IMPL_CONNECTION__LOGGER_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "fwd.hpp"
#include "../fwd.hpp"
#include "../../connectors/gen/Logger.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    struct Logger
    {
        struct ArgTypes
        {
            using clientId      = unsigned;
            using recvBuffer    = BufferSCPtr;
            using sndBuffer     = BufferSCPtr;
            using errorMsg      = std::string;
            using moduleName    = std::string;
        };

        using Connector = connectors::gen::Logger<ArgTypes>;

        struct CProvider : public appTest2::CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create();
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
