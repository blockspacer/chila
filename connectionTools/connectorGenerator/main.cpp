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
#include <chila/connectionTools/lib/tree/print.hpp>
#include <boost/filesystem.hpp>
#include "CodeGenerator.hpp"
#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <chila/lib/misc/util.hpp>
#include <fstream>
#include <chila/lib/misc/macrosDef.hpp>


namespace mtLibTree = chila::connectionTools::lib::tree;
namespace mtBaseConnectorCreator = chila::connectionTools::baseConnectorCreator;
namespace po = boost::program_options;

void showCheckErrorElement(const mtLibTree::CheckErrorElement &ex);
void showCheckErrorGroup(const mtLibTree::CheckErrorGroup &ex);

#include <iostream>

int main(int argc, char** argv) try
{
    po::options_description opDesc("Allowed options");
    po::positional_options_description popDesc;

    opDesc.add_options()
        ("help,h", "produce help message")
        ("input,i", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output file")
        ("showTree,t", "show connector tree");

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

//#define FUENTES_HOME "/home/gimenero/fuentes"
//#define FUENTES_HOME "/home/robert/Documents/Private/nucleo"
//
//    boost::filesystem::path
//        iFile = FUENTES_HOME "/TASACION/FuentesSolaris/src/chila/connectionTools/appTest/app/Network.xml",
//        oFile = FUENTES_HOME "/TASACION/FuentesSolaris/src/chila/connectionTools/appTest/app/NetworkConnectorConnector.hpp";


    mtLibTree::GlobalNsp globalNsp;

    mtLibTree::ConnectorCreator creator(globalNsp, iFile.string());

    mtLibTree::Connector &connector = creator.getConnector();

    connector.check();


    std::cout << connector.getPath().getStringRep() << std::endl;

    std::ofstream file;

    file.exceptions(std::ios::badbit | std::ios::failbit);

    file.open(oFile.string().c_str());
    if (vm.count("showTree"))
    {
        chila::lib::misc::SimplePrinter< boost::reference_wrapper<std::ostream> >
                printer(boost::ref(std::cout));

        printer << globalNsp;
    }

    mtBaseConnectorCreator::CodeGenerator generator(connector, file);

    generator.generate();

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




