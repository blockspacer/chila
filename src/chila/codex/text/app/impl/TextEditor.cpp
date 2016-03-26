/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "TextEditor.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>

#include <chila/lib/misc/util.hpp>
#include <fstream>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/detail/range_return.hpp>
#include "connection/CPDataTypes.hpp"
#include "../../../base/lib/macrosExp.hpp"
#include "chila/lib/misc/RepeatText.hpp"
#include <boost/range/join.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <chila/lib/misc/iter_iterator_val.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <chila/lib/qt/util.hpp>
#include <iostream>
#include <cctype>

#define MODULE_NAME TextEditor

#include "macros.fgen.hpp"

#define get_curr_data \
    auto *_data = getCurrData(); \
    if (!_data) return; \
    auto &data = *_data

#define my_connect_signal_ntf_ptr(object, name) \
    data.slots.object.signal_##name = object->signal_##name().connect_notify

#define my_connect_signal_ntf_ref(object, name) \
    data.slots.object.signal_##name = object.signal_##name().connect_notify

#define my_connect_signal_ref(object, name) \
    data.slots.object.signal_##name = object.signal_##name().connect

#define dec_rev_range \
    auto begin = buffer->begin(); \
    auto pos = buffer->get_iter_at_offset(buffer->property_cursor_position()); \
    auto range = boost::make_iterator_range(begin, pos); \
    auto revRange = range | boost::adaptors::reversed

#define show_range(range) showRange(#range, range)
#define show_range_ind(range) showRange(#range, range | boost::adaptors::indirected)

#define key_press_event_case(left, right) \
        case right: \
            postFun("textView.signal_key_press_event()", [this, event, &data, eventExecuter] \
            { \
                indentMatching(data.textView.get_buffer(), left, right); \
                contentsModified(data, eventExecuter); \
            }); \
            return true;

#define def_range_adaptor_fun(Name, ret) \
    struct Name##Range \
    { \
        template <typename Range> \
        auto operator()(const Range &range) const -> decltype(ret) \
        { \
            return ret; \
        } \
    }

#define def_join(ret) \
    { \
        template <typename RangePair> \
        auto operator()(const RangePair &rangePair) const -> decltype(ret) \
        { \
            return ret; \
        } \
    };

//CHILA_LIB_MISC__ENABLE_SIGC_RETURN_FROM_LAMBDA

MY_NSP_START
{
    using chila::lib::misc::rvalue_cast;
    constexpr unsigned BUFFER_SIZE = 655360;

    auto findSpaceNL = [](char c)
    {
        return c == ' ' || c == '\n';
    };

    auto findNonspaceNL = [](char c)
    {
        return c != ' ' || c == '\n';
    };

    template <typename Range>
    void showRange(const std::string &rangeName, const Range &range)
    {
        std::cout << rangeName << ": [";
        for (char c : range)
            std::cout << (c == ' ' ? '_' : c);

        std::cout << "]\n" << std::endl;
    }

    TextEditor::TextEditor(module_args_ex) :
        connection::TextEditor::CProvider(instanceName),
        qEngine(qEngine),
        createFileIdFun(createFileIdFun),
        textItemsComp(&qEngine, QUrl(QStringLiteral("qrc:/TextItems.qml"))),
        textItems(clMisc::deref(textItemsComp.create()))
    {
        connector.bindActions(*this);
    }

    void TextEditor::MOD_ACTION_SIG(launcher_start)
    {
        ccCommon::ActionPathDataList editAList = { { "edit", "Edit" } };

        execute_event(registerAction)(editAList, ccCommon::ActionData{"copy",         "Copy",             "Copies the text.",             "StandardKey.Copy"});
        execute_event(registerAction)(editAList, ccCommon::ActionData{"paste",        "Paste",            "Pastes the text.",             "StandardKey.Paste"});
        execute_event(registerAction)(editAList, ccCommon::ActionData{"cut",          "Cut",              "Cuts the text.",               "StandardKey.Cut"});
        execute_event(registerAction)(editAList, ccCommon::ActionData{"undo",         "Undo",             "Undoes the last operation.",   "StandardKey.Undo"});
        execute_event(registerAction)(editAList, ccCommon::ActionData{"redo",         "Redo",             "Redoes the last operator.",    "StandardKey.Redo" });
        execute_event(addSeparator)(editAList);
        execute_event(registerAction)(editAList, ccCommon::ActionData{"findReplace",  "Find & Replace",   "Find and replace text.",        "StandardKey.Find" });

        qtSigConns.textChanged = CHILA_LIB_QT__CONNECT_SIGNAL(textItems, textChanged, (this), (textAreaVar))
        {
            auto &textArea = clMisc::deref(textAreaVar.value<QObject*>());

            if (auto dataPtr = getDataPtr(textArea))
            {
                auto &data = *dataPtr;
                auto &eventExecuter = boost::any_cast<ev_executer_type(tabAdded)&>(data.eventExecuter);

                if (data.isOriginalContents())
                {
                    execute_event(contentsAreOriginal)(data.id);
                }
                else
                {
                    execute_event(contentsModified)(data.id);
                }
            }
        });

        execute_event(launcher_started)();
    }

    void TextEditor::MOD_ACTION_SIG(findReplace_start)
    {
//        get_curr_data;
//
//        auto buffer = data.textView.get_buffer();
//        if (!buffer->get_has_selection())
//            return;
//
//        Gtk::TextIter begin, end;
//        buffer->get_selection_bounds(begin, end);
//
//        execute_event(findReplace_setFindText)(std::string(begin, end));
    }

