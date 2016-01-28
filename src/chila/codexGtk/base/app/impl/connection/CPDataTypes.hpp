/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__CPDATATYPES_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__CPDATATYPES_HPP

#include "fwd.hpp"
#include <gtkmm.h>
#include "MainWindow.hpp"
#include <boost/asio.hpp>
#include <chila/lib/misc/ValueStreamer.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct TabId : public MainWindow::TabId
    {
        const unsigned id = getNextId();

        void stream(std::ostream &out) const override
        {
            out << id;
        }

        static unsigned getNextId()
        {
            static unsigned nextId = 0;
            return nextId++;
        }
    };

    struct CPDataTypes
    {
        using notebook_tabId            = TabIdSCPtr;
        using notebook_tabName          = std::string;
        using notebook_tabTooltip       = std::string;
        using notebook_tabWidget        = Gtk::Widget*;
        using nullObject                = NullObjectSCPtr;
        using fileName                  = bfs::path;

        using cmdNetServer_clientId     = unsigned;
        using cmdNetServer_rcvBuffer    = ccloCIConn::Buffer;
        using cmdNetServer_sndBuffer    = ccloCIConn::CharVectorSCPtr;
        using cmdNetServer_endpoint     = boost::asio::ip::tcp::endpoint;
        using cmdNetServer_address      = boost::asio::ip::address;
        using cmdNetServer_host         = std::string;
        using cmdNetServer_msgId        = unsigned;
        using cmdNetServer_funPath      = clMisc::Path;
        using cmdNetServer_funArgs      = cclOther::ArgumentStrMap;
        using cmdNetServer_message      = std::string;
        using cmdNetServer_msgBuffer    = ccloCIConn::CharVectorSCPtr;

        using actionPath                = clMisc::Path;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

