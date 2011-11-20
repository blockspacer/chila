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

    #ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_APROVIDERSTACKER_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_CODEGEN_APROVIDERSTACKER_HPP

    #include <boost/preprocessor.hpp>
    #include "ArgumentGetter.hpp"
    #include <chila/lib/misc/macrosDef.hpp>

    #define APCFVEC_SIZE boost::fusion::result_of::size<ApcFVec>::value

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ApcFVec, typename InArgMap, typename FunToProvide, unsigned argCount>
        struct AProviderStackerImpl {};

        template <typename ApcFVec, typename InArgMap, typename FunToProvide>
        struct AProviderStacker :
            public AProviderStackerImpl<ApcFVec, InArgMap, FunToProvide, APCFVEC_SIZE>
        {
            AProviderStacker(const ApcFVec &apcFVec, FunToProvide funToProvide) :
                AProviderStackerImpl<ApcFVec, InArgMap, FunToProvide, APCFVEC_SIZE>(apcFVec, funToProvide) {}
        };

        template <typename InArgMap, typename ApcFVec, typename FunToProvide>
        inline AProviderStacker<ApcFVec, InArgMap, FunToProvide> aProviderStacker(const ApcFVec &apcFVec,
            FunToProvide funToProvide)
        {
            return AProviderStacker<ApcFVec, InArgMap, FunToProvide>(apcFVec, funToProvide);
        }


    }}}}

    #undef APCFVEC_SIZE

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/AProviderStacker.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_NAMESPACE 
    #include <chila/lib/misc/macrosUndef.hpp>
    #endif

#else

    #include <chila/lib/misc/macrosDef.hpp>

    #define genCount BOOST_PP_ITERATION()

    #define APC_PASS_ARG(z, index, data) \
        boost::fusion::at_c<BOOST_PP_DEC(BOOST_PP_SUB(genCount, index))>(apcFVec).createAProvider(

    #define APC_CLOSE_FUN(z, index, data) BOOST_PP_RPAREN()

    #define APC_TYPE_AT(index) boost::fusion::result_of::value_at_c<                            \
            ApcFVec, BOOST_PP_DEC(BOOST_PP_SUB(genCount, index))>::type

    #define APC_PASS_TMPL_ARG(z, index, data)                                                   \
        typename boost::fusion::result_of::value_at_c<                                          \
            ApcFVec, BOOST_PP_DEC(BOOST_PP_SUB(genCount, index))>::type::template ResultOf<

    #define APC_CLOSE_TMPL_ARG(z, index, data)  >::Type

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ApcFVec, typename InArgMap, typename FunToProvide>
        struct AProviderStackerImpl<ApcFVec, InArgMap, FunToProvide, genCount>
        {
            typedef
                BOOST_PP_REPEAT(genCount, APC_PASS_TMPL_ARG,)           // Generators
                ArgumentGetter<InArgMap>                                // ArgumentGetter
                BOOST_PP_REPEAT(genCount, APC_CLOSE_TMPL_ARG,)          // close template args
                ResultType;

            ApcFVec apcFVec;
            FunToProvide funToProvide;
            typedef typename FunToProvide::result_type result_type;
            AProviderStackerImpl(ApcFVec apcFVec, FunToProvide funToProvide) :
                apcFVec(apcFVec), funToProvide(funToProvide) {}

            result_type operator()(const InArgMap &inArgs)
            {
                return funToProvide                             // Stack of (from last to first)...
                (
                    BOOST_PP_REPEAT(genCount, APC_PASS_ARG,)    // ArgumentProviders
                    argumentGetter(inArgs)                      // ArgumentGetter
                    BOOST_PP_REPEAT(genCount, APC_CLOSE_FUN,)   // close parentheses
                );
            }

            ResultType create(const InArgMap &inArgs) const
            {
                return                                          // Stack of (from last to first)...
                (
                    BOOST_PP_REPEAT(genCount, APC_PASS_ARG,)    // Generators
                    argumentGetter(inArgs)                      // ArgumentGetter
                    BOOST_PP_REPEAT(genCount, APC_CLOSE_FUN,)   // close parentheses
                );
            }
        };
    }}}}

    #undef genCount
    #undef APC_PASS_ARG
    #undef APC_CLOSE_FUN
    #undef DEF_APC_STACKER
    #undef APC_PASS_TMPL_ARG
    #undef APC_CLOSE_TMPL_ARG
    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosUndef.hpp>

#endif
