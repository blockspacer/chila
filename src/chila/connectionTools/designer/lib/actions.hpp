/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ACTIONS_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ACTIONS_HPP

#define def_action_base(r, data, elem) public elem

#define def_action(Name, ActionType, Interfaces, ttitle) \
        struct Name : \
            public ActionType \
            BOOST_PP_COMMA_IF(BOOST_PP_SEQ_SIZE(Interfaces)) \
            BOOST_PP_SEQ_FOR_EACH(def_action_base,,Interfaces) \
        {                                                       \
            Name(std::string id = "", ActionMap *parent = nullptr) : ActionType(rvalue_cast(id), parent) {} \
            static std::string title() { return ttitle; }          \
            std::string name() const override { return ttitle; }          \
        }

#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <chila/connectionTools/lib/tree/fwd.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Action: public ActionElement
    {
        Action(std::string id = "", ActionMap *parent = nullptr) : ActionElement(rvalue_cast(id), parent) {}

        virtual std::string name() const = 0;
        std::string string() const { return name(); }
    };

    struct ActionWithValue: public Action
    {
        std::string current;
        ActionWithValue(std::string id = "", ActionMap *parent = nullptr) : Action(rvalue_cast(id), parent) {}
    };

    struct ActionWithPos: public Action
    {
        chila::connectionTools::lib::tree::ValueVec posibilities;

        ActionWithPos(std::string id = "", ActionMap *parent = nullptr) : Action(rvalue_cast(id), parent) {}
    };


    namespace actions
    {
        struct AddElement { virtual ~AddElement() {} };
        struct SetValue { virtual ~SetValue() {} };
        struct SetDesc { virtual ~SetDesc() {} };

        def_action(SetValueWPos,    ActionWithPos,      (SetValue),     "set value");
        def_action(SetValueWVal,    ActionWithValue,    (SetValue),     "set value");
        def_action(Remove,          Action,             ,               "remove");
        def_action(Rename,          Action,             ,               "rename");
        def_action(Add,             Action,             (AddElement),   "add element");
        def_action(AddWPos,         ActionWithPos,      (AddElement),   "add element");
        def_action(AddWVal,         ActionWithValue,    (AddElement),   "add element");
        def_action(GoToReferenced,  Action,             ,               "go to referenced");
        def_action(MoveUp,          Action,             ,               "move up");
        def_action(MoveDown,        Action,             ,               "move down");
        def_action(Cut,             Action,             ,               "cut");
        def_action(Paste,           Action,             ,               "paste");
        def_action(SetDescription,  ActionWithValue,    (SetDesc),      "set description");
    }

    inline std::ostream &operator<<(std::ostream &out, const Action &action)
    {
        return out << action.string();
    }

}
MY_NSP_END

#undef def_action_base
#undef def_action
#include "macros.fgen.hpp"


#endif
