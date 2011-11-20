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


    #ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTPROVIDER_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTPROVIDER_HPP

    #include <boost/preprocessor.hpp>
    #include <boost/mpl/at.hpp>
    #include <boost/mpl/has_key.hpp>
    #include <chila/lib/misc/macrosDef.hpp>

    #define SET_SIZE(vec) boost::fusion::result_of::size<ArgsProvidedFSet>::value

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {

        template <typename PrevProvidder, typename ProviderFun, typename ArgsProvidedFSet, unsigned argCount>
        struct ArgumentProviderImpl {};

        template <typename PrevProvidder, typename ProviderFun, typename ArgsProvidedFSet>
        struct ArgumentProvider :
            public ArgumentProviderImpl<PrevProvidder, ProviderFun, ArgsProvidedFSet, SET_SIZE(ArgsProvidedFSet)>
        {
            typedef ArgumentProviderImpl<PrevProvidder, ProviderFun, ArgsProvidedFSet, SET_SIZE(ArgsProvidedFSet)> Base;

            ArgumentProvider(ProviderFun providerFun, PrevProvidder prevProvider) :
                Base(prevProvider, providerFun) {}
        };

        template <typename ArgsProvidedFSet, typename PrevProvider, typename ProviderFun>
        inline ArgumentProvider<PrevProvider, ProviderFun, ArgsProvidedFSet> argumentProvider(
            PrevProvider prevProvider, ProviderFun providerFun)
        {
            return ArgumentProvider<PrevProvider, ProviderFun, ArgsProvidedFSet>(providerFun, prevProvider);
        }

    }}}}

    #undef SET_SIZE

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/ArgumentProvider.hpp>
    #include BOOST_PP_ITERATE()

    #include <chila/lib/misc/macrosDef.hpp>
    #undef DEF_NAMESPACE
    #endif

#else

    #define argCount BOOST_PP_ITERATION()
    #define GET_ARGUMENT_FUN(z, index, data) \
        typename This::ProviderFun::template result_of<ALIAS_AT(index)>::type \
            getArgument(ALIAS_AT(index)) const { return providerFun.getArgument(ALIAS_AT(index)()); }
    #define RESULT_OF_ALIAS(Provider, AliasType)   \
        typename Provider::template result_of<AliasType>

    #define ALIAS_ITER(z, index, data) typedef BOOST_PP_IF(index, \
        typename boost::mpl::next<BOOST_PP_CAT(AliasIter, BOOST_PP_DEC(index)>::type), \
        typename boost::mpl::begin<ArgsProvidedFSet>::type) AliasIter##index;

    #define ALIAS_AT(index) typename boost::mpl::deref<AliasIter##index>::type

    #define SET_CONTAINS(AliasType) boost::mpl::has_key<ArgsProvidedFSet, AliasType>

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {

        template <typename PrevProvidder, typename _ProviderFun, typename ArgsProvidedFSet>
        struct ArgumentProviderImpl<PrevProvidder, _ProviderFun, ArgsProvidedFSet, argCount>
        {
            typedef _ProviderFun ProviderFun;
            typedef ArgumentProviderImpl<PrevProvidder, ProviderFun, ArgsProvidedFSet, argCount> This;

            BOOST_PP_REPEAT(argCount, ALIAS_ITER, )

            PrevProvidder prevProvider;
            ProviderFun providerFun;

            // Default result of getArgument, taken from the next provider
            template <typename AliasType>
            struct result_of
            {
                typedef typename boost::mpl::eval_if<SET_CONTAINS(AliasType),
                    RESULT_OF_ALIAS(ProviderFun, AliasType),
                    RESULT_OF_ALIAS(PrevProvidder, AliasType)>::type type;
            };

            // Constructor
            ArgumentProviderImpl(PrevProvidder prevProvider, ProviderFun providerFun) :
                prevProvider(prevProvider), providerFun(providerFun) {}

            // Default getArgument, the value is taken from the next provider
            template <typename AliasType>
            typename result_of<AliasType>::type getArgument(AliasType) const
            {
                return this->prevProvider.getArgument(AliasType());
            }

            // Specializations of getArgument, values taken from 'providerFun'
            BOOST_PP_REPEAT(argCount, GET_ARGUMENT_FUN,)
        };

    }}}}

    #undef argCount
    #undef GET_ARGUMENT_FUN
    #undef RESULT_OF_ALIAS
    #undef ALIAS_ITER
    #undef ALIAS_AT
    #undef SET_CONTAINS
    #undef DEF_NAMESPACE 

    #include <chila/lib/misc/macrosDef.hpp>

#endif

