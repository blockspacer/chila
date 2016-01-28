/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <iostream>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <libxml++/libxml++.h>
#include <boost/filesystem.hpp>
#include <chila/lib/xmlppUtils/util.hpp>
#include <boost/tokenizer.hpp>
#include <chila/lib/misc/ContainerSinkInserter.hpp>
#include "floatfann.h"
#include <chila/lib/misc/RepeatText.hpp>
#include "fann_cpp.h"
#include "Dictionary.hpp"

#define show_error_info(out, Type, name) \
        if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
            out << "- " << name << ": " << "[" << *value << "]" << std::endl;

namespace bfs = boost::filesystem;
namespace cTrans = chila::translate;

using WordWPVecFound = std::function<void(const cTrans::WordWPVec &vec)>;
using WordPosMap = std::map<std::string, std::set<unsigned>>;

void showException(const std::exception &ex);
cTrans::Dictionary loadDictionary(const xmlpp::Element &root);
cTrans::WordSetVec getWords(const cTrans::Dictionary &dic, const std::string &input);
void walkWords(const cTrans::WordSetVec &vec, cTrans::PhraseVec &phrases);
const cTrans::Phrase &findCorrectPhrase(const cTrans::PhraseVec &phrases, const std::string &text);
void train(FANN::neural_net &net, const cTrans::Dictionary &dic, const std::string &iText, const std::string &oText, unsigned maxTraining, bool verbose);
std::string test(FANN::neural_net &net, const cTrans::Dictionary &dic, const std::string &iText, unsigned maxTesting, bool verbose);
void train(FANN::neural_net &net, const std::vector<float> &input, const std::vector<float> &output);
float *run(FANN::neural_net &net, const std::vector<float> &input);

#define field_diff(field) float(wp.word.field != word.field ? 1 : 0)

#include "macros.fgen.hpp"
#include "Word.hpp"

using chila::lib::misc::rvalue_cast;

int main(int argc, char **argv) try
{
    bfs::path file = "dictionary.xml";

    xmlpp::DomParser parser(file.string().c_str());
    auto &document = *parser.get_document();
    auto root = chila::lib::misc::checkNotNull(document.get_root_node());

    if (!root || root->get_name() != "dictionary")
    {
        BOOST_THROW_EXCEPTION(chila::lib::misc::ApplicationError("invalid dictionary"));
    }

    auto dic = loadDictionary(*root);

    FANN::neural_net net;
    net.create_shortcut
    (
        4,  // num_layers,
        cTrans::ATTRIBUTE_COUNT * cTrans::MAX_WORDS,  // num_input,
        cTrans::ATTRIBUTE_COUNT * cTrans::MAX_WORDS,  // num_neurons_hidden,
        cTrans::ATTRIBUTE_COUNT * cTrans::MAX_WORDS,  // num_neurons_hidden,
        cTrans::ATTRIBUTE_COUNT + 1   // num_output
    );

    net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC);
    net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC);

    bool verbose = true;
    for (unsigned i = 0; i < 1000; ++i)
    {
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.33, 0.33, 0.00,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0500, 0.2500, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.67, 0.33, 0.00,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0000, 0.0833, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.67, 0.33, 0.00,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0500, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.60, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.0833, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.2500, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.60, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.33, 0.33, 0.00,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0500, 0.2500, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.67, 0.33, 0.00,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0000, 0.0833, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.67, 0.33, 0.00,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0500, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.60, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.0833, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.2500, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.60, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.2500, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.00, 0.67, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0000, 0.1667, 0.0000, 0.0000});
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.60, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.40, 0.00, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0500, 0.0500, 0.2500, 0.0000, 0.0000});
//
//        train(net, {0.20, 0.33, 0.33, 0.00,  0.40, 0.00, 0.33, 0.25,  0.60, 0.33, 0.33, 0.00,  0.00, 0.33, 0.33, 0.00,  0.00, 0.00, 0.00, 0.00}, {0.0000, 0.0000, 0.0000, 0.0000, 0.0000});

        train(net, dic, "this is a test", "ésta es una prueba", 2000, i == 0 && verbose);
