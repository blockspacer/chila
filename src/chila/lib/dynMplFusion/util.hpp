/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_DYNMPLFUSION__UTIL_HPP
#define CHILA_LIB_DYNMPLFUSION__UTIL_HPP

#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,dynMplFusion)
{

    template <typename Type>
    Type &cast(Type &data) { return data; }

    template <typename Type>
    Type &cast(boost::any &data)
    {
        return boost::any_cast<Type&>(data);
    }

    template <typename Type>
    const Type &cast(const boost::any &data)
    {
        return boost::any_cast<const Type&>(data);
    }
}}}

#endif
