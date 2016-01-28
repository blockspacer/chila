/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../util.hpp"
#include "../exceptions.hpp"
#include <typeinfo>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/test/parameterized_test.hpp>
#include <iostream>

#include "common.hpp"
#include <chila/lib/misc/macrosExp.hpp>

namespace tut
{
    struct utilData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(util)

    CHILA_LIB_TUT__DEF_TEST(1, "check")
    {
        TiXmlDocument doc;

        libMisc::check(doc);

        doc.LoadFile("fail!");

        TUT_ENSURE_THROW(libMisc::check(doc), libMisc::TiXmlError);
    }}
}

