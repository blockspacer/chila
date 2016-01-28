/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "App.hpp"
#include "chila/connectionTools/lib/other/Launcher.hpp"
#include <boost/filesystem.hpp>
#include <chila/connectionTools/lib/other/FunDynDataCreator.hpp>
#include <chila/connectionTools/lib/other/DataMap.hpp>
#include "chila/connectionTools/lib/other/util.hpp"
#include <chila/connectionTools/lib/other/AddDebugFileFun.hpp>
#include "../../common/DFFPostFun.hpp"
#include <boost/range.hpp>
#include "../../common/util.hpp"
#include <boost/range/algorithm.hpp>

#include "macros.fgen.hpp"

#define MY_QUALIFIER(Type, object) \
        (impl::connection::CPerformerData::ModuleTypes::Type, object)

#define ADD_MODULE_FUN(module) \
    addConnectorFunctions(*(providers.module));

MY_NSP_START
{
    App::App(const boost::filesystem::path &installDir, cclOther::DataMap &dataMap) :
        work(boost::make_unique<boost::asio::io_service::work>(ioService)),
        showArguments(true),
        gtkTimer(ioService),
        installDir(installDir),
        builder(common::loadGtkBuilder(installDir / "base/widgets.glade"))
    {
        debugLogFile = boost::make_unique<cclOther::fileDebug::LogFile>("/home/robert/tmp/testDebug.log", 10, 3, 10000, false);

        providers.create_module_na(base_application);

        providers.create_module_wa(base_mainWindow,
                ioService,
                builder,
                common::createPostFun("base:mainWindow", ioService, debugLogFile.get()));

        providers.create_module_wa(base_fileChooser_open,
                impl::connection::FileChooser::Type::OPEN,
                common::createPostFun("base:fileChooser:open", ioService, debugLogFile.get()));

        providers.create_module_wa(base_fileChooser_saveAs,
                impl::connection::FileChooser::Type::SAVE,
                common::createPostFun("base:fileChooser:saveAs", ioService, debugLogFile.get()));

        providers.create_module_wa(base_appCommand_netServer,
                ioService,
                "localhost",
                "10000",
                boost::posix_time::seconds(5),
                {"localhost"},
                4096);

        providers.create_module_wa(base_appCommand_funDynExecuter,
                dynFExecuter);

        providers.create_module_na(base_appCommand_funDynXMLParser);

        providers.create_module_wa(base_appCommand_msgCreator,
                ccloCIConn::MsgReadCriteriaEnum::NLCR,
                0,
                4096);

        providers.create_module_na(base_actionExecuter);


        dataMap.insertRef("queues.event", ioService);
        dataMap.insertVal("debugLogFile", debugLogFile.get());
        dataMap.insertRef("valueStreamer", valueStreamer);
        dataMap.insertRef("dynFExecuter", dynFExecuter);
        dataMap.insertVal("installDir", installDir);


//        add_default_anyprinter(unsigned);
//        add_default_anyprinter(std::string);
//        add_default_anyprinter(boost::filesystem::path);
//        add_default_anyprinter(boost::asio::ip::tcp::endpoint);
//        add_default_anyprinter(boost::asio::ip::address);
//        add_default_anyprinter(chila::lib::misc::Path);
//        add_default_anyprinter_sptr_get(const impl::connection::MainWindow::TabId);

//        clMisc::addFunWR<ccloCIConn::Buffer>(valueStreamer, [](std::ostream &out, const ccloCIConn::Buffer &val)
//        {
//            out.write(val.first, val.second);
//        });
//
//        clMisc::addFunWR<ccloCIConn::CharVectorSCPtr>(valueStreamer, [](std::ostream &out, const ccloCIConn::CharVectorSCPtr &val)
//        {
//            boost::copy(*val, std::ostream_iterator<char>(out));
//        });

//        clMisc::addFunWR<cclOther::dynFunExecuter::ArgumentStrMap>(valueStreamer, [](std::ostream &out, const cclOther::dynFunExecuter::ArgumentStrMap &val)
//        {
//            auto first = true;
//            for (auto &vt : val)
//            {
//                if (first) first = false;
//                else out << ", ";
//
//                out << "{" << vt.first << ": " << vt.second << "}";
//            }
//        });
    }

    void App::connect(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect)
    {
        using chila::connectionTools::lib::other::funExecSequence;

        if (preLoaderConnect)
        {
            cclOther::addToMapAndLauncher(cMap, launcher, "base.application", providers.base_application->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.actionExecuter", providers.base_actionExecuter->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.mainWindow", providers.base_mainWindow->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.fileChooser.open", providers.base_fileChooser_open->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.fileChooser.saveAs", providers.base_fileChooser_saveAs->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.appCommand.netServer", providers.base_appCommand_netServer->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.appCommand.funDynExecuter", providers.base_appCommand_funDynExecuter->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.appCommand.funDynXMLParser", providers.base_appCommand_funDynXMLParser->connector);
            cclOther::addToMapAndLauncher(cMap, launcher, "base.appCommand.msgCreator", providers.base_appCommand_msgCreator->connector);

            add_to_event(providers.base_mainWindow, exitActionActivated)[&]
            {
                launcher.finish();
            });

            launcher.finishedFun = [&]
            {
                gtkTimer.cancel();
                work.reset();
            };

            impl::connection::CPerformerData::connect(AppParams(), cMap);
        }
        else
        {
//            clMisc::ThreadPool::setThreadName("event");
            CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN
            (
                ((CPModTypes::Application)(base_application))
                ((CPModTypes::ActionExecuter)(base_actionExecuter))
                ((CPModTypes::MainWindow)(base_mainWindow))
                ((CPModTypes::FileChooser)(base_fileChooser_open))
                ((CPModTypes::FileChooser)(base_fileChooser_saveAs))
                ((CPModTypes::CmdNetServer)(base_appCommand_netServer))
                ((CPModTypes::FunDynExecuter)(base_appCommand_funDynExecuter))
                ((CPModTypes::FunDynXMLParser)(base_appCommand_funDynXMLParser))
                ((CPModTypes::CmdNetTextMsgCreator)(base_appCommand_msgCreator))
                ,
                ADD_MODULE_FUN
            )

            ADD_DFF_AND_POST(providers)

//            // posted by 'postFun'
//            set_dff_post_functions(base_fileChooser_open, event, "events",
//                    (fileChosen));
//
//            set_dff_post_functions(base_fileChooser_saveAs, event, "events",
//                    (fileChosen));

//            dynFExecuter.addFunction("base.fileChooser.actions.open", providers.base_fileChooser->connector.actions.open);
        }
    }

    void App::setTimer()
    {
        gtkTimer.expires_from_now(boost::posix_time::milliseconds(1));

        gtkTimer.async_wait([&](const boost::system::error_code &ec)
        {
            if (ec) return;

            while (gtkMain.events_pending())
                gtkMain.iteration(false);

            setTimer();
        });
    }

    template <typename Provider>
    void App::addConnectorFunctions(Provider &provider)
    {
//        if (isDisabled(provider.instanceName))
//        {
//            provider.nullActions();
//        }
//        else
//        {
//            if (provider.instanceName != "loggers.logger0" && provider.instanceName != "loggers.logger1")
//            {
//                log_launcher_event(provider, starting, Starting);
//                log_launcher_event(provider, started, Started);
//                log_launcher_event(provider, deactivating, Deactivating);
//                log_launcher_event(provider, deactivated, Deactivated);
//                log_launcher_event(provider, finishing, Finishing);
//                log_launcher_event(provider, finished, Finished);
//            }

            provider.connector.events.fatalError.addFun([this, &provider](const std::string &msg)
            {
//                providers.loggers_logger0->connector.actions.fatalError(boost::posix_time::microsec_clock::local_time(), provider.instanceName, msg);
//                fatalError(provider.instanceName, msg);
//                abortApp(provider.instanceName, msg);
                std::cerr << "Fatal error: " << msg << std::endl;
                abort();
            });
//        }
    }

    void App::start()
    {
        setTimer();
        ioService.run();
    }
}
MY_NSP_END