//        train(net, dic, "this is a failure", "ésta es una falla", i == 0 && verbose);
        train(net, dic, "this is a dog", "éste es un perro", 2000, i == 0 && verbose);
//        train(net, dic, "this is a cat", "éste es un gato", i == 0 && verbose);
//        train(net, dic, "this is a cow", "ésta es una vaca", i == 0 && verbose);
//        std::cout << i << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;

    auto trans0 = test(net, dic, "this is a test", 2000, verbose);
//    auto trans1 = test(net, dic, "this is a failure", verbose);
    auto trans2 = test(net, dic, "this is a dog", 2000, verbose);
//    auto trans3 = test(net, dic, "this is a cat", verbose);
//    auto trans4 = test(net, dic, "this is a cow", verbose);

//    std::cout << trans << std::endl;


    ::sleep(1);


    return EXIT_SUCCESS;
}
catch (const chila::lib::misc::ApplicationError &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
catch (const chila::lib::xmlppUtils::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}

void train(FANN::neural_net &net, const std::vector<float> &input, const std::vector<float> &output)
{
    net.train(chila::lib::misc::removeConst(input.data()), chila::lib::misc::removeConst(output.data()));
}

float *run(FANN::neural_net &net, const std::vector<float> &input)
{
    return net.run(chila::lib::misc::removeConst(input.data()));
}

void getInput(unsigned pos, const cTrans::Word &word, std::vector<float> &input)
{
    input[pos + 0] = float(word.type) / cTrans::getSize<cTrans::Type>();
    input[pos + 1] = float(word.gender) / cTrans::getSize<cTrans::Gender>();
    input[pos + 2] = float(word.cardinality) / cTrans::getSize<cTrans::Cardinality>();
    input[pos + 3] = float(word.time) / cTrans::getSize<cTrans::Time>();
}


void train(FANN::neural_net &net, const cTrans::Dictionary &dic, const std::string &iText, const std::string &oText, unsigned maxTraining, bool verbose)
{
    using chila::lib::misc::containerSinkInserter;

    auto words = getWords(dic, iText);

    cTrans::PhraseVec phrases;
    walkWords(words, phrases);

    const cTrans::Phrase &correct = ct_apperror_element_nf_ref(findCorrectPhrase(phrases, oText), "could not find the correct phrase");

    std::vector<float> input, output;
    input.resize(cTrans::ATTRIBUTE_COUNT * cTrans::MAX_WORDS);
    output.resize(cTrans::ATTRIBUTE_COUNT + 1);
    float total[cTrans::ATTRIBUTE_COUNT + 1];

    unsigned pIndex = 0;
    for (auto &phrase : phrases)
    {
        unsigned pos = 0;
        std::fill(input.begin(), input.end(), 0);
        std::fill(output.begin(), output.end(), 0);

        std::fill(total, total + cTrans::ATTRIBUTE_COUNT + 1, 0);

        auto coutP = std::cout.tellp();
        for (auto &wp : phrase.words)
        {
            if (verbose)
                std::cout << std::fixed << std::setprecision(2) << wp.word.value << " ";

            auto cwPos = correct.positions[wp.pos];
            auto &word = correct.words[cwPos].word;

            getInput(pos * cTrans::ATTRIBUTE_COUNT, wp.word, input);

            auto posDiff = chila::lib::misc::absDiff(pos, cwPos);
            my_assert(posDiff < cTrans::MAX_POS);

//            total[0] += posDiff / cTrans::MAX_POS;
            total[1] += field_diff(type) / cTrans::getSize<cTrans::Type>();
            total[2] += field_diff(gender) / cTrans::getSize<cTrans::Gender>();
            total[3] += field_diff(cardinality) / cTrans::getSize<cTrans::Cardinality>();
//            total[4] += field_diff(time);

            ++pos;
        }

        for (unsigned i = 0; i < cTrans::ATTRIBUTE_COUNT + 1; ++i)
            output[i] = total[i] / pos;

        if (rand() % 5 == 0) train(net, input, output);

        auto coutDiff = std::cout.tellp() - coutP;

        if (verbose)
        {
            std::cout << std::fixed << std::setprecision(2) << ": "
                      << chila::lib::misc::repeatText(30 - coutDiff, " ")
                      << "[" << containerSinkInserter(input) << "] - ["
                      << std::fixed << std::setprecision(4);

            bool first = true;
            for (auto val : output)
            {
                if (first)
                    first = false;
                else
                    std::cout << ", ";

                std::cout << std::fixed << std::setprecision(4) << (val >= 0 ? " " : "") << val;
            }

            std::cout << "]" << std::endl;
        }


        if (++pIndex >= maxTraining) break;
    }
}

std::string test(FANN::neural_net &net, const cTrans::Dictionary &dic, const std::string &iText, unsigned maxTesting, bool verbose)
{
    using chila::lib::misc::containerSinkInserter;

    auto words = getWords(dic, iText);

    std::map<float, cTrans::Phrase> phraseMap;

    cTrans::PhraseVec phrases;
    walkWords(words, phrases);

    std::vector<float> input;
    input.resize(cTrans::ATTRIBUTE_COUNT * cTrans::MAX_WORDS);

    unsigned pIndex = 0;
    for (auto &phrase : phrases)
    {
        unsigned pos = 0;
        std::fill(input.begin(), input.end(), 0);

        auto coutP = std::cout.tellp();
        for (auto &wp : phrase.words)
        {
            if (verbose)
                std::cout << wp.word.value << " ";

            getInput(pos * cTrans::ATTRIBUTE_COUNT, wp.word, input);

            ++pos;
        }

        auto *ret = run(net, input);
        float total = 0;

        if (verbose)
        {
            auto coutDiff = std::cout.tellp() - coutP;
            std::cout << ": " << chila::lib::misc::repeatText(30 - coutDiff, " ") << "[" << std::fixed << std::setprecision(2) <<  containerSinkInserter(input) << "] - [";
        }

        for (unsigned i = 0; i < cTrans::ATTRIBUTE_COUNT + 1; ++i, total += ret[i])
        {
            if (verbose)
                std::cout << (i ? ", " : "") << std::fixed << std::setprecision(4) << (ret[i] >= 0 ? " " : "") << ret[i];

            total += ret[i];
        }

        if (verbose)
            std::cout << std::fixed << std::setprecision(4) << "]: " << total << std::endl;

        phraseMap.insert({total, phrase});
        if (++pIndex >= maxTesting) break;
    }

    unsigned index = 0;
    for (auto &vt : phraseMap)
    {
        std::cout << std::fixed << std::setprecision(4) << vt.first << ": ";
        for (auto &word : vt.second.words)
        {
            std::cout << word.word.value << " ";
        }
        std::cout << std::endl;

        if (index++ > 10)
        {
            std::cout << std::endl;
            break;
        }
    }

    std::cout << std::endl;

    return "";
}

void showException(const std::exception &ex)
{
    std::cerr << "error: " << ex.what() << std::endl;

    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::XPath, "xml path");
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Row, "row");
    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Column, "column");
}

