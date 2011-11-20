/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../MemFnExecuter.hpp"
#include "common.hpp"
#include <boost/mem_fn.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE


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

