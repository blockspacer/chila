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

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef _CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN_PROCESSINGCONNECTOR_HPP
#define _CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN_PROCESSINGCONNECTOR_HPP

#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <string>

#include <boost/mpl/set.hpp>
#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define MY_BIND_ACTION(name) \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name)
#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen
#define DEF_MODULE_ARGUMENT CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_ARGUMENT
#define DEF_MODULE_FUNCTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_FUNCTION
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK

DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector. 
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor. 
      */
    template <typename DataTypes>
    struct Processing
    {
        typedef Processing Connector; 

        // Arguments
        DEF_MODULE_ARGUMENT(connectorName);
        DEF_MODULE_ARGUMENT(outBuffer);
        DEF_MODULE_ARGUMENT(procMessage);

        // Events
        struct Events
        {
            DEF_MODULE_FUNCTION(connectorFinalizing);
            DEF_MODULE_FUNCTION(connectorStart);
            DEF_MODULE_FUNCTION(messageProcessed, outBuffer, procMessage);
        } events;

        // Actions
        struct Actions
        {
            DEF_MODULE_FUNCTION(processMessage, procMessage);
        } actions;

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(processMessage);
        }
    };
}}}}}}

#include <chila/lib/misc/macrosUndef.hpp>
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>
#undef DEF_NAMESPACE
#undef MY_BIND_ACTION
#undef MT_CODEGEN_NSP
#undef DEF_MODULE_ARGUMENT
#undef DEF_MODULE_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
