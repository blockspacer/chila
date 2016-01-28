/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__UTIL_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__UTIL_HPP

#include "fwd.hpp"
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include "Launcher.hpp"
#include "common/impl/connection/Forwarder.hpp"
#include <boost/asio.hpp>
#include "exceptions.hpp"
#include "../codegen/fwd.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Connector>
    void addToMapAndLauncher(
        codegen::ConnectorMap &cMap,
        Launcher &launcher,
        const std::string &name,
        Connector &connector)
    {
        cMap.add(name, connector);
        launcher.add(connector);
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

    struct ForwarderQPoster
    {
        using result_type = void;
        boost::asio::io_service &queue;

        ForwarderQPoster(boost::asio::io_service &queue) : queue(queue) {}

        template <typename EventExecuter, typename Object>
        void operator()(const EventExecuter &eventExecuter, const Object &object) const
        {
            queue.post([eventExecuter, object]
            {
                eventExecuter.template execute<common::impl::connection::Forwarder::CProvider::Connector::Events::MData_forwarded>(object);
            });
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

