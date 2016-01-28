/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Logger.hpp"
#include <boost/make_shared.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define MODULE_NAME MainWindow

#include "macros.fgen.hpp"

MY_NSP_START
{
    connection::Logger::CProviderSPtr connection::Logger::create()
    {
        return boost::make_shared<app::impl::Logger>();
    }
}
MY_NSP_END

