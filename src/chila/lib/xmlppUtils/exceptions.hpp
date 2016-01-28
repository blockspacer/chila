/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_XMLPPUTILS__EXCEPTIONS_HPP
#define CHILA_LIB_XMLPPUTILS__EXCEPTIONS_HPP

#include <chila/lib/misc/exceptions.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define DEF_RUNTIME_ERROR_WT            CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT
#define DEF_RUNTIME_ERROR_FROM_BASE      CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE

#include "nspDef.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR_WT(Exception, "xmlppUtils exception");

    DEF_RUNTIME_ERROR_FROM_BASE(Exception, InvalidTagName, "invalid tag name");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, InvalidAttributeValue, "invalid attribute value");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ChildElementNotFound, "child XML element not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, InvalidElement, "invalid element");
}
MY_NSP_END

#include "nspUndef.hpp"

#undef DEF_RUNTIME_ERROR_WT
#undef DEF_RUNTIME_ERROR_FROM_BASE
#endif
