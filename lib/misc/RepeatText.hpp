/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_LIB_MISC_REPEATTEXT_HPP
#define CHILA_LIB_MISC_REPEATTEXT_HPP

#include "SinkInserter.hpp"

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{
    template <typename StringType>
    struct RepeatText : public chila::lib::misc::SinkInserter< RepeatText<StringType> >
    {
        unsigned count;
        StringType text;
        RepeatText(unsigned count, StringType text) :
            count(count), text(text) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            for (unsigned i = 0; i < count; ++i) out << text;
        }
    };

    template <typename StringType>
    inline RepeatText<StringType> repeatText(unsigned count, StringType text)
    {
        return RepeatText<StringType>(count, text);
    }
}}}

#include <chila/lib/misc/macrosUndef.hpp>
#undef DEF_NAMESPACE
#endif
