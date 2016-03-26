/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ACTIONMAP_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__ACTIONMAP_HPP


#include "fwd.hpp"
#include <boost/utility.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/iter_iterator.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/misc/macrosExp.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__DEF_ITER_ITERATOR(action_map_iterator,
    (
        return **(this->it);
    ));


    class ActionMap final: public ActionElement, boost::noncopyable
    {
        private:
            using Map = std::map<std::string, ActionElementSPtr>;
            using IterVec = std::vector<Map::iterator>;

        public:
            typedef action_map_iterator<IterVec::iterator, Map::value_type> iterator;
            typedef action_map_iterator<IterVec::const_iterator, const Map::value_type> const_iterator;

            ActionMap(std::string id = "", ActionMap *parent = nullptr) : ActionElement(rvalue_cast(id), parent) {}

            template <typename Type>
            Type &addAction(std::string key = Type::title())
            {
                auto ret = std::make_shared<Type>(key, this);
                add(rvalue_cast(key), ret);
                return *ret;
            }

            ActionMap &addMap(std::string key)
            {
                auto ret = std::make_shared<ActionMap>(key, this);
                add(rvalue_cast(key), ret);
                return *ret;
            }

            ActionElement *getPtr(const std::string &key);
            const ActionElement *getPtr(const std::string &key) const;

            ActionElement &get(const std::string &key);
            const ActionElement &get(const std::string &key) const;

            iterator begin() { return iterator(iters.begin()); }
            iterator end() { return iterator(iters.end()); }

            const_iterator begin() const { return const_iterator(iters.begin()); }
            const_iterator end() const { return const_iterator(iters.end()); }

            bool empty() const { return map.empty(); }

        private:
            Map map;
            IterVec iters;

            void add(std::string key, ActionElementSPtr value);
    };

}
MY_NSP_END

#undef def_action
#include "macros.fgen.hpp"


#endif
