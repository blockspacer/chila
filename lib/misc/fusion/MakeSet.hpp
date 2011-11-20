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

#ifndef BOOST_PP_IS_ITERATING

    #ifndef _CHILA_LIB_MISC_FUSION_MAKESET_H
    #define _CHILA_LIB_MISC_FUSION_MAKESET_H

    #warning Not tested!

    #include <boost/preprocessor.hpp>
    #include <boost/fusion/container/set.hpp>
    #include <boost/mpl/set.hpp>


    #include <chila/lib/misc/macrosDef.hpp>

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,lib,misc,fusion))
    {
        template <typename MPLForwardSeq, unsigned argCount>
        struct MakeSetImpl {};

        template <typename MPLForwardSeq>
        struct MakeSet : public MakeSetImpl< MPLForwardSeq, boost::mpl::size<MPLForwardSeq>::value >
        {
        };

    }}}}

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 10)
    #define BOOST_PP_FILENAME_1         <chila/lib/misc/fusion/MakeSet.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosDef.hpp>
    #endif

#else

    #include <chila/lib/misc/macrosDef.hpp>

    #define argCount BOOST_PP_ITERATION()

    #define DEF_PARAM(z, index, data) typename boost::mpl::at_c<MPLForwardSeq, index>::value

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,lib,misc,fusion))
    {

        template <typename MPLForwardSeq>
        struct MakeSetImpl<MPLForwardSeq, argCount>
        {
            typedef boost::mpl::set<BOOST_PP_ENUM(argCount, DEF_PARAM,)> type;
        };

    }}}}

    #undef DEF_PARAM
    #undef argCount
    #undef DEF_NAMESPACE

    #include <chila/lib/misc/macrosUndef.hpp>

#endif