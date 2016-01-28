/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__MAINWINDOW_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__MAINWINDOW_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "fwd.hpp"
#include "../../connectors/gen/MainWindow.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include <boost/asio/io_service.hpp>
#include <chila/lib/misc/ValueStreamer.hpp>
#include <QQuickWindow>

#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME MainWindow


#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__MODULE_PARAMS_MainWindow \
    ((const std::string&)(instanceName)) \
    ((QQuickWindow&)(window))

MY_NSP_START
{
    struct MainWindow
    {
        struct TabId : public virtual clMisc::ValueStreamer::Streamable
        {
            virtual bool operator<(const TabId &rhs) const { return this < &rhs; }
            virtual ~TabId() {}
        };

        CHILA_LIB_MISC__FWDEC_SPTR(TabId);

        struct ArgTypes
        {
            using fileName              = bfs::path;
            using notebook_tabId        = TabIdSCPtr;
            using notebook_tabName      = std::string;
            using notebook_tabTooltip   = std::string;
            using notebook_tabWidget    = QObject*;
            using errorMsg              = std::string;
            using actionPath            = clMisc::Path;
            using actionPathDataList    = ccCommon::ActionPathDataList;
            using actionData            = ccCommon::ActionData;
        };

        DEF_CPROVIDER(MainWindow);

        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef MODULE_NAME

#endif
