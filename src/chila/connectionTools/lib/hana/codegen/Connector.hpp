/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_HPP

#include "fwd.hpp"
#include <boost/cast.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Connector
    {
        virtual ~Connector() {}
    };

    template <typename Derived>
    struct ConnectorImpl: public Connector
    {
        Derived &derived()              { return *boost::polymorphic_downcast<Derived*>(this); }
        const Derived &derived() const  { return *boost::polymorphic_downcast<const Derived*>(this); }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
