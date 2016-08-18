/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.other'
 *
 * 'chila.connectionTools.lib.other' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.other' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.other'. If not, see <http://www.gnu.org/licenses/>.
 */

#include <type_traits>
#include <chila/lib/misc/macrosExp.hpp>

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_TYPE(elem) BOOST_PP_SEQ_ELEM(0, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_TYPE_CREF(elem) \
        typename boost::call_traits<typename boost::unwrap_reference<CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_TYPE(elem)>::type>::param_type

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_NAME(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_VARIABLE(r, data, elem) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_TYPE(elem) CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_NAME(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_RET(r, data, elem) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_TYPE_CREF(elem) \
        getArgument(typename ArgAliases::CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_NAME(elem)) const { \
        return CHILA_CONNECTIONTOOLS_LIB_OTHER__ALIAS_NAME(elem); }

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_BASE(provAliases)                   \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_VARIABLE,, provAliases)    \
        typedef ArgAliases ArgAliasesType;  \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_RET,, provAliases)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_TYPE(Key, Value) Key##Value##Map

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_VAR_NAME(Key, Value) \
        BOOST_PP_CAT(v, CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_TYPE(Key, Value))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ASOC_MAP(Key, Value) \
        typedef lib::ThreadSafeMap<Key##SCPtr, Value##SCPtr> CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_TYPE(Key, Value); \
        extern CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_TYPE(Key, Value) CHILA_CONNECTIONTOOLS_LIB_OTHER__MAP_VAR_NAME(Key, Value)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MOD_ARG(name) boost::call_traits<ArgTypes::name>::param_type name

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODACTION_ARG(r, data, elem) \
    ( CHILA_CONNECTIONTOOLS_LIB_OTHER__MOD_ARG(elem) )

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODACTION_ARGS(arguments) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__MODACTION_ARG,, arguments)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROV_BASE_FROM_SEQ_ELEM(r, data, name) ((typename ArgAliases::name::Type)(name))
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FROM_SEQ_ELEM(r, data, i, name) \
    BOOST_PP_COMMA_IF(i) typename ArgAliases::name::ParamType name

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FROM_ASEQ(seq) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_BASE \
    ( \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROV_BASE_FROM_SEQ_ELEM,,seq) \
    )

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FROM_SEQ(seq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FROM_SEQ_ELEM,,seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FROM_SEQ(seq) BOOST_PP_SEQ_ENUM(seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, provName) \
    BOOST_PP_CAT(BOOST_PP_CAT(NSP, __ARGPROV_RARG_SEQ_), provName)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PROVIDED_ARGS(NSP, provName) \
    BOOST_PP_CAT(BOOST_PP_CAT(NSP, __ARGPROV_PARG_SEQ_), provName)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR(NSP, provName) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FROM_ASEQ(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PROVIDED_ARGS(NSP, provName))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_CONSARGS(argSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_CONSARG,,argSeq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_INITARGS(argSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_INITARG,,argSeq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR_WC(NSP, provName, customArgs) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FROM_ASEQ(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PROVIDED_ARGS(NSP, provName)) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAMED(NSP, Construct, provName, customArgs); \
    \
    Prov_##provName(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_CONSARGS(customArgs) \
                    BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                        BOOST_PP_SEQ_SIZE(customArgs), \
                        BOOST_PP_SEQ_SIZE(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, provName)))) \
                    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(NSP, provName))


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(NSP, provName) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FROM_SEQ(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, provName))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS_SIZE(NSP, provName) \
    BOOST_PP_SEQ_SIZE(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, provName))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FOR(NSP, provName) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FROM_SEQ(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, provName))


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_TYPE(elem) BOOST_PP_SEQ_ELEM(0, elem)
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_FIELD(r, data, elem) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_TYPE(elem) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_CONSARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    typename boost::call_traits<CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_TYPE(elem)>::param_type \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_INITARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem)(\
        CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_PASSARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i)  CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAME(elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS(NSP, name, argSeq) \
    template <typename ArgAliases> \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAMED(NSP, BOOST_PP_CAT(BOOST_PP_CAT(Prov_, name), PC), name, argSeq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_NAMED(NSP, Name, name, argSeq) \
    struct Name \
    { \
        typedef BOOST_PP_CAT(Prov_, name)<ArgAliases> result_type; \
        \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_FIELD,,argSeq) \
        \
        Name(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_CONSARGS(argSeq)) \
            BOOST_PP_IF(BOOST_PP_SEQ_SIZE(argSeq),:,) \
            CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_INITARGS(argSeq) {} \
        \
        result_type operator()(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(NSP, name)) const \
        { \
            return result_type(BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS_PASSARG,,argSeq) \
                BOOST_PP_COMMA_IF(BOOST_PP_AND(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS_SIZE(NSP, name), BOOST_PP_SEQ_SIZE(argSeq))) \
                CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FOR(NSP, name)); \
        } \
    }

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_PATH(elem) BOOST_PP_SEQ_ELEM(0, elem)
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_ALIAS(elem) BOOST_PP_SEQ_ELEM(0, elem)
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS_PARENT_TYPEDEF(r, data, elem) \
        typedef CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_PATH(elem) CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS_TYPEDEF(r, GET_CONNECTOR, elem) \
        typedef GET_CONNECTOR(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_PATH(elem)) CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_DEC_CONN_INSTNACE(r, data, elem) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_ALIAS(elem) &CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_DEC_CONN_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_ALIAS(elem) &CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INIT_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem)(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem))


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPEDEF_CONN_PARENT_ALIASES(seq) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS_PARENT_TYPEDEF,,seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPEDEF_CONN_ALIASES(seq, GET_CONNECTOR) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_ALIAS_TYPEDEF, GET_CONNECTOR, seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DECLARE_CONN_INSTANCES(seq) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_DEC_CONN_INSTNACE,,seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DECLARE_CONN_ARGUMENTS(seq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_DEC_CONN_ARG,,seq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__INIT_CONN_ARGUMENTS(seq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INIT_ARG,,seq)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CPERFORMERDATA_INIT(conn_alias_seq, conn_instances_seq, GET_CONNECTOR) \
        struct ModuleTypes  \
        {   \
            CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPEDEF_CONN_PARENT_ALIASES(conn_alias_seq) \
        };  \
        \
        struct Connectors \
        { \
            CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPEDEF_CONN_ALIASES(conn_alias_seq, GET_CONNECTOR) \
            \
            CHILA_CONNECTIONTOOLS_LIB_OTHER__DECLARE_CONN_INSTANCES(conn_instances_seq) \
            \
            Connectors \
            ( \
                CHILA_CONNECTIONTOOLS_LIB_OTHER__DECLARE_CONN_ARGUMENTS(conn_instances_seq) \
                \
            ) : CHILA_CONNECTIONTOOLS_LIB_OTHER__INIT_CONN_ARGUMENTS(conn_instances_seq) {} \
        };



#define CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCES_ELEM(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCES(instanceSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCES_ELEM,, instanceSeq)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_TYPE(name) \
    BOOST_PP_CAT(Connector::Actions::MData_, name::EventExecuter)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_ARG(name) \
    const CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_TYPE(name) &eventExecuter


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(NSP, CConnector, name) \
    name(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_PUSH_BACK(CHILA_CONNECTIONTOOLS_LIB_OTHER__MODACTION_ARGS( \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTION_ARGS_NAME(NSP, ACTION, CConnector, name)), \
            CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_ARG(name))))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC(name) \
    template <typename ArgAliases> \
    struct BOOST_PP_CAT(Prov_, name)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(NSP, name, customArgs) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC(name) { \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR_WC(NSP, name, customArgs)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_EXTERN_TEMPLATE(r, aProvNsp, name) \
    extern template class aProvNsp::BOOST_PP_CAT(Prov_, name)<CPerformerData::ConnectionPerformer::ArgAliases>;


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_EXTERN_TEMPLATE_SEQ(aProvNsp, aProvSeq) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_EXTERN_TEMPLATE, aProvNsp, aProvSeq)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_TEMPLATE_INST(r, aProvNsp, name) \
    template class aProvNsp::BOOST_PP_CAT(Prov_, name)<CPerformerData::ConnectionPerformer::ArgAliases>;


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_TEMPLATE_INST_SEQ(aProvNsp, aProvSeq) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_TEMPLATE_INST, aProvNsp, aProvSeq)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_FATAL_ARGS(msg, func, file, line) \
    (msg + std::string(" [func='") + func + "', file='" + file + "', line=" + boost::lexical_cast<std::string>(line) + "]")

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_FFL(msg, func, file, line) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT(fatalError) CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_FATAL_ARGS(msg, func, file, line)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL(msg) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_FFL(msg, __func__, __FILE__, __LINE__)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_FFL_TN(msg, func, file, line) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN(fatalError) CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_FATAL_ARGS(msg, func, file, line)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_TN(msg) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_FFL_TN(msg, __func__, __FILE__, __LINE__)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT(exp) ((exp) ? static_cast<void>(0) : \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL(std::string("Assertion '" #exp "' failed")));

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT_TN(exp) ((exp) ? static_cast<void>(0) : \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_TN(std::string("Assertion '" #exp "' failed")));

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__FORWARD_ACTIONEV(NSP, Connector, action)             \
    void CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(NSP, Connector, BOOST_PP_CAT(prv_, action)) \
    { \
        connector.events.BOOST_PP_CAT(pub_, action)(BOOST_PP_SEQ_ENUM( \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTION_ARGS_NAME(NSP, ACTION, Connector, BOOST_PP_CAT(prv_, action)))); \
    }

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT(name) \
    eventExecuter.execute<std::remove_reference<decltype(connector)>::type::Events::BOOST_PP_CAT(MData_, name)>

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN(name) \
    eventExecuter.template execute<typename std::remove_reference<decltype(connector)>::type::Events::BOOST_PP_CAT(MData_, name)>

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CHOLDER_INSERT_ELEM(r, INSERT_FUN, i, elem) \
    INSERT_FUN \
    ( \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_ALIAS(elem), \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem) \
    );

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CHOLDER_INSERT(INSERT_FUN, instanceSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__CHOLDER_INSERT_ELEM, INSERT_FUN, instanceSeq)


// CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR ----------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CREATOR(NSP, name, EncType) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(NSP, name, ) : \
            BOOST_PP_SEQ_ELEM(0, CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PROVIDED_ARGS(NSP, name))(std::make_shared<EncType>( \
                BOOST_PP_SEQ_ENUM(CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, name)))) \
    { \
    }};


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_READER_FIELD(r, inputArg, i, arg) \
    BOOST_PP_COMMA_IF(i) arg(inputArg->arg)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_READER(NSP, name) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(NSP, name, ) : \
            BOOST_PP_SEQ_FOR_EACH_I \
            ( \
                CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_READER_FIELD, \
                BOOST_PP_SEQ_ELEM(0, CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_REQUIRED_ARGS(NSP, name)), \
                CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PROVIDED_ARGS(NSP, name) \
            ) \
    { \
    }};

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CR(NSP, creatorName, readerName, EncType) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CREATOR(NSP, creatorName, EncType) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_READER(NSP, readerName)

// CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY ----------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_DEF_FIELD(r, Types, field) \
    Types::field field;

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_PASS_FIELD(r, Types, i, field) \
    BOOST_PP_COMMA_IF(i) typename boost::call_traits<Types::field>::param_type &field

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_SET_FIELD(r, data, i, field) \
    BOOST_PP_COMMA_IF(i) field(field)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY(Name, Types, fields) \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_DEF_FIELD, Types, fields) \
        \
        Name(BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_PASS_FIELD, Types, fields)) : \
            BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEFINE_ENCAPSULATOR_BODY_SET_FIELD,, fields) {}


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_OP_LESS_THAN(Lhs, Rhs) \
    bool operator<(const Rhs &rhs) const { return *this < *boost::polymorphic_downcast<const Lhs*>(&rhs); }

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPED_INSTANCES_ELEM(r, prefix, i, elem) \
    prefix::CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_ALIAS(elem)::CProviderUPtr CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem);

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPED_INSTANCES(prefix, instanceSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__TYPED_INSTANCES_ELEM, prefix, instanceSeq)

// CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN ------------------------------------------------------------------------------------------------
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN_ELEM(i, fun, z, elem) \
    fun(CHILA_CONNECTIONTOOLS_LIB_OTHER__CONN_INSTANCE_NAME(elem))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN(connInstanceSeq, fun) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__INSTANCE_SEQ_APPLY_FUN_ELEM, fun, connInstanceSeq)


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SETPOST_FUNCTION(function, queue) \
    function.passFunAndSet(chila::lib::misc::SetPostFun(queue))


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_CREATORS_ELEM(r, aProvNsp, name) \
    BOOST_PP_CAT(aProvNsp::Prov_, name)<ConnectionPerformer::ArgAliases>::Construct name;

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_CREATORS(NSP, aProvNsp) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_PROVIDER_CREATORS_ELEM, aProvNsp, BOOST_PP_CAT(NSP, __APCREATORS_SEQ))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CATCH_INV_STATE_TF(exp) \
    try { exp; } \
    catch (const chila::connectionTools::lib::other::InvalidStateError &ex) \
    { \
        chila::connectionTools::lib::other::raiseFatalFromInvalidState< \
            std::remove_reference<decltype(connector)>::type::Events::MData_fatalError>(eventExecuter, ex); \
    }

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_CPROVIDER(Connector) \
        struct CProvider : \
            public chila::connectionTools::lib::other::ModuleImpl<CProvider, Connector> \
        { \
            CProvider(const std::string &instanceName) : \
                ModuleImpl(instanceName) {} \
            \
            CProvider(const std::string &instanceName, const chila::connectionTools::lib::other::ParameterList &parameters) : \
                ModuleImpl(instanceName, parameters) {} \
        }; \
        \
        CHILA_LIB_MISC__FWDEC_SPTR(CProvider)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__VAR(r, data, elem) \
    BOOST_PP_IF(BOOST_PP_SEQ_ELEM(0, elem), \
        BOOST_PP_SEQ_ELEM(1, elem)(BOOST_PP_SEQ_ELEM(1, elem)) BOOST_PP_COMMA, BOOST_PP_EMPTY)()

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__PARAM(r, data, elem) \
    (chila::connectionTools::lib::other::Parameter(BOOST_PP_SEQ_ELEM(2, elem), \
     chila::connectionTools::lib::other::toString(BOOST_PP_SEQ_ELEM(1, elem))))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SAVEPARAMS(Base, params) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__VAR,,params) \
    Base(instanceName, boost::assign::list_of BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__PARAM,,params).to_container(parameters))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_WA(Prefix, NSP, name, ...) \
    name = Prefix::NSP##__CONN_INSTANCE_ALIAS_OF_##name::create(chila::lib::misc::Path(#name, "_").getStringRep(), __VA_ARGS__)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_NA(Prefix, NSP, name) \
    name = Prefix::NSP##__CONN_INSTANCE_ALIAS_OF_##name::create(chila::lib::misc::Path(#name, "_").getStringRep())

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__POSTFUN_AND_DFF(prefix, module, funType, fun, debugLogFilePtr, queue, anyPrinter, showArguments) \
            prefix.module->connector.funType##s.fun.passFunAndSet(chila::lib::misc::SetPostFun(queue)); \
            if (debugLogFilePtr) \
            { \
                prefix.module->connector.funType##s.fun.passFunAndSet(chila::connectionTools::lib::other::DebugFileFunPFS<decltype( \
                    prefix.module->connector.funType##s.fun)>(*debugLogFilePtr, anyPrinter, chila::lib::misc::Path(#module, "_").getStringRep(":"), \
                        #funType, showArguments, "posted in '" #funType "s'" )); \
            }
// CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS -----------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_ELEM(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_SEQ_ELEM(0, elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS(moduleParams) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_ELEM,, moduleParams)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(NSP, ModuleName) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS(BOOST_PP_CAT(BOOST_PP_CAT(NSP, __MODULE_PARAMS_), ModuleName))

// CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS -----------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS_ELEM(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS(moduleParams) \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS_ELEM,, moduleParams)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS_EX(NSP, ModuleName) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS(BOOST_PP_CAT(BOOST_PP_CAT(NSP, __MODULE_PARAMS_), ModuleName))

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTION(prefix, object, type, function, queueName, anyPrinter) \
    if (debugLogFile)  \
    {  \
        BOOST_PP_CAT(prefix.object->connector.type, s).function.passFunAndSet  \
        (  \
            chila::connectionTools::lib::other::DebugFileFunPFS<decltype(BOOST_PP_CAT(prefix.object->connector.type, s).function)>  \
            (  \
                *debugLogFile, anyPrinter, "" + chila::lib::misc::replace(BOOST_PP_STRINGIZE(object), "_", ":") + "", "type", showArguments, "posted in 'queueName'"  \
            )  \
        );  \
    }


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_POST_FUNCTION(prefix, object, type, function, queue, queueName, anyPrinter) \
    prefix.object->connector.type##s.function.passFunAndSet(chila::lib::misc::SetPostFun(queue));  \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTION(prefix, object, type, function, queueName, anyPrinter)

#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS_ELEM(r, data, elem) \
    CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTION \
    ( \
        BOOST_PP_SEQ_ELEM(0, data), \
        BOOST_PP_SEQ_ELEM(1, data), \
        BOOST_PP_SEQ_ELEM(2, data), \
        elem, \
        BOOST_PP_SEQ_ELEM(3, data), \
        BOOST_PP_SEQ_ELEM(4, data)  \
    )


#define CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS(prefix, object, type, queueName, anyPrinter, functions) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS_ELEM, (prefix)(object)(type)(queueName)(anyPrinter), functions)

