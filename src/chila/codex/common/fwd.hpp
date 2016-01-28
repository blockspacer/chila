/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_COMMON__FWD_HPP
#define CHILA_CODEX_COMMON__FWD_HPP

#include "../fwd.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__NAMED_TUPLE
    (
        ActionPathData, 0,
        ((std::string)(name))
        ((std::string)(label))
    );

    CHILA_LIB_MISC__NAMED_TUPLE
    (
        ActionData, 0,
        ((std::string)(name))
        ((std::string)(label))
        ((std::string)(tooltip))
        ((std::string)(shortcutKey))
    );

    using ActionPathDataList = std::vector<ActionPathData>;
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

