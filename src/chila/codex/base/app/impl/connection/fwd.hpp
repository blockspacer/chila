/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL_CONNECTION__FWD_HPP
#define CHILA_CODEX_BASE_APP_IMPL_CONNECTION__FWD_HPP

#include "../fwd.hpp"
#include <chila/connectionTools/lib/common/impl/connection/Forwarder.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__FWDEC_TYPE(NullObject);
    CHILA_LIB_MISC__FWDEC_TYPE(TabId);

    struct NullObject final : public cclCommon::impl::connection::Forwarder::Object
    {
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
