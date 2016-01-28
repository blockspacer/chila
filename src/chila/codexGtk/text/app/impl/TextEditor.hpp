/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL__TEXTEDITOR_HPP
#define CHILA_CODEX_TEXT_APP_IMPL__TEXTEDITOR_HPP

#include "connection/TextEditor.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/iterator_range.hpp>
#include "../../lib/TextEditorData.hpp"
#include <gtkmm.h>
#include <boost/bind.hpp>
#include "../../../common/ModActions.hpp"
#include <ctype.h>


#define MODULE_NAME TextEditor

#include "macros.fgen.hpp"

MY_NSP_START
{
    class TextEditor final: public connection::TextEditor::CProvider
    {
        public:
            using CreateFileIdFun = connection::TextEditor::CreateFileIdFun;
            using PostFun = connection::TextEditor::PostFun;

            TextEditor(module_args_ex);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate)    { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)        { execute_event(launcher_finished)(); }

            void MOD_ACTION_SIG(newEditor);
            void MOD_ACTION_SIG(openEditor);
            void MOD_ACTION_SIG(addText);
            void MOD_ACTION_SIG(applyTags);
            void MOD_ACTION_SIG(saveEditorContents_current);
            void MOD_ACTION_SIG(saveEditorContents_as);
            void MOD_ACTION_SIG(saveAll);
            void MOD_ACTION_SIG(openingDone);
            void MOD_ACTION_SIG(savingDone);
            void MOD_ACTION_SIG(undo);
            void MOD_ACTION_SIG(redo);
            void MOD_ACTION_SIG(fileSelected);
            void MOD_ACTION_SIG(editorTypeChanged);
            void MOD_ACTION_SIG(closingEditor);
            void MOD_ACTION_SIG(closingSelectedEditor);
            void MOD_ACTION_SIG(findReplace_start);
            void MOD_ACTION_SIG(findReplace_findPrevious);
            void MOD_ACTION_SIG(findReplace_findNext);
            void MOD_ACTION_SIG(findReplace_replace);
            void MOD_ACTION_SIG(findReplace_replaceAll);
            void MOD_ACTION_SIG(findReplace_stateChanged);
            void MOD_ACTION_SIG(findReplace_restoreFind) {}

        private:
            using FileIdSCPtr = connection::TextEditor::FileIdSCPtr;
            using BufferRange = connection::BufferRange;
            using GtkTTagSet = std::set<std::string>;
            using Data = lib::TextEditorData;
            using Checks = connection::FindReplaceChecks;
            using GtkActionPtr = Glib::RefPtr<Gtk::Action>;

            using GtkTextBufferPtr = Glib::RefPtr<Gtk::TextBuffer>;

            using DataMap = std::map<FileIdSCPtr, Data>;

            CreateFileIdFun createFileIdFun;

            ccCommon::ModActions modActions;
            bool savingAll = false;

            unsigned nextId = 0;

            static constexpr unsigned tabSize = 4;

            DataMap dataMap;
            DataMap::iterator currDataIt = dataMap.end();
            DataMap::iterator savingDataIt = dataMap.end();
            PostFun postFun;

            Data &getData(const FileIdSCPtr &fileId);
            Data *getCurrData();

            template <typename EventExecuter>
            void openEditorPrv(const FileIdSCPtr &fileId, const bfs::path &fileName, const std::string &parserId, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void parseTextPrv(const Data &data, const EventExecuter &eventExecuter) const;

            template <typename EventExecuter>
            void saveEditorContents(const Data &data, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void contentsModified(Data &data, const EventExecuter &eventExecuter);

            void indentSelection(Data &data, int indCount);

            void addInsertAction(Data &data, unsigned posNum, const std::string &text);
            void addEraseAction(Data &data, unsigned posNum, const std::string &text);

            template <typename EventExecuter>
            bool signalKeyPressEvent(Data &data, const GdkEventKey &event, const EventExecuter &eventExecuter);

            template <typename ReverseFun, typename JoinFun>
            bool find(Data &data, const ReverseFun &reverseFun, const JoinFun &joinFun);

            template <typename Range, typename ReverseFun>
            bool findRange(Data &data, const Range &range, const ReverseFun &reverseFun);

//            template <typename ReverseFun>
//            bool findSelection(Data &data, const ReverseFun &reverseFun);

            template <typename EventExecuter>
            bool findPrevious(Data &data, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            bool findNext(Data &data, const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            bool findReplace(Data &data, const std::string &replaceText, const EventExecuter &eventExecuter);

            void findHighlight(Data &data);

            template <typename Range, typename Text, typename Compare, typename Deref>
            auto search(
                const Range &range,
                const Text &text,
                const Compare &compare,
                const Deref &deref,
                bool wholePhrase) -> decltype(boost::make_iterator_range(range.begin(), range.end()));

            void createAction(
                ccCommon::ActionDataList aList,
                const GtkActionPtr &action,
                const Gtk::AccelKey &aKey);

            void createAction(
                ccCommon::ActionDataList aList,
                const std::string &name,
                const std::string &label,
                const std::string &tooltip,
                const Gtk::BuiltinStockID &id,
                const Gtk::AccelKey &aKey);

            template <typename EventExecuter>
            void registerActions(const EventExecuter &eventExecuter);

            template <typename EventExecuter>
            void closingEditorPrv(Data &data, const EventExecuter &eventExecuter);
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

