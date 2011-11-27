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

#include "Logger.hpp"
#include <boost/make_shared.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(5, (chila,connectionTools,appTest,app,impl))
{
    void Logger::moduleStarted(const std::string &moduleName)
    {
        std::cout << "Module started: " << moduleName << std::endl;
    }

    void Logger::clientConnected(unsigned clientId)
    {
        std::cout << "[client " << clientId << "] Client connected. " << std::endl;
    }

    void Logger::clientDisconnected(unsigned clientId)
    {
        std::cout << "[client " << clientId << "] Client disconnected. " << std::endl;
    }

    void Logger::msgReceived(unsigned clientId, const BufferSCPtr &recvBuffer)
    {
        std::cout << "[client " << clientId << "] Message received: [";
        std::copy(recvBuffer->begin(), recvBuffer->end(), std::ostream_iterator<char, char>(std::cout,""));
        std::cout << "]" << std::endl;
    }

    void Logger::msgProcessed(unsigned clientId, const BufferSCPtr &sndBuffer)
    {
        std::cout << "[client " << clientId << "] Message processed: [";
        std::copy(sndBuffer->begin(), sndBuffer->end(), std::ostream_iterator<char, char>(std::cout,""));
        std::cout << "]" << std::endl;
    }

    connection::Logger::CProviderSPtr connection::Logger::create()
    {
        return boost::make_shared<app::impl::Logger>();
    }
}}}}}

