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

#include <chila/connectionTools/lib/tree/ApplicationCreator.hpp>
#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
#include <chila/connectionTools/lib/tree/print.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <chila/connectionTools/lib/tree/FunctionConnection.hpp>
#include <chila/lib/misc/util.hpp>
#include "CodeGenerator.hpp"
#include <fstream>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/trim.hpp>
#include <boost/bind.hpp>

typedef std::vector<std::string> StringVec;

StringVec getIdVec(const std::string &text, const char *sep = ",");

namespace mtLibTree = chila::connectionTools::lib::tree;
namespace conGen = chila::connectionTools::connectionsGenerator;
namespace po = boost::program_options;

//#define PATH_PREFIX "/home/robert/Documents/Private/nucleo/TASACION/FuentesSolaris/src/chila"
#define PATH_PREFIX "/home/gimenero/fuentes/TASACION/FuentesSolaris/src/chila"


int main(int argc, char** argv) try
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("app,a", po::value<std::string>(), "application file")
        ("connectors,c", po::value<std::string>(), "comma separated connector files")
        ("output,o", po::value<std::string>(), "output file")
        ("showTree,t", "show global namespace tree");

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
    boost::filesystem::path appFile, oFile;

    // Loads the application file
    if (vm.count("app"))
    {
        appFile = vm["app"].as<std::string>();
    }
    else
    {
        std::cout << "error: no application file" << std::endl;
        return EXIT_FAILURE;
    }

    // Loads the module files
    if (vm.count("connectors"))
    {
        StringVec modFilesStr = getIdVec(vm["connectors"].as<std::string>());
        std::copy(modFilesStr.begin(), modFilesStr.end(), std::back_inserter(modFiles));
    }
    else
    {
        std::cout << "error: no connector files" << std::endl;
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

    mtLibTree::GlobalNsp globalNsp;

    BOOST_FOREACH(const boost::filesystem::path &modPath, modFiles)
    {
        mtLibTree::ConnectorCreator(globalNsp, modPath.string());
    }

    mtLibTree::Application &app = mtLibTree::ApplicationCreator(globalNsp, appFile).getApplication();

    if (vm.count("showTree"))
    {
        chila::lib::misc::SimplePrinter< boost::reference_wrapper<std::ostream> >
                printer(boost::ref(std::cout));

        printer << globalNsp;
        std::cout << std::flush;
    }

    app.check();


    std::ofstream file;

    file.exceptions(std::ios::badbit | std::ios::failbit);

    file.open(oFile.string().c_str());
    conGen::CodeGenerator generator(app, file);

    generator.generate();


    return EXIT_SUCCESS;
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
catch (const mtLibTree::CheckError &ex)
{
    std::cerr << "\nerror en Application object: \n";
    ex.write(std::cerr) << std::flush;
    return EXIT_FAILURE;
}


/** Parses 'names' into 'nameVec'. */
StringVec getIdVec(const std::string &text, const char *sep)
{
    StringVec ids;
    typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
    Tokenizer tokens(text, boost::char_separator<char>(sep));
    for (Tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        std::string name = *iter;
        boost::trim(name);
        ids.push_back(name);
    }

    return ids;
}
