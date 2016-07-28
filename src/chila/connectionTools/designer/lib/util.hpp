/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */


#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__UTIL_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__UTIL_HPP


#include "fwd.hpp"
#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Iterator>
    boost::iterator_range<Iterator> getParentAndChildren(const Iterator &begin, const Iterator &end, const decltype(begin->first) &val)
    {
        return clMisc::getChildren(boost::make_iterator_range(begin, end),
                    [&](const typename std::remove_reference<decltype(*begin)>::type &vt) { return !vt.first.startsWith(val); });
    }
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
