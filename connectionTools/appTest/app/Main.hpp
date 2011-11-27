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

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP__MAIN_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP__MAIN_HPP

#include "impl/connection/ApplicationData.hpp"
#include <boost/asio/io_service.hpp>


#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#include <chila/lib/misc/macrosDef.hpp>

DEF_NAMESPACE(4, (chila,connectionTools,appTest,app))
{
    class Main
    {
        public:
            Main
            (
                boost::asio::io_service &ioService,
                const boost::asio::ip::tcp::endpoint &listenEndPoint
            );

            void start();

        private:
            typedef app::impl::connection::ApplicationData::AppArgs AppArgs;
            app::impl::connection::ApplicationData appData;

            app::impl::connection::Logger::CProviderSPtr logger;
            app::impl::connection::Network::CProviderSPtr network;
            app::impl::connection::MessageProcessor::CProviderSPtr messageProcessor;
    };

}}}}

#include <chila/lib/misc/macrosUndef.hpp>
#undef DEF_NAMESPACE
#endif


