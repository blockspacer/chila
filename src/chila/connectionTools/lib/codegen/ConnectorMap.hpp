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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTORMAP_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTORMAP_HPP

#include "fwd.hpp"
#include <boost/cast.hpp>
#include <chila/lib/misc/Path.hpp>
#include <map>
#include "macros.fgen.hpp"

MY_NSP_START
{
    class ConnectorMap
    {
        public:
            Connector &add(clMisc::Path path, Connector &connector);
            Connector &get(const clMisc::Path &path) const;

            template <typename Type>
            Type &get(const clMisc::Path &path) const { return dynamic_cast<Type&>(get(path)); }

        private:
            using Map = std::map<clMisc::Path, Connector*>;
            Map map;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
