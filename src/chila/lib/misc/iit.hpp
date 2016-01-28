/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// Code made public by Brian Rackle at http://blog.brainstembreakfast.com/update/c++/2014/10/19/the-iterator-iterator

#ifndef CHILA_LIB_MISC__IIT_HPP
#define CHILA_LIB_MISC__IIT_HPP

#include <boost/ref.hpp>
#include <boost/preprocessor.hpp>

#include <chila/lib/misc/macrosExp.hpp>


#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename T>
    class itr : public T
    {
        T _obj;

        public:
            itr(T&& obj) : _obj(rvalue_cast(obj)) {}

            bool operator!=(const itr& other) const { return _obj != other._obj; }
            T operator*() const { return _obj; }
            const itr& operator++() { ++_obj; return *this; }
    };

    template <typename T>
    class val
    {
        T _obj;

        public:
            val(T&& obj) : _obj(rvalue_cast(obj)) {}

            auto begin() const -> itr<decltype(std::begin(this->_obj))> { return std::begin(_obj); }
            auto end() const -> itr<decltype(std::end(this->_obj))> { return std::end(_obj); }
    };

    template <typename T>
    class ref
    {
        T& _obj;

        public:
            ref(T& obj) : _obj(obj) {}

            auto begin() const -> itr<decltype(std::begin(this->_obj))> { return std::begin(_obj); }
            auto end() const -> itr<decltype(std::end(this->_obj))> { return std::end(_obj); }
    };

    template <typename T>
    auto iit(T&& t) -> typename std::conditional<
        std::is_lvalue_reference<decltype(t)>::value, ref<T>, val<T>>::type
    {
        return std::forward<T>(t);
    }
}
MY_NSP_END

#include "macros.fgen.hpp"



#endif

