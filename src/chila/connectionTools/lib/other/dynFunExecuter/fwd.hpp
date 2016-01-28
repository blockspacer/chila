/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <map>
#include <chila/lib/misc/Path.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    using ArgumentStrMap = std::map<std::string, std::string>;

    CHILA_LIB_MISC__FWDEC_TYPE(ExecuterMap);

    CHILA_LIB_MISC__NAMED_TUPLE(XMLResult, 1,
        ((chila::lib::misc::Path)(path))
        ((ArgumentStrMap)(arguments))
    );

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_TYPE
#endif
