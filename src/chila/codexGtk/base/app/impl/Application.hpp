/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL__APPLICATION_HPP
#define CHILA_CODEX_BASE_APP_IMPL__APPLICATION_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/Application.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <boost/bind.hpp>
#include <ctype.h>


#define MODULE_NAME Application

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Application final: public connection::Application::CProvider
    {
        public:
            Application(const std::string &instanceName) :
                connection::Application::CProvider(instanceName)
            {
                connector.bindActions(*this);
            }

            void MOD_ACTION_SIG(launcher_start) { execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish) { execute_event(launcher_finished)(); }

       private:


    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

