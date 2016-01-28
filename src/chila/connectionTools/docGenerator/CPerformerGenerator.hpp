/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#ifndef CHILA_CONNECTIONTOOLS_DOCGENERATOR__CPERFORMERGENERATOR_HPP
//#define CHILA_CONNECTIONTOOLS_DOCGENERATOR__CPERFORMERGENERATOR_HPP
//
//#include <chila/connectionTools/lib/tree/Connector.hpp>
//#include <boost/function.hpp>
//#include <iostream>
//#include "GeneratorBase.hpp"
//#include <boost/filesystem/path.hpp>
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//#define cclTree chila::connectionTools::lib::tree
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    class CPerformerGenerator final: public GeneratorBase
//    {
//        public:
//            typedef std::vector<boost::filesystem::path> ConnectorFiles;
//
//            CPerformerGenerator(const cclTree::ConnectionPerformer &cPerformerCreator, std::ostream &out,
//                    const std::string &title, const ConnectorFiles &connectorFiles) :
//                GeneratorBase(out, cPerformerCreator), cPerformerCreator(cPerformerCreator), title(title), connectorFiles(connectorFiles) {}
//
//            void generate();
//
//        private:
//            const cclTree::ConnectionPerformer &cPerformerCreator;
//            const std::string title;
//            const ConnectorFiles connectorFiles;
//
//            void generateArgAliases();
//            void generateConnectorAliases();
//            void generateArgProviderCreators();
//            void generateConnectorInstances();
//    };
//
//}}}
//
//#undef cclTree
//#undef DEF_NAMESPACE
//
//
//#endif
