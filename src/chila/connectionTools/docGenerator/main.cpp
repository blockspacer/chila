/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#include <chila/connectionTools/lib/tree/ConnectorCreator.hpp>
//#include <chila/connectionTools/lib/tree/CPerformerCreator.hpp>
//#include <chila/connectionTools/lib/tree/print.hpp>
//#include <boost/filesystem.hpp>
//#include "ConnectorGenerator.hpp"
//#include "CPerformerGenerator.hpp"
//#include <boost/make_shared.hpp>
//#include <boost/program_options.hpp>
//#include <chila/lib/misc/util.hpp>
//#include <boost/assign/list_of.hpp>
//#include <boost/date_time/posix_time/posix_time_types.hpp>
//#include <boost/date_time/posix_time/conversion.hpp>
//#include <fstream>
//#include <chila/connectionTools/lib/other/CPerformerFiles.hpp>
//#include <chila/lib/misc/macrosExp.hpp>
//#include <iostream>
//
//
//namespace cclTree = chila::connectionTools::lib::tree;
//namespace mtLibOther = chila::connectionTools::lib::other;
//namespace mtBaseDocGenerator = chila::connectionTools::docGenerator;
//namespace po = boost::program_options;
//
//void showCheckErrorElement(const cclTree::CheckErrorElement &ex);
//void showCheckErrorGroup(const cclTree::CheckErrorGroup &ex);
//
//inline boost::posix_time::ptime getTimeOfPath(const boost::filesystem::path &path)
//{
//    return boost::posix_time::from_time_t(boost::filesystem::last_write_time(path));
//}
//
//template <typename CreateFun, typename GenerateFun>
//void generateObject(const boost::filesystem::path &iFile, const boost::filesystem::path &oDir, bool force, bool verbose,
//        const CreateFun &create, const GenerateFun &generate);
//
//struct CreateConnector
//{
//    typedef cclTree::Connector& result_type;
//    cclTree::GlobalNsp &globalNsp;
//
//    CreateConnector(cclTree::GlobalNsp &globalNsp) : globalNsp(globalNsp) {}
//
//    cclTree::Connector &operator()(const boost::filesystem::path &iFile) const
//    {
//        return cclTree::ConnectorCreator(globalNsp, iFile.string()).getConnector();
//    }
//};
//
//struct GenerateConnector
//{
//    typedef void result_type;
//
//    void operator()(const cclTree::Connector &connector, std::ofstream &file) const
//    {
//        mtBaseDocGenerator::ConnectorGenerator(connector, file).generate();
//    }
//};
//
//struct CreateConnectionPerformer
//{
//    typedef cclTree::ConnectionPerformer& result_type;
//    cclTree::GlobalNsp &globalNsp;
//
//    CreateConnectionPerformer(cclTree::GlobalNsp &globalNsp) : globalNsp(globalNsp) {}
//
//    cclTree::ConnectionPerformer &operator()(const boost::filesystem::path &iFile) const
//    {
//        return cclTree::CPerformerCreator(globalNsp, iFile.string()).getConnectionPerformer();
//    }
//};
//
//struct GenerateConnectionPerformer
//{
//    typedef void result_type;
//
//    const std::string title;
//    const mtLibOther::CPerformerFiles &cPerformerFiles;
//
//    GenerateConnectionPerformer(const std::string &title, const mtLibOther::CPerformerFiles &cPerformerFiles) :
//        title(title), cPerformerFiles(cPerformerFiles) {}
//
//    void operator()(const cclTree::ConnectionPerformer &connector, std::ofstream &file) const
//    {
//        mtLibOther::CPerformerFiles::FileVec connFiles = cPerformerFiles.getConnectorFiles();
//
//        for (auto &file : connFiles)
//        {
//            file.replace_extension("docbook.xml");
//            file = file.filename();
//        }
//
//        mtBaseDocGenerator::CPerformerGenerator(connector, file, title, connFiles).generate();
//    }
//};
//
//int main(int argc, char** argv) try
//{
//    po::options_description opDesc("Allowed options");
//    po::positional_options_description popDesc;
//    bool force = false, verbose = false;
//    std::string title;
//
//    opDesc.add_options()
//        ("help,h", "produce help message")
//        ("input,i", po::value<std::string>(), "input file")
//        ("output,o", po::value<std::string>(), "output directory")
//        ("title,t", po::value<std::string>(), "title of the document")
//        ("force,f", po::value<std::string>(), "force creation (normaly only creates if source is newer)")
//        ("verbose,v", po::value<std::string>(), "verbose mode");
//
////        ("showTree,t", "show namespace tree");
//
//    popDesc.add("input", -1);
//
//    po::variables_map vm;
//    try
//    {
//        po::store(po::command_line_parser(argc, argv).options(opDesc).positional(popDesc).run(), vm);
//        po::notify(vm);
//    }
//    catch(const std::exception &ex)
//    {
//        std::cout << "error: " << ex.what() << std::endl;
//        return 1;
//    }
//
//    if (vm.count("force")) force = true;
//    if (vm.count("verbose")) verbose = true;
//
////    #warning sacar
////    verbose = true;
////    force = true;
//
//    if (vm.count("help"))
//    {
//        std::cout << opDesc << std::endl;
//        return 1;
//    }
//
//    boost::filesystem::path iCPerformerFile, oDir;
//
//    // Loads the input file
//    if (vm.count("input"))
//        iCPerformerFile = vm["input"].as<std::string>();
//    else
//    {
//        std::cout << "error: no input file" << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    // Loads the output file
//    if (vm.count("output"))
//        oDir = vm["output"].as<std::string>();
//    else
//    {
//        std::cout << "error: no output file" << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    if (vm.count("title"))
//    {
//        title = vm["title"].as<std::string>();
//    }
//    else
//    {
//        std::cerr << "a title must be provided" << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    mtLibOther::CPerformerFiles cPerformerFiles(iCPerformerFile);
//
//    cclTree::GlobalNsp globalNsp;
//
//    // Loads the connectors to the global namespace and generates their documentation
//    const mtLibOther::CPerformerFiles::FileVec &vec = cPerformerFiles.getConnectorFiles();
//    for (const auto &iFile : vec)
//    {
//        generateObject(iFile, oDir, force, verbose, CreateConnector(globalNsp), GenerateConnector());
//    }
//
//    generateObject(cPerformerFiles.getCPerformerFile(), oDir, force, verbose, CreateConnectionPerformer(globalNsp),
//            GenerateConnectionPerformer(title, cPerformerFiles));
//
//    return 0;
//}
//catch (const chila::lib::misc::TiXmlError &ex)
//{
//    std::cerr << std::endl << "error opening input: " << ex.what() << ".\n" << std::endl;
//    return EXIT_FAILURE;
//}
//catch (const cclTree::ConnectorCreationError &ex)
//{
//    std::cerr << std::endl << "error reading input: " << ex.what() << ".\n" << std::endl;
//    return EXIT_FAILURE;
//}
//catch (const cclTree::CheckErrorElement &ex)
//{
//    std::cerr << "\nerror en Connector object: \n";
//    showCheckErrorElement(ex);
//    return EXIT_FAILURE;
//}
//catch (const cclTree::CheckErrorGroup &ex)
//{
//    std::cerr << "\nerror en Connector object: \n";
//    showCheckErrorGroup(ex);
//    return EXIT_FAILURE;
//}
//
//void showCheckErrorElement(const cclTree::CheckErrorElement &ex)
//{
//    std::cerr << "- " << ex.getPath().getStringRep() << ": " << ex.getError() << std::endl;
//}
//
//void showCheckErrorGroup(const cclTree::CheckErrorGroup &ex)
//{
//    for (const auto &cError : ex.getErrors())
//    {
//        if (const cclTree::CheckErrorElementSCPtr &error =
//                boost::dynamic_pointer_cast<const cclTree::CheckErrorElement>(cError))
//        {
//            showCheckErrorElement(*error);
//        }
//        else if (const cclTree::CheckErrorGroupSCPtr &error =
//                boost::dynamic_pointer_cast<const cclTree::CheckErrorGroup>(cError))
//        {
//            showCheckErrorGroup(*error);
//        }
//        else abort();
//    }
//}
//
//template <typename CreateFun, typename GenerateFun>
//void generateObject(const boost::filesystem::path &iFile, const boost::filesystem::path &oDir, bool force, bool verbose,
//        const CreateFun &create, const GenerateFun &generate)
//{
//    boost::filesystem::path oFile = oDir / iFile.filename();
//    oFile.replace_extension("docbook.xml");
//
//    const typename CreateFun::result_type object = create(iFile.string());
//    object.check();
//
//    if (!force && boost::filesystem::exists(oFile) && getTimeOfPath(iFile) <= getTimeOfPath(oFile))
//        return;
//
//    if (verbose)
//        std::cout << oFile << std::endl;
//
//    std::ofstream file;
//    file.exceptions(std::ios::badbit | std::ios::failbit);
//
//    file.open(oFile.string().c_str());
//    generate(object, file);
//}
//
