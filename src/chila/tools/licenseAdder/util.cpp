#include "util.hpp"
#include "Grammar.hpp"
#include <boost/spirit/include/qi.hpp>
#include "exceptions.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Grammar>
    void parseIt(Grammar &grammar, typename Grammar::iterator_type &it, typename Grammar::iterator_type end) try
    {
        bool r = boost::spirit::qi::parse(it, end, grammar);

        if (!r || !grammar.parsed)
        {
            BOOST_THROW_EXCEPTION(ParseError("parsing failed"));
        }
    }
    catch (const boost::spirit::qi::expectation_failure<typename Grammar::iterator_type> &ex)
    {
        BOOST_THROW_EXCEPTION(ParseError("expectation failure in: '" + std::string(ex.first, ex.last) + "'..."));
    }

    void parseStream(MPIterator &it, const MPIterator &end, const Format &format)
    {
        Grammar<MPIterator> grammar(format);
        parseIt(grammar, it, end);
    }

    void parseText(const std::string &text, const std::string &startText, const std::string &endText)
    {
//        Grammar<std::string::const_iterator> grammar(startText, endText);
//
//        auto it = text.begin();
//        parseIt(grammar, it, text.end());
    }
}
MY_NSP_END
