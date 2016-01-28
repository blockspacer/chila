/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__NODEWITHCHILDREN_HPP
#define CHILA_LIB_NODE__NODEWITHCHILDREN_HPP

#include "Node.hpp"
#include <boost/utility.hpp>
#include "fwd.hpp"
#include "exceptions.hpp"
#include <chila/lib/misc/iter_iterator.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_ITER_ITERATOR(node_iterator_tpl)

    template <typename Iterator, typename CastedType, typename Fun>
    using node_iterator = node_iterator_tpl<Iterator, CastedType, CastedType&, Fun>;



    class NodeWithChildren: public Node
    {
        public:
            typedef Node            value_type;
            typedef Node&           reference;
            typedef const Node&     const_reference;
            typedef Node*           pointer;
            typedef const Node*     const_pointer;

            struct DerefFun
            {
                template <typename CastedTypeRef, typename Iterator>
                CastedTypeRef cast(const Iterator &it) const
                {
                    return dynamic_cast<CastedTypeRef>(*(*it)->second);
                }
            };

            typedef node_iterator<NodeUPtrItVec::iterator, Node, DerefFun> iterator;
            typedef node_iterator<NodeUPtrItVec::const_iterator, const Node, DerefFun> const_iterator;

            /** Streams the node. */
            virtual void stream(std::ostream &out, unsigned indent = 0) const override;

            Node &child(const std::string &name);
            const Node &child(const std::string &name) const;

            Node *childPtr(const std::string &name);
            const Node *childPtr(const std::string &name) const;

            template <typename Type>
            Type &typedChild(const std::string &name) { return castNode<Type>(child(name)); }

            template <typename Type>
            const Type &typedChild(const std::string &name) const { return castNode<const Type>(child(name)); }

            template <typename Type>
            Type *typedChildPtr(const std::string &name);

            template <typename Type>
            const Type *typedChildPtr(const std::string &name) const;

            unsigned childCount() const { return children.size(); }

            iterator begin() { return iterator(itChildren.begin()); }
            iterator end() { return iterator(itChildren.end()); }

            const_iterator begin() const { return const_iterator(itChildren.begin()); }
            const_iterator end() const { return const_iterator(itChildren.end()); }

            const_iterator cbegin() const { return begin(); }
            const_iterator cend() const { return end(); }

            Node &front() { return *(begin()); }
            Node &back() { auto it = end(); return *(--it); }

            const Node &front() const { return *(begin()); }
            const Node &back() const { auto it = end(); return *(--it); }

            bool contains(const std::string &name) const { return children.count(name); }

            bool empty() const { return children.empty(); }

            Node *findPtr(const chila::lib::misc::Path &path) override;
            const Node *findPtr(const chila::lib::misc::Path &path) const override;

            virtual Node &find(const chila::lib::misc::Path &path) override;
            virtual const Node &find(const chila::lib::misc::Path &path) const override;

            virtual void check(CheckData *data = nullptr) const override;

            unsigned size() const { return children.size(); }

            std::string moveUp(const std::string &name, bool keepNames);
            std::string moveDown(const std::string &name, bool keepNames);

            virtual void remove(const std::string &name) { removeNode(name); }

        protected:
            template <typename Derived>
            Derived &add(std::unique_ptr<Derived> node);

            template <typename Derived>
            Derived &add(std::string name, std::unique_ptr<Derived> node)
            {
                node->_name = rvalue_cast(name);
                return add(rvalue_cast(node));
            }

            NodeUPtr removeNode(const std::string &name);

            std::vector<NodeUPtr> removeAll();

        private:
            NodeUPtrMap children;
            NodeUPtrItVec itChildren;

            NodeUPtrItVec::iterator findIt(const std::string &name);

            void swapNodes(const NodeUPtrItVec::iterator &nodeIt1, const NodeUPtrItVec::iterator &nodeIt2, bool keepNames);
    };

    /** Adds a node. */
    template <typename Derived>
    Derived &NodeWithChildren::add(std::unique_ptr<Derived> node)
    {
        std::string nodeName = node->name();
        Derived *ret = node.get();

        auto insRet = children.insert(NodeUPtrMap::value_type(nodeName, rvalue_cast(node)));
        if (!insRet.second)
            BOOST_THROW_EXCEPTION(ChildAlreadyExists(nodeName));


        ret->_parent = this;
        itChildren.push_back(insRet.first);

        return *ret;
    }


    template <typename Type>
    inline Type *NodeWithChildren::typedChildPtr(const std::string &name)
    {
        if (Node *ret = NodeWithChildren::childPtr(name))
        {
            if (Type *typed = dynamic_cast<Type*>(ret))
                return typed;
            else
                BOOST_THROW_EXCEPTION(InvalidChildType("child '" + name + "' is not of type '" + typeid(Type).name() + "'"));
        }

        return nullptr;
    }

    template <typename Type>
    inline const Type *NodeWithChildren::typedChildPtr(const std::string &name) const
    {
        if (const Node *ret = NodeWithChildren::childPtr(name))
        {
            if (const Type *typed = dynamic_cast<const Type*>(ret))
                return typed;
            else
                BOOST_THROW_EXCEPTION(InvalidChildType("child '" + name + "' is not of type '" + typeid(Type).name() + "'"));
        }

        return nullptr;
    }
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
