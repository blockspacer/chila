/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE2__CONTAINER_HPP
#define CHILA_LIB_NODE2__CONTAINER_HPP

#include "Node.hpp"
#include <boost/make_shared.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Container
    {
        public:
            template <typename Type>
            void add(std::string name, Type data)
            {
                auto ret = map.insert({rvalue_cast(name), boost::make_shared<Holder<Type>>(data)});
                my_assert(ret.second);
                itVec.push_back(ret.first);
            }

            template <typename Type>
            const Type &get(const std::string &name) const
            {
                auto it = map.find(name);
                my_assert(it != map.end());

                return boost::dynamic_pointer_cast<const Holder<Type>>(it->second)->held;
            }

            void stream(std::ostream &out, unsigned indent = 0) const;

        private:
            struct IHolder
            {
                virtual void stream(std::ostream &out, unsigned indent) const = 0;
                virtual ~IHolder() = default;
            };

            using IHolderSCPtr = boost::shared_ptr<const IHolder>;

            template <typename Type>
            struct Holder final : public IHolder
            {
                Type held;

                Holder(Type held) : held(rvalue_cast(held)) {}

                void stream(std::ostream &out, unsigned indent) const override
                {
                    held.stream(out, indent);
                }
            };

            using Map = std::map<std::string, IHolderSCPtr>;
            using ItVec = std::vector<Map::iterator>;

            Map map;
            ItVec itVec;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
