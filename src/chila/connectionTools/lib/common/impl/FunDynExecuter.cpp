/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FunDynExecuter.hpp"

#include <chila/lib/misc/macrosExp.hpp>


#include "macros.fgen.hpp"

#define MODULE_NAME FunDynExecuter


MY_NSP_START
{
    void FunDynExecuter::MOD_ACTION_SIG(execute)
    {
        executerMap.execute(funPath, arguments);
    }

    connection::FunDynExecuter::CProviderUPtr connection::FunDynExecuter::create(
        const std::string &instanceName, const lib::other::dynFunExecuter::ExecuterMap &executerMap)
    {
        return std::make_unique<impl::FunDynExecuter>(instanceName, executerMap);
    }
}
MY_NSP_END


