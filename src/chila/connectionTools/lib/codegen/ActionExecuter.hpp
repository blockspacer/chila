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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONEXECUTER_HPP

#include <chila/lib/misc/macrosExp.hpp>
#include <boost/ref.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename EventTag, unsigned ActionIndex, typename Action>
    struct ActionExecuterBase
    {
        typedef Action type;
        typedef void result_type;

        const Action &action;

        ActionExecuterBase(const Action &action) : action(action) {}
    };

    template <typename EventTag, unsigned ActionIndex, typename Action>
    struct ActionExecuter final: public ActionExecuterBase<EventTag, ActionIndex, Action>
    {
        ActionExecuter(const Action &action) :
            ActionExecuterBase<EventTag, ActionIndex, Action>(action) {}

        void operator()() const
        {
            return boost::unwrap_ref(this->action)();
        }

        #define DEF_OPERATOR(z, argCount, data) \
            template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)> \
            void operator()(BOOST_PP_ENUM_BINARY_PARAMS(argCount, const Arg, &arg)) const \
            { \
                return boost::unwrap_ref(this->action)(BOOST_PP_ENUM_PARAMS(argCount, arg)); \
            }

        BOOST_PP_REPEAT_FROM_TO(1, 19, DEF_OPERATOR,)

        #undef DEF_OPERATOR
    };


    template <typename EventTag, unsigned ActionIndex, typename Action>
    inline ActionExecuter<EventTag, ActionIndex, Action> actionExecuter(const Action &action)
    {
        return ActionExecuter<EventTag, ActionIndex, Action>(action);
    }

    template <typename Action>
    struct ConnectorTypeOf
    {
        typedef typename Action::ConnectorType type;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
