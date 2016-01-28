/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_HPP

#include "fwd.hpp"
#include <boost/cast.hpp>
#include <initializer_list>
#include "nullFunctions.hpp"
#include <boost/thread/mutex.hpp>
#include "exceptions.hpp"
#include <chila/connectionTools/lib/other/exceptions.hpp>
#include <boost/range/algorithm/find.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Module
    {
        using ModuleState = chila::connectionTools::lib::other::ModuleState;

        ParameterList parameters;
        const std::string instanceName;
        ModuleState state;

        Module(const std::string &instanceName) : instanceName(instanceName), state(ModuleState::NONE) {}

        Module(const std::string &instanceName, const ParameterList &parameters) :
            parameters(parameters), instanceName(instanceName), state(ModuleState::NONE) {}

        virtual void nullEvents() = 0;
        virtual void nullActions() = 0;

        virtual void checkState(const std::initializer_list<ModuleState> &states, const char *function, const char *file, unsigned line) const = 0;

        void checkStateLM(boost::mutex &mutex, const std::initializer_list<ModuleState> &states, const char *function, const char *file, unsigned line) const
        {
            boost::mutex::scoped_lock lock(mutex);
            checkState(states, function, file, line);
        }

        void setState(ModuleState newState, const char *function, const char *file, unsigned line)
        {
            switch (newState)
            {
                case ModuleState::STARTING:       checkState({ModuleState::NONE}, function, file, line); break;
                case ModuleState::STARTED:        checkState({ModuleState::NONE, ModuleState::STARTING}, function, file, line); break;
                case ModuleState::DEACTIVATING:   checkState({ModuleState::STARTED}, function, file, line); break;
                case ModuleState::DEACTIVATED:    checkState({ModuleState::STARTED, ModuleState::DEACTIVATING}, function, file, line); break;
                case ModuleState::FINISHING:      checkState({ModuleState::DEACTIVATED}, function, file, line); break;
                case ModuleState::FINISHED:       checkState({ModuleState::DEACTIVATED, ModuleState::FINISHING}, function, file, line); break;
                default : abort(); break;
            }

            state = newState;
        }

        void setState(boost::mutex &mutex, ModuleState newState, const char *function, const char *file, unsigned line)
        {
            boost::mutex::scoped_lock lock(mutex);
            setState(newState, function, file, line);
        }

        virtual ~Module() {}
    };

    template <typename Derived, typename _Connector>
    struct ModuleImpl: public Module
    {
        using Connector = _Connector;
        using ArgTypes = typename Connector::ArgTypes;
        Connector connector;

        ModuleImpl(const std::string &instanceName) : Module(instanceName) {}

        ModuleImpl(const std::string &instanceName, const ParameterList &parameters) :
            Module(instanceName, parameters) {}


        Derived &derived() { return *boost::polymorphic_downcast<Derived*>(this); }
        const Derived &derived() const { return *boost::polymorphic_downcast<const Derived*>(this); }

        void nullEvents() override
        {
            chila::connectionTools::lib::other::nullFunctions(connector.events.list());
        }

        void nullActions() override
        {
            chila::connectionTools::lib::other::nullFunctions(connector.actions.list());
        }

        void checkState(const std::initializer_list<ModuleState> &states, const char *function, const char *file, unsigned line) const override
        {
            if (boost::range::find(states, state) == std::end(states))
                boost::throw_exception(chila::connectionTools::lib::other::InvalidStateError()
                        << chila::connectionTools::lib::other::ErrorInfo::ModState(state)
                        << boost::throw_function(function)
                        << boost::throw_file(file)
                        << boost::throw_line(line));
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
