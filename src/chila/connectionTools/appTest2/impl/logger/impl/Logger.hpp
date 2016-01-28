/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_IMPL__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_IMPL_LOGGER_IMPL__LOGGER_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "fwd.hpp"
#include <iterator>
#include "connection/Logger.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define MODULE_NAME Logger

#include "nspDef.hpp"

MY_NSP_START
{
    struct Logger final: public connection::Logger::CProvider
    {
        using Connector = connection::Logger::Connector;
        using ArgTypes = connection::Logger::ArgTypes;

        Connector connector;

        Logger()
        {
            connector.bindActions(*this);
        }

        void MOD_ACTION_SIG(launcher_start);
        void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
        void MOD_ACTION_SIG(launcher_finish) { execute_event(launcher_finished)(); }

        connection::Logger::Connector &getConnector() { return connector; }

        void MOD_ACTION_SIG(moduleStarted);
        void MOD_ACTION_SIG(clientConnected);
        void MOD_ACTION_SIG(clientDisconnected);
        void MOD_ACTION_SIG(connectionError);
        void MOD_ACTION_SIG(msgReceived);
        void MOD_ACTION_SIG(msgProcessed);
    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif
