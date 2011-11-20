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

#ifndef CHILA_MODULETOOLS_BINDTEST_MODULES_HPP
#define	CHILA_MODULETOOLS_BINDTEST_MODULES_HPP

#include <boost/function.hpp>
#include <string>
#include <iostream>
#include <boost/mpl/set.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <boost/mpl/vector.hpp>
#include "Message.hpp"
#include "Connectors.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,connectionTools,bindTest))
{
    struct Module0
    {
        typedef Module0 This;

        struct DataTypes
        {
            typedef unsigned clientId;
            typedef unsigned messageId;
            typedef const std::string& error;
            typedef float timeStamp;
        };

        typedef Connector0<DataTypes> Connector;
        Connector connector;

        Module0()
        {
//            BIND_ACTION(action1);
            connector.bindActions(*this);
        }

        void action1(unsigned clientId, unsigned messageId, float timeStamp)
        {
            std::cout << "action1: (clientId: " << clientId << ", messageId: " << messageId
                      << ", timeStamp: " << timeStamp << ")" << std::endl;

        }
    };

    struct Module1
    {
        typedef Module1 This;

        struct DataTypes
        {
            typedef const MessageSCPtr& message;
            typedef const std::string& error;
            typedef float timeStamp;
        };

        typedef Connector1<DataTypes> Connector;
        Connector connector;

        Module1()
        {
//            BIND_ACTION(action1);
            connector.bindActions(*this);
        }

        void action1(const MessageSCPtr &message, const std::string &error, float timeStamp)
        {
            std::cout << "action1: (message.clientId: " << message->clientId
                      << ", message.messageId: " << message->messageId << ", error: " << error
                      << ", timeStamp: " << timeStamp << ")" << std::endl;
        }
    };

}}}

#undef MT_CODEGEN_NSP
#undef DEF_NAMESPACE
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>
#include <chila/lib/misc/macrosDef.hpp>
#endif