//
//    inline bool isEqual(char lhs, char rhs, bool matchCase)
//    {
//        return (matchCase && lhs == rhs) || (!matchCase && std::tolower(lhs) == std::tolower(rhs));
//    }
//
    void TextEditor::MOD_ACTION_SIG(findReplace_stateChanged)
    {
//        get_curr_data;
//        auto buffer = data.textView.get_buffer();
//        auto oldSelectionCheck = data.findData.checks.selection;
//
//        data.findData.text = findReplace_findText;
//        data.findData.checks = findReplace_checks;
//
//        if (!oldSelectionCheck && data.findData.checks.selection && buffer->get_has_selection())
//        {
//            Gtk::TextIter begin, end;
//            buffer->get_selection_bounds(begin, end);
//
//            data.findData.selBegin = std::distance(buffer->begin(), begin);
//            data.findData.selEnd = std::distance(buffer->begin(), end);
//        }
//        else if (!data.findData.checks.selection)
//        {
//            data.findData.selBegin = 0;
//            data.findData.selEnd = 0;
//        }
//
//        findHighlight(data);
    }
//
//    void TextEditor::findHighlight(Data &data)
//    {
//        auto buffer = data.textView.get_buffer();
//        auto range = boost::make_iterator_range(buffer->begin(), buffer->end());
//        auto &text = data.findData.text;
//        auto &checks = data.findData.checks;
//
//        buffer->remove_tag(data.highlightTag, buffer->begin(), buffer->end());
//        buffer->remove_tag(data.selFindTag, buffer->begin(), buffer->end());
//
//        if (checks.selection)
//        {
//            buffer->apply_tag
//            (
//                data.selFindTag,
//                buffer->get_iter_at_offset(data.findData.selBegin),
//                buffer->get_iter_at_offset(data.findData.selEnd)
//            );
//        }
//
//        if (text.size() && checks.highlightMatches)
//        {
//            auto compare = [&](char lhs, char rhs)  { return isEqual(lhs, rhs, checks.matchCase); };
//            auto deref =   [](char c)               { return c; };
//
//            while (true)
//            {
//                auto foundRange = search(range, text, compare, deref, checks.wholePhrase);
//
//                if (boost::empty(foundRange))
//                    break;
//
//                buffer->apply_tag(data.highlightTag, foundRange.begin(), foundRange.end());
//
//                range = boost::make_iterator_range(foundRange.end(), buffer->end());
//            }
//        }
//    }
//
//    template <typename Range, typename Text, typename Compare, typename Deref>
//    auto TextEditor::search(
//        const Range &range,
//        const Text &text,
//        const Compare &compare,
//        const Deref &deref,
//        bool wholePhrase) -> decltype(boost::make_iterator_range(range.begin(), range.end()))
//    {
//        auto foundBegin = boost::search(range, text, compare);
//        auto foundEnd = foundBegin;
//
//        if (foundBegin != range.end())
//        {
//            std::advance(foundEnd, text.size());
//
//            if (wholePhrase)
//            {
//                if (foundBegin != range.begin())
//                {
//                    auto foundBeginBefore = foundBegin;
//                    if (std::isalpha(deref(*--foundBeginBefore)))
//                        return boost::make_iterator_range(range.end(), range.end());
//                }
//
//                if (foundEnd != range.end())
//                {
//                    if (std::isalpha(deref(*foundEnd)))
//                        return boost::make_iterator_range(range.end(), range.end());
//                }
//            }
//        }
//
//        return boost::make_iterator_range(foundBegin, foundEnd);
//    }
//
//    template <typename Range, typename ReverseFun>
//    bool TextEditor::findRange(Data &data, const Range &range, const ReverseFun &reverseFun)
//    {
//        auto buffer = data.textView.get_buffer();
//        auto &text = data.findData.text;
//        auto &checks = data.findData.checks;
//
//        auto compare = [&](const Gtk::TextIter &lhs, char rhs)
//        {
//            return isEqual(*lhs, rhs, checks.matchCase);
//        };
//
//        auto deref = [](const Gtk::TextIter &it)
//        {
//            return *it;
//        };
//
//        auto foundRange = reverseFun(search(range, reverseFun(text), compare, deref, checks.wholePhrase));
//
//        if (!boost::empty(foundRange))
//        {
//            auto beg = *foundRange.begin();
//            auto end = *foundRange.end();
//
//            buffer->select_range(beg, end);
//            data.textView.scroll_to(beg);
//
//            return true;
//        }
//        else
//        {
//            buffer->select_range(*range.end(), *range.end());
//            return false;
//        }
//    }
//
//    inline Gtk::TextIter adjustIter(const Gtk::TextIter &it, const Gtk::TextIter &begin, const Gtk::TextIter &end)
//    {
//        return it < begin ? begin : (it > end ? end : it);
//    }
//
//    template <typename ReverseFun, typename JoinFun>
//    bool TextEditor::find(Data &data, const ReverseFun &reverseFun, const JoinFun &joinFun)
//    {
//        auto buffer = data.textView.get_buffer();
//        auto &text = data.findData.text;
//        auto &checks = data.findData.checks;
//
//        auto rangeBegin = checks.selection ? buffer->get_iter_at_offset(data.findData.selBegin) : buffer->begin();
//        auto rangeEnd = checks.selection ? buffer->get_iter_at_offset(data.findData.selEnd) : buffer->end();
//
//        auto upperEnd = buffer->get_iter_at_offset(buffer->property_cursor_position());
//        decltype(upperEnd) lowerBegin;
//
//        upperEnd = adjustIter(upperEnd, rangeBegin, rangeEnd);
//
//        if (buffer->get_has_selection())
//        {
//            Gtk::TextIter begin;
//            buffer->get_selection_bounds(begin, lowerBegin);
//        }
//        else
//        {
//            lowerBegin = upperEnd;
//        }
//
//        lowerBegin = adjustIter(lowerBegin, rangeBegin, rangeEnd);
//
//        auto rangeUpper = reverseFun(boost::make_iterator_range
//        (
//            clMisc::make_iter_iterator_val(rangeBegin),
//            clMisc::make_iter_iterator_val(upperEnd)
//        ));
//
//        auto rangeLower = reverseFun(boost::make_iterator_range
//        (
//            clMisc::make_iter_iterator_val(lowerBegin),
//            clMisc::make_iter_iterator_val(rangeEnd)
//        ));
//
//        decltype(rangeLower) ran[] = { rangeLower, rangeUpper };
//        auto ranRan = boost::make_iterator_range(ran, ran + 2);
//
//        auto range = joinFun(reverseFun(ranRan));
//
//        return findRange(data, range, reverseFun);
//    }
//
//    def_range_adaptor_fun(Reverse, range | boost::adaptors::reversed);
//    def_range_adaptor_fun(Identity, range);
//
//    template <bool wrapAround>
//    struct Join
//    def_join(boost::join(*rangePair.begin(), *(rangePair.begin() + 1)));
//
//    template <>
//    struct Join<false>
//    def_join(*rangePair.begin());
//
//    template <typename EventExecuter>
//    bool TextEditor::findPrevious(Data &data, const EventExecuter &eventExecuter)
//    {
//        if (data.findData.checks.wrapAround)
//            return find(data, ReverseRange(), Join<true>());
//        else
//            return find(data, ReverseRange(), Join<false>());
//    }
//
//    template <typename EventExecuter>
//    bool TextEditor::findNext(Data &data, const EventExecuter &eventExecuter)
//    {
//        if (data.findData.checks.wrapAround)
//            return find(data, IdentityRange(), Join<true>());
//        else
//            return find(data, IdentityRange(), Join<false>());
//    }
//
//
    void TextEditor::MOD_ACTION_SIG(findReplace_findPrevious)
    {
//        get_curr_data;
//        findPrevious(data, eventExecuter);
    }
