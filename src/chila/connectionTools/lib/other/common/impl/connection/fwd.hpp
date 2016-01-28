/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__FWD_HPP

#include "../fwd.hpp"
#include <chila/lib/misc/fwd.hpp>
#include <chila/lib/misc/exceptions.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    using Buffer = std::pair<const char*, unsigned>;
    using CharVector  = std::vector<char>;

    FWDEC_SPTR(CharVector);
    FWDEC_SPTR(Buffer);

    CHILA_LIB_MISC__DEF_ENUM_TEMPLATES;

    CHILA_LIB_MISC__DEF_ENUM_TYPE(MsgReadCriteriaEnum,
        ((LENGTH)("length"))
        ((NLCR)("nlcr")));

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
