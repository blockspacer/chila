/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Launcher.hpp"
#include "fwd.hpp"
#include <boost/bind.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <chila/lib/misc/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    void Launcher::connect()
    {
        my_assert(!connectors.empty());

        for (auto it = connectors.begin(); it != connectors.end(); ++it)
        {
            auto &connector = *it;
            if (it == connectors.begin())
            {
                connector->addToDeactivatedEvent([this](){ allDeactivated(); });
                connector->addToFinishedEvent(finishedFun);
            }

            if (it + 1 == connectors.end())
            {
                if (startedFun) connector->addToStartedEvent(startedFun);
            }
            else
            {
                auto &nextConn = *(it + 1);

                connector->addToStartedEvent([nextConn]() { nextConn->start(); });
                nextConn->addToDeactivatedEvent([connector]() { connector->deactivate(); });
                nextConn->addToFinishedEvent([connector]() { connector->finish(); });
            }

            connector->addToStartedEvent([this, connector](){ lastStarted = connector; });
        }
    }


    void Launcher::start()
    {
        my_assert(!connectors.empty());
        connectors.front().get()->start();
    }

    void Launcher::finish()
    {
        my_assert(lastStarted);
        lastStarted->deactivate();
    }

    void Launcher::allDeactivated()
    {
        my_assert(lastStarted);
        lastStarted->finish();
    }


}
MY_NSP_END
