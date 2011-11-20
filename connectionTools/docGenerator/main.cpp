/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/ApplicationCreator.hpp>
#include <chila/connectionTools/lib/tree/print.hpp>
#include <boost/filesystem.hpp>
#include "ConnectorGenerator.hpp"
#include "ApplicationGenerator.hpp"
#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <chila/lib/misc/util.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
#include <fstream>
#include <chila/connectionTools/lib/other/AppFiles.hpp>
#include <chila/lib/misc/macrosDef.hpp>
#include <iostream>


namespace mtLibTree = chila::connectionTools::lib::tree;
namespace mtLibOther = chila::connectionTools::lib::other;
namespace mtBaseDocGenerator = chila::connectionTools::docGenerator;
namespace po = boost::program_options;

void showCheckErrorElement(const mtLibTree::CheckErrorElement &ex);
void showCheckErrorGroup(const mtLibTree::CheckErrorGroup &ex);

inline boost::posix_time::ptime getTimeOfPath(const boost::filesystem::path &path)
{
    return boost::posix_time::from_time_t(boost::filesystem::last_write_time(path));
}

template <typename CreateFun, typename GenerateFun>
void generateObject(const boost::filesystem::path &iFile, const boost::filesystem::path &oDir, bool force, bool verbose,
        const CreateFun &create, const GenerateFun &generate);

struct CreateConnector
{
    typedef mtLibTree::Connector& result_type;
    mtLibTree::GlobalNsp &globalNsp;

    CreateConnector(mtLibTree::GlobalNsp &globalNsp) : globalNsp(globalNsp) {}

    mtLibTree::Connector &operator()(const boost::filesystem::path &iFile) const
    {
        return mtLibTree::ConnectorCreator(globalNsp, iFile.string()).getConnector();
    }
};

struct GenerateConnector
{
    typedef void result_type;

    void operator()(const mtLibTree::Connector &connector, std::ofstream &file) const
    {
        mtBaseDocGenerator::ConnectorGenerator(connector, file).generate();
    }
};

struct CreateApplication
{
    typedef mtLibTree::Application& result_type;
    mtLibTree::GlobalNsp &globalNsp;

    CreateApplication(mtLibTree::GlobalNsp &globalNsp) : globalNsp(globalNsp) {}

    mtLibTree::Application &operator()(const boost::filesystem::path &iFile) const
    {
        return mtLibTree::ApplicationCreator(globalNsp, iFile.string()).getApplication();
    }
};

struct GenerateApplication
{
    typedef void result_type;

    const std::string title;
    const mtLibOther::AppFiles &appFiles;

    GenerateApplication(const std::string &title, const mtLibOther::AppFiles &appFiles) :
        title(title), appFiles(appFiles) {}

    void operator()(const mtLibTree::Application &connector, std::ofstream &file) const
    {
        mtLibOther::AppFiles::FileVec connFiles = appFiles.getConnectorFiles();

        BOOST_FOREACH(boost::filesystem::path &file, connFiles)
        {
            file.replace_extension("docbook.xml");
            file = file.filename();
        }

        mtBaseDocGenerator::ApplicationGenerator(connector, file, title, connFiles).generate();
    }
};

