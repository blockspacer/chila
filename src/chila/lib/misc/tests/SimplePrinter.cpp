/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../SimplePrinter.hpp"
#include "../SinkInserter.hpp"
#include "common.hpp"
#include <sstream>
#include <iomanip>
#include <chila/lib/misc/macrosExp.hpp>

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

