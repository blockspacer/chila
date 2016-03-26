/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_LIB__TEXTEDITORDATA_HPP
#define CHILA_CODEX_TEXT_LIB__TEXTEDITORDATA_HPP

#include <chila/lib/misc/util.hpp>
#include "../app/impl/connection/TextEditor.hpp"
#include <chila/codex/base/lib/macrosExp.hpp>
#include "../app/impl/connection/types.hpp"
#include <chila/lib/qt/SigConn.hpp>
#include "BufferAction.hpp"
#include <boost/any.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class TextEditorData
    {
        public:
            using FileIdSCPtr = app::impl::connection::TextEditor::FileIdSCPtr;
//            using TextTagPtr = Glib::RefPtr<Gtk::TextTag>;
//            using Checks = app::impl::connection::FindReplaceChecks;
//
            const FileIdSCPtr id;
            std::string type;
            QObject &textArea;
            boost::any eventExecuter;
//
//            Gtk::TextView &textView = clGtkmm::makeManagedRef<Gtk::TextView>();
            bool isClosing = false;
//            TextTagPtr highlightTag = createTag(1, 1, 0),
//                       selFindTag = createTag(.9, .9, .9);
//
//            struct QtSigConns
//            {
//                std::shared_ptr<clQt::SigConn0> textChanged;
//            } qtSigConns;
////
//            CHILA_LIB_MISC__NAMED_TUPLE
//            (
//                FindData, 0,
//                ((std::string)(text))
//                ((Checks)(checks))
//                ((unsigned)(selBegin))
//                ((unsigned)(selEnd))
//            ) findData = { "", { false, false, false, false, false, false, false, false }, 0, 0 };
//
//            using ModifyTextFun = boost::function<bool(unsigned pos, BufferAction &action)>;
//
//
            TextEditorData(FileIdSCPtr id, std::string type, QObject &textArea, boost::any eventExecuter);
//
//            void addAction(BufferAction::Type type, unsigned pos, const Glib::ustring &text, const ModifyTextFun &modifyText);
//
//            BufferActionGroup &addActionGroup()
//            {
//                auto action = std::make_shared<BufferActionGroup>();
//                addAction(action);
//                return *action;
//            }
//
//            void undo();
//            void redo();
//            void clearActions();
//
//
            std::string getContents() const;
            void setContents(const std::string &text);
//
            void setOriginalContents()      { originalContents = getContents(); }
            bool isOriginalContents() const { return getContents() == originalContents; }
//
//            Gtk::TextIter insertText(const Gtk::TextIter &it, const std::string &text);
//            Gtk::TextIter eraseText(const Gtk::TextIter &begin, const Gtk::TextIter &end);
//            std::pair<Gtk::TextIter, Gtk::TextIter> replace(const Gtk::TextIter &begin, const Gtk::TextIter &end, const std::string &text);
//
//            void addPredefinedTags();
//
//        private:
//            BufferActionList bActionList;
//            BufferActionList::iterator bActionIt = bActionList.end();
            std::string originalContents;
//
//            void addAction(const BufferActionBaseSPtr &action);
//            static TextTagPtr createTag(double red, double green, double blue);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
