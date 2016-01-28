/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_CONNECTORGENERATOR__CODEGENERATOR_HPP
#define CHILA_CONNECTIONTOOLS_CONNECTORGENERATOR__CODEGENERATOR_HPP

#include <chila/connectionTools/lib/tree/types.hpp>
#include <iostream>
#include <chila/lib/misc/macrosExp.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define cclTree chila::connectionTools::lib::tree
#define libMisc chila::lib::misc


#include "nspDef.hpp"

MY_NSP_START
{
    class CodeGenerator
    {
        private:
            const cclTree::connector::Connector &connector;
            std::ostream &out;
            libMisc::Path modNspPath;

            void generateHeader();
            void generateFooter();

            void generateConnector();

        public:
            CodeGenerator(const cclTree::connector::Connector &connector, std::ostream &out);

            void generate();

            std::string argSeqName() const;
            std::string funSeqName(const std::string &name) const;
            std::string funArgECSeqName(const std::string &name, const std::string &prefix, const std::string &funName) const;

            void generateArgSeq(const cclTree::connector::ArgumentMap &arguments);

            template <typename Function, typename Group, typename Map>
            void generateFunSeqs(const Map &functions, const std::string &name);

            void generateStrFunSeqs(const std::string &name, bool isAction);

            void generateActionEvCalled(const cclTree::connector::ActionMap &functions);
    };

}
MY_NSP_END

#include "nspUndef.hpp"

#undef libMisc
#undef cclTree
#undef DEF_NAMESPACE


#endif
