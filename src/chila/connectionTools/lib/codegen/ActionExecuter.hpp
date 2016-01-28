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
        typedef typename Action::type::ConnectorType type;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
