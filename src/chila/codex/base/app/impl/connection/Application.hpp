/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__APPLICATION_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__APPLICATION_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "fwd.hpp"
#include "../../connectors/gen/Application.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include <boost/asio/io_service.hpp>

#include "../fwd.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Application
    {
        struct ArgTypes
        {
            using fileName = bfs::path;
            using notebook_tabName = std::string;
            using notebook_tabWidget = int; //Gtk::Widget*;
            using menuItemPath = clMisc::Path;
            using errorMsg = std::string;
        };

        DEF_CPROVIDER(Application);

        static CProviderUPtr create(const std::string &instanceName);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
