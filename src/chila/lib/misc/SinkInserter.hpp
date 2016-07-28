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

#ifndef CHILA_LIB_MISC__SINKINSERTER_HPP
#define CHILA_LIB_MISC__SINKINSERTER_HPP

#include <iostream>

#define CHILA_LIB_MISC__FSI_METHOD_BIND(method) \
    chila::lib::misc::funSinkInserter([&](std::ostream &out) { method(out); })

#define CHILA_LIB_MISC__FSI_METHOD_BIND_WA(method, ...) \
    chila::lib::misc::funSinkInserter([&](std::ostream &out) { method(out, __VA_ARGS__); })

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct SinkInserterBase {};

    template <typename Derived>
    struct SinkInserter: public SinkInserterBase
    {
        template <typename Sink>
        void operator()(Sink &out) const
        {
            static_cast<const Derived*>(this)->write(out);
        }
    };

    template <typename Fun>
    struct FunSinkInserter final: public SinkInserter< FunSinkInserter<Fun> >
    {
        Fun fun;

        FunSinkInserter(const Fun &fun) : fun(fun) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            fun(out);
        }
    };


    template <typename Sink, typename Derived>
    inline Sink &operator<<(Sink &out, const SinkInserter<Derived> &inserter)
    {
        inserter(out);
        return out;
    }

    template <typename Fun>
    inline FunSinkInserter<Fun> funSinkInserter(const Fun &fun)
    {
        return FunSinkInserter<Fun>(fun);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
