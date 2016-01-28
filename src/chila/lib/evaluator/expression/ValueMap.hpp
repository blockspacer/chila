/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_EXPRESSION__VALUEMAP_HPP
#define CHILA_LIB_EVALUATOR_EXPRESSION__VALUEMAP_HPP

#include "fwd.hpp"
#include <map>
#include <boost/any.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <stdlib.h>

#include "nspDef.hpp"

MY_NSP_START
{
    class ValueMap
    {
        private:
            typedef std::map<std::string, ValueSCPtr> MapType;
            MapType values;

        public:
            void setValue(const std::string &varName, const ValueSCPtr &value)
            {
                values[varName] = value;
            }

            template <typename Type>
            void setValue(const std::string &varName, const Type &value)
            {
                values[varName] = boost::make_shared< ValueBase<Type> >(value);
            }

            const ValueSCPtr &getValue(const std::string &varName) const
            {
                MapType::const_iterator it = values.find(varName);
                if (it == values.end())
                    throw ValueNotSet();
                else
                    return it->second;
            }
    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif

