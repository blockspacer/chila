/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ActionMap.hpp"
#include "actions.hpp"
#include "macros.fgen.hpp"

#define ipss(size) chila::lib::misc::InPlaceStrStream<size>()

MY_NSP_START
{
    ActionElement *ActionMap::getPtr(const std::string &key)
    {
        auto it = map.find(key);
        if (it == map.end())
            return nullptr;

        return it->second.get();
    }

    const ActionElement *ActionMap::getPtr(const std::string &key) const
    {
        auto it = map.find(key);
        if (it == map.end())
            return nullptr;

        return it->second.get();
    }

    ActionElement &ActionMap::get(const std::string &key)
    {
        auto *ret = getPtr(key);
        if (!ret)
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        return *ret;
    }

    const ActionElement &ActionMap::get(const std::string &key) const
    {
        auto *ret = getPtr(key);
        if (!ret)
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        return *ret;
    }

    void ActionMap::add(std::string key, ActionElementSPtr value)
    {
        auto ret = map.insert(Map::value_type(rvalue_cast(key), rvalue_cast(value)));
        if (!ret.second)
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementAlreadyExists());

        iters.push_back(ret.first);
    }
}
MY_NSP_END

#include "macros.fgen.hpp"
