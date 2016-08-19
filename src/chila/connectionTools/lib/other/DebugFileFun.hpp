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

        #ifdef __clang__
            template <typename... Arg>
            void operator()(const Arg& ...arg) const
            {
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
                    function ? ([&] { function(arg...); }) : fileDebug::LogFile::Function()
                );
            }

        #else
            #define DEF_OPER(z, n, data) \
                    BOOST_PP_IF(n, template <,) \
                    BOOST_PP_ENUM_PARAMS(n, typename Arg) \
                    BOOST_PP_IF(n, >,) \
                    void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, const Arg, &arg)) \
                    { \
                        const auto dynData = creator(BOOST_PP_ENUM_PARAMS(n, arg)); \
                        \
                        fileDebug::LogFile::ArgMap argMap; \
                        \
                        for (auto &arg : dynData.argVec) \
                        { \
                            auto argInserter = chila::lib::misc::funSinkInserter([&](std::ostream &out) \
                            { \
                                valueStreamer.stream(out, arg.value); \
                            }); \
                            \
                            argMap.insert({arg.name, ipss(1024) << argInserter << ipss_end}); \
                        } \
                        \
                        logFile.writeFunction \
                        ( \
                            "<" + funType + "> " + connInstanceName + "." + FunctionMData::getName(), \
                            argMap, showArguments, comments, \
                            function ? ([&] { function(BOOST_PP_ENUM_PARAMS(n, arg)); }) : fileDebug::LogFile::Function() \
                        ); \
                    }

            BOOST_PP_REPEAT_FROM_TO(0, 49, DEF_OPER,)

            #undef DEF_OPER
        #endif
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
