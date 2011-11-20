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

#ifndef CHILA_CONNECTIONTOOLS_LIB_MODULE_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_MODULE_HPP

#include "fwd.hpp"
#include "Object.hpp"
#include "Arguments.hpp"
#include "Functions.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    struct Connector : public Object<NspBase>, public Arguments<Connector>
    {
        public:
            Functions actions, events;

            StringVec headerCode;

            Connector(NspBase &container, const std::string &name, const std::string &description) :
                Object<NspBase>(container, name),
                actions(*this, "actions"), events(*this, "events"), description(description) {}

            libMisc::Path getPath() const { return Object<NspBase>::getPath(); }
            const std::string &getDescription() const { return description; }

            void check() const
            {
                CheckErrorGroup errorGroup;
                bool hasErrors = false;

                try { actions.check();    } catch (const CheckError &ex) { errorGroup.addError(ex); hasErrors = true; }
                try { events.check();  } catch (const CheckError &ex) { errorGroup.addError(ex); hasErrors = true; }

                if (hasErrors) throw errorGroup;
            }

        private:
            std::string description;
    };
}}}}


#undef libMisc
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

