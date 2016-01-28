/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP__APP_HPP
#define CHILA_CODEX_BASE_APP__APP_HPP

#include "impl/connection/CPerformerData.hpp"
#include <chila/lib/misc/ValueStreamer.hpp>
#include <chila/connectionTools/lib/other/dynFunExecuter/ExecuterMap.hpp>
#include <chila/connectionTools/lib/other/dynFunExecuter/util.hpp>
#include <chila/connectionTools/lib/other/fileDebug/LogFile.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    class App
    {
        public:
            App(const boost::filesystem::path &installDir, cclOther::DataMap &dataMap);
            void connect(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect);
            void start();

        private:
            using WorkUPtr = std::unique_ptr<boost::asio::io_service::work>;
            using CPModTypes = impl::connection::CPerformerData::ModuleTypes;

            boost::asio::io_service ioService;
            bfs::path installDir;
            WorkUPtr work;
            Gtk::Main gtkMain;
            Glib::RefPtr<Gtk::Builder> builder;
            boost::asio::deadline_timer gtkTimer;

            struct Providers
            {
                CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPED_INSTANCES(CPModTypes, CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ)
            } providers;

            clMisc::ValueStreamer valueStreamer;

            cclOther::fileDebug::LogFileUPtr debugLogFile;
            bool showArguments;

            cclOther::dynFunExecuter::ExecuterMap dynFExecuter;

            Glib::RefPtr<Gtk::Builder> loadBuilder(const boost::filesystem::path &file);
            void setTimer();

            template <typename Provider>
            void addConnectorFunctions(Provider &provider);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
