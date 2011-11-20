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

#ifndef CHILA_CONNECTIONTOOLS_LIB_ARGUMENTGENERATOR_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_ARGUMENTGENERATOR_HPP

#include "fwd.hpp"
#include "APCArguments.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class ArgProviderCreator : public Object<Application>
    {
        private:
            APCArguments required, provided;

        public:
            ArgProviderCreator(Application &container, const std::string &name) :
                Object<Application>(container, name),
                required(*this, "required"), provided(*this, "provided") {}

            const APCArguments &getRequiredArguments() const { return required; }
            const APCArguments &getProvidedArguments() const { return provided; }

            APCArguments &getRequiredArguments() { return required; }
            APCArguments &getProvidedArguments() { return provided; }

            void check() const
            {
                required.check();
                provided.check();
            }

    };
}}}}

#undef libMisc

#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

