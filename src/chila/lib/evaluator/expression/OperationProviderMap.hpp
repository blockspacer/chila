/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_EXPRESSION__OPERATIONPROVIDERMAP_HPP
#define CHILA_LIB_EVALUATOR_EXPRESSION__OPERATIONPROVIDERMAP_HPP

#include "defMacros.hpp"
#include "expression.hpp"
#include <boost/make_shared.hpp>
#include <stdlib.h>
#include <map>
#include <list>

#include "nspDef.hpp"

MY_NSP_START
{
    struct OperationProvider
    {
        virtual OperationSPtr create(const ArgumentListSCPtr &argList) const = 0;
        virtual ~OperationProvider() {}
    };

    template <typename Operation, typename Arg>
    struct BaseOperationProvider final: public OperationProvider
    {
        Arg arg;
        std::string name;

        BaseOperationProvider(const std::string &name, const Arg &arg) : name(name), arg(arg) {}

        OperationSPtr create(const ArgumentListSCPtr &argList) const try
        {
            return boost::make_shared<Operation>(name, arg, argList);
        }
        catch (const IncompatibleArgumentList&)
        {
            return boost::shared_ptr<Operation>();
        }
    };

    class OperationProviderMap
    {
        private:
            typedef std::list<OperationProviderSCPtr> ProviderList;
            typedef std::map<std::string, ProviderList> ProviderMap;
            ProviderMap providers;

        public:
            void add(const std::string &name, const OperationProviderSCPtr &provider)
            {
                providers[name].push_back(provider);
            }

            OperationSCPtr create(const std::string &name, const ArgumentListSCPtr &argList) const
            {
                ProviderMap::const_iterator plIt = providers.find(name);
                if (plIt == providers.end())
                    throw OperationProviderDoesNotExists();

                const ProviderList &pList = plIt->second;

                for (ProviderList::const_iterator it = pList.begin(); it != pList.end(); ++it)
                {
                    const OperationProvider &provider = **it;
                    if (OperationSCPtr ret = provider.create(argList))
                        return ret;
                }

                throw OperationProviderDoesNotExists();
            }

    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif

