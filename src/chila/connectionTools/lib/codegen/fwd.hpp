/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.codegen'
 *
 * 'chila.connectionTools.lib.codegen' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.codegen' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.codegen'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

#include "macros.fgen.hpp"

#define FWDEC_TYPE  CHILA_LIB_MISC__FWDEC_TYPE

MY_NSP_START
{
    namespace clMisc = chila::lib::misc;

    FWDEC_TYPE(Connector);
    FWDEC_TYPE(ConnectorMap);
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef FWDEC_TYPE

#endif
