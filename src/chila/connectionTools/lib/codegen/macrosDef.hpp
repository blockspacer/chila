/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <boost/type_traits/add_reference.hpp>
#include <boost/bind.hpp>
#include "FunMData.hpp"

// BOOST_PP_ENUM(<empty>) solution
#define BOOST_PP_SEQ_ENUM_0


/*********************************************************** Connector *******************************************************************/

// Names ----------------------------------------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ARGS_NAME(NSP, Connector) \
    BOOST_PP_CAT(BOOST_PP_CAT(\
        NSP, __CONNECTOR_ARGS_), Connector)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector) \
    BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(\
        NSP, __CONNECTOR_), FNAME), S_), Connector)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTION_ARGS_NAME(NSP, FNAME, Connector, function) \
    BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT( \
        NSP, __CONNECTOR_), FNAME), _ARGS_), Connector), _), function)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ACTION_EVCALLED_NAME(NSP, Connector, function) \
    BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(NSP, __CONNECTOR_ACTION_EVCALLED_), Connector), _), function)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENT(argName) \
        struct argName \
        { \
            typedef typename ArgTypes::argName Type; \
            typedef typename boost::call_traits<Type>::param_type ParamType; \
            static const char *getName() { return BOOST_PP_STRINGIZE(argName); } \
        }

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS_ELEM(r, data, elem) \
    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENT(elem);

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS(NSP, Connector) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS_ELEM,, \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ARGS_NAME(NSP, Connector))

// DEF_CONNECTOR_FUNCTIONS ----------------------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DMF_DEFARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) \
    typename boost::call_traits<typename ArgTypes::elem>::param_type elem

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ACTION_SIG_ARG(r, name, i, elem) \
    BOOST_PP_COMMA_IF(i) typename decltype(typename boost::hana::at(\
        typename BOOST_PP_CAT(MData_, name)::Arguments{}, boost::hana::integral_constant<int, i>)::type::ParamType


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ACTION(NSP, Connector, name, args) \
        struct MData_##name final: public chila::connectionTools::lib::codegen::FunMData<MData_##name, Connector, decltype(boost::hana::tuple_t<BOOST_PP_SEQ_ENUM(args)>)> \
        { \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_TYPE( \
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ACTION_EVCALLED_NAME(NSP, Connector, name)); \
            typename EventExecuter::EventFSeq eventFSeq; \
            \
            MData_##name(Connector &connector) : eventFSeq(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_INIT( \
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ACTION_EVCALLED_NAME(NSP, Connector, name))) {} \
            \
            template <typename Fun> \
            void operator=(const Fun &fun) { this->assign(fun); } \
            \
            void operator()(BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DMF_DEFARG,, args)) const \
            { \
                this->function(BOOST_PP_SEQ_ENUM(args)); \
            } \
            \
            static const char *getName() { return #name; } \
            static chila::lib::misc::Path path() { return (Connector::path() + "actions") + chila::lib::misc::Path(#name, "_").getStringRep(":"); } \
        } name

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_EVENT(NSP, Connector, name, args) \
        class MData_##name final: public chila::connectionTools::lib::codegen::FunMData<MData_##name, Connector, decltype(boost::hana::tuple_t<BOOST_PP_SEQ_ENUM(args)>)> \
        { \
            public: \
                template <typename EventFSeq> \
                friend class chila::connectionTools::lib::codegen::EventExecuter; \
                \
                public: \
                \
                template <typename Fun> \
                void operator=(const Fun &fun) { this->assign(fun); } \
                \
                static const char *getName() { return #name; } \
                static chila::lib::misc::Path path() { return (Connector::path() + "events") + chila::lib::misc::Path(#name, "_").getStringRep(":"); } \
                \
            private: \
                void operator()(BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DMF_DEFARG,, args)) const \
                { \
                    this->function(BOOST_PP_SEQ_ENUM(args)); \
                } \
        } name

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS_ELEM(r, data, function) \
    BOOST_PP_CAT(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_, BOOST_PP_SEQ_ELEM(1, data))( \
        BOOST_PP_SEQ_ELEM(0, data), BOOST_PP_SEQ_ELEM(2, data), function, \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTION_ARGS_NAME \
        ( \
            BOOST_PP_SEQ_ELEM(0, data), \
            BOOST_PP_SEQ_ELEM(1, data), \
            BOOST_PP_SEQ_ELEM(2, data), \
            function \
        ));

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(NSP, FNAME, Connector) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS_ELEM, (NSP)(FNAME)(Connector), \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector))



/****************************************************** ConnectionPerformer **************************************************************/

// DEF_ARG_ALIAS ---------------------------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS(aliasName) \
        struct aliasName \
        { \
            typedef typename ArgTypes::aliasName Type; \
            typedef typename boost::call_traits<Type>::param_type ParamType; \
            static const char *getName() { return #aliasName; } \
        }

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_ELEM(r, data, elem) \
    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS(elem);

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES(aliasSeq) \
        BOOST_PP_SEQ_FOR_EACH(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_ELEM,,aliasSeq)

// DEF_CONNECTOR_FUN_FUSIONSEQ ------------------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_TYPE_ELEM(r, Const, i, function) \
    BOOST_PP_COMMA_IF(i) Const typename boost::add_reference<BOOST_PP_CAT(MData_, function)>::type

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_RET_ELEM(r, ref, i, function) \
    BOOST_PP_COMMA_IF(i) ref(function)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(NSP, FNAME, Connector) \
    typedef boost::hana::tuple< \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_TYPE_ELEM,, \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector)) > List; \
    typedef boost::hana::tuple< \
    BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_TYPE_ELEM, const, \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector)) > CList; \
    List list() { return boost::hana::make_tuple(\
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_RET_ELEM, boost::ref, \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector))); } \
    CList list() const { return boost::hana::make_tuple(\
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ_RET_ELEM, boost::cref, \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, FNAME, Connector))); }

