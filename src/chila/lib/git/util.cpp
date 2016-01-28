/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "exceptions.hpp"
#include <iostream>

#include "nspDef.hpp"

MY_NSP_START
{
    void check(int error, const char *msg)
    {
        if (error)
            BOOST_THROW_EXCEPTION(Exception(msg ? msg : "", error));
    }

    int status_cb(const char *path, unsigned statusFlags, void *fun)
    {
        return (*reinterpret_cast<const StatusFun*>(fun))(path, statusFlags);
    }

    void statusForEach(git_repository &repo, const StatusFun &fun)
    {
        git_status_options options = {0};

        options.version = GIT_STATUS_OPTIONS_VERSION;
        options.show = GIT_STATUS_SHOW_WORKDIR_ONLY;
        options.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED | GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

        check(git_status_foreach_ext(&repo, &options, status_cb, reinterpret_cast<void*>(const_cast<StatusFun*>(&fun))));
    }

}
MY_NSP_END

