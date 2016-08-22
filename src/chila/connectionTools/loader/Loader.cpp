#include "Loader.hpp"
#include <boost/make_shared.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename FunType>
    FunType *Loader::loadLibrary(const boost::filesystem::path &path, const std::string &symbol)
    {
        auto dLibrary = std::make_shared<clMisc::DynamicLibrary>(path);
        my_assert(dLibrarySet.insert(dLibrary).second);

        return dLibrary->getSymbol<FunType>(symbol.c_str());
    }

    boost::filesystem::path Loader::loadInitProvider(const boost::filesystem::path &path, int &argc, char** argv)
    {
        auto initApp = loadLibrary<InitAppFun>(path,
            "_Z7initAppRiPPcRN5chila15connectionTools3lib5other7DataMapE");

        return (*initApp)(argc, argv, dataMap);
    }

    void Loader::loadConnectorsProvider(const boost::filesystem::path &path, bool preLoaderConnect)
    {
        auto loadConnectors = loadLibrary<LoadConnectorsFun>(path,
            "_Z14loadConnectorsRN5chila15connectionTools3lib7codegen12ConnectorMapERKNS1_5other7DataMapERNS5_8LauncherEb");

        (*loadConnectors)(cMap, dataMap, launcher, preLoaderConnect);
    }

    void Loader::loadRunnerAndRun( const boost::filesystem::path &path)
    {
        auto startApp = loadLibrary<StartAppFun>(path,
            "_Z16startApplicationRN5chila15connectionTools3lib7codegen12ConnectorMapE");

        launcher.start();
        (*startApp)(dataMap);
    }
}
MY_NSP_END

