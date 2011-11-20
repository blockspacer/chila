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

#ifndef CHILA_CONNECTIONTOOLS_LIB_APCARGUMENTS_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_APCARGUMENTS_HPP

#include "fwd.hpp"
#include "APCArgument.hpp"
#include "ObjectContainer.hpp"
#include "macrosDef.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class APCArguments : public Object<ArgProviderCreator>, public virtual ObjectContainer
    {
        private:
            Application &getApplication();
            const Application &getApplication() const;

        public:
            APCArguments(ArgProviderCreator &container, const std::string &name) :
                Object<ArgProviderCreator>(container, name) {}

            void setArgument(const std::string &name)
            {
                setObject(new APCArgument(*this, name));
            }

            OBJECT_GROUP_DEF_GETTERS(APCArgument, Argument)
            OBJECT_GROUP_DEF_VEC_GETTER(APCArgument, Arguments)

            void check() const { ObjectContainer::checkObjects(); }

    };
}}}}

#undef DEF_NAMESPACE

#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosUndef.hpp>
#endif

