/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__FILELOADER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL_CONNECTION__FILELOADER_HPP

#include "fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include "../../connectors/gen/FileLoader.hpp"
#include <boost/asio/io_service.hpp>
#include "../fwd.hpp"
#include "../../../lib/ActionMap.hpp"
#include "../../../lib/actions.hpp"
#include <boost/filesystem/path.hpp>

#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct FileLoader
    {
        struct ArgTypes
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

        using Connector = connectors::gen::FileLoader<ArgTypes>;

        struct CProvider: public connection::CProvider
        {
            virtual Connector &getConnector() = 0;
        };

        FWDEC_SPTR(CProvider);

        static CProviderSPtr create(
            boost::asio::io_service &ioService,
            const ClmPathVec &flowCInstances,
            const ClmPathSet &flowCInstancesDim,
            bool showFunEvents);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_SPTR

#endif
