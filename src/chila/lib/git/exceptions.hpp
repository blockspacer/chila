/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_GIT__EXCEPTIONS_HPP
#define CHILA_LIB_GIT__EXCEPTIONS_HPP

#include "fwd.hpp"
#include <stdexcept>

#include <boost/exception/all.hpp>
#include "nspDef.hpp"

MY_NSP_START
{
    struct Exception : public std::runtime_error, public boost::exception
    {
        int error, klass;

        Exception(const std::string &msg, int error) : std::runtime_error(getError(msg, error)), error(error)
        {
        }

        std::string getError(const std::string &msg, int error);

        ~Exception() throw() {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
