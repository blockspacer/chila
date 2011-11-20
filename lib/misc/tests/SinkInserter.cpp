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

#include "../SinkInserter.hpp"
#include "common.hpp"
#include <sstream>
#include <iostream>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

namespace tut
{
    struct SinkInserterData {};    
    CHILA_LIB_TUT__DEF_TEST_GROUP(SinkInserter)

    struct MyInserter : public libMisc::SinkInserter<MyInserter>
    {
        template <typename Sink>
        void write(Sink &out) const
        {
            out << "hello world!";
        }
    };

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        std::stringstream str;
        str << MyInserter();
        TUT_ENSURE_EQUAL(str.str(), "hello world!");
    }}

}

