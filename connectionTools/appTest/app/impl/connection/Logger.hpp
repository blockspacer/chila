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

#ifndef CHILA_CONNECTION_TOOLS_APPTEST_APP_IMPL_CONNECTION__LOGGER_HPP
#define CHILA_CONNECTION_TOOLS_APPTEST_APP_IMPL_CONNECTION__LOGGER_HPP

#include "../fwd.hpp"
#include "../../connectors/gen/Logger.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,impl,connection))
{
    struct Logger
    {
        struct ArgTypes
        {
            typedef unsigned clientId;
            typedef const BufferSCPtr &recvBuffer;
            typedef const BufferSCPtr &sndBuffer;
            typedef const std::string &errorMsg;
            typedef const std::string &moduleName;
        };

        typedef connectors::gen::Logger<ArgTypes> Connector;

        struct CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create();
    };
}}}}}}

#undef FWDEC_SPTR
#undef DEF_NAMESPACE

#endif
