/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__FWD_HPP
#define CHILA_LIB_MISC__FWD_HPP

#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/ref.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/make_unique.hpp>
#include "macrosExp.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    using StringSet = std::set<std::string>;
    using StringVec = std::vector<std::string>;

    template <typename Type>
    class SmartSUPtr;

    struct print_exp_default_tag;
    CHILA_LIB_MISC__FWDEC_TYPE(Watch);

    template <typename Type, typename Tag>
    struct PrintExp;

    template <typename Tag, typename Type>
    inline PrintExp<Type, Tag> printExp(const Type &data) { return PrintExp<Type, Tag>(data); }

    CHILA_LIB_MISC__FWDEC_TYPE(Printer);

    CHILA_LIB_MISC__FWDEC_TYPE(Path);
    CHILA_LIB_MISC__FWDEC_TYPE(DynamicLibrary);

    template <typename PtrType>
    struct PtrForwarder;

    struct Streamable
    {
        virtual void stream(std::ostream &out) const { out << std::hex << this << std::dec; }
    };

    CHILA_LIB_MISC__FWDEC_SPTR(Streamable);

    CHILA_LIB_MISC__FWDEC_TYPE(ApplicationError);

    template <typename T>
    typename std::remove_reference<T>::type &&rvalue_cast(T&& t) // thanks Scott M.
    {
       static_assert(!std::is_const<typename std::remove_reference<T>::type>::value,
          "You've attempted a cast to a const rvalue reference. "
          "Make sure you're not trying to move a const object, "
          "as this would likely result in a copy not a move. "
          "If you need it for real, call rvalue_cast(...) instead.");

       return std::move(t);
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
