/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__GRAMMAR_HPP
#define CHILA_LIB_EVALUATOR_PARSER__GRAMMAR_HPP

#include <chila/lib/evaluator/expression/ValueMap.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <chila/lib/evaluator/expression/expression.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_char_class.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include "interfaces.hpp"
#include <iostream>

#define null_exp expression::ExpressionSCPtr()

#define SHOW_PROD(name) [std::cout << boost::lambda::constant(#name) << '\n']

#define bind_exp_n(Type, method, object) \
    boost::phoenix::bind(&Type::method, boost::phoenix::ref(object))

#define bind_exp(Type, method, object, ...) \
    boost::phoenix::bind(&Type::method, boost::phoenix::ref(object), __VA_ARGS__)

#define create_value(Type, arg) bind_exp(IExpressionProvider, create##Type##Value, *expProvider, arg)

#define create_nullary_op(name) \
    createOperation(name, createArgumentList())

#define create_unary_op(name, arg) \
    createOperation(name, pushBackExpression(createArgumentList(), arg))

#define create_binary_op(name, arg1, arg2) createOperation(name, \
    pushBackExpression(pushBackExpression(createArgumentList(), arg1), arg2))

#define create_operation(name, args) createOperation(name, args)

#define create_null_exp_aux boost::phoenix::construct<BinaryExpAux>("", expression::ExpressionSCPtr())

#define create_exp_aux(opName, exp) boost::phoenix::construct<BinaryExpAux>(opName, exp)

#define aux_binary_op(more_complex, opName, simpler) \
    opName >> simpler##_exp                               [ _a = create_binary_op(opName, _r1, _1)  ]    \
           >> more_complex##_exp_aux(_a)                  [ _val = _1    ]

#define recursive_exp_start(more_complex, simpler)  \
            more_complex##_exp = simpler##_exp[_a = _1] >> more_complex##_exp_aux(_a)      [ _val = _1 ];   \
            more_complex##_exp_aux =

#define recursive_exp_end   | qi::eps [ _val = _r1 ]

#include "nspDef.hpp"

