/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__DEBUGFILEFUN_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEBUGFILEFUN_HPP

#include "fwd.hpp"
#include "FunDynDataCreator.hpp"
#include <chila/connectionTools/lib/other/fileDebug/LogFile.hpp>
#include <chila/lib/misc/QueuePoster.hpp>
#include <chila/lib/misc/ValueStreamer.hpp>
#include <chila/lib/misc/InPlaceStrStream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/hana.hpp>
#include <chila/lib/misc/SinkInserter.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename FunctionMData>
    struct DebugFileFun
    {
        typedef void result_type;

        std::string connInstanceName, funType;

        fileDebug::LogFile &logFile;
        bool showArguments;
        std::string comments;
        typename FunctionMData::Function function;
        FunDynDataCreator<FunctionMData> creator;
        const chila::lib::misc::ValueStreamer &valueStreamer;

        DebugFileFun
        (
            fileDebug::LogFile &logFile,
            const chila::lib::misc::ValueStreamer &valueStreamer,
            const std::string &connInstanceName,
            const std::string &funType,
            const typename FunctionMData::Function &fun,
            bool showArguments,
            const std::string &comments
        ) :
            logFile(logFile),
            valueStreamer(valueStreamer),
            function(fun),
            funType(funType),
            connInstanceName(connInstanceName),
            showArguments(showArguments),
            comments(comments) {}

            template <unsigned argIndex>
            void streamParam(std::ofstream &file, const fileDebug::LogFile::WritePrefix &prefix)
            {
            }

            template <unsigned argIndex, typename Arg, typename ...Args>
            void streamParam(std::ofstream &file, const fileDebug::LogFile::WritePrefix &prefix, const Arg &arg, const Args&... args)
            {
                using ArgType = typename decltype(+boost::hana::at(typename FunctionMData::Arguments{}, boost::hana::int_c<argIndex>))::type;

                file << prefix << "  |--- " << ArgType::getName() << ": [" << valueStreamer.inserter(arg) << "]" << std::endl;

                streamParam<argIndex + 1>(file, prefix, args...);
            }

            template <typename ...Args>
            void operator()(const Args&... args)
            {
                logFile.writeFunEx(function ? ([&] { function(args...); }) : fileDebug::LogFile::Function(),
                    [&](std::ofstream &file, const fileDebug::LogFile::WritePrefix &prefix)
                    {
                        file << prefix << "---> " << "<" << funType + "> " << connInstanceName << "." << FunctionMData::getName();

                        if (!comments.empty()) file << " (" << comments << ")";

                        file << std::endl;

                        streamParam<0>(file, prefix, args...);
                    });
            }
    };

    template <typename FunctionMData>
    struct DebugFileFunPFS
    {
        using result_type = DebugFileFun<FunctionMData>;

        fileDebug::LogFile &logFile;
        const std::string connInstanceName, funType;
        bool showArguments;
        std::string comments;
        const chila::lib::misc::ValueStreamer &valueStreamer;

        DebugFileFunPFS
        (
            fileDebug::LogFile &logFile,
            const chila::lib::misc::ValueStreamer &valueStreamer,
            const std::string &connInstanceName,
            const std::string &funType,
            bool showArguments,
            const std::string &comments
        ) :
            logFile(logFile),
            valueStreamer(valueStreamer),
            connInstanceName(connInstanceName),
            funType(funType),
            showArguments(showArguments),
            comments(comments) {}

        result_type operator()(const typename FunctionMData::Function &fun) const
        {
            return result_type(logFile, valueStreamer, connInstanceName, funType, fun, showArguments, comments);
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
