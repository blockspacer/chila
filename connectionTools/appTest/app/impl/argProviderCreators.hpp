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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_ARGPROVIDERCREATORS_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_ARGPROVIDERCREATORS_HPP

//#include "../connectors/gen/Logging.hpp"
#include <boost/mpl/map.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    template <typename ArgAliases>
    struct MessageCreatorArgProvider
    {
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename ArgAliases::procMessage, ProcMessageSCPtr>
        > ResultOfMap;

        ProcMessageSCPtr message;
        MessageCreatorArgProvider(unsigned clientId, const BufferSCPtr &buffer) :
            message(boost::make_shared<MyProcMessage>(clientId, buffer)) {}

        const ProcMessageSCPtr &getArgument(typename ArgAliases::procMessage) const { return message; }
    };

    template <typename ArgAliases>
    struct MessageReaderArgProvider
    {
        typedef boost::mpl::map
        <
            boost::mpl::pair<typename ArgAliases::clientId, unsigned>
        > ResultOfMap;

        MyProcMessageSCPtr message;
        MessageReaderArgProvider(const ProcMessageSCPtr &message) :
            message(boost::dynamic_pointer_cast<const MyProcMessage>(message)) {}

        unsigned getArgument(typename ArgAliases::clientId) const { return message->clientId; }
    };

}}}}}

#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>
#endif
