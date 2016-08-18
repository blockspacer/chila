/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXCEPTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EXCEPTIONS_HPP

#include <chila/lib/misc/exceptions.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR(Exception);
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorInstanceAlreadyExists, "connector instance already exists");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorInstanceNotFound, "connector instance not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, FunctionAlreadySet, "function already set");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, FunctionNotSet, "function not set");

//    struct ErrorInfo
//    {
//        using ConnectorInstancePath = boost::error_info<struct tag_cinstance_name, chila::lib::misc::Path>;
//    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

