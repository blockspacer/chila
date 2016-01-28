/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__CPERFORMERDATA_HPP

#include "../../connectors/gen/ConnectionPerformer.hpp"
#include <chila/lib/misc/Construct.hpp>
#include "Logger.hpp"
#include "MainWindow.hpp"
#include "FileLoader.hpp"
#include "argProviders.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct CPerformerData
    {
        struct Connectors
        {
            using Logger = connection::Logger::Connector;
            using MainWindow = connection::MainWindow::Connector;
            using FileLoader = connection::FileLoader::Connector;

            MainWindow &mainWindow;
            FileLoader &fileLoader;
            Logger &logger;

            Connectors
            (
                connection::Logger::Connector &logger,
                connection::FileLoader::Connector &fileLoader,
                connection::MainWindow::Connector &mainWindow
            ) :
                logger(logger),
                fileLoader(fileLoader),
                mainWindow(mainWindow)
            {}
        };

        struct AliasTypes
        {
            using moduleName        = std::string;
            using filePath          = boost::filesystem::path;
            using nodePath          = chila::lib::misc::Path;
            using treeNodePath      = chila::lib::misc::Path;
            using nodeId            = std::string;
            using value             = std::string;
            using cToolsPath        = chila::lib::misc::Path;
            using action            = lib::ActionSCPtr;
            using actionList        = lib::ActionMapSCPtr;
            using errorText         = std::string;
            using outputText        = std::string;
            using position          = unsigned;
            using nodePathPair      = NodePathPair;
            using openNode          = bool;
            using isExpandable      = bool;
            using textProperties    = lib::TextPropertiesSPtr;
        };

        using ConnectionPerformer = app::connectors::gen::ConnectionPerformer<AliasTypes, Connectors>;

        struct AppArgs
        {
            chila::connectionTools::lib::codegen::ConnectorMap &cMap;

            struct Providers
            {
                ModuleNameProviderCreator<ConnectionPerformer::ArgAliases> fileLoaderNameProv, mainWindowNameProv;

                Providers() :
                        fileLoaderNameProv("fileLoader"), mainWindowNameProv("MainWindow") {}

            } providers;

            AppArgs(chila::connectionTools::lib::codegen::ConnectorMap &cMap) : cMap(cMap) {}
        };

        static void connect(chila::connectionTools::lib::codegen::ConnectorMap &cMap)
        {
            AppArgs args(cMap);
            ConnectionPerformer::connect(args);
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
