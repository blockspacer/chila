/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_TRANSLATE__WORD_HPP
#define CHILA_TRANSLATE__WORD_HPP

#include <chila/lib/misc/util.hpp>
#include <set>
#include "macros.fgen.hpp"

#define if_name(nname, VALUE) if (name == #nname) return Type::VALUE;


MY_NSP_START
{
    CHILA_LIB_MISC__NAMED_TUPLE(Word, 1,
        ((unsigned long)(id))
        ((std::string)(value))
        ((Type)(type))
        ((Gender)(gender))
        ((Cardinality)(cardinality))
        ((Time)(time))
    );

    CHILA_LIB_MISC__NAMED_TUPLE(WordWP, 1,
        ((unsigned)(pos))
        ((Word)(word))
    );

    inline std::ostream &operator<<(std::ostream &out, const Word &rhs)
    {
        return out << "<value='" << rhs.value << "', type='" << getName(rhs.type) << "'>";
    }

    inline std::ostream &operator<<(std::ostream &out, const WordWP &rhs)
    {
        return out << "<pos='" << rhs.pos << "', word='" << rhs.word << "'>";
    }

    CHILA_LIB_MISC__NAMED_TUPLE(Phrase, 1,
        ((WordWPVec)(words))
        ((PosVec)(positions))
    );
}
MY_NSP_END

#undef if_name
#include "macros.fgen.hpp"
#endif
