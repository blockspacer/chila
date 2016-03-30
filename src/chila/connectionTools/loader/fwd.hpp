/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LOADER__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LOADER__FWD_HPP

#include <vector>
#include <set>
#include <memory>
#include <memory>
#include <chila/lib/misc/exceptions.hpp>
#include <chila/connectionTools/lib/codegen/fwd.hpp>
#include "chila/connectionTools/lib/other/fwd.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    namespace clMisc = chila::lib::misc;
    namespace cclOther = chila::connectionTools::lib::other;

    using ConnectorMap = chila::connectionTools::lib::codegen::ConnectorMap;

    CHILA_LIB_MISC__FWDEC_TYPE(Loader);
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
