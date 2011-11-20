/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_MODULETOOLS_FUNCTIONBINDER_APPLICATION_HPP
#define	CHILA_MODULETOOLS_FUNCTIONBINDER_APPLICATION_HPP

#include <boost/mpl/map.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <chila/connectionTools/lib/codegen/util.hpp>
#include <chila/connectionTools/lib/codegen/ArgumentProviderCreator.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen
#define mtLibCGen chila::connectionTools::lib::codegen
#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK
#define APROVIDER_CREATOR CHILA_CONNECTIONTOOLS_LIB_CODEGEN__APROVIDER_CREATOR



DEF_NAMESPACE(3, (chila,connectionTools,bindTest))
{
    template <typename Connectors>
    struct Application
    {
        struct ArgAliases
        {
            DEF_ARG_ALIAS(clientId);
            DEF_ARG_ALIAS(messageId);
            DEF_ARG_ALIAS(message);
            DEF_ARG_ALIAS(error);
            DEF_ARG_ALIAS(timeStamp);
        };

        struct Connector0Desc
        {
            typedef typename Connectors::Connector0 Connector;

            // arg ---> alias
            typedef boost::mpl::map
            <
                DEF_ARG_ALIAS_LINK(clientId,    clientId),
                DEF_ARG_ALIAS_LINK(messageId,   messageId),
                DEF_ARG_ALIAS_LINK(error,       error),
                DEF_ARG_ALIAS_LINK(timeStamp,   timeStamp)
            > ArgAliasLinks;
        };

        struct Connector1Desc
        {
            typedef typename Connectors::Connector1 Connector;

            // arg ---> alias
            typedef boost::mpl::map
            <
                DEF_ARG_ALIAS_LINK(message,     message),
                DEF_ARG_ALIAS_LINK(error,       error),
                DEF_ARG_ALIAS_LINK(timeStamp,   timeStamp)
            > ArgAliasLinks;
        };

        // ConnectorDescMap
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename Connectors::Connector0, Connector0Desc>,
            boost::mpl::pair<typename Connectors::Connector1, Connector1Desc>
        > ConnectorDescMap;

        #define myMsgProvCreatorAPC APROVIDER_CREATOR       \
        (                                                   \
            args.providers.myMsgProvCreator,                \
            (clientId)(messageId),                          \
            (message)                                       \
        )

        #define myMsgProvReaderAPC  APROVIDER_CREATOR       \
        (                                                   \
            args.providers.myMsgProvReader,                 \
            (message),                                      \
            (clientId)(messageId)                           \
        )

        template <typename Args>
        static void connect(const Args &args)
        {
            mtLibCGen::bindActions<ConnectorDescMap>
            (
                args.connectors.connector0.events.event1,
                boost::fusion::make_vector(myMsgProvCreatorAPC),
                boost::fusion::make_vector
                (
                    args.connectors.connector1.actions.action1,
                    args.connectors.connector1.actions.action1
                )
            );

            mtLibCGen::bindActions<ConnectorDescMap>
            (
                args.connectors.connector1.events.event1,
                boost::fusion::make_vector
                (
                    myMsgProvReaderAPC
                ),
                boost::fusion::make_vector
                (
                    args.connectors.connector0.actions.action1
                )
            );
        }

        #undef myMsgProvCreator
        #undef myMsgProvReader
    };



}}}

#undef mtLibCGen
#undef MT_CODEGEN_NSP
#undef DEF_NAMESPACE
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK
#undef APROVIDER_CREATOR
#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>
#include <chila/lib/misc/macrosDef.hpp>
#endif

