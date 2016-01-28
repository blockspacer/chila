/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_LIB__TYPES_HPP
#define CHILA_CODEX_TEXT_LIB__TYPES_HPP

#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__NAMED_TUPLE(Color, 1,
        ((float)(red))
        ((float)(green))
        ((float)(blue))
    );
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
