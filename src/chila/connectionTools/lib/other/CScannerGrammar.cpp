/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.other'
 *
 * 'chila.connectionTools.lib.other' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.other' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.other'. If not, see <http://www.gnu.org/licenses/>.
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
