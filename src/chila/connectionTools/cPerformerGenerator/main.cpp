/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/connectionTools/lib/tree/util.hpp>

#include <chila/connectionTools/lib/tree/CPerformerCreator.hpp>
#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/print.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/xmlppUtils/exceptions.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include <chila/lib/misc/util.hpp>
#include "CodeGenerator.hpp"
#include <fstream>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/trim.hpp>
#include <boost/bind.hpp>

namespace cclTree = chila::connectionTools::lib::tree;
namespace cPerfGen = chila::connectionTools::cPerformerGenerator;
namespace po = boost::program_options;


typedef std::vector<std::string> StringVec;

typedef std::pair<boost::filesystem::path, boost::filesystem::path> PathPair;

struct CPData
{
    boost::filesystem::path input, output;
    cclTree::cPerformer::ConnectionPerformer *cPerformer;

    CPData() : cPerformer(nullptr) {}
};


typedef std::vector<CPData> CPDataVec;

CPData getCPData(const std::string &text, const char *sep = ",");
void showException(const std::exception &ex);


#define show_error_info(out, Type, name) \
        if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
            out << "- " << name << ": " << "[" << *value << "]" << std::endl;

//#define DONT_CATCH_EXCEPTIONS

int main(int argc, char** argv)
#ifndef DONT_CATCH_EXCEPTIONS
try
#endif
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("cPerformerPair,p", po::value<StringVec>(), "connectionPerformer input and output files, comma separated")
        ("connector,c", po::value<StringVec>(), "Connector file")
        ("showTree,t", "output global namespace to standard output")
        ("normalized,n", "output normalized XML to standard output");

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

    typedef std::vector<boost::filesystem::path> PathVec;
    PathVec modFiles;
    CPDataVec cpDataVec;

    // Loads the Connection Performer files
    if (vm.count("cPerformerPair"))
    {
        StringVec filesStr = vm["cPerformerPair"].as<StringVec>();

        for (const auto &p : filesStr)
        {
            cpDataVec.push_back(getCPData(p));
        }
    }
    else
    {
        std::cout << "error: no connection-performer files" << std::endl;
        return EXIT_FAILURE;
    }

    // Loads the module files
    if (vm.count("connector"))
    {
        StringVec modFilesStr = vm["connector"].as<StringVec>();
        std::copy(modFilesStr.begin(), modFilesStr.end(), std::back_inserter(modFiles));
    }
    else
    {
        std::cout << "error: no connector files" << std::endl;
        return EXIT_FAILURE;
    }

    cclTree::Namespace globalNsp;

    for (const auto &modPath : modFiles)
    {
        cclTree::ConnectorCreator(globalNsp, modPath.string()).create();
    }

    for (auto &cpData : cpDataVec)
    {
        cpData.cPerformer = &cclTree::CPerformerCreator(globalNsp, cpData.input).create();
    }

    if (vm.count("showTree"))
    {
        chila::lib::misc::SimplePrinter< boost::reference_wrapper<std::ostream> >
                printer(boost::ref(std::cout));

        printer << globalNsp;
        std::cout << std::flush;
    }

    globalNsp.check();

    for (const auto &cpData : cpDataVec)
    {
        std::ofstream file;

        file.exceptions(std::ios::badbit | std::ios::failbit);

        file.open(cpData.output.string().c_str());
        cPerfGen::CodeGenerator generator(*cpData.cPerformer, file);

        generator.generate();

//        if (vm.count("normalized"))
//        {
//            chila::connectionTools::lib::tree::sendXMLToStream(std::cout, cPerformer);
//        }
    }

    return EXIT_SUCCESS;
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
catch (const chila::lib::node::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const chila::connectionTools::lib::tree::Exception &ex)
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

    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Path, "path");
    show_error_info(std::cerr, cclTree::ErrorInfo::ReferencePath, "reference path");
    if (const auto *value = boost::get_error_info<cclTree::ErrorInfo::ReqProvVec>(ex))
    {
        std::cerr << "- arguments: " << std::endl;
        cclTree::print(std::cerr, *value, 1);
    }
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::XPath, "xml path");
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Row, "row");
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Column, "column");
}


/** Parses 'names' into 'nameVec'. */
CPData getCPData(const std::string &text, const char *sep)
{
    CPData ret;

    typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
    Tokenizer tokens(text, boost::char_separator<char>(sep));
    Tokenizer::iterator iter = tokens.begin();

    if (iter == tokens.end())
    {
        std::cerr << "invalid pair cPerformer-pair" << std::endl;
        exit(EXIT_FAILURE);
    }

    ret.input = *iter++;

    if (!boost::filesystem::exists(ret.input))
    {
        std::cerr << "file does not exists: " << ret.input << std::endl;
        exit(EXIT_FAILURE);
    }

    if (iter == tokens.end())
    {
        std::cerr << "invalid pair cPerformer-pair: '" << text << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        ret.output = *iter;
    }

    return ret;
}
