/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__EXCEPTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EXCEPTIONS_HPP

#include "fwd.hpp"
#include <chila/lib/misc/exceptions.hpp>

#define DEF_RUNTIME_ERROR_WT            CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT

#include "macros.fgen.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR_WT(ParseError, "parse error");
    DEF_RUNTIME_ERROR_WT(InvalidStateError, "invalid state");
    DEF_RUNTIME_ERROR_WT(DataMapElementNotFound, "data-map element not found");

    struct ErrorInfo
    {
        typedef boost::error_info<struct mod_state, ModuleState> ModState;
        typedef boost::error_info<struct source_type, std::string> SourceType;
        typedef boost::error_info<struct dest_type, std::string> DestType;
        typedef boost::error_info<struct data_map_value_name, std::string> DataMapValueName;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef DEF_RUNTIME_ERROR_WT
#endif
