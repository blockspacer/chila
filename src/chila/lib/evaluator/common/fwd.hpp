/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_COMMON__FWD_HPP
#define CHILA_LIB_EVALUATOR_COMMON__FWD_HPP

#include <chila/lib/evaluator/expression/expression.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <chila/lib/evaluator/expression/defMacros.hpp>

#define def_type(Name, type) \
    typedef py::com::personal::lib::evaluator::expression::ValueBase<type> Name##Value;         \
    typedef py::com::personal::lib::evaluator::expression::Evaluable<type> Name##Evaluable;     \
    FWDEC_SPTR(Name##Value)


#include "nspDef.hpp"

MY_NSP_START
{
    def_type(Boolean, bool);
    def_type(Numeric, double);
    def_type(String, std::string);
}
MY_NSP_END

#include "nspUndef.hpp"
#undef def_type

#endif
