/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__FWD_HPP
#define CHILA_LIB_EVALUATOR_PARSER__FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "nspDef.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__FWDEC_TYPE(IExpressionProvider);

    template <typename Iterator>
    struct IParser;

    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(ParseError, "parse error");
}
MY_NSP_END

#include "nspUndef.hpp"


#endif
