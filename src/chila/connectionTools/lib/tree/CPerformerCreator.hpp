/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__CPERFORMERCREATOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__CPERFORMERCREATOR_HPP

#include "fwd.hpp"
#include "types.hpp"
#include "CreatorBase.hpp"
#include <boost/filesystem.hpp>
#include <libxml++/libxml++.h>

#include "nspDef.hpp"

MY_NSP_START
{
    class CPerformerCreator final: public CreatorBase
    {
        private:
            void parseArguments(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &argumentsElem);
            void parseConnectorAliases(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &aliasesElem);
            void parseArgProviderCreators(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &creatorsElem);
            void parseConnectorInstances(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &instancesElem);


            static std::string parseAction(const std::string &actionStr, std::string &actionName);

        public:
            CPerformerCreator(Namespace &nspBase, const boost::filesystem::path &file) :
                CreatorBase(nspBase, file) {}

            cPerformer::ConnectionPerformer &create();
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif


