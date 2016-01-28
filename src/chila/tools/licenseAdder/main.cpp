#include <iostream>
#include <boost/program_options.hpp>
#include "exceptions.hpp"
#include "util.hpp"
#include <chila/lib/misc/Path.hpp>
#include <chila/lib/xmlppUtils/exceptions.hpp>
#include "Formats.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <fstream>

namespace po = boost::program_options;
namespace clMisc = chila::lib::misc;
namespace ctLAdder = chila::tools::licenseAdder;
namespace clXmlppUtils = chila::lib::xmlppUtils;
namespace bfs = boost::filesystem;
namespace bp = boost::posix_time;

CHILA_LIB_MISC__DEF_EX_DETAIL_FUN(exDetailFun, (clMisc::ExceptionInfo)(ctLAdder::ExceptionInfo))

void parseFile(
    const boost::filesystem::path &file,
    const ctLAdder::Format &format,
    const clMisc::StringVec &lines,
    const bfs::path &pPath,
    const std::string &program);

void writeNotice(
    const ctLAdder::Format &format,
    const clMisc::StringVec &lines,
    const bfs::path &pPath,
    const std::string &program);

const ctLAdder::Format &getFormat(const ctLAdder::Formats &formats, const std::string &formatStr, const bfs::path &iPath);

int main(int argc, char **argv) try
{
    namespace po = boost::program_options;

    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("file,i", po::value<std::string>(), "The input file to be processed")
        ("program,p", po::value<std::string>(), "Name of the program or library")
        ("formatsFile", po::value<std::string>(), "Formats file (default: 'formats.xml'")
        ("format,f", po::value<std::string>(), "The file format name")
        ("line,l", po::value<clMisc::StringVec>(), "Copyright line")
        ("permission,n", po::value<std::string>(), "Permission file to add/replace");

    popDesc.add("file", 1);

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cerr << "error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        return EXIT_SUCCESS;
    }

    ctLAdder::Formats formats;
    bfs::path iPath = clMisc::getProgramOption<std::string>(vm, "file");
    bfs::path pPath = clMisc::getProgramOption<std::string>(vm, "permission", "");
    auto program = clMisc::getProgramOption<std::string>(vm, "program", "");
    bfs::path formatsFile = clMisc::getProgramOption<std::string>(vm, "formatsFile", "formats.xml");
    auto formatStr = clMisc::getProgramOption<std::string>(vm, "format", "");
    auto lines = clMisc::getProgramOption<clMisc::StringVec>(vm, "line");

    formats.load(formatsFile);

    auto &format = getFormat(formats, formatStr, iPath);

    if (!bfs::is_regular_file(iPath))
    {
        BOOST_THROW_EXCEPTION(clMisc::InvalidPath() << clMisc::ExceptionInfo::FilePath(iPath));
    }

    if (bfs::file_size(iPath))
        parseFile(iPath, format, lines, pPath, program);

    return EXIT_SUCCESS;
}
CHILA_LIB_MISC__CATCH_EXCEPTIONS_MAIN
(
    (ctLAdder::ParseError)
    (clMisc::InvalidPath)
    (ctLAdder::InvalidFormatsFile)
    (ctLAdder::FormatNameIsDuplicated)
    (ctLAdder::DuplicatePattern)
    (ctLAdder::PatternNotFound)
    (clXmlppUtils::Exception),
    exDetailFun
);

const ctLAdder::Format &getFormat(const ctLAdder::Formats &formats, const std::string &formatStr, const bfs::path &iPath)
{
    if (formatStr.empty())
        return formats.fromFile(iPath);
    else
        return formats[formatStr];
}

void parseFile(
    const boost::filesystem::path &file,
    const ctLAdder::Format &format,
    const clMisc::StringVec &lines,
    const bfs::path &pPath,
    const std::string &program) try
{
    std::ifstream iFile;

    iFile.exceptions(std::ios::badbit);
    iFile.open(file.c_str());

    iFile.unsetf(std::ios::skipws);

    auto it = boost::spirit::make_default_multi_pass(ctLAdder::ISIterator(iFile)),
         end = boost::spirit::make_default_multi_pass(ctLAdder::ISIterator());

    ctLAdder::parseStream(it, end, format);

    std::cout << format.header;
    writeNotice(format, lines, pPath, program);

    std::copy(it, end, std::ostream_iterator<char>(std::cout));

    std::cout.flush();
}
catch (const ctLAdder::ParseError &ex)
{
    throw ex << clMisc::ExceptionInfo::FilePath(file);
}

void writeNotice(
    const ctLAdder::Format &format,
    const clMisc::StringVec &lines,
    const bfs::path &pPath,
    const std::string &program)
{
    auto year = bp::second_clock::local_time().date().year();

    std::cout << format.start << " 2005-" << year << " ";

    bool first = true;
    for (const auto &line : lines)
    {
        if (first)
            first = false;
        else
            std::cout << "\n" << format.lineStart;

        std::cout << line;
    }

    if (!pPath.empty())
    {
        if (!bfs::is_regular_file(pPath))
        {
            BOOST_THROW_EXCEPTION(clMisc::InvalidPath() << clMisc::ExceptionInfo::FilePath(pPath));
        }

        std::cout << "\n" << format.emptyLineStart << "\n"
                  << format.lineStart << "This file is part of '" << program << "'.\n"
                  << format.emptyLineStart;

        std::ifstream pFile;
        pFile.exceptions(std::ios::badbit);
        pFile.open(pPath.string().c_str());

        char buff[1024];
        while (pFile.good())
        {
            pFile.getline(buff, sizeof(buff));
            buff[pFile.gcount()] = 0;

            if (!pFile.gcount() && !pFile.good())
                break;

            auto line = std::string(buff);
            auto qProg = "'" + program + "'";
            boost::replace_first(line, "This program", qProg);
            boost::replace_first(line, "this program", qProg);

            std::cout << "\n" << (line.empty() ? format.emptyLineStart : format.lineStart) << line;
        }
    }

    std::cout << format.end;
}
