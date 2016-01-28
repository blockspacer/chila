/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__SINKINSERTER_HPP
#define CHILA_LIB_MISC__SINKINSERTER_HPP

#include <iostream>

#define CHILA_LIB_MISC__FSI_METHOD_BIND(method, owner) \
    chila::lib::misc::funSinkInserter(boost::bind(&method, owner, _1))

#define CHILA_LIB_MISC__FSI_METHOD_BIND_WA(method, owner, ...) \
    chila::lib::misc::funSinkInserter(boost::bind(&method, owner, _1, __VA_ARGS__))

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct SinkInserterBase {};

    template <typename Derived>
    struct SinkInserter: public SinkInserterBase
    {
        template <typename Sink>
        void operator()(Sink &out) const
        {
            static_cast<const Derived*>(this)->write(out);
        }
    };

    template <typename Fun>
    struct FunSinkInserter final: public SinkInserter< FunSinkInserter<Fun> >
    {
        Fun fun;

        FunSinkInserter(const Fun &fun) : fun(fun) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            fun(out);
        }
    };


    template <typename Sink, typename Derived>
    inline Sink &operator<<(Sink &out, const SinkInserter<Derived> &inserter)
    {
        inserter(out);
        return out;
    }

    template <typename Fun>
    inline FunSinkInserter<Fun> funSinkInserter(const Fun &fun)
    {
        return FunSinkInserter<Fun>(fun);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
