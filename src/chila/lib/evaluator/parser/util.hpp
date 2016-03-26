/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__UTIL_HPP
#define CHILA_LIB_EVALUATOR_PARSER__UTIL_HPP

#include "fwd.hpp"
#include <string>
#include "nspDef.hpp"

MY_NSP_START
{
    #define dec_create(name, Iterator)                                      \
        std::shared_ptr< IParser<Iterator> > name(                        \
            const IExpressionProviderSCPtr &expProvider, bool optimize)

    dec_create(createStrItParser, std::string::const_iterator);
//    dec_create(createCCharParser, const char*);

    #undef dec_create

}
MY_NSP_END

#include "nspUndef.hpp"

#endif
