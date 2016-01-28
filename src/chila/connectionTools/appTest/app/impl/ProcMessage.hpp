/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__PROCMESSAGE_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL__PROCMESSAGE_HPP

#include "fwd.hpp"

#define MODULE_NAME ProcMessage

#include "nspDef.hpp"

MY_NSP_START
{
    struct ProcMessage
    {
        const BufferSPtr &getBuffer() const = 0;
        virtual ~ProcMessage() {}
    };

    struct MyProcMessage final: public ProcMessage
    {
        unsigned clientId;
        BufferSPtr buffer;

        MyProcMessage(unsigned clientId, const BufferSPtr &buffer) :
            clientId(clientId), buffer(buffer) {}

        const BufferSPtr &getBuffer() const { return buffer; }
    };
}
MY_NSP_END

#include "nspUndef.hpp"
#endif
