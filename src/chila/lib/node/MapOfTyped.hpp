/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__MAPOFTYPED_HPP
#define CHILA_LIB_NODE__MAPOFTYPED_HPP

#include "ContainerOfTyped.hpp"
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <boost/utility.hpp>

#define FWDEC_SPTR  CHILA_LIB_MISC__FWDEC_SPTR

#define CHILA_META_NODE__DEF_MAP_OF_TYPED_BASE(z, data, i, Base) , public Base

#define CHILA_META_NODE__DEF_MAP_OF_TYPED(Name, Type, Bases) \
    struct Name: \
        public chila::lib::node::MapOfTyped<Type> \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_META_NODE__DEF_MAP_OF_TYPED_BASE,,Bases) \
    { \
        friend chila::lib::node::Node; \
        public: \
            static std::unique_ptr<Name> create(std::string name) \
            { \
                return Node::createNamed<Name>(rvalue_cast(name)); \
            } \
    };

#include "nspDef.hpp"

MY_NSP_START
{
    struct NodeMap: public virtual NodeWithChildren
    {

    };

    template <typename _Type>
    struct MapOfTyped: public ContainerOfTyped<_Type>, public NodeMap
    {
        using Type = _Type;
        using TypeUPtr = typename ContainerOfTyped<Type>::TypeUPtr;

        template <typename Derived = Type>
        Derived &add(std::string name)
        {
            return NodeWithChildren::add(Derived::create(rvalue_cast(name)));
        }

        Node &takeChild(MapOfTyped<Type> &from, const std::string &name)
        {
            if (childPtr(name))
            {
                BOOST_THROW_EXCEPTION(ChildAlreadyExists());
            }

            return NodeWithChildren::add(from.removeNode(name));
        }

        Node &takeChild(IContainerOfTyped &from, const std::string &name) override
        {
            return takeChild(dynamic_cast<MapOfTyped<Type>&>(from), name);
        }

        bool canTakeChildFrom(IContainerOfTyped &from) const override
        {
            return dynamic_cast<MapOfTyped<Type>*>(&from);
        }
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#undef FWDEC_SPTR
#endif
