/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "Node.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    chila::lib::misc::Path getNodePath(const Node &node)
    {
        return node.path();
    }
}
MY_NSP_END
