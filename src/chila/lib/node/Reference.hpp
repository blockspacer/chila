/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__REFERENCE_HPP
#define CHILA_LIB_NODE__REFERENCE_HPP

#include "Node.hpp"
#include "fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include <chila/lib/misc/util.hpp>
#include <boost/call_traits.hpp>

#define CHILA_META_NODE__DEF_REFERENCE_TNODE(Name, Type, RefType, Container) \
    CHILA_META_NODE__DEF_TYPED_NODE(Name, Type, (chila::lib::node::Reference<RefType>), \
    ( \
        CHILA_META_NODE__DEF_REFERENCE_NODE_METHODS(Container) \
        CHILA_META_NODE__DEF_CHECK_BASES((Reference<RefType>), 0) \
    ))

#define CHILA_META_NODE__DEF_REFERENCE_VNODE(Name, RefType, Container) \
    CHILA_META_NODE__DEF_VOID_NODE(Name, (chila::lib::node::Reference<RefType>), \
    ( \
        CHILA_META_NODE__DEF_REFERENCE_NODE_METHODS(Container) \
        CHILA_META_NODE__DEF_CHECK_BASES((Reference<RefType>), 0) \
    ))

#define CHILA_META_NODE__DEF_REFERENCE_NODE_METHODS(Container) \
        Type &referenced() override; \
        const Type &referenced() const override; \
        static Container &base(Node &ref); \
        static const Container &base(const Node &ref); \
        chila::lib::node::NodeSPtr createWithRef(const chila::lib::node::Node &newReferenced) const override;

#include "nspDef.hpp"

MY_NSP_START
{
    struct IReference
    {
        virtual chila::lib::misc::Path refPath() const = 0;
        virtual chila::lib::node::NodeSPtr createWithRef(const chila::lib::node::Node &newReferenced) const = 0;
        virtual ~IReference() {}
    };

    template <typename _Type>
    struct Reference: public IReference
    {
        using Type = _Type;

        virtual Type &referenced() = 0;
        virtual const Type &referenced() const = 0;

        chila::lib::misc::Path refPath() const override { return referenced().path(); }

        void check(chila::lib::node::CheckData *data = nullptr) const
        {
            chila::lib::node::CheckExceptionList list;
            chila::lib::node::checkAndAdd(list, [&]{ referenced(); });
            if (!list.exceptions.empty()) throw list;
        }
    };
}
MY_NSP_END

#include "nspUndef.hpp"


#endif
