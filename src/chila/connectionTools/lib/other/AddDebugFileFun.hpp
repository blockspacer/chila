#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__ADDDEBUGFILEFUN_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ADDDEBUGFILEFUN_HPP

#include "DebugFileFun.hpp"
#include "fwd.hpp"
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <chila/lib/misc/QueuePoster.hpp>
#include <boost/lexical_cast.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    auto addDebugFileFun
    (
        fileDebug::LogFile &logFile,
        const chila::lib::misc::ValueStreamer &valueStreamer,
        const std::string &connInstanceName,
        const std::string &funType,
        bool showArguments
    )
    {
        return [&logFile, &valueStreamer, connInstanceName, funType, showArguments](auto &funMData)
        {
            using FunctionMData = typename std::remove_reference<decltype(funMData)>::type;

            if (funMData)
                funMData.passFunAndSet(debugFileFunPFS<FunctionMData>(logFile, valueStreamer, connInstanceName, funType, showArguments, ""));
            else
                funMData = debugFileFun<FunctionMData>(logFile, valueStreamer, connInstanceName, funType, typename FunctionMData::Function(), showArguments, "");
        };
    }

    template <typename FunctionsFSeq>
    void addDebugFileFunToFunctions(
        fileDebug::LogFile &logFile,
        const chila::lib::misc::ValueStreamer &valueStreamer,
        const std::string &connInstanceName,
        const std::string &funType,
        const FunctionsFSeq &functions,
        bool showArguments)
    {
        boost::fusion::for_each(functions, addDebugFileFun(logFile, valueStreamer, connInstanceName, funType, showArguments));
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
