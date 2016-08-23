#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__DEBUGFILEFUN_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEBUGFILEFUN_HPP

#include "fwd.hpp"
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include "FunDynDataCreator.hpp"
#include <chila/connectionTools/lib/other/fileDebug/LogFile.hpp>
#include <chila/lib/misc/QueuePoster.hpp>
#include <chila/lib/misc/ValueStreamer.hpp>
#include <chila/lib/misc/InPlaceStrStream.hpp>
#include <boost/lexical_cast.hpp>
#include <chila/lib/misc/SinkInserter.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename FunctionMData>
    auto debugFileFun
    (
        fileDebug::LogFile &logFile,
        const chila::lib::misc::ValueStreamer &valueStreamer,
        const std::string &connInstanceName,
        const std::string &funType,
        const typename FunctionMData::Function &fun,
        bool showArguments,
        const std::string &comments
    )
    {
        return [&logFile, &valueStreamer, connInstanceName, funType, fun, showArguments, comments](const auto& ...arg)
        {
            FunDynDataCreator<FunctionMData> creator;
            const auto dynData = creator(arg...);

            fileDebug::LogFile::ArgMap argMap;

            for (auto &arg : dynData.argVec)
            {
                auto argInserter = chila::lib::misc::funSinkInserter([&](std::ostream &out)
                {
                    valueStreamer.stream(out, arg.value);
                });

                argMap.insert({arg.name, ipss(1024) << argInserter << ipss_end});
            }

            logFile.writeFunction
            (
                "<" + funType + "> " + connInstanceName + "." + FunctionMData::getName(),
                argMap, showArguments, comments,
                fun ? ([&] { fun(arg...); }) : fileDebug::LogFile::Function()
            );
        };
    }

    template <typename FunctionMData>
    auto debugFileFunPFS
    (
        fileDebug::LogFile &logFile,
        const chila::lib::misc::ValueStreamer &valueStreamer,
        const std::string &connInstanceName,
        const std::string &funType,
        bool showArguments,
        const std::string &comments
    )
    {
        return [&logFile, &valueStreamer, connInstanceName, funType, showArguments, comments](const typename FunctionMData::Function &fun)
        {
            return debugFileFun<FunctionMData>(logFile, valueStreamer, connInstanceName, funType, fun, showArguments, comments);
        };
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
