/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP

#include "fwd.hpp"
#include "../../connectors/gen/ConnectionPerformer.hpp"
#include <chila/connectionTools/lib/common/impl/connection/Forwarder.hpp>
#include <chila/connectionTools/lib/common/impl/connection/FunDynExecuter.hpp>
#include <chila/connectionTools/lib/common/impl/connection/Network.hpp>
#include <chila/connectionTools/lib/common/impl/connection/TextMessageCreator.hpp>
#include <chila/connectionTools/lib/common/impl/connection/FunDynXMLParser.hpp>
#include "CPDataTypes.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "MainWindow.hpp"
#include "Application.hpp"
#include "ActionExecuter.hpp"
#include "FileChooser.hpp"
#include "argProviders.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct CPerformerData
    {
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CPERFORMERDATA_INIT
        (
            ((connection::Application)(Application))
            ((connection::MainWindow)(MainWindow))
            ((connection::FileChooser)(FileChooser))
            ((connection::ActionExecuter)(ActionExecuter))
            ((cclCommon::impl::connection::Network)(CmdNetServer))
            ((cclCommon::impl::connection::FunDynExecuter)(FunDynExecuter))
            ((cclCommon::impl::connection::FunDynXMLParser)(FunDynXMLParser))
            ((cclCommon::impl::connection::TextMessageCreator)(CmdNetTextMsgCreator)),
            CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ,
            my_get_connector
        )

        using AliasTypes = CPDataTypes;

        typedef app::connectors::gen::ConnectionPerformer<AliasTypes, Connectors> ConnectionPerformer;

        struct AppArgs
        {
            chila::connectionTools::lib::codegen::ConnectorMap &cMap;

            struct Providers
            {
                CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_CREATORS(NSP, argProv)

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
