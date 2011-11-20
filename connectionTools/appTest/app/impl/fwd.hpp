/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_FWD_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_FWD_HPP

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define libMisc chila::lib::misc

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_SPTR CHILA_LIB_MISC__FWDEC_SPTR
#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    typedef std::vector<char> Buffer;

    FWDEC_SPTR(Buffer);
    FWDEC_TYPE(ProcMessage);
    FWDEC_TYPE(MyProcMessage);
    FWDEC_TYPE(Client);



    struct ProcMessage
    {
        virtual BufferSCPtr getBuffer() const = 0;
    };

    struct MyProcMessage : public ProcMessage
    {
        unsigned clientId;
        BufferSCPtr buffer;
        BufferSCPtr getBuffer() const { return buffer; }

        MyProcMessage(unsigned clientId, const BufferSCPtr &buffer) :
            clientId(clientId), buffer(buffer) {}
    };

}}}}}

#undef DEF_NAMESPACE
#undef appTest
#undef libMisc
#include <chila/lib/misc/macrosUndef.hpp>
#endif
