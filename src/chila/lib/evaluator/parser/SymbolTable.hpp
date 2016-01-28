/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_PARSER__SYMBOLTABLE_HPP
#define CHILA_LIB_EVALUATOR_PARSER__SYMBOLTABLE_HPP

#include "nspDef.hpp"

MY_NSP_START
{
    DEF_RUNTIME_ERROR2(SymbolAlreadyExists, "symbol already exists");
    DEF_RUNTIME_ERROR2(SymbolDoesNotExists, "symbol does not exists");
    DEF_RUNTIME_ERROR2(TypeDoesNotExists, "type does not exists");

    class SymbolTable
    {
        private:
            typedef std::map<std::string, expression::VariableProviderSCPtr> IdProviderMap;

            IdProviderMap providers;
            const expression::VariableProviderMap &identifierProviderMap;

        public:
            SymbolTable(const expression::VariableProviderMap &identifierProviderMap) :
                identifierProviderMap(identifierProviderMap) {}

            void addSymbol(const std::string &varName, const std::string &typeName) try
            {
                const expression::VariableProviderSCPtr &provider = identifierProviderMap.get(typeName);
                if (!providers.insert(IdProviderMap::value_type(varName, provider)).second)
                    throw SymbolAlreadyExists();
            }
            catch (const expression::VariableProviderDoesNotExists &ex)
            {
                throw TypeDoesNotExists();
            }

            expression::ExpressionSCPtr createVariable(const std::string &varName) const
            {
                IdProviderMap::const_iterator it = providers.find(varName);
                if (it == providers.end())
                    throw SymbolDoesNotExists();

                return it->second->create(varName);
            }

            void clear()
            {
                providers.clear();
            }
    };

}
MY_NSP_END

#include "nspUndef.hpp"


#endif
