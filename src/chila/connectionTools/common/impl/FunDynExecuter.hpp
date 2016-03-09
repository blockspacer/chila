/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON_IMPL__FUNDYNEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_COMMON_IMPL__FUNDYNEXECUTER_HPP

#include "connection/FunDynExecuter.hpp"
#include "../../dynFunExecuter/ExecuterMap.hpp"

#include <chila/connectionTools/lib/other/util.hpp>

#include "macros.fgen.hpp"

#define MODULE_NAME FunDynExecuter


MY_NSP_START
{
    class FunDynExecuter final: public connection::FunDynExecuter::CProvider
    {
        public:
            FunDynExecuter(const std::string &instanceName, const dynFunExecuter::ExecuterMap &executerMap) :
                connection::FunDynExecuter::CProvider(instanceName), executerMap(executerMap)
            {
                connector.bindActions(*this);
            }

            void MOD_ACTION_SIG(launcher_start)      { set_state_lm(mutex, ModuleState::STARTED);     execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate) { set_state_lm(mutex, ModuleState::DEACTIVATED); execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)     { set_state_lm(mutex, ModuleState::FINISHED);    execute_event(launcher_finished)(); }

            void MOD_ACTION_SIG(execute);


        private:
            boost::mutex mutex;
            const dynFunExecuter::ExecuterMap &executerMap;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"




#undef DEF_NAMESPACE
#undef MOD_ACTION_SIG

#endif