const cTrans::Phrase &findCorrectPhrase(const cTrans::PhraseVec &phrases, const std::string &text)
{
    for (auto &phrase : phrases)
    {
        unsigned pos = 0;
        bool diff = false;
        chila::lib::misc::tokenize(text, " ", [&](const std::string &token)->bool
        {
            if (token != phrase.words.at(pos++).word.value)
            {
                diff = true;
                return false;
            }

            return true;
        });

        if (!diff)
            return phrase;
    }

    BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());
}

template <typename Type>
Type readType(const xmlpp::Element &element, const std::string &attrName) try
{
    return cTrans::getValue<Type>(chila::lib::xmlppUtils::getAttribute<std::string>(element, attrName));
}
catch (const chila::lib::misc::InvalidArgument &ex)
{
    chila::lib::xmlppUtils::throwInvalidAttributeValue("invalid value for attribute '" + attrName + "'", element);
}

template <typename Type>
Type readType(const xmlpp::Element &element, const std::string &attrName, const std::string &def) try
{
    return cTrans::getValue<Type>(chila::lib::xmlppUtils::getAttribute<std::string>(element, attrName, def));
}
catch (const chila::lib::misc::InvalidArgument &ex)
{
    chila::lib::xmlppUtils::throwInvalidAttributeValue("invalid value for attribute '" + attrName + "'", element);
}

