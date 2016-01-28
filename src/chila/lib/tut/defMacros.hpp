/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define CHILA_LIB_TUT__DEF_TEST_GROUP(Name) \
    typedef test_group<Name##Data> tg;        \
    tg tg##Name(#Name);

#define CHILA_LIB_TUT__DEF_TEST(num, Name) \
        template<>                                          \
        template<>                                          \
        void tg::object::test<num>()          \
        {                                                   \
            set_test_name(Name);


#define CHILA_LIB_TUT__ENSURE(exp) \
        CHILA_LIB_TUT__CHECKPOINT, ensure(#exp, exp)

#define CHILA_LIB_TUT__ENSURE_EQUAL(lhs, rhs) \
        CHILA_LIB_TUT__CHECKPOINT, chila::lib::tut::ensureEqual(#lhs, (lhs), (rhs))

#define CHILA_LIB_TUT__ENSURE_THROW(exp, exception) \
        try                                             \
        {                                               \
            CHILA_LIB_TUT__CHECKPOINT;      \
            exp;                                        \
            fail("exception expected: " #exception);    \
        }                                               \
        catch (const exception &ex) {}


#define CHILA_LIB_TUT__CHECKPOINT \
        chila::lib::tut::checkPoint().set(__FILE__, __LINE__)

