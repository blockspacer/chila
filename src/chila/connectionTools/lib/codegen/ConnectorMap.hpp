/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
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