//
    void TextEditor::MOD_ACTION_SIG(findReplace_findNext)
    {
//        get_curr_data;
//        findNext(data, eventExecuter);
    }
//
//    template <typename Range>
//    bool allUpper(const Range &range)
//    {
//        for (auto c : range)
//            if (c == std::tolower(c)) return false;
//
//        return true;
//    }
//
//    template <typename EventExecuter>
//    bool TextEditor::findReplace(Data &data, const std::string &replaceText, const EventExecuter &eventExecuter)
//    {
//        auto blocker = data.slots.buffer.blocker();
//        auto buffer = data.textView.get_buffer();
//        auto &text = data.findData.text;
//        auto &checks = data.findData.checks;
//
//        if (buffer->get_has_selection())
//        {
//            Gtk::TextIter begin, end;
//            buffer->get_selection_bounds(begin, end);
//
//            bool toUp = checks.preserveCase && allUpper(boost::make_iterator_range(begin, end));
//
//            auto rep = data.replace(begin, end, toUp ? boost::to_upper_copy(replaceText) : replaceText);
//
//            buffer->place_cursor(checks.replaceBackwards ? rep.second : rep.first);
//            contentsModified(data, eventExecuter);
//        }
//
//        if (checks.replaceBackwards)
//            return findPrevious(data, eventExecuter);
//        else
//            return findNext(data, eventExecuter);
//    }
//
    void TextEditor::MOD_ACTION_SIG(findReplace_replace)
    {
//        get_curr_data;
//
//        findReplace(data, findReplace_replaceText, eventExecuter);
    }
