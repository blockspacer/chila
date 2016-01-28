/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__REPEATTEXT_HPP
#define CHILA_LIB_MISC__REPEATTEXT_HPP

#include "SinkInserter.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename StringType>
    struct RepeatText final: public chila::lib::misc::SinkInserter< RepeatText<StringType> >
    {
        unsigned count;
        StringType text;
        RepeatText(unsigned count, StringType text) :
            count(count), text(text) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            for (unsigned i = 0; i < count; ++i) out << text;
        }
    };

    template <typename StringType>
    inline RepeatText<StringType> repeatText(unsigned count, StringType text)
    {
        return RepeatText<StringType>(count, text);
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
