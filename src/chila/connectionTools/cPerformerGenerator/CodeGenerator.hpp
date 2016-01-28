/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_CPERFORMERGENERATOR__CODEGENERATOR_HPP
#define CHILA_CONNECTIONTOOLS_CPERFORMERGENERATOR__CODEGENERATOR_HPP

#include <chila/connectionTools/lib/tree/fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <set>
#include <chila/lib/misc/macrosExp.hpp>

#define cclTree chila::connectionTools::lib::tree
#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#include "nspDef.hpp"

MY_NSP_START
{
    class CodeGenerator
    {
        public:
            CodeGenerator(const cclTree::cPerformer::ConnectionPerformer &cPerformer, std::ostream &out) :
                cPerformer(cPerformer), headerOut(out) {}

            void generate();

        private:
            using StringSet = std::set<std::string>;

            const cclTree::cPerformer::ConnectionPerformer &cPerformer;
            std::ostream &headerOut;

            void generateConnections(unsigned indent);
            void generateConnInstanceGroup(unsigned indent, const cclTree::cPerformer::ConnectorInstanceGroup &connInstance);
            void generateEventCall(unsigned indent, const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall);
            void generateEventCallOp(unsigned indent, const cclTree::cPerformer::EventCall &eventCall);
            void generateEventCallTmplArgs(unsigned indent, const cclTree::connector::ArgRefMap &args);
            void generateEventCallDeclArgs(unsigned indent, const cclTree::connector::ArgRefMap &args);
            void generateEventCallOpBody(unsigned indent, const cclTree::cPerformer::EventCall &eventCall);
            void generateConnInstancesClass(unsigned indent, const cclTree::cPerformer::ConnectorInstanceMap &cInstances);

            void generateConnEventCalls(unsigned indent, const cclTree::cPerformer::ConnectorInstance &connInstance, const std::string &cInstanceName);
            void generateConnEventCall(unsigned indent, const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall);
            void generateAProvCreators(unsigned indent, const cclTree::cPerformer::EventCall &eventCall);
            void generateActionVec(unsigned indent, const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall);

            enum ApcAcGenEnum
            {
                AAGE_TEMPLATE,
                AAGE_FIELD,
                AAGE_ARG,
                AAGE_INIT_LIST,
                AAGE_PASS_ARG_TYPE,
                AAGE_PASS_ARG_VAR
            };

            void generateAProvVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
                const cclTree::cPerformer::EventCall &eventCall);
            void generateActionVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
                const cclTree::cPerformer::EventCall &eventCall);
            void generateApcActionVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
                const cclTree::cPerformer::EventCall &eventCall);
    };
}
MY_NSP_END

#include "nspUndef.hpp"
#undef cclTree
#undef DEF_NAMESPACE
#endif
