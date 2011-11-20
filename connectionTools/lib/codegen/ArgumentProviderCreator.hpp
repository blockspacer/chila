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


    #ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTPROVIDERCREATOR_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTPROVIDERCREATOR_HPP

    #include <boost/preprocessor.hpp>
    #include "ArgumentProvider.hpp"
    #include <boost/mpl/has_key.hpp>
    #include <boost/fusion/view.hpp>
    #include <boost/mpl/at.hpp>
    #include <boost/fusion/sequence/intrinsic/size.hpp>
    #include <chila/lib/misc/fusion/MakeSet.hpp>
    #include <boost/type_traits/is_same.hpp>
    #include <chila/lib/misc/macrosDef.hpp>

    #define GET_SIZE(vec) boost::fusion::result_of::size<RequiredAliasesFSec>::value

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {

        template <typename AProviderCreatorFun, typename RequiredAliasesFSec, typename ProvidedAliasesFSec,
                unsigned argCount>
        struct ArgumentProviderCreatorImpl {};

        template <typename AProviderCreatorFun, typename RequiredAliasesFSec, typename ProvidedAliasesFSec>
        struct ArgumentProviderCreator :
            public ArgumentProviderCreatorImpl<AProviderCreatorFun, RequiredAliasesFSec, ProvidedAliasesFSec,
                   GET_SIZE(RequiredAliasesFSec)>
        {
            typedef ArgumentProviderCreatorImpl<AProviderCreatorFun, RequiredAliasesFSec, ProvidedAliasesFSec,
                    GET_SIZE(RequiredAliasesFSec)> Base;

            ArgumentProviderCreator(AProviderCreatorFun aProviderCreatorFun) :
                Base(aProviderCreatorFun) {}
        };

        template <typename RequiredAliasesFSec, typename ProvidedAliasesFSec, typename AProviderCreatorFun>
        inline ArgumentProviderCreator<AProviderCreatorFun, RequiredAliasesFSec, ProvidedAliasesFSec>
            argumentProviderCreator(AProviderCreatorFun aProviderCreatorFun)
        {
            return ArgumentProviderCreator<AProviderCreatorFun, RequiredAliasesFSec, ProvidedAliasesFSec>(
                   aProviderCreatorFun);
        }


        /** Helper Adaptor for ArgProviderCreatorFuns. */
        template <typename ArgProviderCreatorFun>
        struct ArgumentProviderCreatorFunAdaptor
        {
            typedef typename ArgProviderCreatorFun::result_type ArgProvider;
            typedef typename ArgProvider::ResultOfMap ResultOfMap;

            struct AProvider
            {
                ArgProvider argProvider;

                template <typename AliasType>
                struct result_of
                {
                    BOOST_MPL_ASSERT((boost::mpl::has_key<ResultOfMap, AliasType>));
                    typedef typename boost::mpl::at<ResultOfMap, AliasType>::type type;
                };

                AProvider(ArgProvider argProvider) : argProvider(argProvider) {}

                template <typename AliasType>
                typename result_of<AliasType>::type getArgument(AliasType) const
                {
                    return argProvider.getArgument(AliasType());
                }
            };

            ArgProviderCreatorFun argProviderCreatorFun;

            ArgumentProviderCreatorFunAdaptor(ArgProviderCreatorFun argProviderCreatorFun) :
                argProviderCreatorFun(argProviderCreatorFun) {}

            AProvider create() const { return AProvider(argProviderCreatorFun()); }

            #define DEF_CREATE_FUN(z, argCount, data)                                                   \
                template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                                 \
                AProvider create(BOOST_PP_ENUM_BINARY_PARAMS(argCount, Arg, &arg)) const                \
                {                                                                                       \
                    return AProvider(argProviderCreatorFun(BOOST_PP_ENUM_PARAMS(argCount, arg)));       \
                }

            BOOST_PP_REPEAT_FROM_TO(1, 9, DEF_CREATE_FUN, )


            #undef DEF_CREATE_FUN
        };

        template <typename ArgProviderCreatorFun>
        inline ArgumentProviderCreatorFunAdaptor<ArgProviderCreatorFun> argumentProviderCreatorFunAdaptor(
            ArgProviderCreatorFun argProviderCreatorFun)
        {
            return ArgumentProviderCreatorFunAdaptor<ArgProviderCreatorFun>(argProviderCreatorFun);
        }

    }}}}

    #undef GET_SIZE

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/ArgumentProviderCreator.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_NAMESPACE

    #include <chila/lib/misc/macrosDef.hpp>
    #endif

#else

    #define argCount BOOST_PP_ITERATION()
    #define GET_REQ_ALIAS_AT(index) typename boost::mpl::at_c<RequiredAliasesFSec, index>::type
    #define GET_PROV_ALIAS_AT(index) typename boost::mpl::at_c<ProvidedAliasesFSec, index>::type
    #define GET_ARGUMENT(z, index, data) prevProvider.getArgument(GET_REQ_ALIAS_AT(index)())
    #define CREATE_APROVIDER(argCount) \
        aProviderCreatorFun.create(BOOST_PP_ENUM(argCount, GET_ARGUMENT,))

//    #define RETURN_OF_ALIAS(z, index, data) \
//        typedef typename ProvidedAliasesFSec::AProvider::template result_of<GET_PROV_ALIAS_AT(index)>::type \
//            Alias##index;

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename AProviderCreatorFun, typename RequiredAliasesFSec, typename ProvidedAliasesFSec>
        struct ArgumentProviderCreatorImpl<AProviderCreatorFun, RequiredAliasesFSec, ProvidedAliasesFSec, argCount>
        {
//            struct RetTypes
//            {
//                BOOST_PP_REPEAT(argCount, RETURN_OF_ALIAS,)
//            };

            template <typename PrevProvider>
            struct ResultOf
            {
                typedef ArgumentProvider<PrevProvider, typename AProviderCreatorFun::AProvider, ProvidedAliasesFSec>
                    Type;
            };

            AProviderCreatorFun aProviderCreatorFun;

            ArgumentProviderCreatorImpl(AProviderCreatorFun aProviderCreatorFun) :
                aProviderCreatorFun(aProviderCreatorFun) {}

            template <typename PrevProvider>
            typename ResultOf<PrevProvider>::Type createAProvider(PrevProvider prevProvider) const
            {
                return argumentProvider<ProvidedAliasesFSec>(prevProvider, CREATE_APROVIDER(argCount));
            }
        };


    }}}}

    #undef GET_REQ_ALIAS_AT
    #undef GET_ARGUMENT
    #undef CREATE_APROVIDER
    #undef argCount
    #undef DEF_NAMESPACE 

    #include <chila/lib/misc/macrosDef.hpp>

#endif