//
    void TextEditor::MOD_ACTION_SIG(findReplace_replaceAll)
    {
//        get_curr_data;
//
//        while (findReplace(data, findReplace_replaceText, eventExecuter));
    }
//
//
    void TextEditor::MOD_ACTION_SIG(newEditor)
    {
        auto fileId = createFileIdFun();
        openEditorPrv(fileId, "(new)", "", eventExecuter);
    }
//
    void TextEditor::MOD_ACTION_SIG(openEditor)
    {
        openEditorPrv(fileId, fileName, parserId, eventExecuter);
    }
//
//    template <typename EventExecuter>
//    void TextEditor::parseTextPrv(const Data &data, const EventExecuter &eventExecuter) const
//    {
//        char buff[BUFFER_SIZE];
//        if (data.type.empty())
//            return;
//
//        auto end = data.getContents(buff, sizeof(buff));
//
//        execute_event_tn(parseText)(data.id, data.type, BufferRange(buff, end));
//    }
//
//    template <typename Type>
//    inline std::shared_ptr<Type> makeSharedClone(const Type &type)
//    {
//        return std::make_shared<Type>(type);
//    }
//
//    unsigned getLineIndent(const Glib::RefPtr<Gtk::TextBuffer> &buffer)
//    {
//        dec_rev_range;
//
//        auto lastSpaces = boost::find_if<boost::return_begin_found>(revRange, findNonspaceNL);
//
//        while (lastSpaces.end() != revRange.end() && *lastSpaces.end() != '\n')
//        {
//            auto rangeLeft = boost::make_iterator_range(lastSpaces.end(), revRange.end());
//            rangeLeft = boost::find_if<boost::return_found_end>(rangeLeft, findSpaceNL);
//
//            lastSpaces = boost::find_if<boost::return_begin_found>(rangeLeft, findNonspaceNL);
//        }
//
//        return boost::distance(lastSpaces);
//    }
//
//    std::pair<unsigned, unsigned> findMatchingIndent(const Glib::RefPtr<Gtk::TextBuffer> &buffer, char c)
//    {
//        dec_rev_range;
//
//        auto sizeAll = boost::distance(revRange);
//        auto rangeLeft = boost::find_if<boost::return_found_end>(revRange, findNonspaceNL);
//
//        auto secondSize = boost::distance(rangeLeft);
//        if (secondSize && *rangeLeft.begin() == '\n')
//        {
//            rangeLeft = boost::find<boost::return_next_end>(rangeLeft.advance_begin(1), c);
//            rangeLeft = boost::find<boost::return_begin_found>(rangeLeft, '\n');
//
//            return std::make_pair(boost::distance(rangeLeft), sizeAll - secondSize);
//        }
//        else return std::make_pair(0, 0);
//    }
//
//    unsigned getLinePos(const Glib::RefPtr<Gtk::TextBuffer> &buffer)
//    {
//        dec_rev_range;
//
//        auto lineEnd = boost::find(revRange, '\n');
//
//        return std::distance(revRange.begin(), lineEnd);
//    }
//
//    void indentMatching(const Glib::RefPtr<Gtk::TextBuffer> &buffer, char left, char right)
//    {
//        auto indents = findMatchingIndent(buffer, left);
//
//        std::stringstream str;
//        if (indents.first > indents.second)
//        {
//            str << clMisc::repeatText(indents.first - indents.second, " ");
//        }
//        else if (indents.first < indents.second)
//        {
//            auto diff = indents.second - indents.first;
//            auto curPos = buffer->property_cursor_position();
//            auto begin = buffer->get_iter_at_offset(curPos - diff);
//            auto end = buffer->get_iter_at_offset(curPos);
//
//            buffer->erase(begin, end);
//        }
//
//        str << right;
//        buffer->insert_at_cursor(str.str());
//    }
//
//
//    struct FindTextIterVal
//    {
//        char c;
//
//        FindTextIterVal(char c) : c(c) {}
//
//        bool operator()(const Gtk::TextIter &it) const
//        {
//            return *it == c;
//        }
//    };
//
//   struct FindTextIterNValNL
//    {
//        char c;
//
//        FindTextIterNValNL(char c) : c(c) {}
//
//        bool operator()(const Gtk::TextIter &it) const
//        {
//            return *it != c || *it == '\n';
//        }
//    };
//
//    void TextEditor::indentSelection(Data &data, int indCount)
//    {
//        auto buffer = data.textView.get_buffer();
//
//        Gtk::TextIter begin, end;
//
//        auto buffRange = boost::make_iterator_range
//        (
//            clMisc::make_iter_iterator_val(buffer->begin()),
//            clMisc::make_iter_iterator_val(buffer->end())
//        );
//
//        buffer->get_selection_bounds(begin, end);
//
//        auto selRange = boost::make_iterator_range
//        (
//            clMisc::make_iter_iterator_val(begin),
//            clMisc::make_iter_iterator_val(end)
//        );
//
//        auto prevRangeRev = boost::make_iterator_range(buffRange.begin(), selRange.begin()) | boost::adaptors::reversed;
//        auto prevRangeLineRev = boost::find_if<boost::return_begin_found>(prevRangeRev, FindTextIterVal('\n'));
//        auto prevRangeLine = prevRangeLineRev | boost::adaptors::reversed;
//        auto selBeginDist = boost::distance(prevRangeLine);
//
//        auto afterRange = boost::make_iterator_range(selRange.end(), buffRange.end());
//        auto afterRangeLine = boost::find_if<boost::return_begin_found>(afterRange, FindTextIterVal('\n'));
//        auto selEndDist = boost::distance(afterRangeLine);
//
//        auto selRangeEx = boost::make_iterator_range
//        (
//            clMisc::make_iter_iterator_val(*prevRangeLine.begin()),
//            clMisc::make_iter_iterator_val(*afterRangeLine.end())
//        );
//
//        auto selRangeExAux = selRangeEx;
//
//        std::stringstream str;
//
//        bool firstLine = true;
//        while (!boost::empty(selRangeExAux))
//        {
//            auto spaceRange = boost::find_if<boost::return_begin_found>(selRangeExAux, FindTextIterNValNL(' '));
//            auto dist = boost::distance(spaceRange);
//
//            int indCountSized = indCount * tabSize;
//            int toInsertSize = dist + indCountSized < 0 ? -dist : indCountSized;
//
//            if (firstLine)
//            {
//                firstLine = false;
//                selBeginDist += toInsertSize;
//            }
//
//            if (toInsertSize < 0)
//            {
//                selRangeExAux.advance_begin(-toInsertSize);
//            }
//
//            auto toInsert = boost::find_if<boost::return_begin_next>(selRangeExAux, FindTextIterVal('\n'));
//
//            if (toInsertSize >= 0)
//            {
//                if (boost::distance(toInsert) > 1)
//                    str << clMisc::repeatText(toInsertSize, " ");
//            }
//
//            std::copy(*toInsert.begin(), *toInsert.end(), std::ostream_iterator<char>(str));
//
//            selRangeExAux.advance_begin(boost::distance(toInsert));
//        }
//
//        auto blocker = data.slots.buffer.blocker();
//
//        auto text = str.str();
//
//        auto rep = data.replace(*selRangeEx.begin(), *selRangeEx.end(), text);
//
//        std::advance(rep.first, selBeginDist);
//        std::advance(rep.second, -selEndDist);
//
//        buffer->select_range(rep.first, rep.second);
//    }
//
//    template <typename EventExecuter>
//    void TextEditor::contentsModified(Data &data, const EventExecuter &eventExecuter)
//    {
//        if (data.isOriginalContents())
//            execute_event_tn(contentsAreOriginal)(data.id);
//        else
//            execute_event_tn(contentsModified)(data.id);
//
//        parseTextPrv(data, eventExecuter);
//        findHighlight(data);
//    }
//
//    void TextEditor::addInsertAction(Data &data, unsigned posNum, const std::string &text)
//    {
//        data.addAction(lib::BufferAction::Type::INSERT, posNum, text,
//            [&](unsigned pos, lib::BufferAction &lastAction)
//            {
//                if (pos == lastAction.pos + lastAction.text.size())
//                {
//                    lastAction.text += text;
//                    return true;
//                }
//
//                return false;
//            });
//    }
//
//    void TextEditor::addEraseAction(Data &data, unsigned posNum, const std::string &text)
//    {
//        data.addAction(lib::BufferAction::Type::ERASE, posNum, text,
//            [&](unsigned pos, lib::BufferAction &lastAction)
//            {
//                my_assert(lastAction.pos);
//
//                if (pos == lastAction.pos - 1)
//                {
//                    --lastAction.pos;
//                    lastAction.text = text + lastAction.text;
//                    return true;
//                }
//
//                return false;
//            });
//    }
//
//    template <typename EventExecuter>
//    bool TextEditor::signalKeyPressEvent(Data &data, const GdkEventKey &event, const EventExecuter &eventExecuter)
//    {
//        if (event.state & GDK_CONTROL_MASK && event.keyval == GDK_KEY_BackSpace)
//        {
//            postFun("textView.signal_key_press_event()", [this, event, &data, eventExecuter]
//            {
//                auto buffer = data.textView.get_buffer();
//
//                auto pos = buffer->property_cursor_position();
//                auto linePos = getLinePos(buffer);
//
//                if (linePos)
//                {
//                    auto begin = buffer->get_iter_at_offset(pos - (linePos - 1) % tabSize - 1);
//                    auto end = buffer->get_iter_at_offset(pos);
//                    buffer->erase(begin, end);
//                }
//
//                contentsModified(data, eventExecuter);
//            });
//
//            return true;
//        }
//        else if (event.keyval == GDK_KEY_ISO_Left_Tab || event.keyval == GDK_KEY_Tab)
//        {
//            postFun("textView.signal_key_press_event()", [this, event, &data, eventExecuter]
//            {
//                auto buffer = data.textView.get_buffer();
//
//                if (buffer->get_has_selection())
//                {
//                    if (event.state & GDK_SHIFT_MASK)
//                    {
//                        indentSelection(data, -1);
//                    }
//                    else
//                    {
//                        indentSelection(data, 1);
//                    }
//                }
//                else if (!(event.state & GDK_SHIFT_MASK))
//                {
//                    std::cout << "tab" << std::endl;
//
//                    auto buffer = data.textView.get_buffer();
//                    std::stringstream str;
//
//                    str << clMisc::repeatText(tabSize - getLinePos(buffer) % tabSize, " ");
//                    buffer->insert_at_cursor(str.str());
//                }
//
//                contentsModified(data, eventExecuter);
//            });
//
//            return true;
//        }
//        else if (event.length == 1)
//        {
//            switch(event.string[0])
//            {
//                case '\r':
//                    postFun("textView.signal_key_press_event()", [this, event, &data, eventExecuter]
//                    {
//                        auto buffer = data.textView.get_buffer();
//
//                        if (auto curPos = buffer->property_cursor_position())
//                        {
//                            std::stringstream str;
//
//                            auto c = *buffer->get_iter_at_offset(curPos - 1);
//                            unsigned extra = (c == '{' || c == '(' || c == '[') ? 1 : 0;
//
//                            str << "\n" << clMisc::repeatText(getLineIndent(buffer) + extra * tabSize, " ");
//                            buffer->insert_at_cursor(str.str());
//                        }
//                        contentsModified(data, eventExecuter);
//                    });
//
//                    return true;
//
//                key_press_event_case('{', '}')
//                key_press_event_case('(', ')')
//                key_press_event_case('[', ']')
//
//                default:
//                    break;
//            }
//        }
//
//        return false;
//    }
//
    void TextEditor::MOD_ACTION_SIG(tabAdded)
    {
        auto &textArea = clMisc::deref(notebook_tabWidget);

        auto ret = dataMap.insert({fileId, { fileId, "", textArea, eventExecuter }});
        ct_assert_tn(ret.second);

        ct_assert(dataMapIt.insert({ &textArea, ret.first }).second);

        currDataIt = ret.first;

        execute_event(selectFile)(fileId);
    }



    template <typename EventExecuter>
    void TextEditor::openEditorPrv(const FileIdSCPtr &fileId, const bfs::path &fileName, const std::string &parserId, const EventExecuter &eventExecuter)
    {
        auto &textArea = clMisc::deref(textItems.property("textArea").value<QObject*>());

        execute_event_tn(newTBTabRequested)(fileId, fileName.filename().string(), fileName.string(), &textArea);

//
//        textView.signal_key_press_event().connect([this, &data, eventExecuter](GdkEventKey *event)
//        {
//            return signalKeyPressEvent(data, *event, eventExecuter);
//        },
//        false);
//
//        my_connect_signal_ntf_ptr(buffer, changed)([this, fileId, eventExecuter, &data]
//        {
//            postFun("buffer->signal_changed()", [this, fileId, eventExecuter, &data]
//            {
//                contentsModified(data, eventExecuter);
//            });
//        });
//
//        my_connect_signal_ntf_ptr(buffer, insert)([this, buffer, &data]
//            (const Gtk::TextBuffer::iterator &pos, const Glib::ustring &text, int bytes)
//        {
//            auto posNum = std::distance(buffer->begin(), pos);
//            my_assert(posNum >= 0);
//
//            postFun("buffer->signal_insert()", [this, buffer, posNum, text, &data]
//            {
//                addInsertAction(data, posNum, text);
//            });
//        });
//
//        my_connect_signal_ntf_ptr(buffer, erase)([this, buffer, &data]
//            (const Gtk::TextBuffer::iterator &start, const Gtk::TextBuffer::iterator& end)
//        {
//            auto posNum = std::distance(buffer->begin(), start);
//            my_assert(posNum >= 0);
//            auto text = Glib::ustring(start, end);
//
//            postFun("buffer->signal_erase()", [this, posNum, text, &data]
//            {
//                addEraseAction(data, posNum, text);
//            });
//        });
//
//        scrolled.add(textView);
//
//        execute_event_tn(newTBTabRequested)(fileId, fileName.filename().string(), fileName.string(), &scrolled);
    }

    void TextEditor::MOD_ACTION_SIG(editorTypeChanged)
    {
//        auto &data = getData(fileId);
//        data.type = parserId;
//
//        parseTextPrv(data, eventExecuter);
    }

    TextEditor::Data &TextEditor::getData(const FileIdSCPtr &fileId)
    {
        auto it = dataMap.find(fileId);
        my_assert(it != dataMap.end());
        return it->second;
    }

    TextEditor::Data *TextEditor::getDataPtr(const FileIdSCPtr &fileId)
    {
        auto it = dataMap.find(fileId);
        return it == dataMap.end() ? nullptr : &(it->second);
    }

    TextEditor::Data &TextEditor::getData(const QObject &textArea)
    {
        auto it = dataMapIt.find(&textArea);
        my_assert(it != dataMapIt.end());
        return it->second->second;
    }

    TextEditor::Data *TextEditor::getDataPtr(const QObject &textArea)
    {
        auto it = dataMapIt.find(&textArea);
        return it == dataMapIt.end() ? nullptr : &(it->second->second);
    }


    TextEditor::Data *TextEditor::getCurrData()
    {
        return currDataIt == dataMap.end() ? nullptr : &(currDataIt->second);
    }

    void TextEditor::MOD_ACTION_SIG(undo)
    {
//        get_curr_data;
//
//        data.undo();
//        contentsModified(data, eventExecuter);
    }
