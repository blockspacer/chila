/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__MAINWINDOW_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__MAINWINDOW_HPP

#include "fwd.hpp"
#include "../../connectors/gen/MainWindow.hpp"
#include <chila/lib/misc/Path.hpp>
#include <boost/asio/io_service.hpp>
#include "../../../lib/actions.hpp"
#include "../../../lib/ActionMap.hpp"
#include "../fwd.hpp"

#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct MainWindow
    {
        struct ArgTypes
        {
            using moduleName        = std::string;
            using nodePath          = chila::lib::misc::Path;
            using treeNodePath      = chila::lib::misc::Path;
            using nodeId            = std::string;
            using value             = std::string;
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

        using Connector = connectors::gen::MainWindow<ArgTypes>;

        struct CProvider: public connection::CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create(boost::asio::io_service &ioService, const boost::filesystem::path &gladeFile,
            bool showFunEvents);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_SPTR

#endif
