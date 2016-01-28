/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_GTKMM__UTIL_HPP
#define CHILA_LIB_GTKMM__UTIL_HPP

#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <gtkmm.h>
#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type, typename... Arg>
    inline Type *makeManaged(Arg&& ...arg)
    {
        return chila::lib::misc::checkNotNull(Gtk::manage(new Type(std::forward<Arg>(arg)...)));
    }

    template <typename Type, typename... Arg>
    inline Type &makeManagedRef(Arg&& ...arg)
    {
        return chila::lib::misc::deref(Gtk::manage(new Type(std::forward<Arg>(arg)...)));
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
