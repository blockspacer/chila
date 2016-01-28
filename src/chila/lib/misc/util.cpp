/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "exceptions.hpp"
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <boost/range/algorithm.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    boost::mutex coutMutex, cerrMutex;

    void throwSystemError(int errVal, const char *msg, const char *file, int line)
    {
        boost::system::error_code ec(errVal, boost::system::system_category());
        throw boost::enable_error_info(boost::system::system_error(ec, msg)) <<
            boost::throw_file(file) <<
            boost::throw_line(line);
    }

    /** Gets the relative path of 'path' from 'dir'. */
    boost::filesystem::path getRelativePath(const boost::filesystem::path &dir,
            const boost::filesystem::path &path)
    {
        boost::filesystem::path ret = ".";

        boost::filesystem::path::iterator dirIt, pathIt;
        for (dirIt = dir.begin(), pathIt = path.begin(); dirIt != dir.end(); ++dirIt, ++pathIt)
        {
            if (pathIt == path.end())
                BOOST_THROW_EXCEPTION(std::invalid_argument("path"));

            if (*dirIt != *pathIt)
                BOOST_THROW_EXCEPTION(std::invalid_argument("dir, path"));
        }

        for (; pathIt != path.end(); ++pathIt)
        {
            ret /= *pathIt;
        }

        return ret;
    }

    std::string replace(const std::string &text, const std::string &rep, const std::string &with)
    {
        return boost::replace_all_copy(text, rep, with);
    }

    const char *getEscapeChar(char c)
    {
        switch (c)
        {
            case '\\': return R"(\\)";
            case '\n': return R"(\n)";
            case '\t': return R"(\t)";
            case '\r': return R"(\r)";
            default: return nullptr;
        }
    }

    std::string escapeText(const std::string &text)
    {
        std::stringstream str;

        for (char c : text)
        {
            if (auto escaped = getEscapeChar(c))
                str << escaped;
            else
                str << c;
        }

        return str.str();
    }

    std::string unescapeText(const std::string &text)
    {
        bool escaping = false;

        std::stringstream str;
        for (auto c : text)
        {
            if (escaping)
            {
                switch (c)
                {
                    case 'n': str << '\n'; break;
                    case 'r': str << '\r'; break;
                    case '\\': str << '\\'; break;
                    case 't': str << '\t'; break;
                    default: abort();
                }

                escaping = false;
            }
            else if (c == '\\')
            {
                escaping = true;
            }
            else str << c;
        }

        return str.str();
    }


    void removeTrailingWSpace(std::string &text)
    {
        auto findNonspaceNL = [](char c)
        {
            return c != ' ' || c == '\n';
        };

        auto rangeLeft = boost::make_iterator_range(text.begin(), text.end());

        while (boost::distance(rangeLeft))
        {
            auto spaceRange = boost::find_if<boost::return_begin_found>(rangeLeft, findNonspaceNL);

            if (spaceRange.end() != rangeLeft.end() && *spaceRange.end() == '\n')
            {
                auto it = text.erase(spaceRange.begin(), spaceRange.end());
                rangeLeft = boost::make_iterator_range(it, text.end());
            }
            else
            {
                rangeLeft = boost::make_iterator_range(spaceRange.end(), text.end());
            }

            rangeLeft = boost::find<boost::return_found_end>(rangeLeft, ' ');
        }
    }

    bool wildMatch(const char *pat, const char *str)
    {
       while (*str) {
          switch (*pat) {
             case '?':
                if (*str == '.') return false;
                break;
             case '*':
                do { ++pat; } while (*pat == '*'); /* enddo */
                if (!*pat) return true;
                while (*str) if (wildMatch(pat, str++)) return true;
                return false;
             default:
                if (*str != *pat) return false;
                break;
          } /* endswitch */
          ++pat, ++str;
       } /* endwhile */
       while (*pat == '*') ++pat;
       return !*pat;
    }
}
MY_NSP_END
