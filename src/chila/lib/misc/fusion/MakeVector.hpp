/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef BOOST_PP_IS_ITERATING

    #ifndef CHILA_LIB_MISC_FUSION__MAKEVECTOR_HPP
    #define CHILA_LIB_MISC_FUSION__MAKEVECTOR_HPP

    #warning Not tested!

    #include <boost/preprocessor.hpp>
    #include <boost/fusion/container/vector.hpp>
    #include <boost/mpl/vector.hpp>


    #include "macros.fgen.hpp"

    MY_NSP_START
    {
        template <typename MPLForwardSeq, unsigned argCount>
        struct MakeVectorImpl {};

        template <typename MPLForwardSeq>
        struct MakeVector final: public MakeVectorImpl< MPLForwardSeq, boost::mpl::size<MPLForwardSeq>::value >
        {
        };

    }
    MY_NSP_END

    #include "macros.fgen.hpp"


    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 10)
    #define BOOST_PP_FILENAME_1         <chila/lib/misc/fusion/MakeVector.hpp>
    #include BOOST_PP_ITERATE()

    #endif

#else

    #include <chila/lib/misc/macrosExp.hpp>

    #define argCount BOOST_PP_ITERATION()

    #define DEF_PARAM(z, index, data) typename boost::mpl::at_c<MPLForwardSeq, index>::value

    #include "macros.fgen.hpp"

    MY_NSP_START
    {

        template <typename MPLForwardSeq>
        struct MakeVectorImpl<MPLForwardSeq, argCount>
        {
            typedef boost::mpl::vector<BOOST_PP_ENUM(argCount, DEF_PARAM,)> type;
        };

    }
    MY_NSP_END

    #include "macros.fgen.hpp"


    #undef DEF_PARAM
    #undef argCount

#endif
