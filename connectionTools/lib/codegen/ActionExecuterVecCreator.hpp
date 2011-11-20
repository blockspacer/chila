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

    #ifndef CHILA_FUNCTION_BINDER_ACTIONEXECUTERVECCREATOR_HPP
    #define CHILA_FUNCTION_BINDER_ACTIONEXECUTERVECCREATOR_HPP

    #include <boost/preprocessor.hpp>
    #include <chila/lib/misc/macrosDef.hpp>

    #define VEC_SIZE boost::fusion::result_of::size<ActionFSeq>::value


    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ConnectorDescMap, typename AProviderStackType, typename ActionFSeq, unsigned acCount>
        struct ActionExecuterVecCreatorImpl {};

        template <typename ConnectorDescMap, typename AProviderStackType, typename ActionFSeq>
        struct ActionExecuterVecCreator :
            public ActionExecuterVecCreatorImpl<ConnectorDescMap, AProviderStackType, ActionFSeq, VEC_SIZE>
        {
            ActionExecuterVecCreator(const ActionFSeq &actions) :
                ActionExecuterVecCreatorImpl<ConnectorDescMap, AProviderStackType, ActionFSeq, VEC_SIZE>(actions) {}
        };

        template <typename ConnectorDescMap, typename AProviderStackType, typename ActionFSeq>
        inline ActionExecuterVecCreator<ConnectorDescMap, AProviderStackType, ActionFSeq>
            actionExecuterVecCreator(const ActionFSeq &actions)
        {
            return ActionExecuterVecCreator<ConnectorDescMap, AProviderStackType, ActionFSeq>(actions);
        }

    }}}}

    #undef VEC_SIZE

    // Generate Specializations
    #define BOOST_PP_ITERATION_LIMITS   (0, 9)
    #define BOOST_PP_FILENAME_1         <chila/connectionTools/lib/codegen/ActionExecuterVecCreator.hpp>
    #include BOOST_PP_ITERATE()

    #undef DEF_NAMESPACE
    #include <chila/lib/misc/macrosUndef.hpp>
    #endif

#else

    #include <chila/lib/misc/macrosDef.hpp>

    #define acCount BOOST_PP_ITERATION()

    #define AMAP_EXECUTER_TYPE(z, index, data) ArgMapExecuter<ConnectorDescMap, AProviderStackType, \
        typename boost::fusion::result_of::value_at_c<ActionFSeq, index>::type >

    #define AMAP_EXECUTER(z, index, data) argMapExecuter<ConnectorDescMap, AProviderStackType>(     \
        boost::fusion::at_c<index>(actions))


    #define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

    DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
    {
        template <typename ConnectorDescMap, typename AProviderStackType, typename ActionFSeq>
        struct ActionExecuterVecCreatorImpl<ConnectorDescMap, AProviderStackType, ActionFSeq, acCount>
        {
            typedef boost::fusion::vector
            <
                BOOST_PP_ENUM(acCount, AMAP_EXECUTER_TYPE,)
            > result_type;

            ActionFSeq actions;

            ActionExecuterVecCreatorImpl(const ActionFSeq &actions) : actions(actions) {}

            result_type operator()() const
            {
                return boost::fusion::make_vector(BOOST_PP_ENUM(acCount, AMAP_EXECUTER,));
            }
        };
    }}}}

    #undef DEF_NAMESPACE
    #undef acCount

    #include <chila/lib/misc/macrosUndef.hpp>

#endif
