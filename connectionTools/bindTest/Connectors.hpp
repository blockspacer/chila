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

#ifndef CHILA_MODULETOOLS_BINDTEST_CONNECTORS_HPP
#define	CHILA_MODULETOOLS_BINDTEST_CONNECTORS_HPP

#include <boost/function.hpp>
#include <string>
#include <iostream>
#include <boost/mpl/set.hpp>
#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <boost/mpl/vector.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#define DEF_MODULE_ARGUMENT CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_ARGUMENT
#define DEF_MODULE_FUNCTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_FUNCTION
#define BIND_ACTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION


#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,connectionTools,bindTest))
{
    template<typename DataTypes>
    struct Connector0
    {
        typedef Connector0 Connector;

        DEF_MODULE_ARGUMENT(clientId);
        DEF_MODULE_ARGUMENT(messageId);
        DEF_MODULE_ARGUMENT(error);
        DEF_MODULE_ARGUMENT(timeStamp);

        struct Events
        {
            DEF_MODULE_FUNCTION(event1, clientId, messageId, timeStamp, error);
        } events;

        struct Actions
        {
            DEF_MODULE_FUNCTION(action1,   clientId, messageId, timeStamp);
        } actions;

        template <typename Target>
        void bindActions(Target &target)
        {
            BIND_ACTION(Target, target, action1);
        }
    };

    template<typename DataTypes>
    struct Connector1
    {
        typedef Connector1 Connector;

        DEF_MODULE_ARGUMENT(message);
        DEF_MODULE_ARGUMENT(error);
        DEF_MODULE_ARGUMENT(timeStamp);

        struct Events
        {
            DEF_MODULE_FUNCTION(event1, message, timeStamp, error);
        } events;

        struct Actions
        {
            DEF_MODULE_FUNCTION(action1,   message, error, timeStamp);
        } actions;

        template <typename Target>
        void bindActions(Target &target)
        {
            BIND_ACTION(Target, target, action1);
        }

    };


}}}

#undef DEF_NAMESPACE
#undef MT_CODEGEN_NSP
#undef DEF_MODULE_ARGUMENT
#undef DEF_MODULE_FUNCTION
#undef BIND_ACTION
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>
#include <chila/lib/misc/macrosDef.hpp>
#endif

