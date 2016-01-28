/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../Construct.hpp"
#include "common.hpp"
#include <iostream>
#include <chila/lib/misc/macrosExp.hpp>

namespace tut
{
    struct ConstructData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(Construct)

    struct Test0
    {
        unsigned var;
        Test0() : var(55) {}
    };

    struct Test1
    {
        unsigned var0;
        Test1(unsigned var0) : var0(var0) {}
    };

    struct Test2
    {
        unsigned var0, &var1;
        Test2(unsigned var0, unsigned &var1) : var0(var0), var1(var1) {}
    };

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        unsigned myVar;
        unsigned tt = 99;

        Test0 test0 = libMisc::Construct<Test0>()();
        TUT_ENSURE(test0.var == 55);

        Test1 test1 = libMisc::Construct<Test1>()(80);
        TUT_ENSURE(test1.var0 == 80);

        Test2 test2 = libMisc::Construct<Test2>()(tt, boost::ref(myVar));
        myVar = 56;
        TUT_ENSURE(test2.var0 == 99);
        TUT_ENSURE(test2.var1 == 56);
    }}
}

