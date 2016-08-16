/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__FWD_HPP
#define CHILA_LIB_NODE__FWD_HPP

#include <memory>
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <chila/connectionTools/lib/tree/fwd.hpp>

#define FWDEC_TYPE  CHILA_LIB_MISC__FWDEC_TYPE
#define FWDEC_SPTR  CHILA_LIB_MISC__FWDEC_SPTR

#include <chila/lib/misc/macrosExp.hpp>

#define CHILA_META_NODE__DEF_NODE_BASE(z, data, i, Base) BOOST_PP_COMMA_IF(i) public Base

#define CHILA_META_NODE__DEF_NODE(Name, Bases, Methods) \
    class Name : BOOST_PP_SEQ_FOR_EACH_I(CHILA_META_NODE__DEF_NODE_BASE,,Bases) \
    { \
        public: \
            using This = Name; \
            Name() = default; \
            Name(const Name&) = default; \
            Name(Name&&) = default; \
            \
            static std::shared_ptr<Name> create(std::string name) \
            {\
                std::shared_ptr<Name> ret = std::make_shared<Name>(); \
                ret->_name = name; \
                return ret; \
            } \
            BOOST_PP_SEQ_CAT(Methods) \
            std::pair<chila::lib::node::NodeWithChildrenSPtr, Name&> cloneAll() const \
            { \
                auto ret = Node::cloneAll(); \
                return {ret.first, ret.second.toType<Name>()}; \
            } \
        protected: \
            chila::lib::node::NodeSPtr clone(const std::string &newName = "") const override \
            { \
                auto ret = std::make_shared<Name>(*this); \
                if (!newName.empty()) ret->_name = newName; \
                return ret; \
            } \
    }

#include "nspDef.hpp"

MY_NSP_START
{
    FWDEC_TYPE(Node);
    FWDEC_TYPE(NodeWithChildren);
    FWDEC_TYPE(CheckData);

    typedef std::map<std::string, NodeSPtr> NodeSPtrMap;
    typedef std::vector<NodeSPtrMap::iterator> NodeSPtrItVec;

    template <typename Type>
    struct TypedNode;

    template <typename Type>
    struct MapOfTyped;

    typedef TypedNode<std::string> StringNode;
    typedef TypedNode<unsigned> UnsignedNode;

    typedef std::vector<Node*> NodePtrVec;
    typedef std::vector<const Node*> NodeCPtrVec;

    struct CheckData
    {
        virtual ~CheckData() {}
    };

    using PathVec = std::vector<chila::lib::misc::Path>;


}
MY_NSP_END

#include "nspUndef.hpp"

#undef FWDEC_TYPE
#undef FWDEC_SPTR
#endif
