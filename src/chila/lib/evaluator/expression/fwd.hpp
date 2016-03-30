/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_EXPRESSION__FWD_HPP
#define CHILA_LIB_EVALUATOR_EXPRESSION__FWD_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <chila/lib/misc/exceptions.hpp>

#define DEF_RUNTIME_ERROR_WT CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT

#include "nspDef.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__FWDEC_TYPE(Expression);
    CHILA_LIB_MISC__FWDEC_TYPE(Operation);
    CHILA_LIB_MISC__FWDEC_TYPE(OperationProvider);
    CHILA_LIB_MISC__FWDEC_TYPE(OperationProviderMap);
    CHILA_LIB_MISC__FWDEC_TYPE(VariableProvider);
    CHILA_LIB_MISC__FWDEC_TYPE(VariableProviderMap);
    CHILA_LIB_MISC__FWDEC_TYPE(ValueMap);
    CHILA_LIB_MISC__FWDEC_TYPE(Value);
    CHILA_LIB_MISC__FWDEC_TYPE(Variable);

    DEF_RUNTIME_ERROR_WT(VariableProviderAleradyExists, "variable provider already exists");
    DEF_RUNTIME_ERROR_WT(VariableProviderDoesNotExists, "variable provider does not exists");
    DEF_RUNTIME_ERROR_WT(ValueNotSet, "value not set");
    DEF_RUNTIME_ERROR_WT(InvalidValue, "invalid value");
    DEF_RUNTIME_ERROR_WT(OperationProviderDoesNotExists, "operation provider does not exists");
    DEF_RUNTIME_ERROR_WT(IncompatibleArgumentList, "incompatible argument list");

    typedef std::vector<ExpressionSCPtr> ArgumentList;
    CHILA_LIB_MISC__FWDEC_SPTR(ArgumentList);

    template <typename Type>
    struct ValueBase;

    template <typename Type>
    struct VariableBase;

    template <typename Ret>
    struct Evaluable;

}
MY_NSP_END

#include "nspUndef.hpp"

#undef DEF_RUNTIME_ERROR_WT
#endif

