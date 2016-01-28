/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#include <iostream>
//#include <chila/flow/lib/xml.hpp>
//#include <chila/flow/lib/types.hpp>
//#include <chila/flow/lib/exceptions.hpp>
//#include <chila/flow/odfGenerator/exceptions.hpp>
//#include <fstream>
//#include <libxml++/document.h>
//#include <chila/lib/xmlppUtils/util.hpp>
//#include <chila/connectionTools/lib/tree/CPerformerCreator.hpp>
//#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
//#include <boost/program_options.hpp>
//#include <libxml++/parsers/domparser.h>
//#include <libxml++/exceptions/exception.h>
//#include <chila/connectionTools/lib/tree/print.hpp>
//#include <chila/connectionTools/lib/other/CompletionScanner.hpp>
//#include <chila/connectionTools/lib/other/exceptions.hpp>
//#include <chila/lib/misc/SimplePrinter.hpp>
//#include <chila/node/Node.hpp>
//#include "chila/flow/lib/CompletionManager.hpp"
//
//#define show_error_info(Type, name) \
//    if (const Type::value_type *info = boost::get_error_info<Type>(ex)) \
//        std::cerr << "- " name ": " << *info << std::endl
//
//#define catch_ex(Type, title)                                   \
//        catch (const Type &ex)                                  \
//        {                                                       \
//            std::cerr << title << std::endl;                    \
//            show_error_info(chila::lib::misc::ExceptionInfo::XPath, "xpath");           \
//            show_error_info(chila::lib::misc::ExceptionInfo::Description, "description");           \
//            show_error_info(chila::lib::misc::ExceptionInfo::Row, "row");                           \
//            show_error_info(chila::lib::misc::ExceptionInfo::Column, "column");                     \
//            show_error_info(chila::lib::misc::ExceptionInfo::FilePath, "path");                     \
//            return EXIT_FAILURE;                                                                    \
//        }
//
//namespace po = boost::program_options;
//namespace cclTree = chila::connectionTools::lib::tree;
//
//
//const cclTree::ConnectionPerformer &readCTools(const po::variables_map &vm, cclTree::Namespace &globalNsp);
//chila::flow::lib::implAssoc::NamespacesSPtr readImplAssoc(const po::variables_map &vm);
//
//po::variables_map readOptions(int argc, char** argv);
//
//template <typename Type>
//Type readOption(const po::variables_map &vm, const std::string &name)
//{
//    // Loads the connectionPerformer file
//    if (vm.count(name))
//    {
//        return vm[name].as<Type>();
//    }
//    else
//    {
//        std::cout << "error: missing argument '" << name << "'" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//}
//
//typedef std::vector<std::string> StringVec;
//
//
//int main(int argc, char** argv) try
//{
//    int ret = EXIT_SUCCESS;
//    po::variables_map vm = readOptions(argc, argv);
//
////    cclTree::Namespace globalNsp;
////    const cclTree::ConnectionPerformer &connectionPerformer = readCTools(vm, globalNsp);
//
//    chila::flow::lib::implAssoc::NamespacesSPtr iaNamespaces = readImplAssoc(vm);
//
////    iaNamespaces->stream(std::cout);
//
//    chila::connectionTools::lib::other::CompletionScanner scanner(*iaNamespaces, readOption<std::string>(vm, "base-path"));
//    chila::flow::lib::CompletionsSPtr completions = scanner.generate();
//
//    completions->stream(std::cout);
//
//    #warning this is half-done, file generation still missing
//
//    return ret;
//}
//catch_ex(chila::lib::xmlppUtils::InvalidTagName, ex.what())
//catch_ex(chila::flow::lib::InvalidChildrenCount, ex.what())
//catch_ex(chila::lib::xmlppUtils::InvalidAttributeValue, ex.what())
//catch_ex(xmlpp::exception, ex.what())
//catch_ex(boost::filesystem::filesystem_error, ex.what())
//catch_ex(chila::connectionTools::lib::other::ParseError, ex.what())
//
//
//po::variables_map readOptions(int argc, char** argv)
//{
//    po::variables_map vm;
//    po::options_description opDesc("Allowed options");
//    po::positional_options_description popDesc;
//
//    opDesc.add_options()
//        ("help,h", "produce help message")
////        ("conn-perf,p", po::value<std::string>(), "ConnectionPerformerGenerator file")
//        ("base-path,b", po::value<std::string>(), "Base path")
//        ("impl-assoc,i", po::value<std::string>(), "cTools' implementation associations file");
//
//    try
//    {
//        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
//        po::notify(vm);
//    }
//    catch(const std::exception &ex)
//    {
//        std::cout << "error: " << ex.what() << std::endl;
//        exit(EXIT_FAILURE);
//    }
//
//    if (vm.count("help"))
//    {
//        std::cout << opDesc << std::endl;
//        exit(EXIT_FAILURE);
//    }
//
//    return vm;
//}
//
//const cclTree::ConnectionPerformer &readCTools(const po::variables_map &vm, cclTree::Namespace &globalNsp)
//{
//    typedef std::vector<boost::filesystem::path> PathVec;
//    PathVec connFiles;
//    boost::filesystem::path cpFile = readOption<std::string>(vm, "conn-perf"), oFile;
//
//    StringVec connectors = readOption<StringVec>(vm, "connector");
//    std::copy(connectors.begin(), connectors.end(), std::back_inserter(connFiles));
//
//    const cclTree::ConnectionPerformer &connectionPerformer = cclTree::CPerformerCreator(globalNsp, cpFile).create();
//    for (const auto &modPath : connFiles)
//    {
//        cclTree::ConnectorCreator(globalNsp, modPath.string()).create();
//    }
//
//    globalNsp.check();
//
//    if (vm.count("showTree"))
//    {
//        chila::lib::misc::SimplePrinter< boost::reference_wrapper<std::ostream> > printer(boost::ref(std::cout));
//
//        printer << globalNsp;
//        std::cout << std::flush;
//    }
//
//    return connectionPerformer;
//}
//
//chila::flow::lib::implAssoc::NamespacesSPtr readImplAssoc(const po::variables_map &vm)
//{
//    xmlpp::DomParser parser(readOption<std::string>(vm, "impl-assoc"));
//    xmlpp::Document &document = *parser.get_document();
//    xmlpp::Element *root = document.get_root_node();
//
//    if (root->get_name() != "implAssoc")
//    {
//        std::cerr << "Root node must be 'implAssoc'" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//
//    return chila::flow::lib::readImplAssoc(*root);
//}
