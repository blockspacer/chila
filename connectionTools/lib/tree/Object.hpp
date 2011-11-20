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

#ifndef CHILA_CONNECTIONTOOLS_LIB_OBJECT_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_OBJECT_HPP

#include "fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    template <typename Container>
    class Object : boost::noncopyable, public virtual TreeElement
    {
        public:
            Container &container;

        protected:
            std::string name;

            Object(Container &container, const std::string &name = "") : container(container), name(name)
            {
                assert(!name.empty());
            }

        public:
            virtual ~Object() {}


            const std::string &getName() const { return name; }

            libMisc::Path getPath() const
            {
                return container.getPath() + name;
            }

            GlobalNsp &getGlobalNsp()
            {
                return container.getGlobalNsp();
            }

            const GlobalNsp &getGlobalNsp() const
            {
                return container.getGlobalNsp();
            }

    };
}}}}

#undef DEF_NAMESPACE
#undef libMisc


#include <chila/lib/misc/macrosUndef.hpp>
#endif

