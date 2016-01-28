#ifndef CHILA_TOOLS_LICENSEADDER__FORMATS_HPP
#define CHILA_TOOLS_LICENSEADDER__FORMATS_HPP

#include "fwd.hpp"
#include <map>
#include <boost/filesystem.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Formats
    {
        public:
            void load(const boost::filesystem::path &path);
            const Format &operator[](const std::string &name) const;
            const Format &fromFile(const bfs::path &file) const;

        private:
            using FormatMap = std::map<std::string, Format>;
            using PatFormatMap = std::map<std::string, FormatMap::iterator>;
            FormatMap data;
            PatFormatMap patFormatMap;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
