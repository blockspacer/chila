/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__CPDATATYPES_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__CPDATATYPES_HPP

#include "types.hpp"
#include "TextEditor.hpp"
#include "FileOpener.hpp"
#include "TextHighlighter.hpp"
#include "FindReplace.hpp"
#include "../../../../base/app/impl/connection/CPDataTypes.hpp"
#include "../../../lib/types.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct FileId :
        public TextEditor::FileId,
        public FileOpener::FileId,
        public TextHighlighter::TextId,
        public base::app::impl::connection::TabId
    {
    };

    struct CPDataTypes
    {
        using fileName                  = bfs::path;
        using notebook_tabName          = std::string;
        using notebook_tabTooltip       = std::string;
        using notebook_tabWidget        = QObject*;
        using fileId                    = FileIdSCPtr;
        using textBuffer                = BufferRange;
        using tags                      = TextTagSet;
        using tagsToApply               = TagApplyList;
        using parserId                  = std::string;
        using findReplace_findText      = std::string;
        using findReplace_replaceText   = std::string;
        using findReplace_checks        = FindReplaceChecks;
        using action_path               = clMisc::Path;
        using action_pathDataList           = ccCommon::ActionPathDataList;
        using action_data               = ccCommon::ActionData;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

