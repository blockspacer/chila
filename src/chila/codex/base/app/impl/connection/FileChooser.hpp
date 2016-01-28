/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__FILECHOOSER_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__FILECHOOSER_HPP

#include "fwd.hpp"
#include "../../connectors/gen/FileChooser.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include <boost/asio/io_service.hpp>
#include <QQuickWindow>

#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME FileChooser

#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__MODULE_PARAMS_FileChooser \
    ((const std::string&)(instanceName)) \
    ((Type)(type)) \
    ((QQuickWindow&)(window))

MY_NSP_START
{
    struct FileChooser
    {
        enum class Type
        {
            OPEN,
            SAVE
        };

        struct ArgTypes
        {
            using fileName = boost::filesystem::path;
            using errorMsg = std::string;
        };

        DEF_CPROVIDER(FileChooser);

        using PostFun = std::function<void(const std::string &from, const std::function<void()> &fun)>;
        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#undef MODULE_NAME
#include "macros.fgen.hpp"

#endif
