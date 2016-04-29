/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__NODE_HPP
#define CHILA_LIB_NODE__NODE_HPP

#include <boost/utility.hpp>
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include "util.hpp"
#include "exceptions.hpp"

#define my_assert CHILA_LIB_MISC__ASSERT

#include "nspDef.hpp"

MY_NSP_START
{
    class Node : boost::noncopyable
    {
        friend struct NodeWithChildren;

        public:
            Node() : _parent(nullptr) {}

            /** Returns the full path to the node */
            chila::lib::misc::Path path() const;

            /** Returns the name. */
            const std::string &name() const { return _name; }

            /** Returns the parent. */
            template <typename Derived = NodeWithChildren>
            Derived *parentPtr() { return dynamic_cast<Derived*>(_parent); }

            /** Returns the parent. */
            template <typename Derived = NodeWithChildren>
            const Derived *parentPtr() const { return dynamic_cast<const Derived*>(_parent); }

            /** Returns the parent. */
            template <typename Derived = NodeWithChildren>
            Derived &parent() { return castNode<Derived>(chila::lib::misc::deref(_parent)); }

            /** Returns the parent. */
            template <typename Derived = NodeWithChildren>
            const Derived &parent() const { return castNode<const Derived>(chila::lib::misc::deref(_parent)); }

            /** Streams the node. */
            virtual void stream(std::ostream &out, unsigned indent = 0) const = 0;

            /** Converts this node to a certain type. */
            template <typename Type>
            Type &toType() { return castNode<Type>(*this); }

            /** Converts this node to a certain type. */
            template <typename Type>
            const Type &toType() const { return castNode<const Type>(*this); }

            /** Converts this node to a certain type. */
            template <typename Type>
            Type *toTypePtr() { return dynamic_cast<Type*>(this); }

            /** Converts this node to a certain type. */
            template <typename Type>
            const Type *toTypePtr() const { return dynamic_cast<const Type*>(this); }

            /** Returns the base node, iterating through all the parents. */
            NodeWithChildren *base();

            /** Returns the base node, iterating through all the parents. */
            const NodeWithChildren *base() const;

            /** Finds a node. */
            virtual Node *findPtr(const chila::lib::misc::Path &path);

            /** Finds a node. */
            virtual const Node *findPtr(const chila::lib::misc::Path &path) const;

            /** Finds a node. */
            virtual Node &find(const chila::lib::misc::Path &path);

            /** Finds a node. */
            virtual const Node &find(const chila::lib::misc::Path &path) const;

            /** Checks the node. If fails, throws an exception. */
            virtual void check(CheckData *data = nullptr) const {} // { std::cout << "node check of '" << path() << "'" << std::endl; }

        protected:
            std::string _name;
            NodeWithChildren *_parent;

            /** Creates a Type (which should be a Node) and sets it's name. */
            template <typename Type>
            static std::unique_ptr<Type> createNamed(std::string name)
            {
                std::unique_ptr<Type> ret(new Type()); // can't be friends with std::make_unique

                ret->_name = rvalue_cast(name);
                return ret;
            }

        public:
            virtual ~Node() {}
    };

}
MY_NSP_END

#include "nspUndef.hpp"

#endif
