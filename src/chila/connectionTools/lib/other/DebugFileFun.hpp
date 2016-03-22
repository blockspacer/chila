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

            #define ARG_AT(pos) decltype(+boost::hana::at(typename FunctionMData::Arguments{}, boost::hana::int_c<pos>))::type

            #define STREAM_PARAM(z, n, data) \
                    file << prefix << "  |--- " << ARG_AT(n)::getName() << ": [" << valueStreamer.inserter(BOOST_PP_CAT(arg, n)) << "]" << std::endl;

            #define DEF_OPER(z, n, data) \
                    BOOST_PP_IF(n, template <,) \
                    BOOST_PP_ENUM_PARAMS(n, typename Arg) \
                    BOOST_PP_IF(n, >,) \
                    void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, const Arg, &arg)) \
                    { \
                        logFile.writeFunEx(function ? ([&] { function(BOOST_PP_ENUM_PARAMS(n, arg)); }) : fileDebug::LogFile::Function(), \
                            [&](std::ofstream &file, const fileDebug::LogFile::WritePrefix &prefix) \
                            { \
                                file << prefix << "---> " << "<" << funType + "> " << connInstanceName << "." << FunctionMData::getName(); \
                                \
                                if (!comments.empty()) file << " (" << comments << ")"; \
                                \
                                file << std::endl; \
                                \
                                BOOST_PP_REPEAT(n, STREAM_PARAM,) \
                            }); \
                    }

            BOOST_PP_REPEAT_FROM_TO(0, 49, DEF_OPER,)

            #undef DEF_OPER
            #undef STREAM_PARAM
            #undef ARG_AT
//        #endif
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
