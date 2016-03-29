/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FindReplace.hpp"
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <chila/lib/gtkmm/util.hpp>
#include <chila/lib/misc/util.hpp>
#include <fstream>

#define MODULE_NAME FindReplace

#include "macros.fgen.hpp"

#define response_case_fnd(ENUM, event) \
    case ResponseId::ENUM: \
        execute_event(event)(); \
        break; \

#define response_case_rep(ENUM, event) \
    case ResponseId::ENUM: \
        execute_event(event)(replaceText); \
        break; \

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_LOAD_CHECK_ELEM(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) objects.BOOST_PP_CAT(findReplaceDlg_, elem)->get_active()

#define CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_CONNECT_CHECK_SIGNAL_ELEM(r, data, elem) \
        objects.BOOST_PP_CAT(findReplaceDlg_, elem)->signal_toggled().connect_notify([this, eventExecuter] \
        { \
            checkButtonSignal(BOOST_PP_STRINGIZE(elem), eventExecuter); \
        });


MY_NSP_START
{
    FindReplace::FindReplace(module_args_ex) :
        connection::FindReplace::CProvider(instanceName),
        postFun(postFun),
        builder(builder)
    {
        connector.bindActions(*this);

        BOOST_PP_SEQ_FOR_EACH(CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_GET_WIDGET,,
            CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_GTKOBJECTS_CHECKS)
    }

    FindReplace::Checks FindReplace::getChecks() const
    {
        return Checks
        (
            BOOST_PP_SEQ_FOR_EACH_I(CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_LOAD_CHECK_ELEM,,
                                    CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_CHECKLIST)
        );
    }

    template <typename EventExecuter>
    void FindReplace::checkButtonSignal(const std::string &name, const EventExecuter &eventExecuter)
    {
        auto findText = objects.findReplaceDlg_findText->get_buffer()->get_text();
        auto checks = getChecks();

        postFun("findReplaceDlg_" + name + "->signal_toggled()", [this, findText, checks, eventExecuter]
        {
            execute_event_tn(stateChanged)(findText, checks);
        });
    }

    void FindReplace::MOD_ACTION_SIG(launcher_start)
    {
        auto fontDesc = Pango::FontDescription("monospace");
        objects.findReplaceDlg_findText->override_font(fontDesc);
        objects.findReplaceDlg_replaceText->override_font(fontDesc);

        objects.findReplaceDlg_findText->get_buffer()->signal_changed().connect_notify([this, eventExecuter]
        {
            checkButtonSignal("findReplaceDlg_findText->signal_toggled()", eventExecuter);
        });

        BOOST_PP_SEQ_FOR_EACH(CHILA_CODEX_TEXT_APP_IMPL__FINDREPLACE_CONNECT_CHECK_SIGNAL_ELEM,,
                              CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_CHECKLIST)

        objects.findReplaceDlg->signal_response().connect_notify([this, eventExecuter](int resp)
        {
            if (resp == GTK_RESPONSE_DELETE_EVENT)
            {
                execute_event(closed)();
                return;
            }

            auto findText = objects.findReplaceDlg_findText->get_buffer()->get_text();
            auto replaceText = objects.findReplaceDlg_replaceText->get_buffer()->get_text();

            auto checks = getChecks();

            postFun("findReplaceDlg->signal_response()", [this, findText, replaceText, checks, eventExecuter, resp]
            {
                auto respEnum = ResponseId(resp);
                switch (respEnum)
                {
                    response_case_fnd(FIND_PREVIOUS, findPrevious)
                    response_case_fnd(FIND_NEXT, findNext)
                    response_case_rep(REPLACE, replace)
                    response_case_rep(REPLACE_ALL, replaceAll)

                    default: abort();
                }
            });
        });

        execute_event(launcher_started)();
    }

    void FindReplace::MOD_ACTION_SIG(open)
    {
        objects.findReplaceDlg->show_all();
    }

    void FindReplace::MOD_ACTION_SIG(setTexts)
    {
        objects.findReplaceDlg_findText->get_buffer()->set_text(findText);
    }


    connection::FindReplace::CProviderUPtr connection::FindReplace::create(module_args_ex)
    {
        return std::make_unique<impl::FindReplace>(module_pass_args_ex);
    }
}
MY_NSP_END
