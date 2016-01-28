/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__ARGPROVIDERS_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__ARGPROVIDERS_HPP

#include "../../connectors/gen/ConnectionPerformer.hpp"
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace argProv
    {
        APROVIDER_DEC_EX(nullObjectCreator,)
        {
        }};

        APROVIDER_DEC_EX(cmdNetServer_msgCreatorFromBuff,) :
            cmdNetServer_message(cmdNetServer_msgBuffer->begin(), cmdNetServer_msgBuffer->end())
        {
        }};
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
