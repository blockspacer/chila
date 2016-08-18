/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__LOGGER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__LOGGER_HPP

#include <chila/connectionTools/lib/codegen/ActionExecuter.hpp>
#include <chila/connectionTools/lib/codegen/ActionImplExecuter.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include "fwd.hpp"
#include <iterator>
#include "connection/Logger.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define MODULE_NAME Logger

#include "macros.fgen.hpp"

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

        connection::Logger::Connector &getConnector() { return connector; }

        void MOD_ACTION_SIG(launcher_start) { execute_event(launcher_started)(); }
        void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
        void MOD_ACTION_SIG(launcher_finish) { execute_event(launcher_finished)(); }


        void MOD_ACTION_SIG(moduleStarted)
        {
            std::cout << "Module started: " << moduleName << std::endl;
        }

        void MOD_ACTION_SIG(moduleFinished)
        {
            std::cout << "Module finished: " << moduleName << std::endl;
        }

        void MOD_ACTION_SIG(connectorLoaded)
        {
            std::cout << "Connector loaded: " << cToolsPath << std::endl;
        }

        void MOD_ACTION_SIG(cPerformerLoaded)
        {
            std::cout << "ConnectionPerfomer loaded: " << cToolsPath << std::endl;
        }


    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
