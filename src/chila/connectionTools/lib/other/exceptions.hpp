/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.other'
 *
 * 'chila.connectionTools.lib.other' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.other' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.other'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__EXCEPTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EXCEPTIONS_HPP

#include "fwd.hpp"
#include <chila/lib/misc/exceptions.hpp>

#define DEF_RUNTIME_ERROR_WT            CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT

#include "macros.fgen.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR_WT(ParseError, "parse error");
    DEF_RUNTIME_ERROR_WT(InvalidStateError, "invalid state");

    struct ErrorInfo
    {
        typedef boost::error_info<struct state_info, ModuleState> ModState;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef DEF_RUNTIME_ERROR_WT
#endif
