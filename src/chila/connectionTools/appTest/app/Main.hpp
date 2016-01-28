/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_APPTEST_APP__MAIN_HPP
#define CHILA_CONNECTIONTOOLS_APPTEST_APP__MAIN_HPP

#include "impl/connection/fwd.hpp"
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <boost/asio.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#include <chila/lib/misc/macrosExp.hpp>

DEF_NAMESPACE(4, (chila,connectionTools,appTest,app))
{
    using chila::connectionTools::lib::codegen::ConnectorMap;

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
            app::impl::connection::CProviderSPtr logger;
            app::impl::connection::CProviderSPtr network;
            app::impl::connection::CProviderSPtr messageProcessor;

            ConnectorMap cMap;
    };

}}}}

#undef DEF_NAMESPACE
#endif


