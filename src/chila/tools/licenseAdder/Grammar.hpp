#ifndef CHILA_TOOLS_LICENSEADDER__GRAMMAR_HPP
#define CHILA_TOOLS_LICENSEADDER__GRAMMAR_HPP

//#define BOOST_SPIRIT_QI_DEBUG

#include "fwd.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
//#include <boost/spirit/repository/include/qi_iter_pos.hpp>
#include <boost/bind.hpp>

#define NAME_RULE(rule) BOOST_SPIRIT_DEBUG_NODE(rule)

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace bqi = boost::spirit::qi;
    namespace bascii = boost::spirit::ascii;
    namespace bphoenix = boost::phoenix;
//    namespace brepo = boost::spirit::repository;
    namespace bf = boost::fusion;

    template <typename Iterator>
    struct Grammar : boost::spirit::qi::grammar<Iterator, void()>
    {
        bool parsed = false;

        bqi::rule<Iterator, std::string()> begin;
        bqi::rule<Iterator, void()> content, start, license;

        Grammar(const Format &format) :
            Grammar::base_type(start, "start")
        {
            using bqi::lit;
            using bqi::lexeme;
            using bqi::no_skip;
            using bqi::on_error;
            using bqi::fail;
            using bqi::eps;
            using bqi::uint_;
            using bqi::alnum;
            using bqi::alpha;
            using bascii::char_;
            using bqi::eol;
            using bqi::eps;
            using bqi::omit;
            using bascii::string;
            using bphoenix::construct;
            using bphoenix::ref;

            using bphoenix::val;
            start = format.header >> (-license) [ bphoenix::ref(parsed) = true ];

            begin = *(char_ - format.start);
            content = *(char_ - format.end);
            license =  format.start >> content >> format.end;

            NAME_RULE(start);
            NAME_RULE(begin);
            NAME_RULE(content);
            NAME_RULE(license);
        }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
