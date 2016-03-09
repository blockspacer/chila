/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON_IMPL__FUNDYNXMLPARSER_HPP
#define CHILA_CONNECTIONTOOLS_COMMON_IMPL__FUNDYNXMLPARSER_HPP

#include "connection/FunDynXMLParser.hpp"

#include <chila/connectionTools/lib/other/util.hpp>

#include "macros.fgen.hpp"

#define MODULE_NAME FunDynXMLParser


MY_NSP_START
{
    class FunDynXMLParser final: public connection::FunDynXMLParser::CProvider
    {
        public:
            FunDynXMLParser(const std::string &instanceName) :
                connection::FunDynXMLParser::CProvider(instanceName)
            {
                connector.bindActions(*this);
            }

            void MOD_ACTION_SIG(launcher_start)      { set_state_lm(mutex, ModuleState::STARTED);     execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate) { set_state_lm(mutex, ModuleState::DEACTIVATED); execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)     { set_state_lm(mutex, ModuleState::FINISHED);    execute_event(launcher_finished)(); }

            void MOD_ACTION_SIG(take);


        private:
            boost::mutex mutex;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"




#undef DEF_NAMESPACE
#undef MOD_ACTION_SIG

#endif
