/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_TRANSLATE__DICTIONARY_HPP
#define CHILA_TRANSLATE__DICTIONARY_HPP

#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include "Word.hpp"
#include <map>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Dictionary
    {
        public:
            void addWord(const std::string &value, Type type, Gender gender, Cardinality cardinality, Time time);
            void addTranslation(const std::string &from, const std::string &to);
            const WordSet &getTranslations(const std::string &name) const;
            const Word &getWord(const std::string &name) const;

        private:
            using Map = std::map<std::string, WordSet>;
            using WordMap = std::map<std::string, Word>;
            Map map;
            WordMap wordMap;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