MY_NSP_START
{
    using namespace boost::spirit;

    template <typename Iterator>
    struct Grammar : qi::grammar<Iterator, expression::ExpressionSCPtr(), ascii::space_type>
    {
        typedef ascii::space_type sType;

        qi::rule<Iterator, std::string(), sType>
            IDENTIFIER,
            STRING_LITERAL_AUX;

        qi::rule<Iterator, expression::ExpressionSCPtr(), sType>
            NUMERIC_LITERAL,
            BOOLEAN_LITERAL,
            STRING_LITERAL,
            LITERAL,
            VARIABLE,
            primary_exp,
            unary_exp,
            exp;

        qi::rule<Iterator, expression::ExpressionSCPtr(), sType>
            rule;

        qi::rule<Iterator, expression::ExpressionSCPtr(),
                qi::locals<expression::ArgumentListSPtr, std::string>, sType>
            function_call_exp;

        qi::rule<Iterator, void(const expression::ArgumentListSPtr&),
                qi::locals<expression::ArgumentListSPtr>, sType>
            argument_list;

        qi::rule<Iterator, expression::ExpressionSCPtr(), qi::locals<expression::ExpressionSCPtr>, sType>
            multiplicative_exp,
            additive_exp,
            relational_exp,
            equality_exp,
            logical_and_exp,
            logical_or_exp,
            conditional_exp;

        qi::rule<Iterator, expression::ExpressionSCPtr(const expression::ExpressionSCPtr&),
                qi::locals<expression::ExpressionSCPtr>, sType>
            multiplicative_exp_aux,
            additive_exp_aux,
            relational_exp_aux,
            equality_exp_aux,
            logical_and_exp_aux,
            logical_or_exp_aux,
            conditional_exp_aux;

//        qi::rule<Iterator, qi::locals<std::string>, sType> var_declaration;
//        qi::rule<Iterator, sType> var_declaration_list;

        struct CreateOperation;
        struct CreateArgumentList;
        struct PushBackExpression;
        struct CreateVariable;

        IExpressionProviderSCPtr expProvider;

        const expression::ValueMap *valueMap;

        boost::phoenix::function<CreateOperation> createOperation;
        boost::phoenix::function<CreateArgumentList> createArgumentList;
        boost::phoenix::function<PushBackExpression> pushBackExpression;
        boost::phoenix::function<CreateVariable> createVariable;

        Grammar(const IExpressionProviderSCPtr &expProvider, bool optimize) :
            Grammar::base_type(exp),
            expProvider(expProvider),
            createOperation(CreateOperation(expProvider, optimize)),
            valueMap(NULL),
            createVariable(valueMap)
        {
            using qi::_val;
            using qi::_1;
            using qi::_2;
            using qi::_3;
            using qi::_r1;

            NUMERIC_LITERAL = lexeme[double_]                   [ _val = create_value(Numeric, _1)      ];

            BOOLEAN_LITERAL =
                  lit("true")                                   [ _val = create_value(Boolean, true)    ]
                | lit("false")                                  [ _val = create_value(Boolean, false)   ]
                ;

            STRING_LITERAL = STRING_LITERAL_AUX                 [ _val = create_value(String, _1)       ];

            STRING_LITERAL_AUX %= lexeme['"' >> +(ascii::char_ - '"') >> '"'];

            LITERAL %= NUMERIC_LITERAL | BOOLEAN_LITERAL | STRING_LITERAL;

            IDENTIFIER = lexeme[(ascii::alpha | '_') >> *(ascii::alpha | ascii::digit | '_')];

            // @TODO Ver este tema (lexeme)
            VARIABLE = '$' >> IDENTIFIER [ _val = createVariable(_1) ];

            primary_exp %=
                  LITERAL
                | VARIABLE
                | ('(' >> exp >> ')')
                ;

            unary_exp =
                  function_call_exp             [ _val = _1                         ]
                | '-' >> primary_exp            [ _val = create_unary_op("-", _1)   ]
                | lit("not") >> primary_exp
                | primary_exp                   [ _val = _1                         ]
                ;

            recursive_exp_start(multiplicative,      unary)
                  aux_binary_op(multiplicative, "*", unary)
                | aux_binary_op(multiplicative, "/", unary)
            recursive_exp_end;

            recursive_exp_start(additive,      multiplicative)
                  aux_binary_op(additive, "+", multiplicative)
                | aux_binary_op(additive, "-", multiplicative)
            recursive_exp_end;

            recursive_exp_start(relational,       additive)
                  aux_binary_op(relational, "<",  additive)
                | aux_binary_op(relational, ">",  additive)
                | aux_binary_op(relational, "<=", additive)
                | aux_binary_op(relational, ">=", additive)
            recursive_exp_end;

            recursive_exp_start(equality,        relational)
                  aux_binary_op(equality, "=",   relational)
                | aux_binary_op(equality, "!=",  relational)
            recursive_exp_end;

            recursive_exp_start(logical_and,         equality)
                  aux_binary_op(logical_and, "and",  equality)
            recursive_exp_end;

            recursive_exp_start(logical_or,         logical_and)
                  aux_binary_op(logical_or,  "or",  logical_and)
            recursive_exp_end;

            conditional_exp %=
                  logical_or_exp
//                | logical_or_exp >> '?' >> exp >> '=' >> exp        ) SHOW_PROD(conditional_exp)
                ;

            argument_list =
                  conditional_exp[ pushBackExpression(_r1, _1) ]
                  >> -("," >>  argument_list(_r1))
                ;

            function_call_exp =
                  qi::eps[ _a = createArgumentList() ]
                    >> (IDENTIFIER[ _b = _1 ]
                    >> -('(' >> argument_list(_a) >> ')'))      [ _val = create_operation(_b, _a)  ]
                ;

//            var_declaration =
//                IDENTIFIER[ _a = _1 ] >> ':' >> IDENTIFIER
//                [
//                    bind_exp(SymbolTable, addSymbol, symbolTable, _a, _1)
//                ]
//                ;
//
//            var_declaration_list = var_declaration >> -(',' >> var_declaration_list);

            exp %= conditional_exp;

//            rule = -('[' >> var_declaration_list >> ']' >> ':')
//                    >> exp[ _val = _1 ]
//                    >> eps[ bind_exp_n(SymbolTable, clear, symbolTable) ];
        }


        /** Returns the optimized expression for 'op', that is, it inspects all its arguments
         * looking for some non-value. If it finds one, the operation is returned as passed;
         * if all the arguments are values, the operation is constant, so it executes the
         * operation right in place and returns a value that holds the result of the operation.
         */
        static expression::ExpressionSCPtr getOptimizedOperation(const expression::OperationSCPtr &op)
        {
            const expression::ArgumentList &aList = *(op->getArgumentList());
            for (const auto &exp : aList)
            {
                if (!std::dynamic_pointer_cast<const expression::Value>(exp))
                    return op;
            }

            // If all arguments where values, evaluate the operation and return a value
            // containing the result
            return op->evaluateOnValue(expression::ValueMap());
        }

        /** Creates an operation and returns it. */
        struct CreateOperation
        {
            template <typename Arg0, typename Arg1>
            struct result { typedef expression::ExpressionSCPtr type; };

            IExpressionProviderSCPtr expProvider;
            bool optimize;

            CreateOperation(const IExpressionProviderSCPtr &expProvider, bool optimize) :
                expProvider(expProvider), optimize(optimize) {}

            expression::ExpressionSCPtr operator()(const std::string &name,
                const expression::ArgumentListSCPtr &aList) const
            {
                expression::OperationSCPtr ret = this->expProvider->createOperation(name, aList);
                return optimize && ret->isConstant() ?
                    getOptimizedOperation(ret) : expression::ExpressionSCPtr(ret);
            }
        };

        struct CreateArgumentList
        {
            typedef expression::ArgumentListSPtr result_type;

            expression::ArgumentListSPtr operator()() const
            {
                return std::make_shared<expression::ArgumentList>();
            }
        };

        struct PushBackExpression
        {
            template <typename Arg0, typename Arg1>
            struct result { typedef expression::ArgumentListSPtr type; };

            expression::ArgumentListSPtr operator()(const expression::ArgumentListSPtr &aList,
                const expression::ExpressionSCPtr &ex) const
            {
                aList->push_back(ex);
                return aList;
            }
        };

        /** Creates a variable and returns it. */
        struct CreateVariable
        {
            template <typename Arg1>
            struct result { typedef expression::VariableSCPtr type; };

            const expression::ValueMap *&valueMap;

            CreateVariable(const expression::ValueMap *&valueMap) : valueMap(valueMap) {}

            expression::VariableSCPtr operator()(const std::string &name) const
            {
                my_assert(valueMap);
                return valueMap->getValue(name)->createVariable(name);
            }
        };
    };

//primary_exp
//    : LITERAL
//    | VARIABLE
//    | '(' expression ')'                    {   $$ = $2; }
//    ;

}}}}


#endif
