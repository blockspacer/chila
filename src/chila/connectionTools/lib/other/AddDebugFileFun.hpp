/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

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
    struct AddDebugFileFun
    {
        fileDebug::LogFile &logFile;
        const std::string &connInstanceName;
        const std::string &funType;
        const chila::lib::misc::ValueStreamer &valueStreamer;
        bool showArguments;

        AddDebugFileFun(
                fileDebug::LogFile &logFile,
                const chila::lib::misc::ValueStreamer &valueStreamer,
                const std::string &connInstanceName,
                const std::string &funType,
                bool showArguments) :
            connInstanceName(connInstanceName),
            valueStreamer(valueStreamer),
            funType(funType),
            logFile(logFile),
            showArguments(showArguments)
        {
        }

        template <typename FunctionMData>
        void operator()(FunctionMData &funMData) const
        {
            if (funMData)
                funMData.passFunAndSet(DebugFileFunPFS<FunctionMData>(logFile, valueStreamer, connInstanceName, funType, showArguments, ""));
            else
                funMData = DebugFileFun<FunctionMData>(logFile, valueStreamer, connInstanceName, funType, typename FunctionMData::Function(), showArguments, "");
        }
    };

    template <typename FunctionsFSeq>
    void addDebugFileFunToFunctions(
        fileDebug::LogFile &logFile,
        const chila::lib::misc::ValueStreamer &valueStreamer,
        const std::string &connInstanceName,
        const std::string &funType,
        const FunctionsFSeq &functions,
        bool showArguments)
    {
        boost::fusion::for_each(functions, AddDebugFileFun(logFile, valueStreamer, connInstanceName, funType, showArguments));
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif