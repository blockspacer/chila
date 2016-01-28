/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define CHILA_LIB_DYNFUSION_FUSION__ENABLEVECTOR

#include <iostream>
#include <typeinfo>
#include <chila/lib/dynMplFusion/fusion/vector.hpp>
#include <chila/lib/dynMplFusion/fusion/map.hpp>
#include <chila/lib/dynMplFusion/util.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define SHOW    CHILA_LIB_MISC__SHOW

template <typename Vec, unsigned pos>
struct vec_result_of
{
    typedef CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT_TN(Vec, pos) type;
};

void vecTest();
void mapTest();

int main(int argc, char** argv)
{
    vecTest();


    return 0;
}

void vecTest()
{
    typedef CHILA_LIB_DYNFUSION_FUSION__DEFVECTOR(int, char) Test;

    Test test(3, 'a');

    SHOW(chila::lib::dynMplFusion::cast<int>(CHILA_LIB_DYNFUSION_FUSION__VEC_AT(0, test)));
    SHOW(chila::lib::dynMplFusion::cast<char>(CHILA_LIB_DYNFUSION_FUSION__VEC_AT(1, test)));

    SHOW(typeid(vec_result_of<Test, 0>::type).name());
    SHOW(typeid(vec_result_of<Test, 1>::type).name());

    SHOW(CHILA_LIB_DYNFUSION_FUSION__VEC_SIZE_OF(Test));

}

struct type0 {};
struct type1 {};

void mapTest()
{
    typedef CHILA_LIB_DYNFUSION_FUSION__DEFMAP
    (
        (type0, int),
        (type1, char)
    ) Test;

//    Test test = CHILA_LIB_DYNFUSION_FUSION__MAKEMAP(3, 'a');
//
//    SHOW(chila::lib::dynMplFusion::cast<int>(CHILA_LIB_DYNFUSION_FUSION__MAP_AT(0, test)));
//    SHOW(chila::lib::dynMplFusion::cast<char>(CHILA_LIB_DYNFUSION_FUSION__MAP_AT(1, test)));
//
//    SHOW(typeid(vec_result_of<Test, 0>::type).name());
//    SHOW(typeid(vec_result_of<Test, 1>::type).name());
//
//    SHOW(CHILA_LIB_DYNFUSION_FUSION__MAP_SIZE_OF(Test));
}
