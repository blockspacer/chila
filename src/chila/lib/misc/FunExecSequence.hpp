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

#ifndef CHILA_LIB_MISC__FUNEXECSEQUENCE_HPP
#define CHILA_LIB_MISC__FUNEXECSEQUENCE_HPP

#include <boost/ref.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Fun0, typename Fun1>
    inline auto funExecSequence(const Fun0 &fun0, const Fun1 &fun1)
    {
        return [fun0, fun1](auto&&... args)
        {
            boost::unwrap_ref(fun0)(std::forward<decltype(args)>(args)...);
            boost::unwrap_ref(fun1)(std::forward<decltype(args)>(args)...);
        };
    }

    template <typename FunFrom, typename FunTo>
    void composeFun(FunFrom &from, const FunTo &to)
    {
        if (from)
            from = funExecSequence(from, to);
        else
            from = to;
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
