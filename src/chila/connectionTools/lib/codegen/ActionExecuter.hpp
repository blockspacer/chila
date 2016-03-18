/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONEXECUTER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONEXECUTER_HPP

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename EventTag, unsigned ActionIndex, typename Action>
    struct ActionExecuter
    {
        typedef Action type;
        typedef void result_type;

        const Action &action;

        ActionExecuter(const Action &action) : action(action) {}

        template <typename ...Args>
        void operator()(const Args&... args) const
        {
            return boost::unwrap_ref(action)(args...);
        }
    };

    template <typename EventTag, unsigned ActionIndex, typename Action>
    inline ActionExecuter<EventTag, ActionIndex, Action> actionExecuter(const Action &action)
    {
        return ActionExecuter<EventTag, ActionIndex, Action>(action);
    }

    template <typename Action>
    struct ConnectorTypeOf
    {
        typedef typename Action::type::ConnectorType type;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
