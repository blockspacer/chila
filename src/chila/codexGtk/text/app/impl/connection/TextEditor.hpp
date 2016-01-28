/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TEXTEDITOR_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TEXTEDITOR_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "types.hpp"
#include <gtkmm.h>
#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/TextEditor.hpp"
#include <boost/asio/io_service.hpp>
#include <chila/lib/misc/ValueStreamer.hpp>
#include "../../../lib/fwd.hpp"
#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__MODULE_PARAMS_TextEditor \
    ((const std::string&)(instanceName)) \
    ((const CreateFileIdFun&)(createFileIdFun)) \
    ((const PostFun&)(postFun))

#define MODULE_NAME TextEditor

MY_NSP_START
{
    struct TextEditor
    {
        struct FileId : public virtual clMisc::ValueStreamer::Streamable
        {
            virtual bool operator<(const FileId &id) const { return this < &id; }
            virtual ~FileId() {}
        };

        CHILA_LIB_MISC__FWDEC_SPTR(FileId);

        struct ArgTypes
        {
            using fileName                  = bfs::path;
            using notebook_tabName          = std::string;
            using notebook_tabTooltip       = std::string;
            using notebook_tabWidget        = Gtk::Widget*;
            using errorMsg                  = std::string;
            using fileId                    = FileIdSCPtr;
            using textBuffer                = BufferRange;
            using tags                      = TextTagSet;
            using tagsToApply               = TagApplyList;
            using parserId                  = std::string;
            using findReplace_findText      = std::string;
            using findReplace_replaceText   = std::string;
            using findReplace_checks        = FindReplaceChecks;
            using action_path               = clMisc::Path;
            using action_dataList           = ccCommon::ActionDataList;
            using action_object             = Glib::RefPtr<Gtk::Action>;
        };

        DEF_CPROVIDER;

        using CreateFileIdFun = boost::function<FileIdSCPtr()>;
        using PostFun = std::function<void(const std::string &from, const std::function<void()> &fun)>;

        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#undef MODULE_NAME
#include "macros.fgen.hpp"

#endif
