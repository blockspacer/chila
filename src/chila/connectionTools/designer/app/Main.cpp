/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Main.hpp"
#include "connectors/gen/FileLoader.hpp"
#include <chila/lib/xmlppUtils/util.hpp>
#include <boost/bind.hpp>
#include <chila/connectionTools/lib/other/util.hpp>
#include <chila/connectionTools/lib/other/FunExecSequence.hpp>

#include <boost/filesystem/path.hpp>

#define cast_cprovider(Type, ptr) std::dynamic_pointer_cast<app::impl::connection::Type::CProvider>(ptr)

#define my_insert_fun(Alias, connector) cMap.add \
        ( \
            BOOST_PP_STRINGIZE(connector), \
            cast_cprovider(Alias, connector)->getConnector() \
        )


#include "macros.fgen.hpp"

MY_NSP_START
{
    Main::Main
    (
        boost::asio::io_service &ioService,
        const clMisc::XMLAccessor &projectAccessor,
        const boost::filesystem::path &designerHome,
        bool showFunEvents
    ) :
        ioService(ioService),
        logger(app::impl::connection::Logger::create()),
        mainWindow(app::impl::connection::MainWindow::create(ioService, designerHome / "mainWindow-v2.glade", showFunEvents)),
        fileLoader(app::impl::connection::FileLoader::create(ioService,
            loadPaths<ClmPathVec>
            (
                projectAccessor,
                "/project/flowCInstances/start",
                "flowCInstance"
            ),
            loadPaths<ClmPathSet>
            (
                projectAccessor,
                "/project/flowCInstances/dim",
                "flowCInstance"
            ),
            showFunEvents)),
        cpFiles(loadPaths<PathSet>
        (
            projectAccessor,
            "/project/cPerformers",
            "cPerformer"
        )),
        connFiles(loadPaths<PathSet>
        (
            projectAccessor,
            "/project/connectors",
            "connector"
        ))
    {
        using CPData = app::impl::connection::CPerformerData;

        cclOther::addToMapAndLauncher(cMap, launcher, "logger", logger->getConnector());
        cclOther::addToMapAndLauncher(cMap, launcher, "mainWindow", mainWindow->getConnector());
        cclOther::addToMapAndLauncher(cMap, launcher, "fileLoader", fileLoader->getConnector());

        launcher.startedFun = [this] { started(); };
        launcher.finishedFun = [this] { finished(); };

        CPData::connect(cMap);
        launcher.connect();
    }

    void Main::started()
    {
        ioService.post([=](){ cast_cprovider(FileLoader, fileLoader)->getConnector().actions.loadFiles({cpFiles, connFiles}); });

        ioService.post(boost::bind(boost::ref(cast_cprovider(FileLoader, fileLoader)->getConnector().actions.refreshTree)));
    }

    void Main::finished()
    {
        work.reset();
    }


    void Main::start()
    {
        work = std::make_shared<boost::asio::io_service::work>(boost::ref(ioService));

        launcher.start();
        ioService.run();
    }

    template <typename Type>
    void load(std::set<Type> &set, const std::string &value)
    {
        set.insert(value);
    }

    template <typename Type>
    void load(std::vector<Type> &vec, const std::string &value)
    {
        vec.push_back(value);
    }


    template <typename Ret>
    Ret Main::loadPaths(
        const clMisc::XMLAccessor &projectAccessor,
        const std::string &path,
        const std::string &childName) const
    {
        Ret ret;

        auto &element = projectAccessor.getElement(path);

        for (auto *node : element.get_children(childName))
        {
            auto &elem = dynamic_cast<const xmlpp::Element&>(*node);

            load(ret, chila::lib::xmlppUtils::getAttribute<std::string>(elem, "path"));
        }

        return ret;
    }


}
MY_NSP_END

