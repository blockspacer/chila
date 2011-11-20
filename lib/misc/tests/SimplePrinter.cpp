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

#include "../SimplePrinter.hpp"
#include "../SinkInserter.hpp"
#include "common.hpp"
#include <sstream>
#include <iomanip>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

namespace tut
{
    struct SimplePrinterData {};    
    CHILA_LIB_TUT__DEF_TEST_GROUP(SimplePrinter)

    CHILA_LIB_TUT__DEF_TEST(1, "test")
    {
        typedef boost::reference_wrapper<std::stringstream> Sink;
        std::stringstream str;
        libMisc::SimplePrinter<Sink> printer(boost::ref(str));

        printer << libMisc::indent << "- hello\n";
        {
            libMisc::IndentGuard<Sink> guard(printer);
            printer << libMisc::indent << "- world\n"
                    << libMisc::indent << "- of\n"
                    << libMisc::indent << "- fortune\n";
            {
                libMisc::IndentGuard<Sink> guard(printer);
                printer << libMisc::indent << "- prince\n"
                        << libMisc::indent << "- of\n"
                        << libMisc::indent << "- persia\n";
            }
            printer << libMisc::indent << "- testing\n";
            {
                libMisc::IndentGuard<Sink> guard(printer);
                printer << libMisc::indent << "- main\n"
                        << libMisc::indent << "- on\n"
                        << libMisc::indent << "- fire\n";
            }
        }

        const char *toCompare =
            "- hello\n"
            "  - world\n"
            "  - of\n"
            "  - fortune\n"
            "    - prince\n"
            "    - of\n"
            "    - persia\n"
            "  - testing\n"
            "    - main\n"
            "    - on\n"
            "    - fire\n";

        TUT_ENSURE(str.str() == toCompare);
    }}


}

