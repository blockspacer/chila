/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST2_BASE__FWD_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST2_BASE__FWD_HPP

#include <vector>
#include <memory>
#include <memory>

#include "nspDef.hpp"

MY_NSP_START
{
    using Buffer = std::vector<char>;

    CHILA_LIB_MISC__FWDEC_SPTR(Buffer);
    CHILA_LIB_MISC__FWDEC_TYPE(ProcMessage);
    CHILA_LIB_MISC__FWDEC_TYPE(MyProcMessage);


    struct ProcMessage
    {
        virtual BufferSCPtr getBuffer() const = 0;
    };

    struct MyProcMessage final: public ProcMessage
    {
        unsigned clientId;
        BufferSCPtr buffer;
        BufferSCPtr getBuffer() const { return buffer; }

        MyProcMessage(unsigned clientId, const BufferSCPtr &buffer) :
            clientId(clientId), buffer(buffer) {}
    };


    CHILA_LIB_MISC__FWDEC_TYPE(CProvider);

    struct CProvider
    {
        virtual ~CProvider() {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"
#endif