//
    void TextEditor::MOD_ACTION_SIG(redo)
    {
//        get_curr_data;
//        data.redo();
//        contentsModified(data, eventExecuter);
    }
//
    template <typename EventExecuter>
    void TextEditor::closingEditorPrv(Data &data, const EventExecuter &eventExecuter)
    {
        if (!data.isOriginalContents())
        {
            auto &dialog = clMisc::deref(textItems.findChild<QObject*>("saveDialogQuestion"));

            static clQt::SigConnUPtr onYes = CHILA_LIB_QT__CONNECT_SIGNAL(dialog, yes, (this)(&data)(eventExecuter), )
            {
                data.isClosing = true;
                saveEditorContents(data, eventExecuter);
            });

            static clQt::SigConnUPtr onNo = CHILA_LIB_QT__CONNECT_SIGNAL(dialog, no, (this)(&data)(eventExecuter), )
            {
                execute_event_tn(editorClosed)(data.id);
                //#error continue with the closing path, the file data here should be removed
            });

            dialog.setProperty("visible", QVariant(true));
        }
        else execute_event_tn(editorClosed)(data.id);
    }

    void TextEditor::MOD_ACTION_SIG(closingEditor)
    {
        closingEditorPrv(getData(fileId), eventExecuter);
    }

    void TextEditor::MOD_ACTION_SIG(closingSelectedEditor)
    {
        get_curr_data;
        closingEditorPrv(data, eventExecuter);
    }

    void TextEditor::MOD_ACTION_SIG(addText)
    {
        auto &data = getData(fileId);
        data.setContents(std::string(textBuffer.begin(), textBuffer.end()));


//        auto buffer = data.textView.get_buffer();
//
//        auto sigBlocker = data.slots.buffer.blocker();
//
//        buffer->insert(buffer->end(), boost::begin(textBuffer), boost::end(textBuffer));
    }
