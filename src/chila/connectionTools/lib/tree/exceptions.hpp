/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__EXCEPTIONS_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__EXCEPTIONS_HPP

#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <stdexcept>
#include <string>
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

#define DEF_RUNTIME_ERROR       CHILA_LIB_MISC__DEF_RUNTIME_ERROR
#define DEF_EXCEPTION           CHILA_LIB_MISC__DEF_EXCEPTION
#define DEF_RUNTIME_ERROR_WT            CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT
#define DEF_RUNTIME_ERROR_FROM_BASE     CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE

#include "nspDef.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_RUNTIME_ERROR(Exception);

    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorNotFound, "connector not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ConnectorInstanceNotFound, "connector instance not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, CPerformerNotFound, "connector performer not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, NodeNotFound, "node not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, NodeAlreadyExists, "node already exists");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, ArgumentProviderCreatorNotUsed, "argument provider creator not used");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, AProviderCreatorNotFound, "argument provider creator not found");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, UniqueArgumentRequiredMoreThanOnce, "unique argument required more than once");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, CInstanceReqCycle, "connector instance init requirement cycle");
    DEF_RUNTIME_ERROR_FROM_BASE(Exception, DescriptionIsEmpty, "description is empty");

    struct ErrorInfo
    {
        using Message = boost::error_info<struct tag_msg, std::string>;
        using ReferencePath = boost::error_info<struct tag_reference_path, chila::lib::misc::Path>;
        using ReqProvVec = boost::error_info<struct tag_req_prov_vec, ReqProvVector>;
        using AInsVecInfo = boost::error_info<struct tag_req_data, AInsVec>;
    };

    struct RequiredArgumentNotFound final: public Exception
    {
        chila::lib::misc::Path arg;
        RequiredArgumentNotFound(chila::lib::misc::Path arg) :
            Exception("required argument not found: " + arg.getStringRep(":")), arg(rvalue_cast(arg)) {}
        ~RequiredArgumentNotFound() throw() {}
    };

    struct RequiredArgumentProvidedManyTimes final: public Exception
    {
        chila::lib::misc::Path arg;
        RequiredArgumentProvidedManyTimes(chila::lib::misc::Path arg) :
            Exception("required argument provided many times: " + arg.getStringRep(":")), arg(rvalue_cast(arg)) {}
        ~RequiredArgumentProvidedManyTimes() throw() {}
    };


//    struct InvalidReference final: public Exception
//    {
//        libMisc::Path path;
//
//        InvalidReference(const libMisc::Path &path) : path(path) {}
//        const char *what() const throw() { return "invalid reference"; }
//        std::string message() const { return what() + (": " + path.getStringRep()); }
//        ~InvalidReference() throw() {}
//
//        ExceptionSPtr cloneMe() const { return std::make_shared<InvalidReference>(*this); }
//    };

}
MY_NSP_END

#include "nspUndef.hpp"

#undef DEF_RUNTIME_ERROR_WT
#undef DEF_RUNTIME_ERROR_FROM_BASE

#undef DEF_RUNTIME_ERROR
#undef DEF_MY_EXCEPTION


#endif

