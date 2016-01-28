/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_LIB__FWD_HPP
#define CHILA_CODEX_TEXT_LIB__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <gtkmm.h>

#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__FWDEC_TYPE(Color);
    CHILA_LIB_MISC__FWDEC_TYPE(BufferActionBase);
    CHILA_LIB_MISC__FWDEC_TYPE(BufferAction);
    CHILA_LIB_MISC__FWDEC_TYPE(BufferActionGroup);


    using ColorMap = std::map<std::string, Color>;
    using ExtensionFTypeMap = std::map<std::string, std::string>;
    using GtkTextBufferPtr = Glib::RefPtr<Gtk::TextBuffer>;
    using BufferActionList = std::vector<BufferActionBaseSPtr>;
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
