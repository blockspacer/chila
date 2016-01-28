/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_COMMON__DFFPOSTFUN_HPP
#define CHILA_CODEX_COMMON__DFFPOSTFUN_HPP

#include "../fwd.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>
#include <chila/connectionTools/lib/other/fileDebug/LogFile.hpp>
#include <chila/lib/misc/InPlaceStrStream.hpp>

#include "macros.fgen.hpp"

#define ipss        CHILA_LIB_MISC__IPSS
#define ipss_end    CHILA_LIB_MISC__IPSS_END

MY_NSP_START
{
    struct DFFPostFun
    {
        std::string module;
        boost::asio::io_service &ioService;
        cclOther::fileDebug::LogFile &debugLogFile;

        DFFPostFun(std::string module, boost::asio::io_service &ioService, cclOther::fileDebug::LogFile &debugLogFile) :
            module(rvalue_cast(module)),
            ioService(ioService),
            debugLogFile(debugLogFile) {}

        void operator()(const std::string &from, const std::function<void()> &fun)
        {
//            auto id = nextId();

//            debugLogFile.write(ipss(64) << "Posted (id='" << id << "')" << ipss_end);
            ioService.post([this, from, fun]
            {
                debugLogFile.write(ipss(4096) << module << ": " << from << ipss_end, fun);
            });
        }

//        static unsigned nextId()
//        {
//            static unsigned ret = 0;
//            static boost::mutex mutex;
//
//            boost::mutex::scoped_lock lock(mutex);
//            return ret++;
//        }
    };

    using PostFun = boost::function<void(const std::string &from, const std::function<void()> &fun)>;

    inline PostFun createPostFun(std::string module, boost::asio::io_service &ioService, cclOther::fileDebug::LogFile *debugLogFile)
    {
        if (debugLogFile)
            return DFFPostFun(rvalue_cast(module), ioService, *debugLogFile);
        else
            return [&ioService](const std::string &from, const std::function<void()> &fun)
            {
                ioService.post(fun);
            };
    }
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef ipss
#undef ipss_end

#endif
