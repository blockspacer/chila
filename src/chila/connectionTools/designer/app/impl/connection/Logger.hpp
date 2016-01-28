/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__LOGGER_HPP

#include "fwd.hpp"
#include "../fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include "../../connectors/gen/Logger.hpp"
#include "../../../lib/actions.hpp"

#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Logger
    {
        struct ArgTypes
        {
            using moduleName = std::string;
            using cToolsPath = chila::lib::misc::Path;
        };

        using Connector = connectors::gen::Logger<ArgTypes>;

        struct CProvider: public connection::CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create();
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_SPTR

#endif
