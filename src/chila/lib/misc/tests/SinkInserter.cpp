/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../SinkInserter.hpp"
#include "common.hpp"
#include <sstream>
#include <iostream>
#include <chila/lib/misc/macrosExp.hpp>

namespace tut
{
    struct SinkInserterData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(SinkInserter)

    struct MyInserter final: public libMisc::SinkInserter<MyInserter>
    {
        template <typename Sink>
        void write(Sink &out) const
        {
            out << "hello world!";
        }
    };

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        std::stringstream str;
        str << MyInserter();
        TUT_ENSURE_EQUAL(str.str(), "hello world!");
    }}

}

