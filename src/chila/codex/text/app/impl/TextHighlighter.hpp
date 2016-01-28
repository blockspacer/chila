/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL__TEXTHIGHLIGHTER_HPP
#define CHILA_CODEX_TEXT_APP_IMPL__TEXTHIGHLIGHTER_HPP

#include "connection/TextHighlighter.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>

#include <boost/bind.hpp>
#include <ctype.h>
#include <boost/type_index.hpp>
#include <srchilite/sourcehighlight.h>
#include <srchilite/langmap.h>
#include <srchilite/langdefmanager.h>
#include <srchilite/regexrulefactory.h>
#include <srchilite/formattermanager.h>
#include <srchilite/formatterparams.h>
#include <srchilite/sourcehighlighter.h>

#define MODULE_NAME TextHighlighter

#include "macros.fgen.hpp"

MY_NSP_START
{
    class TextHighlighter final: public connection::TextHighlighter::CProvider
    {
        public:
            TextHighlighter(module_args_ex);

            void MOD_ACTION_SIG(launcher_start)         { execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate)    { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)        { execute_event(launcher_finished)(); }

            void MOD_ACTION_SIG(parseText);

       private:
//            using Iterator = const char*;
//            using ITRange = boost::iterator_range<Iterator>;
//
//            CHILA_LIB_MISC__FWDEC_TYPE(Formatter);
//            CHILA_LIB_MISC__FWDEC_TYPE(ParseData);
//
//            using FormatterMap = std::map<std::string, FormatterSPtr>;
//            using ParseDataMap = std::map<std::string, ParseDataSPtr>;
//
//            connection::TextTagSet textTags;
//            connection::TagApplyList tagApplyList;
//            Iterator parseBegin;
//            std::size_t offset;
//
//            FormatterMap formatterMap;
//            ParseDataMap parseDataMap;
//
//            struct ParseData
//            {
//                TextHighlighter &textHighligther;
//                srchilite::RegexRuleFactory ruleFactory;
//                srchilite::LangDefManager langDefManager;
//                srchilite::HighlightStatePtr state;
//                srchilite::FormatterManager formatterManager;
//                srchilite::FormatterParams params;
//
//                ParseData(TextHighlighter &textHighligther, const std::string &file);
//
//                void parse(const connection::BufferRange &textBuffer);
//            };
//
//
//            void addFormatter(const std::string &name);
//
//            void addParseData(const std::string &name);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

