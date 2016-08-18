/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.codegen'
 *
 * 'chila.connectionTools.lib.codegen' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.codegen' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.codegen'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONIMPLEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONIMPLEXECUTER_HPP

#include "EventExecuter.hpp"
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename MemFn, typename Object, typename EventFSeq>
    struct ActionImplExecuter
    {
        public:
            using result_type = void;

            ActionImplExecuter(const ActionImplExecuter&) = default;

            ActionImplExecuter(const MemFn &fun, Object &object, const EventFSeq &eventFSeq) :
                eventFSeq(eventFSeq), object(object), fun(fun) {}

            template <typename ...Args>
            void operator()(const Args&... arg)
            {
                this->fun(this->object, arg..., eventExecuter(eventFSeq));
            }


        private:
            const EventFSeq &eventFSeq;
            MemFn fun;
            Object &object;
    };

    template <typename MemFn, typename Object, typename EventFSeq>
    inline ActionImplExecuter<MemFn, Object, EventFSeq> actionImplExecuter(const MemFn &fun, Object &object, const EventFSeq &eventFSeq)
    {
        return ActionImplExecuter<MemFn, Object, EventFSeq>(fun, object, eventFSeq);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
