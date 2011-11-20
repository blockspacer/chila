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

#ifndef CHILA_CONNECTIONTOOLS_LIB_APCNAMESREQPROV_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_APCNAMESREQPROV_HPP

#include "fwd.hpp"
#include "ArgProviderCreator.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class APCNamesReqProv : public IArgumentNamesProvider, public IArgumentNamesRequirer
    {
        private:
            StringSet required, provided;
            libMisc::Path path;

        public:
            APCNamesReqProv(const ArgProviderCreator &argProvCreator) : path(argProvCreator.getPath())
            {
                APCArgumentCVec requiredArgs = argProvCreator.getRequiredArguments().getArguments(),
                                providedArgs = argProvCreator.getProvidedArguments().getArguments();

                BOOST_FOREACH(const APCArgument *apcArg, requiredArgs)
                {
                    required.insert(apcArg->getName());
                }

                BOOST_FOREACH(const APCArgument *apcArg, providedArgs)
                {
                    provided.insert(apcArg->getName());
                }
            }

            const libMisc::Path &getPath() const { return path; }

            const StringSet &getRequiredArgNames() const { return required; }
            const StringSet &getProvidedArgNames() const { return provided; }
    };
}}}}

#undef libMisc
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

