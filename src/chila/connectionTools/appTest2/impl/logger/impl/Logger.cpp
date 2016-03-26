/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Logger.hpp"
#include <iostream>
#include <boost/make_shared.hpp>

#define MODULE_NAME Logger

#include "nspDef.hpp"

MY_NSP_START
{
    void Logger::MOD_ACTION_SIG(launcher_start)
    {
        std::cout << "Module started: logger" << std::endl;

        execute_event(launcher_started)();
    }

    void Logger::MOD_ACTION_SIG(moduleStarted)
    {
        std::cout << "Module started: " << moduleName << std::endl;
    }

    void Logger::MOD_ACTION_SIG(clientConnected)
    {
        std::cout << "[client " << clientId << "] Client connected. " << std::endl;
    }

    void Logger::MOD_ACTION_SIG(clientDisconnected)
    {
        std::cout << "[client " << clientId << "] Client disconnected. " << std::endl;
    }

    void Logger::MOD_ACTION_SIG(connectionError)
    {
        std::cout << "[client " << clientId << "] Connection error: " << errorMsg << std::endl;
    }

    void Logger::MOD_ACTION_SIG(msgReceived)
    {
        std::cout << "[client " << clientId << "] Message received: [";
        std::copy(recvBuffer->begin(), recvBuffer->end(), std::ostream_iterator<char, char>(std::cout,""));
        std::cout << "]" << std::endl;
    }

    void Logger::MOD_ACTION_SIG(msgProcessed)
    {
        std::cout << "[client " << clientId << "] Message processed: [";
        std::copy(sndBuffer->begin(), sndBuffer->end(), std::ostream_iterator<char, char>(std::cout,""));
        std::cout << "]" << std::endl;
    }

    connection::Logger::CProviderSPtr connection::Logger::create()
    {
        return std::make_shared<impl::Logger>();
    }
}
MY_NSP_END


