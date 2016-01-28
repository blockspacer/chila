/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__CSCANNERGRAMMAR_HPP
//#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CSCANNERGRAMMAR_HPP
//
//#include <chila/flow/lib/fwd.hpp>
//#include "fwd.hpp"
//#include <chila/lib/misc/Path.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include "exceptions.hpp"
//#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
//#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/spirit/include/phoenix_fusion.hpp>
//#include <boost/spirit/include/phoenix_stl.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
//#include <chila/flow/lib/types.hpp>
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define NAME_RULE(rule) rule.name(#rule)
//#define SHOW    CHILA_LIB_MISC__SHOW
//
//#include "macros.fgen.hpp"
//
//MY_NSP_START
//{
//    namespace bqi = boost::spirit::qi;
//    namespace bascii = boost::spirit::ascii;
//    namespace bphoenix = boost::phoenix;
//
//    template <typename Iterator>
//    struct CScannerGrammar : boost::spirit::qi::grammar<Iterator, void(), bascii::space_type>
//    {
//        chila::flow::lib::CompletionList &cList;
//        chila::lib::misc::Path path;
//
//        void add(const std::string &ac, unsigned per) const
//        {
//            cList.add(ac, chila::node::typed::Float::create(per / float(100)));
//        }
//
//        CScannerGrammar(chila::flow::lib::CompletionList &cList) : CScannerGrammar::base_type(file, "file"), cList(cList)
//        {
//            using bqi::lit;
//            using bqi::lexeme;
//            using bqi::on_error;
//            using bqi::fail;
//            using bqi::eps;
//            using bqi::uint_;
//            using bqi::alnum;
//            using bqi::alpha;
//            using bascii::char_;
//            using bascii::string;
//            using namespace bqi::labels;
//            using bphoenix::construct;
//            using bphoenix::bind;
//            using bphoenix::ref;
//
//            using bphoenix::val;
//
//            identifier %= lexeme[(alpha | '_') >> *(alnum | '_')];
//
//            percentage %= "/*" > uint_ > "%" > "*/";
//
//            word = lexeme[+(char_ - ' ')];
//
//            action_prefix = lexeme[+(char_ - ' ' - ':')] >> "::";
//
//            action_sig %= -action_prefix >> lit("MOD_ACTION_SIG(") > identifier > ")";
//
//            completion = (action_sig >> percentage) [ bind(&CScannerGrammar<Iterator>::add, this, bqi::_1, bqi::_2) ];
//
//            file = *(completion | word);
//
//            on_error<fail>
//            (
//                file
//              , std::cout
//                    << val("Error! Expecting ")
//                    << _4                               // what failed?
//                    << val(" here: \"")
//                    << construct<std::string>(_3, _2)   // iterators to error-pos, end
//                    << val("\"")
//                    << std::endl
//            );
//
//            NAME_RULE(file);
//            NAME_RULE(action_sig);
//            NAME_RULE(identifier);
//            NAME_RULE(percentage);
//            NAME_RULE(completion);
//            NAME_RULE(word);
//            NAME_RULE(action_prefix);
//        }
//
//        bqi::rule<Iterator, void(), bascii::space_type> file;
//        bqi::rule<Iterator, std::string(), bascii::space_type> action_sig;
//        bqi::rule<Iterator, std::string(), bascii::space_type> identifier;
//        bqi::rule<Iterator, unsigned(), bascii::space_type> percentage;
//        bqi::rule<Iterator, void(), bascii::space_type> completion;
//        bqi::rule<Iterator, void(), bascii::space_type> word;
//        bqi::rule<Iterator, void(), bascii::space_type> action_prefix;
//    };
//
//
//}
//MY_NSP_END
//
//#include "macros.fgen.hpp"
//
//#endif
//
//#undef NAME_RULE
//#undef SHOW
//
