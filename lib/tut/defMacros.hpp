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

#define CHILA_LIB_TUT__DEF_TEST_GROUP(Name) \
    typedef test_group<Name##Data> tg;        \
    tg Name##Group(#Name);

#define CHILA_LIB_TUT__DEF_TEST(num, Name) \
        template<> template<>               \
        void tg::object::test<num>()        \
        {                                   \
            set_test_name(Name);


#define CHILA_LIB_TUT__ENSURE(exp) \
        CHILA_LIB_TUT__CHECKPOINT(), ensure(#exp, exp)

#define CHILA_LIB_TUT__ENSURE_EQUAL(lhs, rhs) \
        CHILA_LIB_TUT__CHECKPOINT(), chila::lib::tut::ensureEqual(lhs, rhs)

#define CHILA_LIB_TUT__ENSURE_THROW(exp, exception) \
        try                                             \
        {                                               \
            CHILA_LIB_TUT__CHECKPOINT();      \
            exp;                                        \
            fail("exception expected: " #exception);    \
        }                                               \
        catch (const exception &ex) {}


#define CHILA_LIB_TUT__CHECKPOINT() \
        chila::lib::tut::checkPoint().set(__FILE__, __LINE__)

