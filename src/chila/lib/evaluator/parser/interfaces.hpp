/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__INTERFACES_HPP
#define CHILA_LIB_EVALUATOR_PARSER__INTERFACES_HPP

#include "fwd.hpp"
#include <string>
#include <chila/lib/evaluator/expression/fwd.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    struct IExpressionProvider
    {
        virtual expression::ValueSCPtr createNumericValue(double val) const = 0;
        virtual expression::ValueSCPtr createBooleanValue(bool val) const = 0;
        virtual expression::ValueSCPtr createStringValue(const std::string &val) const = 0;
        virtual expression::OperationSCPtr createOperation(const std::string &name,
            const expression::ArgumentListSCPtr &aList) const = 0;

        virtual ~IExpressionProvider() {}
    };

    template <typename Iterator>
    struct IParser
    {
        virtual expression::ExpressionSCPtr parse(Iterator begin, Iterator end,
            const expression::ValueMap &vMap) const = 0;
        virtual ~IParser() {}
    };

}
MY_NSP_END

#include "nspUndef.hpp"

#endif
