/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Node.hpp"
#include "NodeWithChildren.hpp"

#define INDENT chila::lib::misc::repeatText(indent, "    ")

#include "nspDef.hpp"

MY_NSP_START
{
    chila::lib::misc::Path Node::path() const
    {
        chila::lib::misc::Path ret;

        if (!parentPtr()) return ret;

        ret.add(name());
        for (const auto *cur = parentPtr(); cur->parentPtr(); cur = cur->parentPtr())
            ret.add(cur->name());

        ret.reverse();

        return ret;
    }

    NodeWithChildren *Node::base()
    {
        if (!_parent) return nullptr;

        NodeWithChildren *cur;

        for (cur = _parent; cur->parentPtr(); cur = cur->parentPtr());

        return cur;
    };

    const NodeWithChildren *Node::base() const
    {
        if (!_parent) return nullptr;

        const NodeWithChildren *cur;

        for (cur = _parent; cur->parentPtr(); cur = cur->parentPtr());

        return cur;
    };

    /** Finds a node. */
    Node *Node::findPtr(const chila::lib::misc::Path &path)
    {
        return parentPtr() ? parentPtr()->findPtr(path) : nullptr;
    }

    /** Finds a node. */
    const Node *Node::findPtr(const chila::lib::misc::Path &path) const
    {
        return parentPtr() ? parentPtr()->findPtr(path) : nullptr;
    }

    /** Finds a node. */
     Node &Node::find(const chila::lib::misc::Path &path)
     {
         if (parentPtr())
             return parentPtr()->find(path);
         else
             BOOST_THROW_EXCEPTION(NodeNotFound());
     }

     /** Finds a node. */
     const Node &Node::find(const chila::lib::misc::Path &path) const
     {
         if (parentPtr())
             return parentPtr()->find(path);
         else
             BOOST_THROW_EXCEPTION(NodeNotFound());
     }

}
MY_NSP_END


