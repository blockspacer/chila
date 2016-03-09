/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON_IMPL_CONNECTION__FUNDYNXMLPARSER_HPP
#define CHILA_CONNECTIONTOOLS_COMMON_IMPL_CONNECTION__FUNDYNXMLPARSER_HPP

#include "fwd.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/FunDynXMLParser.hpp"
#include <chila/lib/misc/Path.hpp>
#include "../../../dynFunExecuter/fwd.hpp"

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct FunDynXMLParser
    {
        struct ArgTypes
        {
            using text      = std::string;
            using funPath   = chila::lib::misc::Path;
            using arguments = dynFunExecuter::ArgumentStrMap;
            using errorMsg  = std::string;
        };

        DEF_CPROVIDER(FunDynXMLParser);

        static CProviderUPtr create(const std::string &instanceName);
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
