/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <git2.h>
#include <chila/lib/misc/util.hpp>
#include "exceptions.hpp"
#include "nspDef.hpp"

MY_NSP_START
{
    std::string Exception::getError(const std::string &msg, int error)
    {
        if (auto e = giterr_last())
        {
            klass = e->klass;
            return msg.empty() ? e->message : msg + ": " + e->message;
        }

        return msg;
    }
}
MY_NSP_END

