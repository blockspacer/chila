/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.tree'
 *
 * 'chila.connectionTools.lib.tree' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.tree' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with 'chila.connectionTools.lib.tree'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXCEPTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXCEPTIONS_HPP

#include <chila/lib/misc/exceptions.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR(Exception);
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorInstanceAlreadyExists, "connector instance already exists");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorInstanceNotFound, "connector instance not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, FunctionAlreadySet, "function already set");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, FunctionNotSet, "function not set");

//    struct ErrorInfo
//    {
//        using ConnectorInstancePath = boost::error_info<struct tag_cinstance_name, chila::lib::misc::Path>;
//    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

