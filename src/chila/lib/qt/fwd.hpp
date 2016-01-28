/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_QT__FWD_HPP
#define CHILA_LIB_QT__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <boost/any.hpp>
#include <QObject>

#undef QT_BEGIN_MOC_NAMESPACE
#undef QT_END_MOC_NAMESPACE

#include "macros.fgen.hpp"

#define _CHILA_LIB_QT__ARGS(exp) (exp)

#define CHILA_LIB_QT__SIGNAL(exp) BOOST_PP_EXPAND(SIGNAL _CHILA_LIB_QT__ARGS(exp))

#define CHILA_LIB_QT__SLOT(exp) BOOST_PP_EXPAND(SLOT _CHILA_LIB_QT__ARGS(exp))

MY_NSP_START
{
    CHILA_LIB_MISC__NAMED_TUPLE
    (
        ConnectData, 0,
        ((QMetaObject::Connection)(connection))
        ((boost::any)(router))
    );

    CHILA_LIB_MISC__FWDEC_TYPE(SigConn);
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
