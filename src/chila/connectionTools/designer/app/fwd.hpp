/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP__FWD_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP__FWD_HPP

#define FWDEC_SPTR CHILA_LIB_MISC__FWDEC_SPTR
#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

#include <vector>
#include <set>
#include <chila/lib/misc/Path.hpp>

#include "../fwd.hpp"
#include "macros.fgen.hpp"

MY_NSP_START
{
    using ClmPathVec = std::vector<chila::lib::misc::Path>;
    using ClmPathSet = std::set<chila::lib::misc::Path>;
}
MY_NSP_END


#include "macros.fgen.hpp"
#endif
