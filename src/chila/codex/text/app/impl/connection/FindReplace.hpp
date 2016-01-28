/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FINDREPLACE_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FINDREPLACE_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "types.hpp"

#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/FindReplace.hpp"
#include <chila/lib/misc/ValueStreamer.hpp>
#include <boost/asio/io_service.hpp>
#include "../../../lib/fwd.hpp"
#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME FindReplace

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__MODULE_PARAMS_FindReplace \
    ((const std::string&)(instanceName)) \
    ((const PostFun&)(postFun))

MY_NSP_START
{
    struct FindReplace
    {
        struct ArgTypes
        {
            using findText = std::string;
            using replaceText = std::string;
            using checks = FindReplaceChecks;
            using errorMsg = std::string;
        };

        DEF_CPROVIDER;

        using PostFun = std::function<void(const std::string &from, const std::function<void()> &fun)>;

        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#undef MODULE_NAME
#include "macros.fgen.hpp"

#endif