// BIND_ACTION ----------------------------------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION_ARG(z, n, data) , BOOST_PP_CAT(_, BOOST_PP_INC(n))

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name) \
        this->actions.name = actionImplExecuter(std::mem_fn(&Target::name), target, this->actions.name.eventFSeq)


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_APROVIDER(name, ...) \
        const typename APC##_##name::result_type &name##Prov = apc##_##name(__VA_ARGS__)


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_ARG(connArgName, aliasName) \
                const typename ArgTypes::aliasName &aliasName = \
                    chila::connectionTools::lib::codegen::convert<typename ArgTypes::aliasName>(BOOST_PP_CAT(connArgName, _in));

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_GET_ARGUMENT(provider, aliasName) \
        provider##Prov.getArgument(typename ArgAliases::aliasName())

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_PASS_ARG(connector, action, argName, data) \
        chila::connectionTools::lib::codegen::convert<typename \
            chila::connectionTools::lib::codegen::ConnectorTypeOf<\
                BOOST_PP_CAT(Action_, BOOST_PP_CAT(connector, BOOST_PP_CAT(_, action)))>::type::argName::Type>(data)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_EXECUTE_ACTION(connector, action, ...) \
        BOOST_PP_CAT(act_, BOOST_PP_CAT(connector, BOOST_PP_CAT(_, action)))(__VA_ARGS__)


// CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER --------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_TYPE_EV(r, data, i, elem) \
        BOOST_PP_COMMA_IF(i) typename boost::add_reference<BOOST_PP_CAT(typename Events::MData_, elem)>::type

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_TYPE(eventList) \
        typedef chila::connectionTools::lib::codegen::EventExecuter \
        < \
            boost::fusion::set<BOOST_PP_SEQ_FOR_EACH_I( \
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_TYPE_EV,, eventList)> \
        > EventExecuter\

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_INIT_EV(r, data, i, elem) \
        BOOST_PP_COMMA_IF(i) boost::ref(connector.events.elem)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_INIT(eventList) \
        boost::fusion::make_set(BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__EV_EXECUTER_EVENTEXECUTER_INIT_EV,, eventList))



// CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT ------------------------------------------------------------------------------------------------

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT_ELEM(r, data, i, function) \
        BOOST_PP_COMMA_IF(i) function(connector)

#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(NSP, Connector) \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT_ELEM,, \
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_FUNCTIONS_NAME(NSP, ACTION, Connector))


#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTION_IF_HAS_EVEXECUTER(NSP, Connector, name, expTrue, expFalse) \
    BOOST_PP_IF(BOOST_PP_SEQ_SIZE(CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONNECTOR_ACTION_EVCALLED_NAME(NSP, Connector, name)), expTrue, expFalse)
