/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ModActions.hpp"
#include "macros.fgen.hpp"

MY_NSP_START
{
    void ModActions::createAction(
        ActionDataList aList,
        const Glib::RefPtr<Gtk::Action> &action)
    {
        dataList.push_back({ rvalue_cast(aList), action });
        actionGroup->add(action);
    }

    void ModActions::createAction(
        ActionDataList aList,
        const Glib::RefPtr<Gtk::Action> &action,
        const Gtk::AccelKey &aKey)
    {
        dataList.push_back({ rvalue_cast(aList), action });
        actionGroup->add(action, aKey);
    }

    void ModActions::createAction(
        ActionDataList aList,
        const std::string &name,
        const std::string &label,
        const std::string &tooltip)
    {
        auto action = Gtk::Action::create(name, label, tooltip);

        createAction(rvalue_cast(aList), action);
    }

    void ModActions::createAction(
        ActionDataList aList,
        const std::string &name,
        const std::string &label,
        const std::string &tooltip,
        const Gtk::BuiltinStockID &id,
        const Gtk::AccelKey &aKey)
    {
        auto action = Gtk::Action::create(name, id, label, tooltip);

        createAction(rvalue_cast(aList), action, aKey);
    }

    void ModActions::createAction(
        ActionDataList aList,
        const std::string &name,
        const std::string &label,
        const std::string &tooltip,
        const Gtk::BuiltinStockID &id)
    {
        auto action = Gtk::Action::create(name, id, label, tooltip);

        createAction(rvalue_cast(aList), action);
    }
}
MY_NSP_END
