/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Node.hpp"
#include "NodeWithChildren.hpp"
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

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

    /** Clones the node all the way to the parent. */
    std::pair<NodeWithChildrenSPtr, Node&> Node::cloneAll() const
    {
        auto p = parentPtr();
        if (p)
            return p->cloneChild(_name);
        else
            BOOST_THROW_EXCEPTION(NodeNotCloneable()
                << chila::lib::misc::ExceptionInfo::Type(boost::typeindex::type_id_runtime(*this)));
    }

    void Node::visit(const VisitFun &fun)
    {
        fun(*this);

        if (auto *typed = toTypePtr<NodeWithChildren>())
        {
            for (auto &child : *typed)
                child.visit(fun);
        }
    }
}
MY_NSP_END


