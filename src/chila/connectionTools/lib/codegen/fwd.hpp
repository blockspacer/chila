/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

#include "macros.fgen.hpp"

#define FWDEC_TYPE  CHILA_LIB_MISC__FWDEC_TYPE

MY_NSP_START
{
    namespace clMisc = chila::lib::misc;

    FWDEC_TYPE(Connector);
    FWDEC_TYPE(ConnectorMap);
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef FWDEC_TYPE

#endif
