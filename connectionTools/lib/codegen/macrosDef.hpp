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

#include <boost/preprocessor.hpp>

#ifndef chila_connectionTools_maxGenerators
#define chila_connectionTools_maxGenerators 50
#endif

#ifndef chila_connectionTools_maxActions
#define chila_connectionTools_maxActions 50
#endif


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_ARGUMENT(argName)       \
        struct argName                                                                      \
        {                                                                                   \
            typedef typename DataTypes::argName DataType;                                   \
            static const char *getName() { return #argName; }                               \
        }

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_FUNCTION_OPERATOR_FUN(z, argCount, data) \
        template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                         \
        void operator()(BOOST_PP_ENUM_BINARY_PARAMS(argCount, const Arg, &arg)) const   \
        {                                                                               \
            function(BOOST_PP_ENUM_PARAMS(argCount, arg));                              \
        }

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_FUNCTION(name, ...)         \
        struct MData_##name                                                                     \
        {                                                                                       \
            typedef Connector ConnectorType;                                                    \
            typedef void Result;                                                                \
            typedef boost::mpl::vector<__VA_ARGS__> Arguments;                                  \
            typedef typename chila::connectionTools::lib::codegen::                             \
                FunctionSigCreator<MData_##name>::Type Signature;                               \
            typedef boost::function<Signature> Function;                                        \
                                                                                                \
            Function function;                                                                  \
                                                                                                \
            void operator()() const { function(); }                                             \
            BOOST_PP_REPEAT_FROM_TO(1, 49,                                                      \
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_MODULE_FUNCTION_OPERATOR_FUN,)           \
        } name


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS(aliasName)                   \
        struct aliasName                                            \
        {                                                           \
            static const char *getName() { return #aliasName; }     \
        }

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK(argName, aliasName) \
        boost::mpl::pair<typename Connector::argName, typename ArgAliases::aliasName>


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CAT_ALIASES(r, ArgAliases, elem) \
        (typename ArgAliases::elem)

#define BOOST_PP_SEQ_ENUM_0

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ENUM_ARGS(args) \
        BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH( \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CAT_ALIASES, ArgAliases, args))

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__APROVIDER_CREATOR(providerCreator, reqArgs, provArgs)   \
        chila::connectionTools::lib::codegen::argumentProviderCreator                                 \
        <                                                                       \
            boost::mpl::vector<CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ENUM_ARGS(reqArgs)>,             \
            boost::mpl::set<CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ENUM_ARGS(provArgs)>                \
        >(chila::connectionTools::lib::codegen::argumentProviderCreatorFunAdaptor(providerCreator))


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name) \
        this->actions.name.function = \
        chila::lib::misc::memFnExecuter(boost::mem_fn(&Target::name), boost::ref(target));

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__SHOW_ACTION_ARG(r, data, elem) \
        BOOST_PP_IF(BOOST_PP_SUB(r, 2),  ", " << , ) BOOST_PP_STRINGIZE(elem) << "=[" << elem << "]" <<

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__SHOW_ACTION(name, argList) \
        "[action] " << name << ": <" << BOOST_PP_SEQ_FOR_EACH(\
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__SHOW_ACTION_ARG,, argList) ">"