int main(int argc, char** argv) try
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;
    bool force = false, verbose = false;
    std::string title;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("input,i", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output directory")
        ("title,t", po::value<std::string>(), "title of the document")
        ("force,f", po::value<std::string>(), "force creation (normaly only creates if source is newer)")
        ("verbose,v", po::value<std::string>(), "verbose mode");

//        ("showTree,t", "show namespace tree");

    popDesc.add("input", -1);

    po::variables_map vm;
    try
    {
//        const std::string dir =
//            "/home/robert/Documents/Private/nucleo/TASACION/FuentesSolaris/"
//            "src/chila/smsSender/modules/app/connectors";
        const std::string dir =
            "/home/gimenero/fuentes/TASACION/FuentesSolaris/"
            "src/chila/smsSender/modules/app/connectors";

        const std::vector<std::string> args = boost::assign::list_of
            (std::string("-i"))(dir + "/src/AppFiles.xml")
            (std::string("-o"))(dir + "/doc")
            (std::string("-t"))("smsSender")
            (std::string("-f"))("")
            (std::string("-v"))("");

        po::store(po::command_line_parser(args).options(opDesc).positional(popDesc).run(), vm);

//        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception &ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        return 1;
    }

    if (vm.count("force")) force = true;
    if (vm.count("verbose")) verbose = true;

//    #warning sacar
//    verbose = true;
//    force = true;

    if (vm.count("help"))
    {
        std::cout << opDesc << std::endl;
        return 1;
    }

    boost::filesystem::path iAppFile, oDir;

    // Loads the input file
    if (vm.count("input"))
        iAppFile = vm["input"].as<std::string>();
    else
    {
        std::cout << "error: no input file" << std::endl;
        return EXIT_FAILURE;
    }

    // Loads the output file
    if (vm.count("output"))
        oDir = vm["output"].as<std::string>();
    else
    {
        std::cout << "error: no output file" << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("title"))
    {
        title = vm["title"].as<std::string>();
    }
    else
    {
        std::cerr << "a title must be provided" << std::endl;
        return EXIT_FAILURE;
    }

    mtLibOther::AppFiles appFiles(iAppFile);

    mtLibTree::GlobalNsp globalNsp;

    // Loads the connectors to the global namespace and generates their documentation
    const mtLibOther::AppFiles::FileVec &vec = appFiles.getConnectorFiles();
    BOOST_FOREACH(const boost::filesystem::path &iFile, vec)
    {
        generateObject(iFile, oDir, force, verbose, CreateConnector(globalNsp), GenerateConnector());
    }

    generateObject(appFiles.getAppFile(), oDir, force, verbose, CreateApplication(globalNsp),
            GenerateApplication(title, appFiles));

    return 0;
}
catch (const chila::lib::misc::TiXmlError &ex)
{
    std::cerr << std::endl << "error opening input: " << ex.what() << ".\n" << std::endl;
    return EXIT_FAILURE;
}
catch (const mtLibTree::ConnectorCreationError &ex)
{
    std::cerr << std::endl << "error reading input: " << ex.what() << ".\n" << std::endl;
    return EXIT_FAILURE;
}
catch (const mtLibTree::CheckErrorElement &ex)
{
    std::cerr << "\nerror en Connector object: \n";
    showCheckErrorElement(ex);
    return EXIT_FAILURE;
}
catch (const mtLibTree::CheckErrorGroup &ex)
{
    std::cerr << "\nerror en Connector object: \n";
    showCheckErrorGroup(ex);
    return EXIT_FAILURE;
}

void showCheckErrorElement(const mtLibTree::CheckErrorElement &ex)
{
    std::cerr << "- " << ex.getPath().getStringRep() << ": " << ex.getError() << std::endl;
}

void showCheckErrorGroup(const mtLibTree::CheckErrorGroup &ex)
{
    BOOST_FOREACH(const mtLibTree::CheckErrorSCPtr &cError, ex.getErrors())
    {
        if (const mtLibTree::CheckErrorElementSCPtr &error =
                boost::dynamic_pointer_cast<const mtLibTree::CheckErrorElement>(cError))
        {
            showCheckErrorElement(*error);
        }
        else if (const mtLibTree::CheckErrorGroupSCPtr &error =
                boost::dynamic_pointer_cast<const mtLibTree::CheckErrorGroup>(cError))
        {
            showCheckErrorGroup(*error);
        }
        else abort();
    }
}

template <typename CreateFun, typename GenerateFun>
void generateObject(const boost::filesystem::path &iFile, const boost::filesystem::path &oDir, bool force, bool verbose,
        const CreateFun &create, const GenerateFun &generate)
{
    boost::filesystem::path oFile = oDir / iFile.filename();
    oFile.replace_extension("docbook.xml");

    const typename CreateFun::result_type object = create(iFile.string());
    object.check();

    if (!force && boost::filesystem::exists(oFile) && getTimeOfPath(iFile) <= getTimeOfPath(oFile))
        return;

    if (verbose)
        std::cout << oFile << std::endl;

    std::ofstream file;
    file.exceptions(std::ios::badbit | std::ios::failbit);

    file.open(oFile.string().c_str());
    generate(object, file);
}

