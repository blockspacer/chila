/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONVERT_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CONVERT_HPP

#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/call_traits.hpp>
#include <boost/cast.hpp>
#include <chila/lib/misc/util.hpp>

#define RESULT_OF_CONVERT(opN) typename ResultOfConvert<Target, Type>::convert##opN##_type

#define CONVERT_TMPL_ARG(r, data, i, elem) , typename elem

#define RESULT_OF_CONVERT_IMPL(opN, Ret, sptrTypeBaseOfTarget, isConvertible, typeBaseOfTarget, targetBaseOfType, isSame, opSeq) \
    template <typename Target BOOST_PP_SEQ_FOR_EACH_I(CONVERT_TMPL_ARG,, opSeq)> \
    struct ResultOfConvertImpl \
    < \
        Target, \
        sptrTypeBaseOfTarget, \
        isConvertible, \
        typeBaseOfTarget, \
        targetBaseOfType, \
        isSame \
    > \
    { \
        typedef Ret type; \
        typedef Ret convert##opN##_type; \
    };

#define ENABLE_IF_DUMMY(Type) \
    typename boost::enable_if<boost::is_same<Type, DummyType>, Target>::type

#define DISABLE_IF_DUMMY(Type) \
    typename boost::disable_if<boost::is_same<Type, DummyType>, Target>::type

#define DISABLE_IF_SMARTSUPTR(Type) \
    typename boost::disable_if<boost::is_same<Type, DummyType>, Target>::type

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct DummyType {};


    /* SPtrTypeBaseOfTarget **********************************************************************************************************************/
    template <typename Target, typename Type>
    struct SPtrTypeBaseOfTarget
    {
        typedef boost::false_type type;
    };

    template <typename Target, typename Type>
    struct SPtrTypeBaseOfTarget< std::shared_ptr<Target>, std::shared_ptr<Type> >
    {
        typedef typename boost::is_base_of
        <
            typename boost::remove_const<Type>::type,
            typename boost::remove_const<Target>::type
        >::type type;
    };



    template <typename Target, typename Type>
    constexpr auto enableIf0(Target target, Type type)
    {
        auto sptrIsBase = SPtrTypeBaseOfTarget<Target, Type>::type::value;

        return sptrIsBase;

//        return hana::eval_if(SPtrTypeBaseOfTarget<Target, Type>{},
//            [&](auto _) { return std::unique_ptr<T>(new T(std::forward<Args>(_(args))...)); },
//            [&](auto _) { return std::unique_ptr<T>(new T{std::forward<Args>(_(args))...}); }
    }

//    /* IsSharedSUPtr **********************************************************************************************************************/
//    template <typename Target, typename Type>
//    struct IsSharedUPtr
//    {
//        typedef boost::false_type type;
//    };
//
//    template <typename Target, typename Type>
//    struct IsSharedUPtr< std::shared_ptr<Target> >
//    {
//        typedef typename boost::is_base_of
//        <
//            typename boost::remove_const<Type>::type,
//            typename boost::remove_const<Target>::type
//        >::type type;
//    };


    /* ResultOf *************************************************************************************************************************/
    template
    <
        typename Target,
        typename sptrTypeBaseOfTarget,
        typename isConvertible,
        typename typeBaseOfTarget,
        typename targetBaseOfType,
        typename isSame
    >
    struct ResultOfConvertImpl {};

    template <typename Target, typename Type>
    struct ResultOfConvert final: public ResultOfConvertImpl
    <
        Target,
        typename SPtrTypeBaseOfTarget<Target, Type>::type,
        typename boost::is_convertible<Type, Target>::type,
        typename boost::is_base_of<Type, Target>::type,
        typename boost::is_base_of<Target, Type>::type,
        typename boost::is_same<Target, Type>::type
    >
    {
    };

    /* DummyType *************************************************************************************************************************/
    template <typename Target, typename Type>
    inline ENABLE_IF_DUMMY(Target) convert(const Type &arg) { return Target(); }

    template <typename Target, typename Type>
    inline ENABLE_IF_DUMMY(Type) convert(const Type &arg)   { return Target(); }

    /* std::shared_ptr *****************************************************************************************************************/
    template <typename Target, typename Type>
    inline DISABLE_IF_DUMMY(Target) convert(const std::shared_ptr<Type> &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        typedef typename Target::element_type TargetType;

        assert(dynamic_cast<TargetType*>(arg.get()) == arg.get());

        return std::static_pointer_cast<TargetType>(arg);
    }

    template <typename Target, typename Type>
    inline DISABLE_IF_DUMMY(Target) convert(const std::shared_ptr<const Type> &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        typedef typename Target::element_type TargetType;

        assert(dynamic_cast<TargetType*>(chila::lib::misc::removeConst(arg.get())) == arg.get());

        return std::static_pointer_cast<TargetType>(chila::lib::misc::removeConst(arg));
    }

