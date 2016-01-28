/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_TRANSLATE__FWD_HPP
#define CHILA_TRANSLATE__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <set>
#include <map>
#include <chila/lib/misc/exceptions.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type>
    inline Type getValue(const std::string &name) { abort(); }

    template <typename Type>
    constexpr unsigned getSize() { return 0; }

    CHILA_LIB_MISC__DEF_ENUM_TYPE(Type,
        ((NOUN)("noun"))
        ((PRONOUN)("pronoun"))
        ((VERB)("verb"))
        ((ARTICLE)("article"))
        ((ADVERB)("adverb")))

    CHILA_LIB_MISC__DEF_ENUM_TYPE(Gender,
        ((NONE)("none"))
        ((MALE)("male"))
        ((FEMALE)("female")))

     CHILA_LIB_MISC__DEF_ENUM_TYPE(Cardinality,
        ((NONE)("none"))
        ((SINGULAR)("singular"))
        ((PLURAL)("plural")))

    CHILA_LIB_MISC__DEF_ENUM_TYPE(Time,
        ((NONE)("none"))
        ((PRESENT)("present"))
        ((PAST)("past"))
        ((FUTURE)("future")))

    CHILA_LIB_MISC__FWDEC_TYPE(Word);
    CHILA_LIB_MISC__FWDEC_TYPE(WordWP);
    CHILA_LIB_MISC__FWDEC_TYPE(Phrase);

    using WordSet = std::set<Word>;
    using WordSetVec = std::vector<WordSet>;
    using WordWPVec = std::vector<WordWP>;
    using PosVec = std::vector<unsigned>;
    using PhraseVec = std::vector<Phrase>;

    constexpr unsigned ATTRIBUTE_COUNT = 4;
    constexpr unsigned MAX_WORDS = 5;
    constexpr float MAX_POS = 10;
    constexpr float MAX_TRAINING = 20;
}
MY_NSP_END


#include "macros.fgen.hpp"
#endif
