/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__TYPEDNODE_HPP
#define CHILA_LIB_NODE__TYPEDNODE_HPP

#include "Node.hpp"
#include "fwd.hpp"
#include <chila/lib/misc/util.hpp>
#include <boost/filesystem/path.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <boost/call_traits.hpp>

#define CHILA_META_NODE__DEF_TYPED_NODE_BASE(r, data, elem) , public elem

#define CHILA_META_NODE__DEF_TYPED_NODE(Name, Type, Bases, Methods) \
    struct Name: public chila::lib::node::TypedNode<Type> BOOST_PP_SEQ_FOR_EACH(CHILA_META_NODE__DEF_TYPED_NODE_BASE,, Bases) \
    { \
        friend chila::lib::node::Node; \
        public: \
            using This = Name; \
            explicit Name(const Type &value = Type()) : TypedNode(value) {} \
            void operator=(const Type &rhs) { TypedNode::operator=(rhs); } \
            static std::unique_ptr<Name> create(std::string name) \
            {\
                return Node::createNamed<Name>(rvalue_cast(name)); \
            } \
            BOOST_PP_SEQ_CAT(Methods) \
    }


#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Type>
    struct TypedNode: public Node
    {
        Type value;

        TypedNode(Type value = Type()) : value(rvalue_cast(value)) {}

        void operator=(Type rhs) { value = rvalue_cast(rhs); }

        virtual void stream(std::ostream &out, unsigned indent) const
        {
            out << chila::lib::misc::repeatText(indent, "    ") << name() << ": [" << value << "]" << std::endl;
        }

        operator Type&() { return value; }
        operator const Type&() const { return value; }
    };

    namespace typed
    {
        typedef unsigned long ulong;

        CHILA_META_NODE__DEF_TYPED_NODE(Boolean, bool,,());
        CHILA_META_NODE__DEF_TYPED_NODE(Integer, int,,());
        CHILA_META_NODE__DEF_TYPED_NODE(Float, float,,());
        CHILA_META_NODE__DEF_TYPED_NODE(Double, double,,());
        CHILA_META_NODE__DEF_TYPED_NODE(UInt, unsigned,,());
        CHILA_META_NODE__DEF_TYPED_NODE(ULong, ulong,,());
        CHILA_META_NODE__DEF_TYPED_NODE(String, std::string,,());
        CHILA_META_NODE__DEF_TYPED_NODE(FilePath, boost::filesystem::path,,());
        CHILA_META_NODE__DEF_TYPED_NODE(Path, chila::lib::misc::Path,,());
    }

    template <typename Type>
    inline std::ostream &operator<<(std::ostream &out, const TypedNode<Type> &value)
    {
        return out << value.value;
    }
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
