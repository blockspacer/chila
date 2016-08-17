/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__LAUNCHER_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__LAUNCHER_HPP

#include "fwd.hpp"
#include <boost/make_shared.hpp>
#include <iostream>
#include <chila/lib/misc/Path.hpp>
#include <boost/function.hpp>
#include <chila/connectionTools/lib/other/FunExecSequence.hpp>
#include <vector>

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Launcher
    {
        public:
            Launcher() : lastStarted(NULL) {}

            std::function<void()> startedFun, finishedFun;

            template <typename ConnType>
            void add(ConnType &conn)
            {
                connectors.push_back(connectorImpl(conn));
            }

            void connect();
            void start();
            void finish();
        private:
            using Function = std::function<void()>;

            struct Connector
            {
                LAUNCHER_ADD_TO_EVENT_VIRTUAL(Started, started)
                LAUNCHER_ADD_TO_EVENT_VIRTUAL(Deactivated, deactivated)
                LAUNCHER_ADD_TO_EVENT_VIRTUAL(Finished, finished)

                virtual void start() = 0;
                virtual void deactivate() = 0;
                virtual void finish() = 0;

                virtual chila::lib::misc::Path getPath() const = 0;

                virtual ~Connector() {}
            };

            template <typename ConnType>
            struct ConnectorImpl final: public Connector
            {
                ConnType &connector;

                explicit ConnectorImpl(ConnType &connector) : connector(connector) {}

                LAUNCHER_ADD_TO_EVENT(Started, started)
                LAUNCHER_ADD_TO_EVENT(Deactivated, deactivated)
                LAUNCHER_ADD_TO_EVENT(Finished, finished)

                void start() override { connector.actions.launcher_start(); }
                void deactivate() override { connector.actions.launcher_deactivate(); }
                void finish() override { connector.actions.launcher_finish(); }
                chila::lib::misc::Path getPath() const override { return connector.path(); }
            };

            template <typename ConnType>
            std::shared_ptr<ConnectorImpl<ConnType>> connectorImpl(ConnType &connector)
            {
                return std::make_shared<ConnectorImpl<ConnType>>(connector);
            }

            CHILA_LIB_MISC__FWDEC_SPTR(Connector);


            typedef std::vector<ConnectorSPtr> ConnectorVec;
            ConnectorVec connectors;

            ConnectorSPtr lastStarted;

            void allDeactivated();

    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

