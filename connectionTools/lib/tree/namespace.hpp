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

#ifndef CHILA_CONNECTIONTOOLS_LIB_NAMESPACE_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_NAMESPACE_HPP

#include "ObjectContainer.hpp"
#include "Object.hpp"
#include "Connector.hpp"
#include "Application.hpp"
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class NspBase : public virtual ObjectContainer, public virtual TreeElement
    {
        private:
            NspBase &createNamespaceFromHerePv(StringVec::const_iterator cur, StringVec::const_iterator end);
            Namespace &findNamespacePv(StringVec::const_iterator cur, StringVec::const_iterator end);
            const Namespace &findNamespacePv(StringVec::const_iterator cur, StringVec::const_iterator end) const;

        public:
            NspBase &createNamespaceFromHere(const libMisc::Path &path)
            {
                return createNamespaceFromHerePv(path.getNames().begin(), path.getNames().end());
            }

            Namespace &setNamespace(const std::string &name);

            /** Sets a connector. */
            Connector &setConnector(const std::string &name, const std::string &description)
            {
                return setObject(new Connector(*this, name, description));
            }

            Application &setApplication(const std::string &name)
            {
                return setObject(new Application(*this, name));
            }

            OBJECT_GROUP_DEF_GETTERS(Namespace, Namespace)
            OBJECT_GROUP_DEF_VEC_GETTER(Namespace, Namespaces)

            OBJECT_GROUP_DEF_GETTERS(Connector, Connector)
            OBJECT_GROUP_DEF_VEC_GETTER(Connector, Connectors)

            OBJECT_GROUP_DEF_GETTERS(Application, Application)
            OBJECT_GROUP_DEF_VEC_GETTER(Application, Applications)


            Namespace &findNamespace(const libMisc::Path &path)
            {
                const StringVec &names = path.getNames();
                return findNamespacePv(names.begin(), names.end());
            }

            const Namespace &findNamespace(const libMisc::Path &path) const
            {
                const StringVec &names = path.getNames();
                return findNamespacePv(names.begin(), names.end());
            }

            virtual libMisc::Path getPath() const = 0;


    };

    struct GlobalNsp : public NspBase
    {
        libMisc::Path getPath() const { return libMisc::Path(); }

        GlobalNsp &getGlobalNsp() { return *this; }
        const GlobalNsp &getGlobalNsp() const { return *this; }
    };

    struct Namespace : public Object<NspBase>, public NspBase
    {
        Namespace(NspBase &container, const std::string &name) : Object<NspBase>(container, name)
        {
            if (name.empty())
                throw std::invalid_argument("name");
        }

        libMisc::Path getPath() const { return container.getPath() + name; }

        GlobalNsp &getGlobalNsp() { return container.getGlobalNsp(); }
        const GlobalNsp &getGlobalNsp() const { return container.getGlobalNsp(); }
    };
}}}}

#undef DEF_NAMESPACE
#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosUndef.hpp>
#endif

