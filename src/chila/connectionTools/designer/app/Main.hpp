/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP__MAIN_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP__MAIN_HPP

#include "fwd.hpp"
#include "impl/connection/CPerformerData.hpp"
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include "impl/connection/fwd.hpp"
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <chila/lib/misc/XMLAccessor.hpp>
#include <boost/filesystem/path.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"
#include "chila/connectionTools/lib/codegen/ConnectorMap.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    using PathVec = std::vector<boost::filesystem::path>;
    using chila::connectionTools::lib::codegen::ConnectorMap;
    namespace cclOther = chila::connectionTools::lib::other;

    class Main
    {
        public:
            Main
            (
                boost::asio::io_service &ioService,
                const clMisc::XMLAccessor &projectAccessor,
                const boost::filesystem::path &designerHome,
                bool showFunEvents
            );

            void start();

        private:
            boost::asio::io_service &ioService;

            PathSet cpFiles, connFiles;

            app::impl::connection::Logger::CProviderSPtr logger;
            app::impl::connection::FileLoader::CProviderSPtr fileLoader;
            app::impl::connection::MainWindow::CProviderSPtr mainWindow;

            ConnectorMap cMap;
            cclOther::Launcher launcher;

            using WorkSPtr = std::shared_ptr<boost::asio::io_service::work>;
            WorkSPtr work;

            void started();
            void finished();

            template <typename Ret>
            Ret loadPaths(
                const clMisc::XMLAccessor &projectAccessor,
                const std::string &path,
                const std::string &childName) const;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"
#endif


