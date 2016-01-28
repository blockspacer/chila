/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Dictionary.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    void Dictionary::addWord(const std::string &value, Type type, Gender gender, Cardinality cardinality, Time time)
    {
        my_assert(wordMap.insert({value, {wordMap.size(), value, type, gender, cardinality, time}}).second);
    }

    void Dictionary::addTranslation(const std::string &from, const std::string &to)
    {
        auto it = wordMap.find(to);
        my_assert(it != wordMap.end());

        my_assert(map[from].insert(it->second).second);
    }

    const WordSet &Dictionary::getTranslations(const std::string &name) const
    {
        auto it = map.find(name);
        if (it == map.end())
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        return it->second;
    }

    const Word &Dictionary::getWord(const std::string &name) const
    {
        auto it = wordMap.find(name);
        if (it == wordMap.end())
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        return it->second;
    }
}
MY_NSP_END
