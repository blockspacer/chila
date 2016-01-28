/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_TUT__UTIL_HPP
#define CHILA_LIB_TUT__UTIL_HPP

#include <tut/tut.hpp>
#include <stdlib.h>
#include <sstream>

#include "nspDef.hpp"

MY_NSP_START
{
    struct CheckPoint
    {
        const char *file;
        unsigned line;

        CheckPoint() : file(""), line(0) {}

        void set(const char *file, unsigned line)
        {
            this->file = file;
            this->line = line;
        }
    };

    inline CheckPoint &checkPoint()
    {
        static CheckPoint ret;
        return ret;
    }

    template <typename LHS, typename RHS>
    inline void ensureEqual(const char *lhsStr, const LHS &lhs, const RHS &rhs)
    {
        if (lhs == rhs)
        {
            if (lhs != rhs) ::tut::fail("'lhs' == 'rhs' but also 'lhs' != 'rhs'");
        }
        else if (lhs != rhs)
        {
            if (lhs == rhs) ::tut::fail("'lhs' != 'rhs' but also 'lhs' == 'rhs'");
            std::stringstream str;
            str << "'" << lhsStr << "' : expected '" << rhs << "', actual '" << lhs << "'";
            ::tut::fail(str.str().c_str());
        }
    }
}
MY_NSP_END

#include "nspUndef.hpp"


#endif
