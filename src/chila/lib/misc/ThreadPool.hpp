/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__THREADPOOL_HPP
#define CHILA_LIB_MISC__THREADPOOL_HPP

#include <boost/thread.hpp>
#include <set>

#include <boost/function.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class ThreadPool
    {
        public:
            typedef std::function<void()> Fun;
            typedef std::function<void(const std::string&)> ItFun;
            typedef std::function<void(const std::string&)> StartedFinishedFun;

            StartedFinishedFun startedFun, finishedFun;

            void launch(const std::string &name, const Fun &fun);

            void iterate(const ItFun &fun) const;

            static const std::string &getThreadName();
            static const std::string *getThreadNamePtr();
            static void setThreadName(const std::string &name);

            void waitAll();

        private:
            mutable boost::mutex mutex;
            boost::condition_variable finishedCV;
            typedef std::set<std::string> ThreadSet;
            ThreadSet threads;

            static boost::thread_specific_ptr<std::string> &threadName()
            {
                static boost::thread_specific_ptr<std::string> tn;
                return tn;
            }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

