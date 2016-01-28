/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__PTR_ITERATOR_HPP
#define CHILA_LIB_MISC__PTR_ITERATOR_HPP


#include "fwd.hpp"
#include <boost/iterator/iterator_facade.hpp>

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{

    template <typename Iterator>
    class ptr_iterator final: public boost::iterator_facade
    <
        ptr_iterator<Iterator>,
        typename std::iterator_traits<Iterator>::value_type,
        boost::bidirectional_traversal_tag
    >
    {
        private:
            struct enabler {};

        public:
            ptr_iterator() {}

            explicit ptr_iterator(Iterator it) : it(it) {}

            template <class OtherIterator>
            ptr_iterator
            (
                const ptr_iterator<OtherIterator> &other,
                typename boost::enable_if<boost::is_convertible<OtherIterator, Iterator>, enabler>::type = enabler()
            ) : it(other.it) {}

        private:
            friend class boost::iterator_core_access;
            template <typename> friend class ptr_iterator;

            template <typename OtherIterator>
            bool equal(const ptr_iterator<OtherIterator> &other) const
            {
                return this->it == other.it;
            }

            void increment() { ++it; }
            void decrement() { --it; }
            void advance(typename ptr_iterator::difference_type n) { it += n; }

            template <class OtherIterator>
            typename ptr_iterator::difference_type distance_from(const ptr_iterator<OtherIterator> &other) const
            {
                return other.it - it;
            }

            template <class OtherIterator>
            typename ptr_iterator::difference_type distance_to(const ptr_iterator<OtherIterator> &other) const
            {
                return it - other.it;
            }

            typename std::iterator_traits<Iterator>::reference dereference() const
            {
                return **it;
            }

            Iterator it;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
