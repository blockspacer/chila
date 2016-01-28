/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../RepeatText.hpp"
#include "common.hpp"
#include <sstream>
#include <chila/lib/misc/macrosExp.hpp>

namespace tut
{
    struct RepeatTextData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(RepeatText)

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        std::stringstream str;
        str << libMisc::repeatText(4, "hitman");
        TUT_ENSURE_EQUAL(str.str(),"hitmanhitmanhitmanhitman");
    }}
}

