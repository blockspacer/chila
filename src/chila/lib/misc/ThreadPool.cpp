/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ThreadPool.hpp"
#include <boost/foreach.hpp>
#include <cassert>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/exceptions.hpp>
//#include <sys/prctl.h>

#include "macros.fgen.hpp"

MY_NSP_START
{
    void ThreadPool::launch(const std::string &name, const Fun &fun)
    {
        boost::mutex::scoped_lock lock(mutex);
        my_assert(threads.insert(name).second);
        boost::thread thread([this, name, fun]()
        {
            if (startedFun)
                startedFun(name);

            setThreadName(name);
            fun();

            boost::mutex::scoped_lock lock(mutex);
            my_assert(threads.erase(name));

            finishedCV.notify_all();
            if (finishedFun)
                finishedFun(name);
        });
    }

    void ThreadPool::iterate(const ItFun &fun) const
    {
        boost::mutex::scoped_lock lock(mutex);
        for (const auto &name : threads)
        {
            fun(name);
        }
    }

    void ThreadPool::waitAll()
    {
        boost::mutex::scoped_lock lock(mutex);
        while (threads.size()) finishedCV.wait(lock);
    }

    void ThreadPool::setThreadName(const std::string &name)
    {
        threadName().reset(new std::string(name));
    }


    const std::string &ThreadPool::getThreadName()
    {
        my_assert(threadName().get());
        return *threadName();
    }

    const std::string *ThreadPool::getThreadNamePtr()
    {
        return threadName().get();
    }
}
MY_NSP_END

