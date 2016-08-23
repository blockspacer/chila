#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__UTIL_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__UTIL_HPP

#include "fwd.hpp"
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <boost/asio.hpp>
#include "exceptions.hpp"
#include <chila/lib/misc/util.hpp>
#include "macrosExp.hpp"
#include "../codegen/fwd.hpp"
#include <boost/fusion/algorithm/iteration/for_each.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Fun1>
    inline auto funExecSequence(const Fun1 &fun1)
    {
        return [fun1](const auto &fun0)
        {
            return chila::lib::misc::funExecSequence(fun0, fun1);
        };
    }

    template <typename ConnFun, typename Fun>
    void addToConnFunction(ConnFun &connFun, const Fun &fun)
    {
        if (connFun)
            connFun.passFunAndSet(funExecSequence(fun));
        else
            connFun = fun;
    }

    inline std::string getStateName(ModuleState state)
    {
        switch (state)
        {
            case ModuleState::NONE: return "none";
            case ModuleState::STARTING: return "starting";
            case ModuleState::STARTED: return "started";
            case ModuleState::DEACTIVATING: return "deactivating";
            case ModuleState::DEACTIVATED: return "deactivated";
            case ModuleState::FINISHING: return "finishing";
            case ModuleState::FINISHED: return "finished";
            default : abort(); break;
        }
    }

    template <typename Event, typename EventExecuter>
    void raiseFatalFromInvalidState(const EventExecuter &eventExecuter, const InvalidStateError &ex)
    {
        auto state = chila::lib::misc::deref(boost::get_error_info<ErrorInfo::ModState>(ex));

        eventExecuter.template execute<Event>
            CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_FATAL_ARGS
            (
                "Invalid state: '" + getStateName(state) + "'",
                chila::lib::misc::deref(boost::get_error_info<boost::throw_function>(ex)),
                chila::lib::misc::deref(boost::get_error_info<boost::throw_file>(ex)),
                chila::lib::misc::deref(boost::get_error_info<boost::throw_line>(ex))
            );
    }

    template <typename Type>
    inline chila::lib::misc::StringVec toString(const Type &object) { return { boost::lexical_cast<std::string>(object) }; }

    template <>
    inline chila::lib::misc::StringVec toString(const bool &object) { return {(object ? "true" : "false")}; }

    template <>
    chila::lib::misc::StringVec toString(const chila::lib::misc::StringSet &set);

    template <typename FunctionsFSeq>
    void nullFunctions(const FunctionsFSeq &functions)
    {
        boost::fusion::for_each(functions, [](auto &funMData)
        {
            funMData = [](const auto&... args) {};
        });
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

