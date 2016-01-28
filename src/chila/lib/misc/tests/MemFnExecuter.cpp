/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../MemFnExecuter.hpp"
#include "common.hpp"
#include <boost/mem_fn.hpp>


namespace tut
{
    struct MemFnExecuterData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(MemFnExecuter)

    struct Test
    {
        unsigned myVal;

        unsigned test1() const { return 22; }
        void test2(unsigned val) { myVal = val; }
        std::string test3(const std::string &val1, const std::string &val2) const
        {
            return val1 + val2;
        }
    };

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        Test test;
        TUT_ENSURE(libMisc::memFnExecuter(boost::mem_fn(&Test::test1), test)() == 22);
        libMisc::memFnExecuter(boost::mem_fn(&Test::test2), boost::ref(test))(98);
        TUT_ENSURE(test.myVal == 98);
        TUT_ENSURE(libMisc::memFnExecuter(boost::mem_fn(&Test::test3), boost::cref(test))("hello ", "world") == "hello world");
    }}

}

