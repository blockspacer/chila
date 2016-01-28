/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ADDPOSIBILITIES_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ADDPOSIBILITIES_HPP

#include "fwd.hpp"
#include <set>
#include <functional>
#include <chila/lib/node/NodeWithChildren.hpp>
#include <chila/lib/node/fwd.hpp>
#include <map>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type, typename ChildType, bool withName>
    struct addNode
    {
        ChildType &operator()(chila::lib::node::NodeWithChildren &node, const std::string &nodeName)
        {
            return node.toType<Type>().template add<ChildType>();
        }
    };

    template <typename Type, typename ChildType>
    struct addNode<Type, ChildType, true>
    {
        ChildType &operator()(chila::lib::node::NodeWithChildren &node, const std::string &nodeName)
        {
            return node.toType<Type>().template add<ChildType>(nodeName);
        }
    };

    template <bool withValue>
    struct setValue
    {
        template <typename Type>
        Type &operator()(Type &node, const std::string &value)
        {
            return node;
        }
    };

    template <>
    struct setValue<true>
    {
        template <typename Type>
        Type &operator()(Type &node, const std::string &value)
        {
            node.value = value;
            return node;
        }
    };

    class AddPosibilities
    {
        public:
            struct Posibility
            {
                std::string name;
                AddType addType;

                Posibility(std::string name = "", AddType addType = AddType::NONE) : name(rvalue_cast(name)), addType(addType) {}

                bool operator<(const Posibility &rhs) const { return name < rhs.name; }
            };

            using PosibilitySet = std::set<Posibility>;

            template <typename Type, typename ChildType, bool withName, bool withValue>
            void set(AddType addType, const std::string &childName = "")
            {
                set(typeid(Type).name(), childName, addType,
                    [](chila::lib::node::NodeWithChildren &node,
                       const std::string &value) -> chila::lib::node::Node&
                    {
                        return setValue<withValue>()(addNode<Type, ChildType, withName>()(node, value), value);
                    });
            }

            template <typename Type, typename Fun>
            void set(const std::string &childName, AddType addType, Fun fun)
            {
                map[typeid(Type).name()][childName] = ChildData(addType, rvalue_cast(fun));
            }

            PosibilitySet posibilities(const std::string &typeName) const;

            PosibilitySet posibilities(const chila::lib::node::Node &node) const
            {
                return posibilities(typeid(node).name());
            }

            chila::lib::node::Node &call(
                chila::lib::node::NodeWithChildren &node,
                const std::string &childName,
                const std::string &value);

            unsigned size(const std::string &typeName) const
            {
                auto it = map.find(typeName);
                my_assert(it != map.end());

                return it->second.size();
            }

        private:
            using AdderFun = std::function<chila::lib::node::Node&
            (
                chila::lib::node::NodeWithChildren &node,
                const std::string &value
            )>;

            struct ChildData
            {
                AdderFun fun;
                AddType addType;

                ChildData(AddType addType = AddType::NONE, AdderFun fun = AdderFun()) :
                    addType(addType), fun(rvalue_cast(fun)) {}
            };

            using ChildFunMap = std::map<std::string, ChildData>;
            using AdderMap = std::map<std::string, ChildFunMap>;
            AdderMap map;

            template <typename Fun>
            void set(const std::string &typeName, const std::string &childName, AddType addType, Fun fun)
            {
                map[typeName][childName] = ChildData(addType, rvalue_cast(fun));
            }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"



#endif

