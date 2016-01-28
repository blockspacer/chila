/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__ITER_ITERATOR_VAL_HPP
#define CHILA_LIB_MISC__ITER_ITERATOR_VAL_HPP

#include "fwd.hpp"
#include "iter_iterator.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_ITER_ITERATOR(iter_iterator_val_tpl)

    struct iter_iterator_val_deref
    {
        template <typename CastedTypeRef, typename Iterator>
        CastedTypeRef cast(const Iterator &it) const
        {
            return it;
        }
    };

    template <typename Iterator>
    using iter_iterator_val = iter_iterator_val_tpl<Iterator, Iterator, Iterator, iter_iterator_val_deref>;

    template <typename Iterator>
    inline iter_iterator_val<Iterator> make_iter_iterator_val(Iterator it)
    {
        return iter_iterator_val<Iterator>(it);
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
