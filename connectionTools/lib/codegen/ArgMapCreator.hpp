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


    #ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGMAPCREATOR_HPP
    #define CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGMAPCREATOR_HPP

    #include <boost/mpl/vector.hpp>
    #include <boost/preprocessor.hpp>
    #include <boost/fusion/container/map.hpp>
    #include <chila/lib/misc/macrosDef.hpp>

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ArgAliasLinks, typename event, unsigned argCount>
        struct InArgMapCreatorImpl {};

        template <typename ArgAliasLinks, typename event>
        struct InArgMapCreator : public InArgMapCreatorImpl<
            ArgAliasLinks, event, boost::mpl::size<typename event::Arguments>::value> {};

        template <typename ArgAliasLinks, typename event, unsigned argCount>
        struct OutArgMapCreatorImpl {};

        template <typename ArgAliasLinks, typename event>
        struct OutArgMapCreator : public OutArgMapCreatorImpl<
            ArgAliasLinks, event, boost::mpl::size<typename event::Arguments>::value> {};


        //BOOST_PP_REPEAT(10, DEF_MAP_CREATOR,)
    }}}}

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/ArgMapCreator.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosUndef.hpp>
    #endif

#else

    #define GET_ARG(index) typename boost::mpl::at_c<typename FunctionMData::Arguments, index>::type
    #define ALIAS_OF_ARG(index) typename boost::mpl::at<ArgAliasLinks, GET_ARG(index)>::type

    #define DEF_FU_MAP_ELEM(z, index, data) \
        boost::fusion::pair< ALIAS_OF_ARG(index), GET_ARG(index)::DataType >

    #define DEF_OP_ARG(z, index, data)          const GET_ARG(index)::DataType &arg##index
    #define DEF_MPL_MAP_ELEM(z, index, data)    boost::mpl::pair<ALIAS_OF_ARG(index), GET_ARG(index)>
    #define DEF_MPL_VEC_ELEM(z, index, data)    ALIAS_OF_ARG(index)

    #define argCount BOOST_PP_ITERATION()

    #include <chila/lib/misc/macrosDef.hpp>

    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {

        template <typename ArgAliasLinks, typename event>
        struct InArgMapCreatorImpl<ArgAliasLinks, event, argCount>
        {
            typedef event FunctionMData;
            typedef boost::fusion::map< BOOST_PP_ENUM(argCount, DEF_FU_MAP_ELEM,) > MapType;

            MapType operator()(BOOST_PP_ENUM(argCount, DEF_OP_ARG,)) const
            {
                return MapType(BOOST_PP_ENUM_PARAMS(argCount, arg));
            }

            template <typename Fun>
            struct ArgSynthetizer
            {
                Fun fun;
                ArgSynthetizer(Fun fun) : fun(fun) {}
                typedef typename event::Result result_type;

                result_type operator()(BOOST_PP_ENUM(argCount, DEF_OP_ARG,))
                {
                    return fun(MapType(BOOST_PP_ENUM_PARAMS(argCount, arg)));
                }
            };

            template <typename Fun>
            static ArgSynthetizer<Fun> argSynthetizer(Fun fun)
            {
                return ArgSynthetizer<Fun>(fun);
            }
        };

        template <typename ArgAliasLinks, typename action>
        struct OutArgMapCreatorImpl<ArgAliasLinks, action, argCount>
        {
            typedef action FunctionMData;
            typedef boost::mpl::map< BOOST_PP_ENUM(argCount, DEF_MPL_MAP_ELEM,) > MapType;
            typedef boost::mpl::vector<  BOOST_PP_ENUM(argCount, DEF_MPL_VEC_ELEM,) > VecType;
        };
    }}}}


    #undef argCount
    #undef GET_ARG
    #undef ALIAS_OF_ARG
    #undef DEF_FU_MAP_ELEM
    #undef DEF_OP_ARG
    #undef PASS_OP_ARG
    #undef DEF_MPL_MAP_ELEM
    #undef DEF_MPL_VEC_ELEM
    #undef DEF_MAP_CREATOR
    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosDef.hpp>

#endif
