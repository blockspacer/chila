/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__CONSTRUCT_HPP
#define CHILA_LIB_MISC__CONSTRUCT_HPP

#include <utility>
#include <boost/ref.hpp>
#include <boost/preprocessor.hpp>

#include <chila/lib/misc/macrosExp.hpp>


#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type>
    struct Construct
    {
        typedef Type result_type;

        template <typename... Arg>
        Type operator()(Arg&&... arg) const
        {
            return Type(std::forward<Arg>(arg)...);
        }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"



#endif

