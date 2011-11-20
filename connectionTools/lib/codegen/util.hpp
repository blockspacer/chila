/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_UTIL_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_CODEGEN_UTIL_HPP

#include "ArgMapCreator.hpp"
#include "ArgMapExecuter.hpp"
#include "AProviderStacker.hpp"
#include <chila/lib/misc/fusion/FunSeqExecuter.hpp>
#include <iostream>
#include "ActionExecuterVecCreator.hpp"

#include <boost/fusion/algorithm/iteration/for_each.hpp>

#include "macrosDef.hpp"

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
{

    struct Show
    {
        template <typename PairType>
        void operator()(const PairType &p) const
        {
            std::cout << "<" << boost::fusion::result_of::first<PairType>::type::getName() << "> "
                      << p.second.getName() << ": " << p.second.data << std::endl;

        }
    };


    struct PrintArgs
    {
        typedef void result_type;

        template <typename MapType>
        void operator()(const MapType &list) const
        {
            boost::fusion::for_each(list, Show());
        }
    };

    #define ARG_ALIAS_LINKS_OF(function) \
        typename boost::mpl::at<ConnectorDescMap, typename function::ConnectorType>::type::ArgAliasLinks

    struct FunToProvideAux
    {
        typedef void result_type;

        template <typename Whatever>
        void operator()(const Whatever&) const
        {
        }
    };

    /** Special setter for no action to be executed by 'cb'. Does nothing. Will be called by 'bindActions'. */
    template <typename ConnectorDescMap, typename event, typename AProviderStack, typename ActionFSeq>
    inline void bindActionsN(event &cb, const AProviderStack &aProviderStack, const ActionFSeq &actions,
            boost::mpl::int_<0>)
    {
    }

    /** Special setter for 1 action to be executed by 'cb'. Does nothing. Will be called by 'bindActions'. */
    template <typename ConnectorDescMap, typename event, typename AProviderStack, typename ActionFSeq>
    inline void bindActionsN(event &cb, const AProviderStack &aProviderStack, const ActionFSeq &actions,
            boost::mpl::int_<1>)
    {
        typedef ARG_ALIAS_LINKS_OF(event) SrcArgAliasLinks;
        typedef typename InArgMapCreator<SrcArgAliasLinks, event>::MapType InArgMap;
        typedef typename AProviderStacker<AProviderStack, InArgMap, FunToProvideAux>::ResultType AProviderStackType;

        typedef typename boost::fusion::result_of::value_at_c<ActionFSeq, 0>::type action;
        const action &ac = boost::fusion::at_c<0>(actions);

        cb.function = InArgMapCreator<SrcArgAliasLinks, event>::argSynthetizer(aProviderStacker<InArgMap>(
                aProviderStack, argMapExecuter<ConnectorDescMap, AProviderStackType>(ac)));
    }

    /** General setter for the actions to be executed by 'cb'. Will be called by 'bindActions'. */
    template <typename ConnectorDescMap, typename event, typename AProviderStack, typename ActionFSeq, typename Selector>
    inline void bindActionsN(event &cb, const AProviderStack &aProviderStack, const ActionFSeq &actions,
            Selector)
    {
        typedef ARG_ALIAS_LINKS_OF(event) SrcArgAliasLinks;
        typedef typename InArgMapCreator<SrcArgAliasLinks, event>::MapType InArgMap;
        typedef typename AProviderStacker<AProviderStack, InArgMap, FunToProvideAux>::ResultType AProviderStackType;

        using chila::lib::misc::fusion::funSeqExecuter;

        cb.function = InArgMapCreator<SrcArgAliasLinks, event>::argSynthetizer(aProviderStacker<InArgMap>(
                aProviderStack,
                funSeqExecuter(actionExecuterVecCreator<ConnectorDescMap, AProviderStackType>(actions)())));
    }

    /** Sets the actions to be executed by 'cb'. */
    template <typename ConnectorDescMap, typename event, typename AProviderStack, typename ActionFSeq>
    inline void bindActions(event &cb, const AProviderStack &aProviderStack, const ActionFSeq &actions)
    {
        static const unsigned aCount = boost::fusion::result_of::size<ActionFSeq>::value;

        bindActionsN<ConnectorDescMap>(cb, aProviderStack, actions,
                boost::mpl::int_<aCount>());
    }


}}}}



#undef DEF_NAMESPACE
#include "macrosUndef.hpp"
#include <chila/lib/misc/macrosDef.hpp>
#endif

