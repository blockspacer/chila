/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_DYNMPLFUSION_FUSION__VECTOR_HPP
#define CHILA_LIB_DYNMPLFUSION_FUSION__VECTOR_HPP

#include <boost/preprocessor.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/any.hpp>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/include/at_c.hpp>

#define BOOST_PP_VARIADICS 1

#ifdef CHILA_LIB_DYNFUSION_FUSION__ENABLEVECTOR

#define CHILA_LIB_DYNFUSION_FUSION__DEFVECTOR(...) \
    chila::lib::dynMplFusion::fusion::DynVector<BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)>


//#define CHILA_LIB_DYNFUSION_FUSION__MAKEVECTOR(...) \
//    boost::assign::list_of<boost::any> BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)

#define CHILA_LIB_DYNFUSION_FUSION__VEC_AT(pos, vec) \
    vec.data.at(pos)

#define CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT_TN(pos, Vec) boost::any

#define CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT(pos, Vec) boost::any

#define CHILA_LIB_DYNFUSION_FUSION__VEC_SIZE_OF(Vec) Vec::size

#else

/** Defines a fusion vector. */
#define CHILA_LIB_DYNFUSION_FUSION__DEFVECTOR(...) \
    boost::fusion::vector< BOOST_PP_SEQ_ENUM(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) >

///** Makes a fusion vector. */
//#define CHILA_LIB_DYNFUSION_FUSION__MAKEVECTOR(...) \
//    boost::fusion::make_vector(BOOST_PP_SEQ_ENUM(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

/** Access data from a vector. */
#define CHILA_LIB_DYNFUSION_FUSION__VEC_AT(pos, vec) \
    boost::fusion::at_c<pos>(vec)

#define CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT(Vec, pos) \
    boost::fusion::result_of::at_c<Vec, pos>::type

#define CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT_TN(Vec, pos) \
    typename CHILA_LIB_DYNFUSION_FUSION__VEC_TYPE_AT(Vec, pos)

#define CHILA_LIB_DYNFUSION_FUSION__VEC_SIZE_OF(Vec) \
    boost::fusion::result_of::size<Vec>::value


#endif

#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,dynMplFusion,fusion)
{
    template <unsigned _size>
    struct DynVector
    {
        static const unsigned size = _size;

        typedef std::vector<boost::any> VecType;
        VecType data;

        DynVector() { data.resize(size); }

#define DEF_CONS_LARG(z, n, d) data[n] = BOOST_PP_CAT(arg, n);

#define DEF_CONS(z, n, d) \
        template <BOOST_PP_ENUM_PARAMS(n, typename Arg)> \
        DynVector(BOOST_PP_ENUM_BINARY_PARAMS(n, const Arg, &arg)) \
        { \
            data.resize(n); \
            BOOST_PP_REPEAT(n, DEF_CONS_LARG,) \
        }

        BOOST_PP_REPEAT_FROM_TO(1, 49, DEF_CONS,)

//        template <typename Type>
//        DynVector(const Type &data)
//        {
//            this->data = data;
//            my_assert(this->data.size() == size);
//        }
    };
}}}}

#undef DEF_CONS_LARG
#undef DEF_CONS
#endif