//
    void TextEditor::MOD_ACTION_SIG(applyTags)
    {
//        auto &data = getData(fileId);
//
//        auto &textView = data.textView;
//        auto buffer = textView.get_buffer();
//        auto tagTable = buffer->get_tag_table();
//
//        auto tagList = std::vector<Glib::RefPtr<Gtk::TextTag>>();
//
//        tagTable->foreach([&](const Glib::RefPtr<Gtk::TextTag> &tag)
//        {
//            tagList.push_back(tag);
//        });
//
//        for (auto &tag : tagList)
//        {
//            tagTable->remove(tag);
//        }
//
//        for (auto &textTag : tags)
//        {
//            Gdk::Color color;
//            color.set_rgb_p(textTag.color.red, textTag.color.green, textTag.color.blue);
//            auto tag = Gtk::TextTag::create(textTag.name);
//            tag->property_foreground_gdk() = color;
//
//            tagTable->add(tag);
//        }
//
//        data.addPredefinedTags();
//
//        for (auto &tagToApply : tagsToApply)
//        {
//            buffer->apply_tag_by_name
//            (
//                tagToApply.name,
//                buffer->get_iter_at_offset(tagToApply.start),
//                buffer->get_iter_at_offset(tagToApply.start + tagToApply.size)
//            );
//        }
    }
