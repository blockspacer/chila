/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LOADER__LOADER_HPP
#define CHILA_CONNECTIONTOOLS_LOADER__LOADER_HPP

#include <chila/lib/misc/fwd.hpp>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <chila/lib/misc/DynamicLibrary.hpp>
#include <chila/connectionTools/lib/other/DataMap.hpp>
#include "chila/connectionTools/lib/other/Launcher.hpp"
#include "fwd.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    class Loader
    {
        public:
            boost::filesystem::path loadInitProvider(const boost::filesystem::path &path, int &argc, char** argv);
            void loadConnectorsProvider(const boost::filesystem::path &path, bool preLoaderConnect);
            void loadRunnerAndRun(const boost::filesystem::path &path);
            void connectLauncher() { launcher.connect(); }

        private:
            using Launcher = cclOther::Launcher;

            using DLibrarySet = std::set<clMisc::DynamicLibrarySPtr>;
            using InitAppFun = boost::filesystem::path(int &argc, char** argv, cclOther::DataMap &dataMap);
            using LoadConnectorsFun = void(ConnectorMap &cMap, const cclOther::DataMap &dataMap, cclOther::Launcher &launcher, bool preLoaderConnect);
            using StartAppFun = void(const cclOther::DataMap &dataMap);

            DLibrarySet dLibrarySet;

            ConnectorMap cMap;
            cclOther::DataMap dataMap;
            cclOther::Launcher launcher;

            template <typename FunType>
            FunType *loadLibrary(const boost::filesystem::path &path, const std::string &symbol);
    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif
