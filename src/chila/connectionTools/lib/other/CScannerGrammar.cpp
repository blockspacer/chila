/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#include "CScannerGrammar.hpp"
//#include <fstream>
//#include <iterator>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>
//
//CHILA_LIB_MISC__DEF_NAMESPACE(4, (chila,connectionTools,lib,other))
//{
//    void parseFile(const boost::filesystem::path &file, chila::flow::lib::CompletionList &cList)
//    {
//        typedef std::istreambuf_iterator<char> BasicIterator;
//        typedef boost::spirit::multi_pass<BasicIterator> Iterator;
//        CScannerGrammar<Iterator> grammar(cList);
//
//        std::ifstream iFile;
//
//        iFile.exceptions(std::ios::badbit | std::ios::failbit);
//        iFile.open(file.c_str());
//
//        Iterator it = boost::spirit::make_default_multi_pass(BasicIterator(iFile)),
//                      end = boost::spirit::make_default_multi_pass(BasicIterator());
//
//        bool r = boost::spirit::qi::phrase_parse(it, end, grammar, boost::spirit::ascii::space);
//
//        if (!r)
//        {
//            BOOST_THROW_EXCEPTION(ParseError("could not parse file '" + file.string() + "'"));
//        }
//        else if (it != end)
//        {
//            BOOST_THROW_EXCEPTION(ParseError("file '" + file.string() + "' was not totally parsed"));
//        }
//    }
//}}}}
//
