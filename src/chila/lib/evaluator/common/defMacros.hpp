/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define add_provider(name, Type) \
    providerMap.add(name, boost::make_shared< Type##OperationProvider >());

#define expNSP chila::lib::evaluator::expression

#define adapt_fun_0(Ret) expNSP::functionAdapterWithRet<Ret>
#define adapt_fun_n(Ret, ...) expNSP::functionAdapterWithRet<Ret, __VA_ARGS__>

#define nullary_bind(Ret, fun) adapt_fun_0(Ret)(boost::bind(fun))

#define unary_bind(Ret, fun, Arg) adapt_fun_n(Ret, Arg)(boost::bind(fun, _1))

#define binary_bind(Ret, fun, Arg0, Arg1) adapt_fun_n(Ret, Arg0, Arg1)(boost::bind(fun, _1, _2))

#define lexical_cast_op(Ret, Arg) \
    expNSP::functionAdapter<Arg>(boost::bind(&boost::lexical_cast<Ret, Arg>, _1))

#define nullary_member_bind(Ret, Type, name) unary_bind(Ret, &Type::name, Type)

