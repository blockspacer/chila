/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__STRUCTNODE_HPP
#define CHILA_LIB_NODE__STRUCTNODE_HPP

#include "NodeWithChildren.hpp"
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <boost/call_traits.hpp>

#include <chila/lib/misc/macrosExp.hpp>

#define CHILA_META_NODE__STRUCT_GETTER(Type, name) \
    Type &name() { return typedChild<Type>(BOOST_PP_STRINGIZE(name)); } \
    const Type &name() const { return typedChild<Type>(BOOST_PP_STRINGIZE(name)); }

#define CHILA_META_NODE__STRUCT_LOAD(Type, name) \
    add(Type::create(BOOST_PP_STRINGIZE(name)));

#define CHILA_META_NODE__STRUCT_GETTER_ELEM(r, data, elem) CHILA_META_NODE__STRUCT_GETTER \
    ( \
        BOOST_PP_SEQ_ELEM(0, elem), \
        BOOST_PP_SEQ_ELEM(1, elem) \
    )

#define CHILA_META_NODE__STRUCT_LOAD_ELEM(r, data, elem) CHILA_META_NODE__STRUCT_LOAD \
    ( \
        BOOST_PP_SEQ_ELEM(0, elem), \
        BOOST_PP_SEQ_ELEM(1, elem) \
    )

#define CHILA_META_NODE__DEF_STRUCT_NODE_BASE(z, data, i, Base) , public Base

#define CHILA_META_NODE__DEF_STRUCT_NODE(Name, Bases, Methods, memberSeq) \
    class Name : \
        public virtual chila::lib::node::NodeWithChildren \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_META_NODE__DEF_STRUCT_NODE_BASE,,Bases) \
    { \
        public: \
            using This = Name; \
            \
            Name() \
            { \
                BOOST_PP_SEQ_FOR_EACH(CHILA_META_NODE__STRUCT_LOAD_ELEM,, memberSeq) \
            } \
            Name(const Name&) = default; \
            \
            BOOST_PP_SEQ_FOR_EACH(CHILA_META_NODE__STRUCT_GETTER_ELEM,, memberSeq) \
            \
            static std::shared_ptr<Name> create(std::string name) \
            {\
                auto ret = std::make_shared<Name>(); \
                ret->_name = name; \
                return ret; \
            } \
            BOOST_PP_SEQ_CAT(Methods) \
            \
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
    };

#endif