//
    template <typename EventExecuter>
    void TextEditor::saveEditorContents(Data &data, const EventExecuter &eventExecuter)
    {
        auto text = data.getContents();
        clMisc::removeTrailingWSpace(text);
        data.setContents(text);

        execute_event_tn(saveEditorContents_current)(data.id, BufferRange(text.c_str(), text.c_str() + text.size()));
    }

    void TextEditor::MOD_ACTION_SIG(saveEditorContents_current)
    {
        get_curr_data;

        saveEditorContents(data, eventExecuter);
    }

    void TextEditor::MOD_ACTION_SIG(saveEditorContents_as)
    {
        get_curr_data;

        auto text = data.getContents();
        clMisc::removeTrailingWSpace(text);
        data.setContents(text);

        execute_event(tabDataChanged)(data.id, fileName.filename().string(), fileName.filename().string());
        execute_event(saveEditorContents_as)(data.id, fileName, BufferRange(text.c_str(), text.c_str() + text.size()));
    }
//
    void TextEditor::MOD_ACTION_SIG(saveAll)
    {
//        if (dataMap.size())
//        {
//            savingDataIt = dataMap.begin();
//            saveEditorContents(savingDataIt->second, eventExecuter);
//        }
    }
//
    void TextEditor::MOD_ACTION_SIG(openingDone)
    {
//        auto &data = getData(fileId);
//
//        data.setOriginalContents();
//
//        parseTextPrv(data, eventExecuter);
//
//        execute_event(contentsAreOriginal)(fileId);
    }
//
    void TextEditor::MOD_ACTION_SIG(savingDone)
    {
        auto &data = getData(fileId);

        data.setOriginalContents();

        if (data.isClosing)
            execute_event(editorClosed)(fileId);
        else
            execute_event(contentsAreOriginal)(fileId);

//        if (savingDataIt != dataMap.end() && ++savingDataIt != dataMap.end())
//        {
//            saveEditorContents(savingDataIt->second, eventExecuter);
//        }
    }
//
    void TextEditor::MOD_ACTION_SIG(fileSelected)
    {
        currDataIt = dataMap.find(fileId);
    }


    connection::TextEditor::CProviderUPtr connection::TextEditor::create(module_args_ex)
    {
        return std::make_unique<impl::TextEditor>(module_pass_args_ex);
    }
}
MY_NSP_END
