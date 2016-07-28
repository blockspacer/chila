/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/connectionTools/lib/tree/util.hpp>

#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include <chila/connectionTools/lib/tree/print.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/xmlppUtils/exceptions.hpp>
#include "CodeGenerator.hpp"
#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <chila/lib/misc/util.hpp>
#include <fstream>
#include <chila/lib/misc/macrosExp.hpp>
#include <iostream>

#define show_error_info(out, Type, name, extended) \
        if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
            out << "- " << name << ": " << (extended ? "\n" : "[") << *value << (extended ? "" : "]\n") << std::flush;


namespace cclTree = chila::connectionTools::lib::tree;
namespace po = boost::program_options;

void showException(const std::exception &ex);


int main(int argc, char** argv)
#ifndef DONT_CATCH_EXCEPTIONS
try
#endif
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("input,i", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output file")
        ("showTree,t", "output global namespace to standard output")
        ("normalized,n", "output normalized XML to standard output");


    popDesc.add("input", -1);

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        return 1;
    }

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        return 1;
    }

    boost::filesystem::path iFile, oFile;

    // Loads the input file
    if (vm.count("input"))
    {
        iFile = vm["input"].as<std::string>();
    }
    else
    {
        std::cout << "error: no input file" << std::endl;
        return EXIT_FAILURE;
    }

    // Loads the output file
    if (vm.count("output"))
        oFile = vm["output"].as<std::string>();
    else
    {
        std::cout << "error: no output file" << std::endl;
        return EXIT_FAILURE;
    }

    cclTree::Namespace globalNsp;

    cclTree::ConnectorCreator creator(globalNsp, iFile.string());

    auto &connector = creator.create();

    connector.check();

    std::ofstream file;

    file.exceptions(std::ios::badbit | std::ios::failbit);

    file.open(oFile.string().c_str());
    if (vm.count("showTree"))
    {
        chila::lib::misc::SimplePrinter< boost::reference_wrapper<std::ostream> >
                printer(boost::ref(std::cout));

        printer << globalNsp;
    }

    chila::connectionTools::connectorGenerator::CodeGenerator generator(connector, file);

    generator.generate();

    if (vm.count("normalized"))
    {
//        chila::connectionTools::lib::tree::sendXMLToStream(std::cout, connector);
    }

    return 0;
}
#ifndef DONT_CATCH_EXCEPTIONS
catch (const xmlpp::exception &ex)
{
    std::cerr << "error opening input: " << ex.what() << "." << std::endl;
    return EXIT_FAILURE;
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
#endif


void showException(const std::exception &ex)
{
    std::cerr << ex.what() << std::endl;

//    show_error_info(std::cerr, cclTree::ErrorInfo::CInstance, "connection instance", false);
    show_error_info(std::cerr, cclTree::ErrorInfo::ReferencePath, "reference path", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::XPath, "xml path", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Row, "row", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Column, "column", false);
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Path, "path", false);
}
