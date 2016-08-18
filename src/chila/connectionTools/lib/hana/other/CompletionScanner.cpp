/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#include "CompletionScanner.hpp"
//#include "CScannerGrammar.hpp"
//#include <boost/filesystem.hpp>
//#include <boost/range.hpp>
//
//CHILA_LIB_MISC__DEF_NAMESPACE(4, (chila,connectionTools,lib,other))
//{
//    namespace cfLib = chila::flow::lib;
//
//    void parseFile(const boost::filesystem::path &file, chila::flow::lib::CompletionList &cList);
//
//    chila::flow::lib::CompletionsSPtr CompletionScanner::generate()
//    {
//        chila::flow::lib::CompletionsSPtr completions = cfLib::Completions::create();
//
//        for (const auto &implPath : nspAssoc)
//        {
//            typedef std::map<std::string, cfLib::CompletionConnectorSPtr> CConnMap;
//            CConnMap cConnectors;
//
//            boost::filesystem::directory_iterator dirIt(basePath / implPath), dirEnd;
//
//            for (const auto &path : boost::make_iterator_range(dirIt, dirEnd))
//                if (boost::filesystem::is_regular(path) && (path.extension() == ".hpp" || path.extension() == ".cpp"))
//                {
//                    cfLib::CompletionConnectorSPtr &cConnector = cConnectors[path.stem().string()];
//                    if (!cConnector) cConnector = cfLib::CompletionConnector::create();
//
//                    parseFile(path, cConnector->completions());
//                }
//
//            for (const auto &vt : cConnectors)
//            {
//                completions->compConnections().add(implPath.name() + "." + vt.first, vt.second);
//            }
//        }
//
//        return completions;
//    }
//
//
//
//}}}}
//
