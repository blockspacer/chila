/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "app/Main.hpp"
#include <vector>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/xmlppUtils/exceptions.hpp>
#include <chila/lib/node/exceptions.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <iostream>

using namespace chila::connectionTools::designer;

using StringVec = std::vector<std::string>;
using ClmPathVec = std::vector<chila::lib::misc::Path>;

namespace cclTree = chila::connectionTools::lib::tree;
namespace po = boost::program_options;

void showException(const std::exception &ex);

#define show_error_info(out, Type, name, extended) \
        if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
            out << "- " << name << ": " << (extended ? "\n" : "[") << *value << (extended ? "" : "]\n") << std::flush;

int main(int argc, char** argv) try
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("project,p", po::value<std::string>(), "project file")
        ("verbose,v", "verbose functions and events")
        ("help,h", "produce help message");

    const char *designerHome = getenv("DESIGNER_HOME");

    if (!designerHome)
    {
        std::cerr << "environment variable DESIGNER_HOME not set." << std::endl;
        return EXIT_FAILURE;
    }
    else if (!boost::filesystem::is_directory(designerHome))
    {
        std::cerr << "'" << designerHome << "' is not a directory." << std::endl;
        return EXIT_FAILURE;
    }

    boost::filesystem::path gladeFile(designerHome + std::string("/mainWindow-v2.glade"));
    // (on cygwin boost::filesystem does not work correctly, that's why there's no checking here)

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        return EXIT_SUCCESS;
    }


    boost::filesystem::path project;


    // Loads the Connection Performer files
    if (vm.count("project"))
    {
        project = vm["project"].as<std::string>();
    }
    else
    {
        std::cout << "error: no project file" << std::endl;
        return EXIT_FAILURE;
    }

    boost::asio::io_service ioService;

    xmlpp::DomParser parser(project.string());
    const xmlpp::Document &document = *parser.get_document();
    const xmlpp::Element &rootElem = chila::lib::misc::deref(document.get_root_node());

    chila::lib::misc::XMLAccessor projectAccessor(rootElem);

    app::Main main(ioService, projectAccessor, designerHome, vm.count("verbose"));
    main.start();

    ioService.run();

    return EXIT_SUCCESS;
}
catch (const chila::lib::node::CheckExceptionList &ex)
{
    for (const auto &item : ex.exceptions)
    {
        showException(*item);
        std::cerr << std::endl;
    }
    return EXIT_FAILURE;
}
catch (const chila::connectionTools::lib::tree::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
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
//catch (const std::bad_cast &ex)
//{
//    showException(ex);
//    return EXIT_FAILURE;
//}
//catch (const std::exception &ex)
//{
//    std::cout << boost::diagnostic_information(ex) << std::endl;
//    return EXIT_FAILURE;
//}

void showException(const std::exception &ex)
{
    std::cerr << ex.what() << std::endl;

    show_error_info(std::cerr, cclTree::ErrorInfo::ReferencePath, "reference path", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::XPath, "xml path", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Row, "row", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Column, "column", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Path, "path", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::TypeFrom, "from", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::TypeTo, "to", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::ActualType, "actual", false);
    show_error_info(std::cerr, boost::throw_function, "function", false);
    show_error_info(std::cerr, boost::throw_file, "file", false);
    show_error_info(std::cerr, boost::throw_line, "line", false);
}
