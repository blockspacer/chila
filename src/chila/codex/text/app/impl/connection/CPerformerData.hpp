/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP

#include "../../connectors/gen/ConnectionPerformer.hpp"
#include "CPDataTypes.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "TextEditor.hpp"
#include "TextHighlighter.hpp"
#include "FileOpener.hpp"
#include "FindReplace.hpp"
#include "ActionExecuter.hpp"
#include "chila/codex/base/app/impl/connection/Application.hpp"
#include "chila/codex/base/app/impl/connection/MainWindow.hpp"
#include "chila/codex/base/app/impl/connection/FileChooser.hpp"
#include "chila/codex/base/app/impl/connection/ActionExecuter.hpp"
#include <chila/connectionTools/lib/common/impl/connection/Forwarder.hpp>
#include "argProviders.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct CPerformerData
    {
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CPERFORMERDATA_INIT
        (
            ((base::app::impl::connection::Application)(Application))
            ((base::app::impl::connection::MainWindow)(MainWindow))
            ((base::app::impl::connection::FileChooser)(FileChooser))
            ((base::app::impl::connection::ActionExecuter)(BaseActionExecuter))
            ((connection::ActionExecuter)(TextActionExecuter))
            ((connection::TextEditor)(TextEditor))
            ((connection::TextHighlighter)(TextHighlighter))
            ((connection::FileOpener)(FileOpener))
            ((connection::FindReplace)(FindReplace)),
            CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ,
            my_get_connector
        )

        using AliasTypes = CPDataTypes;

        typedef app::connectors::gen::ConnectionPerformer<AliasTypes, Connectors> ConnectionPerformer;

        struct AppArgs
        {
            chila::connectionTools::lib::codegen::ConnectorMap &cMap;

            struct Providers
            {
                Providers(const AppParams &appParams) {}
            } providers;

            AppArgs(const AppParams &appParams, chila::connectionTools::lib::codegen::ConnectorMap &cMap) :
                providers(appParams),
                cMap(cMap)
            {
            }
        };

        static void connect(const AppParams &appParams, chila::connectionTools::lib::codegen::ConnectorMap &cMap)
        {
            AppArgs args(appParams, cMap);
            ConnectionPerformer::connect(args);
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
