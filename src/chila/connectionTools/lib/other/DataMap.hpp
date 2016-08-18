/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.lib'
 *
 * 'chila.lib' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.lib' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.lib'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__DATAMAP_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DATAMAP_HPP

#include "fwd.hpp"
#include <map>
#include <boost/any.hpp>
#include <chila/lib/misc/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct DataMap
    {
        public:
            template <typename Type>
            Type getVal(const std::string &name) const
            {
                auto it = map.find(name);
                my_assert(it != map.end());

                return boost::any_cast<Type>(it->second);
            }

            template <typename Type>
            void insertVal(std::string name, Type data)
            {
                my_assert(map.insert({rvalue_cast(name), rvalue_cast(data)}).second);
            }

            template <typename Type>
            Type &getRef(const std::string &name) const
            {
                auto it = map.find(name);
                my_assert(it != map.end());

                return boost::unwrap_ref(boost::any_cast<boost::reference_wrapper<Type>&>(const_cast<boost::any&>(it->second)));
            }

            template <typename Type>
            void insertRef(std::string name, Type &data)
            {
                my_assert(map.insert({rvalue_cast(name), boost::ref(data)}).second);
            }


        private:
            using Map = std::map<std::string, boost::any>;
            Map map;

            const Map &getMap() const { return map; }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
