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

    #ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGMAPEXECUTER_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGMAPEXECUTER_HPP

    #include <boost/preprocessor.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/mpl/int.hpp>
    #include <boost/fusion/sequence/intrinsic/at.hpp>
    #include <boost/type_traits/is_same.hpp>

    #include <chila/lib/misc/macrosDef.hpp>

    #define EX_SIZE boost::mpl::size<typename action::Arguments>::value

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ConnectorDescMap, typename AProviderStack, typename action, unsigned argCount>
        struct ArgMapExecuterImpl {};

        template <typename ConnectorDescMap, typename AProviderStack, typename action>
        struct ArgMapExecuter :
            public ArgMapExecuterImpl<ConnectorDescMap, AProviderStack, action, EX_SIZE>
        {
            ArgMapExecuter(const action &ac) :
                ArgMapExecuterImpl<ConnectorDescMap, AProviderStack, action, EX_SIZE>(ac) {}
        };

        template <typename ConnectorDescMap, typename AProviderStack, typename action>
        inline ArgMapExecuter<ConnectorDescMap, AProviderStack, action> argMapExecuter(const action &ac)
        {
            return ArgMapExecuter<ConnectorDescMap, AProviderStack, action>(ac);
        }
    }}}}

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/ArgMapExecuter.hpp>
    #include BOOST_PP_ITERATE()

    #undef EX_SIZE
    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosUndef.hpp>
    #endif

#else

    #include <chila/lib/misc/macrosDef.hpp>

    #define ARG_AT(pos) typename boost::mpl::at_c<typename action::Arguments, pos>::type
    #define ALIAS_OF_ARG(arg) typename boost::mpl::at<ArgAliasLinks, arg>::type
    #define VAL(z, pos, data) aProviderStack.getArgument(ALIAS_OF_ARG(ARG_AT(pos))())

    #define argCount BOOST_PP_ITERATION()

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ConnectorDescMap, typename AProviderStack, typename action>
        struct ArgMapExecuterImpl<ConnectorDescMap, AProviderStack, action, argCount>
        {
            typedef typename boost::mpl::at<ConnectorDescMap, typename action::ConnectorType>::type::ArgAliasLinks
                ArgAliasLinks;

            action ac;
            typedef typename action::Result result_type;

            ArgMapExecuterImpl(const action &ac) : ac(ac) {}

            result_type operator()(const AProviderStack &aProviderStack) const
            {
                return ac.function(BOOST_PP_ENUM(argCount, VAL,));
            }
        };
    }}}}


    #undef argCount
    #undef ARG_AT
    #undef ALIAS_OF_ARG
    #undef VAL
    #undef DEF_NAMESPACE 
    #include <chila/lib/misc/macrosUndef.hpp>


#endif
