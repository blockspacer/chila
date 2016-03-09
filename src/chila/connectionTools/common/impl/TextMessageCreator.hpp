/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON_IMPL__TEXTMESSAGECREATOR_HPP
#define CHILA_CONNECTIONTOOLS_COMMON_IMPL__TEXTMESSAGECREATOR_HPP

#include "connection/TextMessageCreator.hpp"
#include "fwd.hpp"
#include <map>
#include <boost/assign.hpp>
#include <chila/connectionTools/lib/other/FunExecSequence.hpp>
#include <chila/connectionTools/lib/other/util.hpp>


#include "macros.fgen.hpp"

#define MODULE_NAME TextMessageCreator

CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila, connectionTools, lib, other)
{
    inline chila::lib::misc::StringVec toString(const common::impl::connection::MsgReadCriteriaEnum &object)
    {
        return { common::impl::connection::getName(object) };
    }
}}}}

MY_NSP_START
{
    class TextMessageCreator final: public connection::TextMessageCreator::CProvider
    {
        public:
            TextMessageCreator(const std::string &instanceName, connection::MsgReadCriteriaEnum criteria,
                unsigned criteriaValue, unsigned bufferSize)
            : messageCount(0),
                CHILA_CONNECTIONTOOLS_LIB_OTHER__SAVEPARAMS(connection::TextMessageCreator::CProvider,
                  ((1)(criteria)("Read Criteria"))
                  ((1)(criteriaValue)("Criteria Value"))
                  ((1)(bufferSize)("CharVector Size")))
            {
                connector.bindActions(*this);
            }

            void MOD_ACTION_SIG(launcher_start)      { set_state(ModuleState::STARTED); execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate) { set_state(ModuleState::DEACTIVATED); execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)     { set_state(ModuleState::FINISHED); execute_event(launcher_finished)(); }

            void MOD_ACTION_SIG(takeBuffer);
            void MOD_ACTION_SIG(removeBuffer);

        private:
            using CharVectorSPtr = connection::CharVectorSPtr;
            using CharVector = connection::CharVector;

            connection::MsgReadCriteriaEnum criteria;
            unsigned criteriaValue;
            unsigned bufferSize;
            unsigned messageCount;
            typedef std::map<unsigned, CharVectorSPtr> SessionIdBufferMap;
            SessionIdBufferMap sessionIdBufferMap;

            CharVectorSPtr &getSessionBuffer(unsigned sessionId, ev_executer_arg(takeBuffer));
            void takeBufferPrv(const char* bufBegin, const char* bufEnd, unsigned sessionId, ev_executer_arg(takeBuffer));
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#undef MOD_ACTION_SIG

#endif

