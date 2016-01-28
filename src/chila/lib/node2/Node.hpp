/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE2__NODE_HPP
#define CHILA_LIB_NODE2__NODE_HPP

#include "fwd.hpp"
#include <boost/utility.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Node
    {
        public:
            virtual void stream(std::ostream &out, unsigned indent) const = 0;
            virtual ~Node() = default;

        private:

    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
