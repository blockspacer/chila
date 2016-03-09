/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "TextMessageCreator.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME TextMessageCreator

MY_NSP_START
{
    void TextMessageCreator::MOD_ACTION_SIG(takeBuffer)
    {
        check_state(ModuleState::STARTED);
        takeBufferPrv(buffer.first, buffer.first + buffer.second, sessionId, eventExecuter);
    }

    void TextMessageCreator::takeBufferPrv(const char *bufBegin, const char* bufEnd, unsigned sessionId, ev_executer_arg(takeBuffer))
    {
        if (bufBegin == bufEnd)
            return;

        CharVectorSPtr &sessionBuffer = getSessionBuffer(sessionId, eventExecuter);
        const char *it = bufBegin;

        while (it != bufEnd)
        {
            bool criteriaMet = false;
            switch (criteria)
            {
                case connection::MsgReadCriteriaEnum::NLCR:
                    for (;it != bufEnd; it++)
                    {
                        if (*it == '\n' || *it == '\r')
                        {
                            criteriaMet = true;
                            break;
                        }
                    }
                    break;

                case connection::MsgReadCriteriaEnum::LENGTH:
                    {
                        unsigned msgSize = criteriaValue;
                        unsigned capacityLeft = msgSize - sessionBuffer->size();
                        if ((bufEnd - bufBegin) >= capacityLeft)
                        {
                            criteriaMet = true;
                            it += capacityLeft;
                        }
                        else
                        {
                            it = bufEnd;
                        }
                    }
                    break;

                default:
                    abort();
                    break;
            }

            sessionBuffer->insert(sessionBuffer->end(), bufBegin, it);

            if (criteriaMet)
            {
                execute_event(messageObtained)(sessionBuffer, sessionId, messageCount++);

                sessionBuffer = boost::make_shared<CharVector>();
                sessionBuffer->reserve(bufferSize);

                if (criteria == connection::MsgReadCriteriaEnum::NLCR)
                    for (; it != bufEnd && (*it == '\n' || *it == '\r'); ++it) // [test: 10<9>];

                bufBegin = it;
            }
        }

    }

    TextMessageCreator::CharVectorSPtr &TextMessageCreator::getSessionBuffer(unsigned sessionId, ev_executer_arg(takeBuffer))
    {
        SessionIdBufferMap::iterator it = sessionIdBufferMap.find(sessionId);
        if (it == sessionIdBufferMap.end())
        {
            CharVectorSPtr newBuffer(boost::make_shared<CharVector>());
            newBuffer->reserve(bufferSize);
            std::pair<SessionIdBufferMap::iterator, bool> ret = sessionIdBufferMap.insert(std::make_pair(sessionId, newBuffer));
            ct_assert(ret.second);
            it = ret.first;
        }
        return it->second;
    }


    void TextMessageCreator::MOD_ACTION_SIG(removeBuffer)
    {
        check_state(ModuleState::STARTED);
        sessionIdBufferMap.erase(sessionId);
    }

    connection::TextMessageCreator::CProviderUPtr connection::TextMessageCreator::create(
        const std::string &instanceName,
        connection::MsgReadCriteriaEnum criteria,
        unsigned criteriaValue,
        unsigned bufferSize)
    {
        return boost::make_unique<impl::TextMessageCreator>(instanceName, criteria, criteriaValue, bufferSize);
    }


}
MY_NSP_END

#include "macros.fgen.hpp"


