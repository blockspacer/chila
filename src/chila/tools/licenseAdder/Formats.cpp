#include "Formats.hpp"
#include <libxml++/libxml++.h>
#include <chila/lib/xmlppUtils/util.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <chila/lib/misc/util.hpp>
#include "exceptions.hpp"
#include <boost/algorithm/string.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    clMisc::StringSet loadPatterns(const std::string &text);

    void Formats::load(const boost::filesystem::path &path) try
    {
        if (!bfs::is_regular_file(path))
        {
            BOOST_THROW_EXCEPTION(clMisc::InvalidPath() << clMisc::ExceptionInfo::FilePath(path));
        }

        xmlpp::DomParser parser(path.string().c_str());
        auto &document = *parser.get_document();
        auto root = clMisc::checkNotNull(document.get_root_node());

        if (!root || root->get_name() != std::string("formats"))
        {
            BOOST_THROW_EXCEPTION(InvalidFormatsFile("the root 'formats' was not found"));
        }

        clXmlppUtils::iterateChildren(*root, "format", [&](const xmlpp::Element &child)
        {
            try
            {
                auto insRet = data.insert
                ({
                    clXmlppUtils::getAttribute<std::string>(child, "name"),
                    {
                        clMisc::unescapeText(clXmlppUtils::getAttribute<std::string>(child, "header", "")),
                        clMisc::unescapeText(clXmlppUtils::getAttribute<std::string>(child, "start")),
                        clMisc::unescapeText(clXmlppUtils::getAttribute<std::string>(child, "lineStart", "")),
                        clMisc::unescapeText(clXmlppUtils::getAttribute<std::string>(child, "emptyLineStart", "")),
                        clMisc::unescapeText(clXmlppUtils::getAttribute<std::string>(child, "end")),
                        loadPatterns(clXmlppUtils::getAttribute<std::string>(child, "patterns"))
                    }
                });

                if (!insRet.second)
                {
                    clXmlppUtils::throwException(FormatNameIsDuplicated(), child);
                }

                const auto &format = insRet.first->second;

                for (const auto &ext : format.patterns)
                {
                    if (!patFormatMap.insert({ext, insRet.first}).second)
                    {
                        BOOST_THROW_EXCEPTION(DuplicatePattern() << ExceptionInfo::Pattern(ext));
                    }
                }

                return true;
            }
            catch (const DuplicatePattern &ex)
            {
                throw clXmlppUtils::addExceptionInfo(ex, child);
            }
        });
    }
    catch (const boost::exception &ex)
    {
        ex << clMisc::ExceptionInfo::FilePath(path);
        throw;
    }

    const Format &Formats::fromFile(const bfs::path &file) const
    {
        for (const auto &vt : patFormatMap)
        {
            auto &pat = vt.first;
            if (clMisc::wildMatch(pat.c_str(), file.c_str()))
                return vt.second->second;
        }

        BOOST_THROW_EXCEPTION(PatternNotFound() << clMisc::ExceptionInfo::FilePath(file));
    }

    const Format &Formats::operator[](const std::string &name) const
    {
        auto it = data.find(name);
        if (it == data.end())
            BOOST_THROW_EXCEPTION(InvalidFormat(name));

        return it->second;
    }

    clMisc::StringSet loadPatterns(const std::string &text)
    {
        clMisc::StringSet ret;

        clMisc::tokenize(text, ",", [&ret](std::string token)
        {
            boost::trim(token);

            if (!ret.insert(token).second)
            {
                BOOST_THROW_EXCEPTION(DuplicatePattern() << ExceptionInfo::Pattern(token));
            }
            return true;
        });

        return ret;
    }
}
MY_NSP_END

