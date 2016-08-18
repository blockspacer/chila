/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.other'
 *
 * 'chila.connectionTools.lib.other' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.other' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.other'. If not, see <http://www.gnu.org/licenses/>.
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
