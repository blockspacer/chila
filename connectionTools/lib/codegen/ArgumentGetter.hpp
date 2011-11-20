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

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTGETTER_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_CODEGEN_ARGUMENTGETTER_HPP

#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/include/value_at_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,connectionTools,lib,codegen))
{
    template <typename InArgMap>
    struct ArgumentGetter
    {
        template <typename AliasType>
        struct result_of
        {
            BOOST_MPL_ASSERT((boost::fusion::result_of::has_key<InArgMap, AliasType>));
            typedef const typename boost::fusion::result_of::value_at_key<InArgMap, AliasType>::type& type;
        };

        const InArgMap &inArgs;
        ArgumentGetter(const InArgMap &inArgs) : inArgs(inArgs) {}

        template <typename AliasType>
        typename result_of<AliasType>::type getArgument(AliasType) const
        {
            return boost::fusion::at_key<AliasType>(inArgs);
        }
    };

    template <typename InArgMap>
    inline ArgumentGetter<InArgMap> argumentGetter(const InArgMap &inArgs)
    {
        return ArgumentGetter<InArgMap>(inArgs);
    }

}}}}

#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosDef.hpp>
#endif

