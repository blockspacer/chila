/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <fstream>
#include <chila/lib/misc/util.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/algorithm/string.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define my_assert CHILA_LIB_MISC__ASSERT

namespace po = boost::program_options;
namespace clMisc = chila::lib::misc;
namespace bi = boost::interprocess;
namespace bfs = boost::filesystem;

bfs::path file;
clMisc::StringVec prefixes, suffixes;
bool showOnError;

void replace(const bfs::path &outFile);

#define app_assert(exp, msg) \
    if (!(exp)) \
    { \
        std::stringstream str; \
        str << msg; \
        BOOST_THROW_EXCEPTION(clMisc::ApplicationError(str.str())); \
    }


int main(int argc, char **argv) try
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;
    po::variables_map vm;

    opDesc.add_options()
        ("file,f", po::value<std::string>(), "file to process")
        ("prefix,p", po::value<clMisc::StringVec>(), "define prefix to replace")
        ("suffix,s", po::value<clMisc::StringVec>(), "define siffix to replace")
        ("show-on-error,e", "show file on error")
        ("help,h", "produce help message");

    try
    {
        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        exit(EXIT_SUCCESS);
    }

    file = clMisc::getProgramOption<std::string>(vm, "file");
    prefixes = clMisc::getProgramOption<clMisc::StringVec>(vm, "prefix");
    suffixes = clMisc::getProgramOption<clMisc::StringVec>(vm, "suffix");
    showOnError = vm.count("show-on-error");

    app_assert(bfs::exists(file), file << "does not exists");
    app_assert(bfs::is_regular(file), file << " is not a regular file");

    auto outFile = file;
    outFile.replace_extension(outFile.extension().string() + "~");

    replace(outFile);

    bfs::rename(outFile, file);

    return EXIT_SUCCESS;
}
catch (const clMisc::ApplicationError &ex)
{
    if (showOnError && !file.empty())
    {
        std::cerr << "error in file " << file << ": " << ex.what() << std::endl;
    }
    else
    {
        std::cerr << "error: " << ex.what() << std::endl;
    }

    exit(EXIT_FAILURE);
}

template <typename FindIterator>
struct Finder
{
    using Iterator = std::string::const_iterator;

    CHILA_LIB_MISC__NAMED_TUPLE(RangeIters, 1,
        ((const Iterator)(begin))
        ((const Iterator)(end))
        ((Iterator)(it))
    );

    std::vector<RangeIters> rIts;
    FindIterator begin, end, init;

    Finder(const clMisc::StringVec &toFind, FindIterator init = FindIterator()) : begin(init), end(init), init(init)
    {
        for (auto &range : toFind)
        {
            rIts.push_back({range.begin(), range.end(), range.begin()});
            if (rIts.back().begin == rIts.back().end)
                BOOST_THROW_EXCEPTION(std::invalid_argument("'toFind' contains a null range"));
        }
    }

    bool operator()(const FindIterator &it)
    {
        bool matches = false;
        for (auto &rIt : rIts)
        {
            if (begin != end && *it == '\n')
            {
                if (end == init)
                {
                    begin = end;
                }
                return false;
            }
            else if (*(rIt.it) == *it)
            {
                ++rIt.it;

                if (begin == end)
                    begin = it;

                if (rIt.it == rIt.end)
                {
                    end = it + 1;
                }

                matches = true;
            }
            else
            {
                rIt.it = rIt.begin;
            }
        }

        if (!matches)
        {
            if (end != init)
            {
                return false;
            }
            else
            {
                begin = end;
            }
        }

        return true;
    }
};

using Iterator = const char*;
using Range = boost::iterator_range<Iterator>;

Range findRange(Iterator fBeg, Iterator fEnd, Finder<Iterator> &finderPreff, Finder<Iterator> &finderSuff, bool inconsistency)
{
    clMisc::find(Range(fBeg, fEnd), finderPreff);
    app_assert(finderPreff.begin != finderPreff.end, (inconsistency ? "header guard inconsistency" : "header guard not found"));
    app_assert(finderPreff.end != fEnd, "reached end of file");

    clMisc::find(Range(finderPreff.end, fEnd), finderSuff);

    app_assert(finderSuff.begin != finderSuff.end && *(finderSuff.end) == '\n', "header guard inconsistency");

    return Range(finderPreff.begin, finderSuff.end);
}

template <typename Exception, typename Fun, typename CatchFun>
auto executeAndCatch(const Fun &fun, const CatchFun &catchFun) -> decltype(fun()) try
{
    return fun();
}
catch (Exception &ex)
{
    catchFun(ex);
}

std::string getGuard()
{
    std::string ret;

    auto relPath = executeAndCatch<std::invalid_argument>([&]
    {
        return clMisc::getRelativePath(bfs::current_path(), bfs::absolute(file));
    },
    [&](std::invalid_argument &ex)
    {
        std::cerr << "invalid current path" << std::endl;
        exit(EXIT_FAILURE);
    });

    for (auto &elem : relPath.parent_path())
    {
        if (elem.string() != ".")
            ret += (ret.empty() ? "" : "_") + boost::to_upper_copy(elem.string());
    }

    ret += "__" + boost::to_upper_copy(relPath.stem().string());
    ret += "_" + boost::to_upper_copy(relPath.extension().string().substr(1));

    return ret;
}

void replace(const bfs::path &outFile)
{
    clMisc::StringVec ifndefPrefs, definePrefs;
    for (auto &prefix : prefixes)
    {
        ifndefPrefs.push_back("#ifndef " + prefix);
        definePrefs.push_back("#define " + prefix);
    }

    bi::file_mapping m_file(file.c_str(), bi::read_write);
    bi::mapped_region region(m_file, bi::read_write);

    auto fBeg  = reinterpret_cast<const char*>(region.get_address());
    auto size  = region.get_size();
    auto fEnd = fBeg + size;

    Finder<Iterator> finderPref0(ifndefPrefs, nullptr),
                     finderPref1(definePrefs, nullptr),
                     finderSuff0(suffixes, nullptr),
                     finderSuff1(suffixes, nullptr);

    Iterator begin, end;

    auto range0 = findRange(fBeg, fEnd, finderPref0, finderSuff0, false);
    auto range1 = findRange(std::end(range0) + 1, fEnd, finderPref1, finderSuff1, true);

    auto guard = getGuard();

    std::ofstream out;
    out.exceptions(std::ios::badbit);
    out.open(outFile.c_str());

    out.write(fBeg, std::begin(range0) - fBeg);
    out << "#ifndef " << guard;
    out.write(std::end(range0), std::begin(range1) - std::end(range0));
    out << "#define " << guard;
    out.write(std::end(range1), fEnd - std::end(range1));
}
