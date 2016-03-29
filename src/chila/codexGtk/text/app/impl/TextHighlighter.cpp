/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "TextHighlighter.hpp"
#include "connection/CPDataTypes.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <chila/lib/gtkmm/util.hpp>
#include <chila/lib/misc/util.hpp>
#include <fstream>
#include <chila/lib/gtkmm/util.hpp>
#include <boost/filesystem.hpp>
#include <gdkmm-2.4/gdkmm/color.h>
#include <boost/range/iterator_range_core.hpp>
#include "../../lib/types.hpp"


#define MODULE_NAME TextHighlighter

#include "macros.fgen.hpp"

#define SH_DIR "/usr/share/source-highlight"

MY_NSP_START
{
    class TextHighlighter::Formatter: public srchilite::Formatter
    {
        public:
            Formatter(TextHighlighter &highlighter, const std::string &elem = "normal") :
                highlighter(highlighter),
                elem(elem) {}

            void format(const std::string &s, const srchilite::FormatterParams *params = 0) override
            {
                // do not print anything if normal or string to format is empty
                if (elem != "normal" || !s.size())
                {
                    highlighter.tagApplyList.push_back(connection::TagApply(params->start + highlighter.offset, s.size(), elem));
                }
            }

        private:
            TextHighlighter &highlighter;
            std::string elem;
            lib::Color color;
    };

    TextHighlighter::ParseData::ParseData(TextHighlighter &textHighligther, const std::string &file) :
        textHighligther(textHighligther),
        langDefManager(&ruleFactory),
        state(langDefManager.getHighlightState(SH_DIR, file)),
        formatterManager(std::make_shared<Formatter>(textHighligther))
    {

        for (auto &vt : textHighligther.formatterMap)
        {
            formatterManager.addFormatter(vt.first, vt.second);
        }
    }

    void TextHighlighter::ParseData::parse(const connection::BufferRange &textBuffer)
    {
        auto highlighter = std::make_shared<srchilite::SourceHighlighter>(state);

        highlighter->setFormatterParams(&params);
        highlighter->setFormatterManager(&formatterManager);

        textHighligther.parseBegin = textBuffer.begin();
        textHighligther.tagApplyList.clear();

        for (auto start = textBuffer.begin(), it = start;; ++it)
        {
            if (it == textBuffer.end())
            {
                textHighligther.offset = start - textHighligther.parseBegin;
                highlighter->highlightParagraph(std::string(start, it));
                break;
            }
            else if (*it == '\n')
            {
                textHighligther.offset = start - textHighligther.parseBegin;
                highlighter->highlightParagraph(std::string(start, it));
                start = it + 1;
            }
        }
    }

    TextHighlighter::TextHighlighter(module_args_ex) :
        connection::TextHighlighter::CProvider(instanceName)
    {
        connector.bindActions(*this);

        for (auto &vt : colorMap)
        {
            my_assert(textTags.insert({vt.first, vt.second}).second);
            addFormatter(vt.first);
        }

        addParseData("cpp");
        addParseData("xml");
        addParseData("python");
    }

    void TextHighlighter::addFormatter(const std::string &name)
    {
        my_assert(formatterMap.insert({name, std::make_shared<Formatter>(*this, name)}).second);
    }

    void TextHighlighter::addParseData(const std::string &name)
    {
        my_assert(parseDataMap.insert({name, std::make_shared<ParseData>(*this, name + ".lang")}).second);
    }

    void TextHighlighter::MOD_ACTION_SIG(parseText)
    {
        auto it = parseDataMap.find(parserId);
        ct_assert(it != parseDataMap.end());


//        std::cout << "--------------------------------------\n";
//        std::cout.write(textBuffer.begin(), textBuffer.size());
//        std::cout << "--------------------------------------" << std::endl;

        auto &parseData = it->second;
        parseData->parse(textBuffer);

        execute_event(applyTags)(fileId, textTags, tagApplyList);
    }


    connection::TextHighlighter::CProviderUPtr connection::TextHighlighter::create(module_args_ex)
    {
        return std::make_unique<impl::TextHighlighter>(module_pass_args_ex);
    }
}
MY_NSP_END
