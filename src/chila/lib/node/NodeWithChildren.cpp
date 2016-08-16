/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "NodeWithChildren.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <chila/lib/misc/RepeatText.hpp>
#include "util.hpp"
#include <boost/range/combine.hpp>

#define INDENT chila::lib::misc::repeatText(indent, "    ")
#define my_assert   CHILA_LIB_MISC__ASSERT

#include "nspDef.hpp"

MY_NSP_START
{
    /** Returns a child. */
    Node &NodeWithChildren::child(const std::string &name)
    {
        NodeSPtrMap::iterator it = children.find(name);

        if (it == children.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name) << chila::lib::misc::ExceptionInfo::Path(path()));

        return *(it->second);
    }

    /** Returns a child.
     * @throws ChildDoesNotExists
     */
    const Node &NodeWithChildren::child(const std::string &name) const
    {
        NodeSPtrMap::const_iterator it = children.find(name);

        if (it == children.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name) << chila::lib::misc::ExceptionInfo::Path(path()));


        return *(it->second);
    }

    /** Returns a child. */
    Node *NodeWithChildren::childPtr(const std::string &name)
    {
        NodeSPtrMap::iterator it = children.find(name);

        return it == children.end() ? nullptr : it->second.get();
    }

    /** Returns a child. */
    const Node *NodeWithChildren::childPtr(const std::string &name) const
    {
        NodeSPtrMap::const_iterator it = children.find(name);

        return it == children.end() ? nullptr : it->second.get();
    }

    void NodeWithChildren::stream(std::ostream &out, unsigned indent) const
    {
        out << INDENT << name() << ": " << std::endl
            << INDENT << "{" << std::endl;

        for (const auto &it : itChildren)
        {
            it->second->stream(out, indent + 1);
        }

        out << INDENT << "}" << std::endl;
    }

    typedef std::vector<std::string> StringVec;

    template <typename Node, typename NodeWithChildren>
    Node *findIter(Node *node, StringVec::const_iterator cur, StringVec::const_iterator end)
    {
        if (cur == end) return node;

        NodeWithChildren *nwChild = dynamic_cast<NodeWithChildren*>(node);
        if (!nwChild) return nullptr;

        Node *child = nwChild->childPtr(*cur);

        if (!child)
        {
            if (!nwChild->parentPtr())
                return nullptr;

            return findIter<Node, NodeWithChildren>(nwChild->parentPtr(), cur, end);
        }

        return findIter<Node, NodeWithChildren>(child, cur + 1, end);
    }

    Node *NodeWithChildren::findPtr(const chila::lib::misc::Path &path)
    {
        return findIter<Node, NodeWithChildren>(this, path.getNames().begin(), path.getNames().end());
    }

    const Node *NodeWithChildren::findPtr(const chila::lib::misc::Path &path) const
    {
        return findIter<const Node, const NodeWithChildren>(this, path.getNames().begin(), path.getNames().end());
    }

    Node &NodeWithChildren::find(const chila::lib::misc::Path &path)
    {
        Node *ret = findPtr(path);
        if (!ret)
            BOOST_THROW_EXCEPTION(NodeNotFound());
        return *ret;
    }

    const Node &NodeWithChildren::find(const chila::lib::misc::Path &path) const
    {
        const Node *ret = findPtr(path);
        if (!ret)
            BOOST_THROW_EXCEPTION(NodeNotFound());
        return *ret;
    }

    NodeSPtr NodeWithChildren::removeNode(const std::string &name)
    {
        auto it = children.find(name);
        if (it == children.end())
            BOOST_THROW_EXCEPTION(NodeNotFound());

        auto it2 = std::find(itChildren.begin(), itChildren.end(), it);
        my_assert(it2 != itChildren.end());

        auto ret = rvalue_cast(it->second);

        children.erase(it);
        itChildren.erase(it2);

        return ret;
    }

    void NodeWithChildren::check(CheckData *data) const
    {
//        std::cout << "nwc check of '" << path() << "'" << std::endl;
        CheckExceptionList list;
        for (const auto &it : itChildren)
        {
            checkAndAdd(list, [&]{ it->second->check(data); });
        }

        if (!list.exceptions.empty())
            throw list;
    }

    NodeSPtrItVec::iterator NodeWithChildren::findIt(const std::string &name)
    {
        auto ret = std::find_if(itChildren.begin(), itChildren.end(),
                [&](const NodeSPtrMap::iterator &it){ return it->first == name; });

        if (ret == itChildren.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name));

        return ret;
    }

    Node &NodeWithChildren::moveUp(const std::string &name, bool keepNames)
    {
        auto it1 = findIt(name), it2 = it1;
        if (it1 != itChildren.begin())
        {
            swapNodes(it1, --it2, keepNames);
            return *((*it2)->second);
        }

        return *((*it1)->second);
    }

    Node &NodeWithChildren::moveDown(const std::string &name, bool keepNames)
    {
        auto it1 = findIt(name), it2 = it1;
        if (++it2 != itChildren.end())
        {
            swapNodes(it1, it2, keepNames);
            return *((*it2)->second);
        }

        return *((*it1)->second);
    }

    void NodeWithChildren::swapNodes(
        const NodeSPtrItVec::iterator &nodeIt1,
        const NodeSPtrItVec::iterator &nodeIt2,
        bool keepNames)
    {
        if (keepNames)
        {
            auto &node1 = (*nodeIt1)->second,
                 &node2 = (*nodeIt2)->second;

            std::swap(node1, node2);
            std::swap(node1->_name, node2->_name);
        }
        else
        {
            std::swap(*nodeIt1, *nodeIt2);
        }
    }

    std::vector<NodeSPtr> NodeWithChildren::removeAll()
    {
        std::vector<NodeSPtr> ret;

        for (auto &it : itChildren)
            ret.push_back(rvalue_cast(it->second));

        children.clear();
        itChildren.clear();

        return ret;
    }

    NodeWithChildren::NodeWithChildren(const NodeWithChildren &rhs) : Node(rhs)
    {
        for (auto &it : rhs.itChildren)
            add(it->second);
    }

    /** Clones the child, an all its parents. */
    std::pair<NodeWithChildrenSPtr, Node&> NodeWithChildren::cloneChild(const std::string &name) const
    {
        auto p = parentPtr();
        if (p)
        {
            auto ret = p->cloneChild(_name);
            auto &newParent = ret.first;
            auto &myClone = ret.second.toType<NodeWithChildren>();
            auto &node = myClone.replace(child(name).clone());

            return {newParent, node};
        }
        else
        {
            auto newParent = chila::lib::misc::polymorphic_pointer_downcast<NodeWithChildren>(clone());
            auto &node = newParent->replace(child(name).clone());

            return {newParent, node};
        }
    }

    void NodeWithChildren::updateParents()
    {
        for (auto &node : *this)
        {
            node._parent = this;
            if (auto *typed = chila::lib::misc::dcast<NodeWithChildren>(&node))
            {
                typed->updateParents();
            }
        }
    }

    bool NodeWithChildren::compare(const Node &node) const
    {
        if (name() != node.name())
            return false;

        if (!node.isSameType(*this))
            return false;

        if (auto *typed = chila::lib::misc::dcast<NodeWithChildren>(&node))
        {
            if (typed->size() != size())
                return false;

            for (auto p : boost::combine(*typed, *this))
            {
                if (!p.get<0>().compare(p.get<1>()))
                    return false;
            }

            return true;
        }

        return false;
    }

    void NodeWithChildren::takeSimilar(const NodeWithChildren &rhs)
    {
        auto lhsIt = itChildren.begin();
        auto rhsIt = rhs.itChildren.begin();

        for (; lhsIt != itChildren.end() && rhsIt != rhs.itChildren.end(); ++lhsIt, ++rhsIt)
        {
            auto lhsNode = (*lhsIt)->second;
            auto rhsNode = (*rhsIt)->second;

            if (lhsNode->compare(*rhsNode))
            {
                replace(rhsNode);
            }
            else if (lhsNode->isSameType(*rhsNode))
            {
                if (auto *lhsTyped = lhsNode->toTypePtr<NodeWithChildren>())
                {
                    lhsTyped->takeSimilar(rhsNode->toType<NodeWithChildren>());
                }
            }
        }
    }

    Node &NodeWithChildren::renameChild(const std::string &childName, const std::string &newName)
    {
        auto it = children.find(childName);
        if (it == children.end())
            BOOST_THROW_EXCEPTION(NodeNotFound());

        auto node = it->second->clone();
        node->_name = newName;

        replace(node, childName);

        return *node;
    }


}
MY_NSP_END
