/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__CONTAINEROFTYPED_HPP
#define CHILA_LIB_NODE__CONTAINEROFTYPED_HPP

#include "NodeWithChildren.hpp"
#include "fwd.hpp"
#include <boost/utility.hpp>

#define FWDEC_SPTR  CHILA_LIB_MISC__FWDEC_SPTR

#include "nspDef.hpp"

MY_NSP_START
{
    struct IContainerOfTyped
    {
        virtual bool canTakeChildFrom(IContainerOfTyped &from) const = 0;

        virtual Node &takeChild(IContainerOfTyped &from, const std::string &name) = 0;
    };

    template <typename Type>
    struct ContainerOfTyped: public virtual NodeWithChildren, public virtual IContainerOfTyped
    {
        typedef Type            value_type;
        typedef Type&           reference;
        typedef const Type&     const_reference;
        typedef Type*           pointer;
        typedef const Type*     const_pointer;

        typedef node_iterator<NodeSPtrItVec::iterator, Type, NodeWithChildren::DerefFun> iterator;
        typedef node_iterator<NodeSPtrItVec::const_iterator, const Type, NodeWithChildren::DerefFun> const_iterator;

        FWDEC_SPTR(Type);

        typedef std::vector<Type*> PtrVec;
        typedef std::vector<const Type*> CPtrVec;

        Type &get(const std::string &name) { return NodeWithChildren::typedChild<Type>(name); }
        const Type &get(const std::string &name) const { return NodeWithChildren::typedChild<Type>(name); }

        Type *getPtr(const std::string &name) { return NodeWithChildren::typedChildPtr<Type>(name); }
        const Type *getPtr(const std::string &name) const { return NodeWithChildren::typedChildPtr<Type>(name); }

        iterator begin() { return iterator(NodeWithChildren::begin()); }
        iterator end() { return iterator(NodeWithChildren::end()); }

        const_iterator begin() const { return const_iterator(NodeWithChildren::begin()); }
        const_iterator end() const { return const_iterator(NodeWithChildren::end()); }

        const_iterator cbegin() const { return begin(); }
        const_iterator cend() const { return end(); }


        Type &front() { return *(begin()); }
        Type &back() { return *(end() - 1); }

        const Type &front() const { return *(begin()); }
        const Type &back() const { return *(end() - 1); }
    };
}
MY_NSP_END

#include "nspUndef.hpp"


#undef FWDEC_SPTR
#endif
