/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL__ACTIONEXECUTER_HPP
#define CHILA_CODEX_BASE_APP_IMPL__ACTIONEXECUTER_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/ActionExecuter.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>


#define MODULE_NAME ActionExecuter

#include "macros.fgen.hpp"

MY_NSP_START
{
    class ActionExecuter final: public connection::ActionExecuter::CProvider
    {
        public:
            ActionExecuter(const std::string &instanceName);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish);

            void MOD_ACTION_SIG(execute);

       private:
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

