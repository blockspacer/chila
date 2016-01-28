/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__ITER_ITERATOR_HPP
#define CHILA_LIB_MISC__ITER_ITERATOR_HPP

#include "fwd.hpp"
#include <boost/cast.hpp>
#include <boost/iterator/iterator_facade.hpp>

#define CHILA_LIB_MISC__DEF_ITER_ITERATOR(Name) \
    template <typename Iterator, typename CastedType, typename CastedTypeRef, typename Fun> \
    class Name final: public chila::lib::misc::iter_iterator \
    < \
        Name<Iterator, CastedType, CastedTypeRef, Fun>, \
        Iterator, \
        CastedType, \
        CastedTypeRef \
    > \
    {\
        private: \
            struct enabler {}; \
            \
        public: \
            Fun fun; \
            \
            using Base = chila::lib::misc::iter_iterator \
            < \
                Name<Iterator, CastedType, CastedTypeRef, Fun>, \
                Iterator, \
                CastedType, \
                CastedTypeRef \
            >; \
            \
            Name() = default; \
            \
            Name(Iterator it, Fun fun = Fun()) : Base(it), fun(chila::lib::misc::rvalue_cast(fun)) {} \
            \
            template <class OtherIterator, class OtherCastedType, class OtherCastedTypeRef, class OtherFun> \
            Name \
            ( \
                const Name<OtherIterator, OtherCastedType, OtherCastedTypeRef, OtherFun> &other, \
                typename boost::enable_if<boost::is_convertible<OtherIterator, Iterator>, enabler>::type = enabler() \
            ) : Base(other.it), fun(other.fun) {} \
            \
            CastedTypeRef dereferenceImpl() const \
            { \
                return boost::unwrap_ref(fun).template cast<CastedTypeRef>(this->it); \
            } \
    };

#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename Derived, typename Iterator, typename CastedType, typename CastedTypeRef = CastedType&>
    class iter_iterator: public boost::iterator_facade
    <
        Derived,
        CastedType,
        boost::bidirectional_traversal_tag,
        CastedTypeRef
    >
    {
        private:
            struct enabler {};

        public:
            Iterator it;

            iter_iterator() = default;

            iter_iterator(Iterator it) : it(it) {}

            template <class OtherIterator, class OtherCastedType, class OtherCastedTypeRef>
            iter_iterator
            (
                const iter_iterator<Derived, OtherIterator, OtherCastedType, OtherCastedTypeRef> &other,
                typename boost::enable_if<boost::is_convertible<OtherIterator, Iterator>, enabler>::type = enabler()
            ) : it(other.it) {}

        protected:
            friend class boost::iterator_core_access;
            template <typename, typename, typename, typename> friend class iter_iterator;

            template <typename OtherIterator, typename OtherCastedType, typename OtherCastedTypeRef>
            bool equal(const iter_iterator<Derived, OtherIterator, OtherCastedType, OtherCastedTypeRef> &other) const
            {
                return this->it == other.it;
            }

            void increment() { ++it; }
            void decrement() { --it; }
            void advance(typename iter_iterator::difference_type n) { std::advance(it, n); }

            template <class OtherIterator, class OtherCastedType, class OtherCastedTypeRef>
            typename iter_iterator::difference_type distance_from(const iter_iterator<Derived, OtherIterator, OtherCastedType, OtherCastedTypeRef> &other) const
            {
                return other.it - it;
            }

            template <class OtherIterator, class OtherCastedType, class OtherCastedTypeRef>
            typename iter_iterator::difference_type distance_to(const iter_iterator<Derived, OtherIterator, OtherCastedType, OtherCastedTypeRef> &other) const
            {
                return it - other.it;
            }

            Derived &derived()              { return *static_cast<Derived*>(this); }
            const Derived &derived() const  { return *static_cast<const Derived*>(this); }

            CastedTypeRef dereference() const
            {
                return derived().dereferenceImpl();
            }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
