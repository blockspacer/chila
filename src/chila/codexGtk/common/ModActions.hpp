/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_COMMON__MODACTIONS_HPP
#define CHILA_CODEX_COMMON__MODACTIONS_HPP

#include "fwd.hpp"
#include "macros.fgen.hpp"

MY_NSP_START
{
    class ModActions
    {
        public:
            CHILA_LIB_MISC__NAMED_TUPLE
            (
                ModActionData, 0,
                ((ActionDataList)(aList))
                ((Glib::RefPtr<Gtk::Action>)(action))
            );

            using ModActionDataList = std::vector<ModActionData>;

            ModActionDataList dataList;

            void createAction(
                ActionDataList aList,
                const Glib::RefPtr<Gtk::Action> &action,
                const Gtk::AccelKey &aKey);

            void createAction(
                ActionDataList aList,
                const Glib::RefPtr<Gtk::Action> &action);

            void createAction(
                ActionDataList aList,
                const std::string &name,
                const std::string &label,
                const std::string &tooltip);

            void createAction(
                ActionDataList aList,
                const std::string &name,
                const std::string &label,
                const std::string &tooltip,
                const Gtk::BuiltinStockID &id,
                const Gtk::AccelKey &aKey);

            void createAction(
                ActionDataList aList,
                const std::string &name,
                const std::string &label,
                const std::string &tooltip,
                const Gtk::BuiltinStockID &id);

            void createSeparator(ActionDataList aList)
            {
                dataList.push_back({ rvalue_cast(aList), Glib::RefPtr<Gtk::Action>() });
            }

        private:
            Glib::RefPtr<Gtk::ActionGroup> actionGroup = Gtk::ActionGroup::create();
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
