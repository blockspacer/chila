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
            \
            static std::unique_ptr<Name> create(std::string name) \
            {\
                std::unique_ptr<Name> ret = Node::createNamed<Name>(rvalue_cast(name)); \
                return ret; \
            } \
            BOOST_PP_SEQ_CAT(Methods) \
    }

#include "nspDef.hpp"

MY_NSP_START
{
    FWDEC_TYPE(Node);
    FWDEC_TYPE(NodeWithChildren);
    FWDEC_TYPE(CheckData);

    typedef std::map<std::string, NodeUPtr> NodeUPtrMap;
    typedef std::vector<NodeUPtrMap::iterator> NodeUPtrItVec;

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

}
MY_NSP_END

#include "nspUndef.hpp"

#undef FWDEC_TYPE
#undef FWDEC_SPTR
#endif
