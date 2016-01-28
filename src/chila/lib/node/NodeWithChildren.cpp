/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "NodeWithChildren.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <chila/lib/misc/RepeatText.hpp>
#include "util.hpp"

#define INDENT chila::lib::misc::repeatText(indent, "    ")
#define my_assert   CHILA_LIB_MISC__ASSERT

#include "nspDef.hpp"

MY_NSP_START
{
    /** Returns a child. */
    Node &NodeWithChildren::child(const std::string &name)
    {
        NodeUPtrMap::iterator it = children.find(name);

        if (it == children.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name) << chila::lib::misc::ExceptionInfo::Path(path()));

        return *(it->second);
    }

    /** Returns a child.
     * @throws ChildDoesNotExists
     */
    const Node &NodeWithChildren::child(const std::string &name) const
    {
        NodeUPtrMap::const_iterator it = children.find(name);

        if (it == children.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name) << chila::lib::misc::ExceptionInfo::Path(path()));

        return *(it->second);
    }

    /** Returns a child. */
    Node *NodeWithChildren::childPtr(const std::string &name)
    {
        NodeUPtrMap::iterator it = children.find(name);

        return it == children.end() ? nullptr : it->second.get();
    }

    /** Returns a child. */
    const Node *NodeWithChildren::childPtr(const std::string &name) const
    {
        NodeUPtrMap::const_iterator it = children.find(name);

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
        if (!ret) BOOST_THROW_EXCEPTION(NodeNotFound());
        return *ret;
    }

    const Node &NodeWithChildren::find(const chila::lib::misc::Path &path) const
    {
        const Node *ret = findPtr(path);
        if (!ret) BOOST_THROW_EXCEPTION(NodeNotFound());
        return *ret;
    }

    NodeUPtr NodeWithChildren::removeNode(const std::string &name)
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

    NodeUPtrItVec::iterator NodeWithChildren::findIt(const std::string &name)
    {
        auto ret = std::find_if(itChildren.begin(), itChildren.end(),
                [&](const NodeUPtrMap::iterator &it){ return it->first == name; });

        if (ret == itChildren.end())
            BOOST_THROW_EXCEPTION(ChildDoesNotExists(name));

        return ret;
    }

    std::string NodeWithChildren::moveUp(const std::string &name, bool keepNames)
    {
        auto it1 = findIt(name), it2 = it1;
        if (it1 != itChildren.begin())
        {
            swapNodes(it1, --it2, keepNames);
            return (*it2)->second->name();
        }

        return (*it1)->second->name();
    }

    std::string NodeWithChildren::moveDown(const std::string &name, bool keepNames)
    {
        auto it1 = findIt(name), it2 = it1;
        if (++it2 != itChildren.end())
        {
            swapNodes(it1, it2, keepNames);
            return (*it2)->second->name();
        }

        return (*it1)->second->name();
    }

    void NodeWithChildren::swapNodes(
        const NodeUPtrItVec::iterator &nodeIt1,
        const NodeUPtrItVec::iterator &nodeIt2,
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

    std::vector<NodeUPtr> NodeWithChildren::removeAll()
    {
        std::vector<NodeUPtr> ret;

        for (auto &it : itChildren)
            ret.push_back(rvalue_cast(it->second));

        children.clear();
        itChildren.clear();

        return ret;
    }

}
MY_NSP_END
