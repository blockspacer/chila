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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_IMPL_CONNECTION__FWD_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_IMPL_CONNECTION__FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_TYPE      CHILA_LIB_MISC__FWDEC_TYPE

DEF_NAMESPACE(6, (chila,connectionTools,appTest,app,impl,connection))
{
    FWDEC_TYPE(CProvider);

    struct CProvider
    {
        virtual ~CProvider() {}
    };
}}}}}}

#undef DEF_NAMESPACE
#undef FWDEC_TYPE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
