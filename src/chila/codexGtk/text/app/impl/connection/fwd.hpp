/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FWD_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FWD_HPP

#include "../fwd.hpp"
#include <boost/range.hpp>
#include <gtkmm.h>

#include "macros.fgen.hpp"

MY_NSP_START
{
    using BufferRange = boost::iterator_range<const char*>;
    using GtkTextTagPtr = Glib::RefPtr<Gtk::TextTag>;

    CHILA_LIB_MISC__FWDEC_TYPE(FileId);
    CHILA_LIB_MISC__FWDEC_TYPE(TagApply);
    CHILA_LIB_MISC__FWDEC_TYPE(TextTag);

    using TagApplyList = std::vector<TagApply>;
    using TextTagSet = std::set<TextTag>;
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
