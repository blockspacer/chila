/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Application.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>


#define MODULE_NAME Application

#include "macros.fgen.hpp"

MY_NSP_START
{
    connection::Application::CProviderUPtr connection::Application::create(const std::string &instanceName)
    {
        return std::make_unique<impl::Application>(instanceName);
    }
}
MY_NSP_END
