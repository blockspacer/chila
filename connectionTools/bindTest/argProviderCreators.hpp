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

#ifndef CHILA_MODULETOOLS_FUNCTIONBINDER_ARGPROVIDERCREATORS_HPP
#define	CHILA_MODULETOOLS_FUNCTIONBINDER_ARGPROVIDERCREATORS_HPP

#include <boost/make_shared.hpp>
#include <boost/mpl/map.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,connectionTools,bindTest))
{
    template <typename Aliases>
    struct MessageCreatorArgProvider
    {
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename Aliases::message, MessageSCPtr>
        > ResultOfMap;

        MessageSCPtr message;
        MessageCreatorArgProvider(unsigned clientId, unsigned messageId) :
            message(boost::make_shared<Message>(clientId, messageId)) {}

        const MessageSCPtr &getArgument(typename Aliases::message) const { return message; }
    };

    template <typename Aliases>
    struct MessageReaderArgProvider
    {
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename Aliases::clientId, unsigned>,
            boost::mpl::pair<typename Aliases::messageId, unsigned>
        > ResultOfMap;

        const MessageSCPtr &message;
        MessageReaderArgProvider(const MessageSCPtr &message) :  message(message) {}

        unsigned getArgument(typename Aliases::clientId) const { return message->clientId; }
        unsigned getArgument(typename Aliases::messageId) const { return message->messageId; }
    };



}}}

#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif

