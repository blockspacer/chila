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

#include "Modules.hpp"
#include "Application.hpp"
#include "argProviderCreators.hpp"

#include <iostream>
#include <chila/lib/misc/Construct.hpp>



namespace bindTest = chila::connectionTools::bindTest;
namespace libMisc = chila::lib::misc;

struct Connectors
{
    typedef bindTest::Module0::Connector Connector0;
    typedef bindTest::Module1::Connector Connector1;

    Connector0 &connector0;
    Connector1 &connector1;

    Connectors(Connector0 &connector0, Connector1 &connector1) :
        connector0(connector0), connector1(connector1) {}

};

typedef bindTest::Application<Connectors> MyApplication;

struct Args
{
    typedef bindTest::Module0::Connector Connector0;
    typedef bindTest::Module1::Connector Connector1;

    Connectors connectors;

    struct Providers
    {
        libMisc::Construct< bindTest::MessageCreatorArgProvider<MyApplication::ArgAliases> > myMsgProvCreator;
        libMisc::Construct< bindTest::MessageReaderArgProvider<MyApplication::ArgAliases> > myMsgProvReader;
    } providers;

    Args(Connector0 &connector0, Connector1 &connector1) :
        connectors(connector0, connector1) {}
};


int main(int argc, char** argv)
{
    bindTest::Module0 mod0;
    bindTest::Module1 mod1;

    Args args(mod0.connector, mod1.connector);

    MyApplication::connect(args);

    mod0.connector.events.event1.function(8, 3, 9.7, "just saying...");
    mod1.connector.events.event1.function(boost::make_shared<bindTest::Message>(2, 9), 6.4, "that it works.");

    return 0;
}

