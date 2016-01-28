/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__ACTIONEXECUTER_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__ACTIONEXECUTER_HPP

#include "fwd.hpp"
#include "../../connectors/gen/ActionExecuter.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include <boost/asio/io_service.hpp>
#include <gtkmm.h>
#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME ActionExecuter

MY_NSP_START
{
    struct ActionExecuter
    {
        struct ArgTypes
        {
            using actionPath    = clMisc::Path;
            using errorMsg      = std::string;
        };

        DEF_CPROVIDER(ActionExecuter);

        static CProviderUPtr create(const std::string &instanceName);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef MODULE_NAME

#endif
