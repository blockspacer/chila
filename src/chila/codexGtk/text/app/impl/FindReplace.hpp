/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_HPP
#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_HPP

#include "connection/FindReplace.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <gtkmm.h>


#define MODULE_NAME FindReplace

#include "macros.fgen.hpp"

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_WIDGETS_ELEM(r, data, elem) \
    ((Gtk::CheckButton)(BOOST_PP_CAT(findReplaceDlg_, elem)))

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_DECLARE_ELEM(r, data, elem) \
    BOOST_PP_SEQ_ELEM(0, elem) *BOOST_PP_SEQ_ELEM(1, elem);

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_GET_WIDGET(r, data, elem) \
    my_get_widget(BOOST_PP_SEQ_ELEM(1, elem));

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS \
    ((Gtk::Dialog)(findReplaceDlg)) \
    ((Gtk::TextView)(findReplaceDlg_findText)) \
    ((Gtk::TextView)(findReplaceDlg_replaceText))

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_CHECKS \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_WIDGETS_ELEM,, \
                          CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_CHECKLIST)



MY_NSP_START
{
    using Iterator = const char*;

    class FindReplace final: public connection::FindReplace::CProvider
    {
        public:
            using PostFun = connection::FindReplace::PostFun;

            FindReplace(module_args_ex);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate)    { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)        { execute_event(launcher_finished)(); }
            void MOD_ACTION_SIG(open);
            void MOD_ACTION_SIG(setTexts);

       private:
            using Checks = connection::FindReplaceChecks;

            enum class ResponseId
            {
                FIND_PREVIOUS, FIND_NEXT, REPLACE, REPLACE_ALL
            };

            Glib::RefPtr<Gtk::Builder> &builder;
            PostFun postFun;

            struct
            {
                BOOST_PP_SEQ_FOR_EACH(CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_DECLARE_ELEM,,
                    CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_CHECKS)
            } objects;

            Checks getChecks() const;

            template <typename EventExecuter>
            void checkButtonSignal(const std::string &name, const EventExecuter &eventExecuter);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

