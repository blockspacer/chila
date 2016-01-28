/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
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
