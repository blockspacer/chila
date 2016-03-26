/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "impl/connection/CPerformerData.hpp"
#include "Main.hpp"

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#include <chila/lib/misc/macrosExp.hpp>

#define cast_cprovider(Type, ptr) std::dynamic_pointer_cast<app::impl::connection::Type::CProvider>(ptr)

#define my_insert_fun(Alias, connector) cMap.add \
        ( \
            BOOST_PP_STRINGIZE(connector), \
            cast_cprovider(Alias, connector)->getConnector() \
        )

DEF_NAMESPACE(4, (chila,connectionTools,appTest,app))
{
    Main::Main
    (
        boost::asio::io_service &ioService,
        const boost::asio::ip::tcp::endpoint &listenEndPoint
    ) :
        network(app::impl::connection::Network::create(ioService, listenEndPoint)),
        logger(app::impl::connection::Logger::create()),
        messageProcessor(app::impl::connection::MessageProcessor::create(ioService))
    {
        using CPData = app::impl::connection::CPerformerData;

        CHILA_CONNECTIONTOOLS_LIB_OTHER__CHOLDER_INSERT
        (
            my_insert_fun,
            CHILA_CONNECTIONTOOLS_APPTEST_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ
        )

        CPData::connect(cMap);
    }

    void Main::start()
    {
        cast_cprovider(Network, network)->getConnector().actions.start();
    }

}}}}
