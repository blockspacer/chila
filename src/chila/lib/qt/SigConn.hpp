/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_QT__SIGCONN_HPP
#define CHILA_LIB_QT__SIGCONN_HPP

#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <boost/function_types/function_arity.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    using misc::rvalue_cast;

    template <unsigned arity>
    class TSigConn {};

    struct SigConn
    {
        bool enabled = true;

        struct Disabler
        {
            SigConn &sigConn;
            Disabler(SigConn &sigConn) : sigConn(sigConn)
            {
                sigConn.enabled = false;
            }

            ~Disabler() noexcept { sigConn.enabled = true; }
        };

        Disabler disabler() { return Disabler(*this); }

        virtual ~SigConn() = default;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#include "SigConn.fgen.hpp"

#endif
