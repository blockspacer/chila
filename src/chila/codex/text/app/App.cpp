/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "App.hpp"
#include "chila/connectionTools/lib/other/Launcher.hpp"
#include <boost/filesystem.hpp>
#include "impl/connection/CPerformerData.hpp"
#include <chila/connectionTools/lib/other/DataMap.hpp>
#include "chila/connectionTools/lib/other/util.hpp"
#include "chila/connectionTools/lib/other/AddDebugFileFun.hpp"
#include <chila/connectionTools/lib/other/fileDebug/LogFile.hpp>
#include <chila/connectionTools/lib/other/dynFunExecuter/ExecuterMap.hpp>
#include <chila/connectionTools/lib/other/dynFunExecuter/util.hpp>
#include "../lib/types.hpp"
#include "../../common/DFFPostFun.hpp"
#include <boost/algorithm/string.hpp>
#include "../../common/util.hpp"
#include <chila/lib/xmlppUtils/util.hpp>

#include "macros.fgen.hpp"

#define ADD_MODULE_FUN(module) \
    addConnectorFunctions(*(providers.module));

#define add_to_map_and_launcher(name) \
        cclOther::addToMapAndLauncher(cMap, launcher, clMisc::Path(#name, "_").getStringRep(), providers.name->connector)

MY_NSP_START
{
    App::App() :
        showArguments(true)
    {
    }

    void App::connect(ccLoader::ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect) try
    {
        auto &ioService = dataMap.getRef<boost::asio::io_service>("queues.event");
        auto debugLogFile = dataMap.getVal<cclOther::fileDebug::LogFile*>("debugLogFile");
        auto &valueStreamer = dataMap.getRef<clMisc::ValueStreamer>("valueStreamer");
        auto &dynFExecuter = dataMap.getRef<cclOther::dynFunExecuter::ExecuterMap>("dynFExecuter");
        auto &qEngine = dataMap.getRef<QQmlApplicationEngine>("qEngine");
        installDir = dataMap.getVal<bfs::path>("installDir");

//        builder = common::loadGtkBuilder(installDir / "text/widgets.glade");

        if (preLoaderConnect)
        {
            valueStreamer.addFun<impl::connection::BufferRange>([&](std::ostream &out, const impl::connection::BufferRange &range)
            {
                static const unsigned maxSize = 20;

                out << "value='";

                for (auto i = 0; i < range.size() && i < maxSize; ++i)
                {
                    auto c = *(range.begin() + i);

                    switch (c)
                    {
                        case '\n': case '\r': out << ' '; break;
                        default: out << c;
                    }
                }

                out << (range.size() > maxSize ? " ...'" : "'") << ", size=" << range.size();
            });

            // Module creation ---------------------------------------------------------
            auto createFileId = [] { return std::make_shared<impl::connection::FileId>(); };

            providers.create_module_na(text_actionExecuter);

            providers.create_module_wa(text_textEditor,
                qEngine,
                createFileId);

            providers.create_module_wa(text_textHighlighter,
                loadHighlightColors());

            providers.create_module_wa(text_fileOpener,
                loadExtensionFTypeMap(),
                createFileId);

            providers.create_module_wa(text_findReplace,
//                builder,
                common::createPostFun("text:findReplace", ioService, debugLogFile));
            // ----------------------------------------------------------------------------

            add_to_map_and_launcher(text_actionExecuter);
            add_to_map_and_launcher(text_textEditor);
            add_to_map_and_launcher(text_textHighlighter);
            add_to_map_and_launcher(text_fileOpener);
            add_to_map_and_launcher(text_findReplace);

            impl::connection::CPerformerData::connect(AppParams(), cMap);
        }
        else
        {
            CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN(
                ((TextActionExeucter)(text_actionExecuter))
                ((TextEditor)(text_textEditor))
                ((TextHighlighter)(text_textHighlighter))
                ((FileOpener)(text_fileOpener))
                ((FindReplace)(text_findReplace)),
                ADD_MODULE_FUN)

            ADD_DFF_AND_POST(providers)

//            // posted by 'postFun'
//            set_dff_post_functions(text_textEditor, event, "events",
//                    (contentsAreOriginal)
//                    (contentsModified)
//                    (parseText));
//
//            set_post_function(text_textEditor, action, openingDone, ioService, "events");
//            set_post_function(text_textEditor, action, savingDone, ioService, "events");



//                std::stringstream str;
//                str << "<function path='" << providers.text_textEditor->connector.actions.openFile.path() << "'>"
//                    << "<arg name='fileName'>/home/robert/data/ocsGprs/server/log/valgrind.log</arg>"
//                    << "</function>";

//            CHILA_LIB_MISC__SHOW(40, str.str());

//            dynFExecuter.addFunction("text.fileOpener.actions.openFile", providers.text_fileOpener->connector.actions.openFile);


        }
    }
    catch (const cclOther::DataMapElementNotFound &ex)
    {
        auto &srcType = clMisc::deref(boost::get_error_info<cclOther::ErrorInfo::SourceType>(ex));
        auto &destType = clMisc::deref(boost::get_error_info<cclOther::ErrorInfo::DestType>(ex));
        auto &name = clMisc::deref(boost::get_error_info<cclOther::ErrorInfo::DataMapValueName>(ex));

        throw clMisc::ApplicationError("Error getting '" + name + "' from data-map, could not cast '" + srcType + "' to '" + destType + "'");
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
    }

    lib::ColorMap App::loadHighlightColors()
    {
        lib::ColorMap colors;

        xmlpp::DomParser parser((installDir / "text/cnf/highlight.xml").string());
        auto &document = *parser.get_document();
        auto root = clMisc::checkNotNull(document.get_root_node());

        app_assert(root && root->get_name() == std::string("highlight"), "no root or invalid name, must be 'highlight'");

        xmlppUtils::iterateChildren(*root, "element", [&](const xmlpp::Element &child)
        {
            auto name = xmlppUtils::getAttribute<std::string>(child, "name");
            auto red = xmlppUtils::getAttribute<float>(child, "red");
            auto green = xmlppUtils::getAttribute<float>(child, "green");
            auto blue = xmlppUtils::getAttribute<float>(child, "blue");

            auto ret = colors.insert({name, lib::Color(red / 100, green / 100, blue / 100)});
            if (!ret.second)
                xmlppUtils::throwInvalidAttributeValue("color already inserted", child);
        });

        return colors;
    }

    lib::ExtensionFTypeMap App::loadExtensionFTypeMap()
    {
        lib::ExtensionFTypeMap ret;

        xmlpp::DomParser parser((installDir / "text/cnf/fileTypes.xml").string());
        auto &document = *parser.get_document();
        auto root = clMisc::checkNotNull(document.get_root_node());

        app_assert(root && root->get_name() == std::string("fileTypes"), "no root or invalid name, must be 'fileTypes'");

        xmlppUtils::iterateChildren(*root, "type", [&](const xmlpp::Element &child)
        {
            auto name = xmlppUtils::getAttribute<std::string>(child, "name");
            auto extensions = xmlppUtils::getAttribute<std::string>(child, "extensions");

            clMisc::tokenize(extensions, ",", [&](std::string ext)
            {
                boost::trim(ext);
                auto insRet = ret.insert({ext, name});

                if (!insRet.second)
                    xmlppUtils::throwInvalidAttributeValue("extension '" + ext + "' already inserted", child);
            });
        });

        return ret;
    }
}
MY_NSP_END
