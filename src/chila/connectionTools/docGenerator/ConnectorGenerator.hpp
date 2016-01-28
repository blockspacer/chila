/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#ifndef CHILA_CONNECTIONTOOLS_DOCGENERATOR__CONNECTORGENERATOR_HPP
//#define CHILA_CONNECTIONTOOLS_DOCGENERATOR__CONNECTORGENERATOR_HPP
//
//#include <chila/connectionTools/lib/tree/Connector.hpp>
//#include <boost/function.hpp>
//#include <iostream>
//#include "GeneratorBase.hpp"
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//#define cclTree chila::connectionTools::lib::tree
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    class ConnectorGenerator final: public GeneratorBase
//    {
//        public:
//            ConnectorGenerator(const cclTree::Connector &connector, std::ostream &out) :
//                GeneratorBase(out, connector), connector(connector) {}
//
//            void generate();
//
//        private:
//            const cclTree::Connector &connector;
//
//            void generateFunctions(const cclTree::FunctionCVec &functions, const std::string &title);
//            void generateArgumentList(const cclTree::Function &fun);
//    };
//
//}}}
//
//#undef cclTree
//#undef DEF_NAMESPACE
//
//
//#endif
