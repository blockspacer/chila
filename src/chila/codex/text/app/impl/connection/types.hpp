/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_HPP

#include "fwd.hpp"
#include "../../../lib/types.hpp"

#include "macros.fgen.hpp"

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_CHECKLIST \
    (regularExpression) \
    (preserveCase) \
    (wholePhrase) \
    (wrapAround) \
    (matchCase) \
    (highlightMatches) \
    (selection) \
    (replaceBackwards)

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_NAMED_TYPLE_ELEM(r, data, elem) \
    ((bool)(elem))

MY_NSP_START
{
    CHILA_LIB_MISC__NAMED_TUPLE(TagApply, 0,
        ((std::size_t)(start))
        ((std::size_t)(size))
        ((std::string)(name))
    );

    CHILA_LIB_MISC__NAMED_TUPLE(TextTag, 1,
        ((std::string)(name))
        ((lib::Color)(color))
    );

    CHILA_LIB_MISC__NAMED_TUPLE
    (
        FindReplaceChecks, 0,
        BOOST_PP_SEQ_FOR_EACH(CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_NAMED_TYPLE_ELEM,,
                              CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TYPES_CHECKLIST)
    );
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

