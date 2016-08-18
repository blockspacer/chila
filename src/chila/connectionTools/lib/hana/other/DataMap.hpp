/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__DATAMAP_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__DATAMAP_HPP

#include "fwd.hpp"
#include <map>
#include "exceptions.hpp"
#include <boost/any.hpp>
#include <chila/lib/misc/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct DataMap
    {
        public:
            template <typename Type>
            Type getVal(const std::string &name) const
            {
                auto it = map.find(name);
                my_assert(it != map.end());

                auto source = it->second;
                try
                {
                    return boost::any_cast<Type>(source);
                }
                catch (const boost::bad_any_cast &ex)
                {
                    throw DataMapElementNotFound() << ErrorInfo::SourceType(source.type().name())
                                                   << ErrorInfo::DestType(boost::typeindex::type_id<boost::reference_wrapper<Type>>().pretty_name())
                                                   << ErrorInfo::DataMapValueName(name);
                }
            }

            template <typename Type>
            void insertVal(std::string name, Type data)
            {
                my_assert(map.insert({rvalue_cast(name), rvalue_cast(data)}).second);
            }

            template <typename Type>
            Type &getRef(const std::string &name) const
            {
                auto it = map.find(name);
                my_assert(it != map.end());

                auto source = it->second;
                try
                {
                    return boost::unwrap_ref(boost::any_cast<boost::reference_wrapper<Type>&>(const_cast<boost::any&>(source)));
                }
                catch (const boost::bad_any_cast &ex)
                {
                    throw DataMapElementNotFound() << ErrorInfo::SourceType(source.type().name())
                                                   << ErrorInfo::DestType(boost::typeindex::type_id<boost::reference_wrapper<Type>>().pretty_name())
                                                   << ErrorInfo::DataMapValueName(name);
                }
            }

            template <typename Type>
            void insertRef(std::string name, Type &data)
            {
                my_assert(map.insert({rvalue_cast(name), boost::ref(data)}).second);
            }


        private:
            using Map = std::map<std::string, boost::any>;
            Map map;

            const Map &getMap() const { return map; }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
