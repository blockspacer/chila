/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__VECTOROFTYPED_HPP
#define CHILA_LIB_NODE__VECTOROFTYPED_HPP

#include "ContainerOfTyped.hpp"
#include <limits>
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>

#define FWDEC_SPTR  CHILA_LIB_MISC__FWDEC_SPTR

#define CHILA_META_NODE__DEF_VECTOR_OF_TYPED(Name, Type) \
    class Name: public chila::lib::node::VectorOfTyped<Type> \
    { \
        friend chila::lib::node::Node; \
        public: \
            static std::shared_ptr<Name> create(std::string name) \
            { \
                auto ret = std::make_shared<Name>(); \
                ret->_name = name; \
                return ret; \
            } \
            chila::lib::node::NodeSPtr clone(const std::string &newName = "") const override \
            { \
                auto ret = std::make_shared<Name>(*this); \
                if (!newName.empty()) ret->_name = newName; \
                return ret; \
            } \
            virtual bool isSameType(const chila::lib::node::Node &rhs) const override \
            { \
                return dynamic_cast<const Name*>(&rhs); \
            } \
    }; \

#include "nspDef.hpp"

MY_NSP_START
{
    struct NodeVector: public virtual NodeWithChildren
    {
    };

    template <typename Type>
    class VectorOfTyped: public ContainerOfTyped<Type>, public NodeVector
    {
        public:
            VectorOfTyped() : nextId(0) {}

            template <typename Derived = Type>
            Derived &add()
            {
                return static_cast<Derived&>(NodeWithChildren::add(Derived::create(boost::lexical_cast<std::string>(nextId++))));
            }

            bool canTakeChildFrom(IContainerOfTyped &from) const override
            {
                return dynamic_cast<VectorOfTyped<Type>*>(&from);
            }

            Node &takeChild(VectorOfTyped<Type> &from, const std::string &name)
            {
                auto newName = boost::lexical_cast<std::string>(nextId++);
                return NodeWithChildren::add(newName, from.removeNode(name));
            }

            Node &takeChild(IContainerOfTyped &from, const std::string &name) override
            {
                return takeChild(dynamic_cast<VectorOfTyped<Type>&>(from), name);
            }

            void remove(const std::string &name) override
            {
                removeNode(name);
            }

        private:
            unsigned nextId;

            std::shared_ptr<Type> removeNode(const std::string &name);
    };

    template <typename Type>
    std::shared_ptr<Type> VectorOfTyped<Type>::removeNode(const std::string &name)
    {
        auto nodes = removeAll();
        std::shared_ptr<Type> ret;

        nextId = 0;
        for (auto &node : nodes)
        {
            if (node->name() == name)
            {
                ret = std::dynamic_pointer_cast<Type>(node);
                my_assert(bool(ret));
            }
            else
                NodeWithChildren::add(boost::lexical_cast<std::string>(nextId++), rvalue_cast(node));
        }

        return rvalue_cast(ret);
    }

}
MY_NSP_END

#include "nspUndef.hpp"
#undef FWDEC_SPTR
#endif
