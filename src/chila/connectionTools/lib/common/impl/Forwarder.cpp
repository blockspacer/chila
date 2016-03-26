/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Forwarder.hpp"

#include <chila/lib/misc/macrosExp.hpp>


#include "macros.fgen.hpp"

#define MODULE_NAME Forwarder


MY_NSP_START
{
    void Forwarder::MOD_ACTION_SIG(take)
    {
        boost::mutex::scoped_lock lock(mutex);
        check_state(ModuleState::STARTED, ModuleState::DEACTIVATED);

        if (executer)
            executer(eventExecuter, object);
        else
            execute_event(forwarded)(object);
    }

    connection::Forwarder::CProviderUPtr connection::Forwarder::create(const std::string &instanceName, const ExecuterFun &executer)
    {
        return std::make_unique<impl::Forwarder>(instanceName, executer);
    }
}
MY_NSP_END


