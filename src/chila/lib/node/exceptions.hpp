/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__EXCEPTIONS_HPP
#define CHILA_LIB_NODE__EXCEPTIONS_HPP

#include "fwd.hpp"
#include <type_traits>
#include <chila/lib/misc/exceptions.hpp>
#include <boost/make_shared.hpp>

#define DEF_RUNTIME_ERROR_WT            CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT
#define DEF_RUNTIME_ERROR_FROM_BASE     CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE

#include "nspDef.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR(Exception);

    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ChildAlreadyExists, "child already exists");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ChildDoesNotExists, "child does not exists");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, NodeNotFound, "node not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, InvalidChildType, "invalid child type");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, InvalidNode, "invalid node");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, NodeNotCloneable, "node not cloneable");

    struct ExceptionWrapper: public Exception
    {
        std::shared_ptr<std::exception> ex;

        ExceptionWrapper(const ExceptionWrapper &ex) = default;
        template <typename ExType>
        ExceptionWrapper(const ExType &rhs, typename std::enable_if<std::is_same<ExceptionWrapper, ExType>::value == false>::type *v = nullptr) :
            Exception("wrapper"), ex(std::make_shared<ExType>(rhs))
        {
        }
    };

    struct CheckExceptionList: public Exception
    {
        using ExcSPtr = std::shared_ptr<std::exception>;
        using ExceptionVec = std::vector<ExcSPtr>;
        ExceptionVec exceptions;

        CheckExceptionList() : Exception("check exception list") {}

        void add(const ExcSPtr &ex)
        {
            exceptions.push_back(ex);
        }

        template <typename ExType>
        void add(const ExType &ex)
        {
            exceptions.push_back(std::make_shared<ExType>(ex));
        }

        void add(const CheckExceptionList &ex)
        {
            for (auto &item : ex.exceptions)
            {
                exceptions.push_back(item);
            }
        }

        ~CheckExceptionList() throw() {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"


#undef DEF_RUNTIME_ERROR_WT
#undef DEF_RUNTIME_ERROR_FROM_BASE
#endif
