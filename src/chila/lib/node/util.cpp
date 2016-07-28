/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "NodeWithChildren.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    chila::lib::misc::Path getNodePath(const Node &node)
    {
        return node.path();
    }

    NodeWithChildren &mainParent(NodeWithChildren &node)
    {
        if (auto parent = node.parentPtr())
            return mainParent(*parent);
        else
            return node;
    }
}
MY_NSP_END
