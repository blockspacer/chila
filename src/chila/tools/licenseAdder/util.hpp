#ifndef CHILA_TOOLS_LICENSEADDER__UTIL_HPP
#define CHILA_TOOLS_LICENSEADDER__UTIL_HPP

#include "fwd.hpp"
#include <boost/filesystem.hpp>
#include <boost/range.hpp>

#include "macros.fgen.hpp"


MY_NSP_START
{
    void parseText(const std::string &text, const std::string &startText, const std::string &endText);
    void parseStream(MPIterator &it, const MPIterator &end, const Format &format);
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
