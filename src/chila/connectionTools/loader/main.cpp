/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <iostream>
#include <chila/lib/misc/util.hpp>
#include "Loader.hpp"
#include <chila/lib/xmlppUtils/util.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/node/exceptions.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <chila/connectionTools/lib/codegen/exceptions.hpp>
#include "exceptions.hpp"
#include <chila/lib/misc/ValueStreamer.hpp>

namespace clMisc = chila::lib::misc;
namespace ccLoader = chila::connectionTools::loader;
namespace xmlppUtils = chila::lib::xmlppUtils;
namespace bfs = boost::filesystem;

using PathStrVec = std::vector<std::string>;

bfs::path loaderConfig;
ccLoader::Loader loader;

void load();
void showException(const std::exception &ex);

struct A : public clMisc::ValueStreamer::Streamable
{
    void stream(std::ostream &out) const
    {
        std::cout << "A" << std::endl;
    }
};

int main(int argc, char** argv) try
{
    if (argc < 2)
    {
        std::cerr << "usage: loader <providerLibName> <options>" << std::endl;
        exit(EXIT_FAILURE);
    }

    loaderConfig = loader.loadInitProvider("lib" + std::string(argv[1]) + ".so", argc, argv);

    load();

    return EXIT_SUCCESS;
}
catch (const chila::lib::node::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const chila::lib::xmlppUtils::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const clMisc::DynamicLibrarySymbolError &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const clMisc::ApplicationError &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const chila::connectionTools::lib::codegen::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const clMisc::DynamicLibraryError &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const xmlpp::exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}

//catch (const std::exception &ex)
//{
//    std::cout << boost::diagnostic_information(ex) << std::endl;
//    return EXIT_FAILURE;
//}

inline std::string getLibName(const std::string &name)
{
    return "lib" + name + ".so";
}

void loadProviders(const xmlpp::Element &root, const std::string &groupElemName, bool preLoaderConnect)
{
    auto &groupElem = xmlppUtils::getUniqueChildElement(root, groupElemName);
    xmlppUtils::iterateChildren(groupElem, "provider", [&](const xmlpp::Element &provElem)
    {
        auto name = xmlppUtils::getAttribute<std::string>(provElem, "name");
        loader.loadConnectorsProvider(getLibName(name), preLoaderConnect);
    });
}

void load()
{
    xmlpp::DomParser loaderParser(loaderConfig.c_str());
    const auto &loaderDoc = *loaderParser.get_document();
    auto loaderRoot = clMisc::checkNotNull(loaderDoc.get_root_node());

    if (!loaderRoot || loaderRoot->get_name() != "ccLoaderConfig")
    {
        xmlppUtils::throwException(chila::lib::xmlppUtils::InvalidTagName(), *loaderRoot);
    }

    auto runner = xmlppUtils::getAttribute<std::string>(*loaderRoot, "runner");

    loadProviders(*loaderRoot, "preLoaderConnect", true);

    loader.connectLauncher();

    loadProviders(*loaderRoot, "posLoaderConnect", false);

    loader.loadRunnerAndRun(getLibName(runner));
}

void showException(const std::exception &ex)
{
    std::cerr << "error: " << ex.what() << std::endl;

    clMisc::showErrorInfo<chila::lib::misc::ExceptionInfo::XPath>(std::cerr, ex, "xml path");
    clMisc::showErrorInfo<chila::lib::misc::ExceptionInfo::Row>(std::cerr, ex, "row");
    clMisc::showErrorInfo<chila::lib::misc::ExceptionInfo::Column>(std::cerr, ex, "column");
    clMisc::showErrorInfo<chila::lib::misc::ExceptionInfo::Path>(std::cerr, ex, "path");
}
