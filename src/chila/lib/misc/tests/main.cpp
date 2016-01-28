/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <tut/tut.hpp>
#include <iostream>
#include <chila/lib/tut/Visualizator.hpp>

namespace tut
{
    test_runner_singleton runner;
}

int main()
{
    chila::lib::tut::Visualizator vis;
    tut::runner.get().set_callback(&vis);

    tut::runner.get().run_tests();

    return vis.end() ? 0 : 1;
}
