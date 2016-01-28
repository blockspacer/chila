/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__POLYALLOCATOR_HPP
#define CHILA_LIB_MISC__POLYALLOCATOR_HPP

#include <boost/pool/pool_alloc.hpp>


#include "macrosDef.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type> using PolyAllocator = boost::fast_pool_allocator<Type>;

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
