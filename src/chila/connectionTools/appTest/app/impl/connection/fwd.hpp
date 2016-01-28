/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__FWD_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP_IMPL_CONNECTION__FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>



#include "nspDef.hpp"

MY_NSP_START
{
    FWDEC_TYPE(CProvider);

    struct CProvider
    {
        virtual ~CProvider() {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
