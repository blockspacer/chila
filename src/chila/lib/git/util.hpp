/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_GIT__UTIL_HPP
#define CHILA_LIB_GIT__UTIL_HPP

#include "fwd.hpp"
#include <git2.h>
#include <functional>

#include "nspDef.hpp"

MY_NSP_START
{
    using StatusFun = std::function<int(const char *path, unsigned statusFlags)>;

    void check(int error, const char *msg = nullptr);

    void statusForEach(git_repository &repo, const StatusFun &fun);
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
