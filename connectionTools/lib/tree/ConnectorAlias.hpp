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

#ifndef CHILA_CONNECTIONTOOLS_LIB_ARGUMENTALIASLINKGROUP_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_ARGUMENTALIASLINKGROUP_HPP

#include "fwd.hpp"
#include "ObjectContainer.hpp"
#include "ArgumentAliasLink.hpp"
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class ConnectorAlias : public Object<Application>, public virtual ObjectContainer
    {
        private:
            libMisc::Path connectorPath;

        public:
            ConnectorAlias(Application &container, const std::string &name, const libMisc::Path &connectorPath) :
                Object<Application>(container, name), connectorPath(connectorPath) {}

            void setLink(const std::string &argName, const std::string &aliasName)
            {
                setObject(new ArgumentAliasLink(*this, argName, aliasName));
            }

            const libMisc::Path &getConnectorPath() const { return connectorPath; }

            Connector &getConnector();
            const Connector &getConnector() const;


            void check() const;

            OBJECT_GROUP_DEF_GETTERS(ArgumentAliasLink, Link)
            OBJECT_GROUP_DEF_VEC_GETTER(ArgumentAliasLink, Links)
    };
}}}}


#undef libMisc
#undef DEF_NAMESPACE

#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosUndef.hpp>
#endif