//    /* chila::lib::misc::SmartSUPtr *****************************************************************************************************************/
//    template <typename Target, typename Type>
//    inline DISABLE_IF_DUMMY(Target) convert(const chila::lib::misc::SmartSUPtr<Type> &arg)
//    {
////        typedef typename Target::element_type TargetType;
////
////        assert(dynamic_cast<TargetType*>(arg.get()) == arg.get());
////
////        return std::static_pointer_cast<TargetType>(arg);
//        return Target();
//    }
//
//    template <typename Target, typename Type>
//    inline DISABLE_IF_DUMMY(Target) convert(const chila::lib::misc::SmartSUPtr<const Type> &arg)
//    {
////        typedef typename Target::element_type TargetType;
////
////        assert(dynamic_cast<TargetType*>(chila::lib::misc::removeConst(arg.get())) == arg.get());
////
////        return std::static_pointer_cast<TargetType>(chila::lib::misc::removeConst(arg));
//        return Target();
//    }

    /* convert1 *************************************************************************************************************************/


    RESULT_OF_CONVERT_IMPL
    (
        1,
        const Target&,
        boost::false_type,  // Type is base of Target and Target is shared_ptr
        op0,                // Type can be converted to Target
        boost::true_type,   // Type is base of Target
        boost::false_type,  // Target is base of Type
        boost::false_type,  // Target = Type
        (op0)
    )
    template <typename Target, typename Type>
    inline RESULT_OF_CONVERT(5) convert(const Type &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        return *boost::polymorphic_downcast<const Target*>(&arg);
    }

    /* convert2 *************************************************************************************************************************/
    RESULT_OF_CONVERT_IMPL
    (
        2,
        Target,
        boost::false_type,  // Target is shared_ptr
        boost::true_type,   // Type can be converted to Target
        boost::false_type,  // Type is base of Target
        boost::false_type,  // Target is base of Type
        boost::false_type,  // Target = Type
    )
    template <typename Target, typename Type>
    inline RESULT_OF_CONVERT(2) convert(const Type &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        return arg;
    }

    /* convert3 *************************************************************************************************************************/
    RESULT_OF_CONVERT_IMPL
    (
        3,
        typename boost::call_traits<Target>::param_type,
        op0,                // Type is base of Target and Target is shared_ptr
        op1,                // Type can be converted to Target
        op2,                // Type is base of Target
        op3,                // Target is base of Type
        boost::true_type,   // Target = Type
        (op0)(op1)(op2)(op3)
    )
    template <typename Target, typename Type>
    inline RESULT_OF_CONVERT(3) convert(const Type &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        return arg;
    }

    /* convert4 *************************************************************************************************************************/
    RESULT_OF_CONVERT_IMPL
    (
        4,
        typename boost::call_traits<Target>::param_type,
        boost::false_type,  // Type is base of Target and Target is shared_ptr
        op0,                // Type can be converted to Target
        boost::false_type,  // Type is base of Target
        boost::true_type,   // Target is base of Type
        boost::false_type,  // Target = Type
        (op0)
    )
    template <typename Target, typename Type>
    inline RESULT_OF_CONVERT(4) convert(const Type &arg)
    {
        std::cout << enableIf0(boost::hana::type_c<Target>, boost::hana::type_c<Type>) << std::endl;

        return arg;
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef RESULT_OF_CONVERT
#undef RESULT_OF_CONVERT_IMPL
#undef CONVERT_TMPL_ARG
#undef ENABLE_IF_DUMMY
#undef DISABLE_IF_DUMMY

#endif
