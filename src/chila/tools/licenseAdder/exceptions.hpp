#ifndef CHILA_TOOLS_LICENSEADDER__EXCEPTIONS_HPP
#define CHILA_TOOLS_LICENSEADDER__EXCEPTIONS_HPP

#include <chila/lib/misc/fwd.hpp>
#include <chila/lib/misc/exceptions.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(ParseError, "parse error");
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(InvalidFormatsFile, "invalid formats file");
    CHILA_LIB_MISC__DEF_EXCEPTION(FormatNameIsDuplicated, "format name is duplicated");
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(InvalidFormat, "invalid format");
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(DuplicatePattern, "duplicate pattern");
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(PatternNotFound, "pattern not found");

    CHILA_LIB_MISC__DEC_ERROR_INFO_STRUCT
    (
        ((Pattern)(std::string)("pattern"))
    )
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
