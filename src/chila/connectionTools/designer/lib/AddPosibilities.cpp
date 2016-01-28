/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "AddPosibilities.hpp"
#include <chila/lib/misc/exceptions.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    AddPosibilities::PosibilitySet AddPosibilities::posibilities(const std::string &typeName) const
    {
        PosibilitySet ret;
        auto it = map.find(typeName);
        if (it == map.end())
            return PosibilitySet();

        for (const auto &vt : it->second)
        {
            auto &name = vt.first;
            auto &cData = vt.second;

            my_assert(ret.insert(Posibility(name, cData.addType)).second);
        }

        return ret;
    }

    chila::lib::node::Node &AddPosibilities::call(
        chila::lib::node::NodeWithChildren &node,
        const std::string &childName,
        const std::string &value)
    {
        auto it = map.find(typeid(node).name());
        my_assert(it != map.end())

        auto it2 = it->second.find(childName);
        my_assert(it2 != it->second.end());

        ChildData &cData = it2->second;
        return cData.fun(node, value);
    }
}
MY_NSP_END
