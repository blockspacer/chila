/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONVERT_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONVERT_HPP

#include <boost/utility.hpp>
#include <type_traits>
#include <boost/ref.hpp>
#include <memory>
#include <boost/call_traits.hpp>
#include <boost/cast.hpp>
#include <chila/lib/misc/util.hpp>

#define ENABLE_IF_DUMMY(Type) \
    typename boost::enable_if<std::is_same<Type, DummyType>, Target>::type

#define DISABLE_IF_DUMMY(Type) \
    typename boost::disable_if<std::is_same<Type, DummyType>, Target>::type

#define ENABLE_IF(num, ReturnType) \
    std::enable_if_t<decltype(enableIf##num(hana::type_c<Target>, hana::type_c<Type>))::value, ReturnType>

#define DEF_CONVERT_ELEM(r, data, i, cond) \
    BOOST_PP_IF(i, &&,) cond

#define DEF_CONVERT(num, conds, ReturnType) \
    auto enableIf##num = [](auto target, auto type) \
    { \
        return BOOST_PP_SEQ_FOR_EACH_I(DEF_CONVERT_ELEM,, conds); \
    }; \
    template <typename Target, typename Type> \
    inline ENABLE_IF(num, ReturnType) convert(const Type &arg)

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct DummyType {};
    namespace hana = boost::hana;


    /* SPtrTypeBaseOfTarget **********************************************************************************************************************/
    template <typename Target, typename Type>
    struct SPtrTypeBaseOfTarget
    {
        typedef std::false_type type;
    };

    template <typename Target, typename Type>
    struct SPtrTypeBaseOfTarget< std::shared_ptr<Target>, std::shared_ptr<Type> >
    {
        typedef typename std::is_base_of
        <
            typename std::remove_const<Type>::type,
            typename std::remove_const<Target>::type
        >::type type;
    };

    template <typename Target, typename Type>
    constexpr auto hSPtrTypeBaseOfTarget(Target target, Type type)
    {
        return hana::int_c<SPtrTypeBaseOfTarget<typename Target::type, typename Type::type>::type::value>;
    }

    /* DummyType *************************************************************************************************************************/
    template <typename Target, typename Type>
    inline ENABLE_IF_DUMMY(Target) convert(const Type &arg) { return Target(); }

    template <typename Target, typename Type>
    inline ENABLE_IF_DUMMY(Type) convert(const Type &arg)   { return Target(); }

    /* std::shared_ptr *****************************************************************************************************************/
    template <typename Target, typename Type>
    inline DISABLE_IF_DUMMY(Target) convert(const std::shared_ptr<Type> &arg)
    {
        typedef typename Target::element_type TargetType;

        assert(dynamic_cast<TargetType*>(arg.get()) == arg.get());

        return std::static_pointer_cast<TargetType>(arg);
    }

    template <typename Target, typename Type>
    inline DISABLE_IF_DUMMY(Target) convert(const std::shared_ptr<const Type> &arg)
    {
        typedef typename Target::element_type TargetType;

        assert(dynamic_cast<TargetType*>(chila::lib::misc::removeConst(arg.get())) == arg.get());

        return std::static_pointer_cast<TargetType>(chila::lib::misc::removeConst(arg));
    }

    /* convert0 *************************************************************************************************************************/
    DEF_CONVERT(0,
        (hSPtrTypeBaseOfTarget(target, type))
        (hana::traits::is_base_of(type, target))
        (!hana::traits::is_base_of(target, type))
        (!hana::traits::is_same(target, type)),
        const Target&)
    {
        return *boost::polymorphic_downcast<const Target*>(&arg);
    }

    /* convert1 *************************************************************************************************************************/
    DEF_CONVERT(1,
        (!hSPtrTypeBaseOfTarget(target, type))
        (hana::traits::is_convertible(target, type))
        (!hana::traits::is_base_of(type, target))
        (!hana::traits::is_base_of(target, type))
        (!hana::traits::is_same(target, type)),
        Target)
    {
        std::cout << enableIf1(hana::type_c<Target>, hana::type_c<Type>) << std::endl;

        return arg;
    }

    /* convert2 *************************************************************************************************************************/
    DEF_CONVERT(2,
        (hana::traits::is_same(target, type)),
        typename boost::call_traits<Target>::param_type)
    {
        return arg;
    }

    /* convert3 *************************************************************************************************************************/
    DEF_CONVERT(3,
        (!hSPtrTypeBaseOfTarget(target, type))
        (!hana::traits::is_base_of(type, target))
        (hana::traits::is_base_of(target, type))
        (!hana::traits::is_same(target, type)),
        typename boost::call_traits<Target>::param_type)
    {
        return arg;
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef ENABLE_IF_DUMMY
#undef DISABLE_IF_DUMMY
#undef ENABLE_IF
#undef DEF_CONVERT_ELEM
#undef DEF_CONVERT

#endif
