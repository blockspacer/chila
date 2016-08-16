/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "NodeWithChildren.hpp"
#include "Reference.hpp"

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

    PathVec getReferences(
        NodeWithChildren &node,
        const chila::lib::misc::Path &path)
    {
        std::vector<chila::lib::misc::Path> ret;

        node.visit([&](const chila::lib::node::Node &node)
        {
            if (auto *typed = node.toTypePtr<IReference>()) try
            {
                if (typed->refPath() == path)
                    ret.push_back(node.path());
            }
            catch (const chila::lib::node::Exception &ex)
            {
            }
        });

        return ret;
    }

    void replaceReferences(NodeWithChildren &node, const PathVec &paths, const Node &newRefNode)
    {
        for (auto &path : paths)
        {
            auto &ref = node.find(path);
            auto newNode = ref.toType<IReference>().createWithRef(newRefNode);

            ref.parent<NodeWithChildren>().replace(newNode, ref.name());
        }
    }
}
MY_NSP_END
