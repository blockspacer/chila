/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_EXPRESSION__VARIABLEPROVIDERMAP_HPP
#define CHILA_LIB_EVALUATOR_EXPRESSION__VARIABLEPROVIDERMAP_HPP

#include "fwd.hpp"
#include "defMacros.hpp"
#include "expression.hpp"
#include <stdlib.h>
#include <map>
#include <list>

#include "nspDef.hpp"

MY_NSP_START
{
    struct VariableProvider
    {
        virtual ExpressionSCPtr create(const std::string &name) const = 0;
        virtual ~VariableProvider() {}
    };

    template <typename Variable>
    struct BaseVariableProvider final: public VariableProvider
    {
        ExpressionSCPtr create(const std::string &name) const
        {
            return std::make_shared<Variable>(name);
        }
    };

    class VariableProviderMap
    {
        private:
            typedef std::map<std::string, VariableProviderSCPtr> ProviderMap;
            ProviderMap providers;

        public:
            void add(const std::string &typeName, const VariableProviderSCPtr &provider)
            {
                if (!providers.insert(ProviderMap::value_type(typeName, provider)).second)
                    throw VariableProviderAleradyExists();
            }

            const VariableProviderSCPtr &get(const std::string &typeName) const
            {
                ProviderMap::const_iterator it = providers.find(typeName);
                if (it == providers.end())
                    throw VariableProviderDoesNotExists();

                return it->second;
            }
    };

}
MY_NSP_END

#include "nspUndef.hpp"

#endif

