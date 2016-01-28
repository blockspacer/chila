/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__CONTAINERSINKINSERTER_HPP
#define CHILA_LIB_MISC__CONTAINERSINKINSERTER_HPP

#include "SinkInserter.hpp"
#include <boost/foreach.hpp>
#include <boost/call_traits.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Container, typename Sep>
    struct ContainerSinkInserter final: public chila::lib::misc::SinkInserter< ContainerSinkInserter<Container, Sep> >
    {
        Sep sep;
        const Container &cont;

        ContainerSinkInserter<Container, Sep>(const Container &cont, Sep sep) : cont(cont), sep(sep) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            bool first = true;
            for (const auto &vt : cont)
            {
                if (first) first = false;
                else out << sep;

                out << vt;
            }
        }
    };

    template <typename Container, typename Sep>
    inline ContainerSinkInserter<Container, Sep> containerSinkInserter(Container cont, Sep sep)
    {
        return ContainerSinkInserter<Container, Sep>(cont, sep);
    }


    template <typename Container>
    inline ContainerSinkInserter<Container, std::string> containerSinkInserter(const Container &cont)
    {
        return ContainerSinkInserter<Container, std::string>(cont, ", ");
    }

}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
