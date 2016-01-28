/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__PARSER_HPP
#define CHILA_LIB_EVALUATOR_PARSER__PARSER_HPP

#include "Grammar.hpp"
#include "interfaces.hpp"
#include <chila/lib/evaluator/expression/expression.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Iterator>
    class Parser final: public IParser<Iterator>
    {
        private:
            mutable Grammar<Iterator> g;

        public:
            Parser(const IExpressionProviderSCPtr &expProvider, bool optimize) :
                g(expProvider, optimize) {}

            expression::ExpressionSCPtr parse(Iterator begin, Iterator end,
                const expression::ValueMap &vMap) const
            {
                expression::ExpressionSCPtr ret;
                g.valueMap = &vMap;
                bool r = boost::spirit::qi::phrase_parse(begin, end, g, boost::spirit::ascii::space, ret);

                if (!r || begin != end) throw ParseError();
                return ret;
            }
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