cTrans::Dictionary loadDictionary(const xmlpp::Element &root)
{
    cTrans::Dictionary ret;

    using chila::lib::xmlppUtils::iterateChildren;

    auto &wordsElem = chila::lib::xmlppUtils::getUniqueChildElement(root, "words");
    auto &entriesElem = chila::lib::xmlppUtils::getUniqueChildElement(root, "entries");

    xml_iterate_children(wordsElem, "word", wordElem)
    {
        auto value = chila::lib::xmlppUtils::getAttribute<std::string>(wordElem, "value");
        auto type = readType<cTrans::Type>(wordElem, "type");
        auto gender = readType<cTrans::Gender>(wordElem, "gender", "none");
        auto card = readType<cTrans::Cardinality>(wordElem, "card", "none");
        auto time = readType<cTrans::Time>(wordElem, "time", "none");

        ret.addWord(value, type, gender, card, time);
    });

    xml_iterate_children(entriesElem, "entry", entryElem)
    {
        auto value = chila::lib::xmlppUtils::getAttribute<std::string>(entryElem, "value");
        auto options = chila::lib::xmlppUtils::getAttribute<std::string>(entryElem, "options");

        chila::lib::misc::tokenize(options, ", ", [&](const std::string &token)->bool
        {
            ret.addTranslation(value, token);
            return true;
        });
    });

    return ret;
}

cTrans::WordSetVec getWords(const cTrans::Dictionary &dic, const std::string &input)
{
    cTrans::WordSetVec ret;

    unsigned pos = 0;
    chila::lib::misc::tokenize(input, " ", [&](const std::string &token)->bool
    {
        auto &words = dic.getTranslations(token);

        ret.push_back(cTrans::WordSet());
        for (auto &word : words)
        {
            my_assert(ret.back().insert(word).second);
        }

        return true;
    });

    return ret;
}

using TakenVec = std::vector<bool>;

void walkWords(const cTrans::WordSetVec &vec, TakenVec &taken, cTrans::WordWPVec &out, cTrans::PhraseVec &phrases)
{
    bool found = false;
    for (unsigned pos = 0; pos < vec.size(); ++pos)
    {
        for (auto &op : vec[pos])
        {
            if (!taken[pos])
            {
                found = true;
                taken[pos] = true;
                out.push_back({pos, op});
                walkWords(vec, taken, out, phrases);
                out.pop_back();
                taken[pos] = false;
            }
        }
    }

    if (!found)
    {
        cTrans::PosVec posVec;
        posVec.resize(vec.size());
        unsigned pos = 0;
        for (auto &word : out)
        {
            posVec[word.pos] = pos++;
        }

        phrases.push_back({out, rvalue_cast(posVec)});
    }
}

void walkWords(const cTrans::WordSetVec &vec, cTrans::PhraseVec &phrases)
{
    TakenVec taken;
    taken.resize(vec.size());
    cTrans::WordWPVec out;
    walkWords(vec, taken, out, phrases);
}
