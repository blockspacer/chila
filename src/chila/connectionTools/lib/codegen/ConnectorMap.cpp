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

#include "ConnectorMap.hpp"
#include "exceptions.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    Connector &ConnectorMap::add(clMisc::Path path, Connector &connector)
    {
        auto ret = map.insert(Map::value_type(rvalue_cast(path), &connector));
        if (!ret.second)
        {
            BOOST_THROW_EXCEPTION(ConnectorInstanceAlreadyExists(path.getStringRep()));
        }

        return *(ret.first->second);
    }

    Connector &ConnectorMap::get(const clMisc::Path &path) const
    {
        auto it = map.find(path);
        if (it == map.end())
        {
            BOOST_THROW_EXCEPTION(ConnectorInstanceNotFound(path.getStringRep()));
        }

        return *(it->second);
    }

}
MY_NSP_END
