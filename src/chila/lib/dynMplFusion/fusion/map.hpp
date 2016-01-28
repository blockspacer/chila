/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_DYNMPLFUSION_FUSION__MAP_HPP
#define CHILA_LIB_DYNMPLFUSION_FUSION__MAP_HPP

#include <boost/preprocessor.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/any.hpp>
#include <boost/assign.hpp>
#include <map>
#include <boost/fusion/include/at_c.hpp>

#define BOOST_PP_VARIADICS 1

#ifdef CHILA_LIB_DYNFUSION_FUSION__ENABLEMAP

#define CHILA_LIB_DYNFUSION_FUSION__DEFMAP(...) \
    chila::lib::dynMplFusion::fusion::DynMap<BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)>


#define CHILA_LIB_DYNFUSION_FUSION__MAKEMAP(...) \
    boost::assign::map_list_of<std::string, boost::any> BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)

#define CHILA_LIB_DYNFUSION_FUSION__MAP_AT(key, vec) \
    vec.data[typeid(key).name()]

#define CHILA_LIB_DYNFUSION_FUSION__MAP_TYPE_AT_TN(key, Map) boost::any

#define CHILA_LIB_DYNFUSION_FUSION__MAP_TYPE_AT(key, Map) boost::any

#define CHILA_LIB_DYNFUSION_FUSION__MAP_SIZE_OF(Map) Map::size

#else

#define CHILA_LIB_DYNFUSION_FUSION__TYPE_ELEM(r, data, i, elem) BOOST_PP_COMMA_IF(i) \
    boost::fusion::pair \
    < \
        BOOST_PP_TUPLE_ELEM(0, elem), \
        BOOST_PP_TUPLE_ELEM(1, elem) \
    >

//#define CHILA_LIB_DYNFUSION_FUSION__MAKE_ELEM(r, data, i, elem) BOOST_PP_COMMA_IF(i) \
//    boost::fusion::make_pair \
//    ( \
//        BOOST_PP_TUPLE_ELEM(0, elem), \
//        BOOST_PP_TUPLE_ELEM(1, elem) \
//    )

/** Defines a fusion map. */
#define CHILA_LIB_DYNFUSION_FUSION__DEFMAP(...) \
    boost::fusion::map< BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_DYNFUSION_FUSION__TYPE_ELEM,, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) >

///** Makes a fusion map. */
//#define CHILA_LIB_DYNFUSION_FUSION__MAKEMAP(...) \
//    boost::fusion::make_map(BOOST_PP_SEQ_ENUM(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

/** Access data from a map. */
#define CHILA_LIB_DYNFUSION_FUSION__MAP_AT(key, vec) \
    boost::fusion::at_c<key>(vec)

#define CHILA_LIB_DYNFUSION_FUSION__MAP_TYPE_AT(Map, key) \
    boost::fusion::result_of::at_c<Map, key>::type

#define CHILA_LIB_DYNFUSION_FUSION__MAP_TYPE_AT_TN(Map, key) \
    typename CHILA_LIB_DYNFUSION_FUSION__MAP_TYPE_AT(Map, key)

#define CHILA_LIB_DYNFUSION_FUSION__MAP_SIZE_OF(Map) \
    boost::fusion::result_of::size<Map>::value


#endif

#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,dynMplFusion,fusion)
{
    template <unsigned _size>
    struct DynMap
    {
        static const unsigned size = _size;

        typedef std::map<std::string, boost::any> MapType;
        MapType data;

        DynMap() {}

#define DEF_CONS_LARG(z, n, d) data[n] = BOOST_PP_CAT(arg, n);

#define DEF_CONS(z, n, d) \
        template <BOOST_PP_ENUM_PARAMS(n, typename Arg)> \
        DynMap(BOOST_PP_ENUM_BINARY_PARAMS(n, const Arg, &arg)) \
        { \
            data.resize(n); \
            BOOST_PP_REPEAT(n, DEF_CONS_LARG,) \
        }

//        BOOST_PP_REPEAT_FROM_TO(1, 49, DEF_CONS,)

        template <typename Type>
        DynMap(const Type &data)
        {
            this->data = data;
            my_assert(this->data.size() == size);
        }
    };
}}}}

#endif
