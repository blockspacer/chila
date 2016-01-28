/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ActionExecuter.hpp"
#include <boost/make_shared.hpp>
#include <chila/lib/misc/util.hpp>


#define MODULE_NAME ActionExecuter

#include "macros.fgen.hpp"

#define execute_action(name) \
    if (actionPath == clMisc::Path(#name, "_").getStringRep()) \
        execute_event(name)()

MY_NSP_START
{
    ActionExecuter::ActionExecuter(const std::string &instanceName) :
        connection::ActionExecuter::CProvider(instanceName)
    {
        connector.bindActions(*this);
    }

    void ActionExecuter::MOD_ACTION_SIG(launcher_start)
    {
        execute_event(launcher_started)();
    }

    void ActionExecuter::MOD_ACTION_SIG(execute)
    {
        execute_action(file_new);
        else execute_action(file_open);
        else execute_action(file_save);
        else execute_action(file_saveAs);
        else execute_action(file_saveAll);
        else execute_action(file_close);
        else execute_action(file_closeAll);
        else execute_action(file_quit);
    }


    void ActionExecuter::MOD_ACTION_SIG(launcher_finish)
    {
//        timer.cancel();

        execute_event(launcher_finished)();
    }

    connection::ActionExecuter::CProviderUPtr connection::ActionExecuter::create(const std::string &instanceName)
    {
        return boost::make_unique<impl::ActionExecuter>(instanceName);
    }
}
MY_NSP_END
