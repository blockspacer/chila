/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "../Path.hpp"
#include "../exceptions.hpp"
#include "../util.hpp"
#include <iostream>
#include "common.hpp"
#include <chila/lib/misc/macrosExp.hpp>

namespace tut
{
    struct PathData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(Path)

    CHILA_LIB_TUT__DEF_TEST(1, "Path")
    {
        libMisc::Path path;
        path.add("py").add("com").add("chila");

        TUT_ENSURE_EQUAL(path, libMisc::Path("py.com.chila"));
        TUT_ENSURE_EQUAL(path, libMisc::Path(std::string("py.com.chila")));

        const libMisc::Path::StringVec &names = path.getNames();
        TUT_ENSURE_EQUAL(names[0], "py");
        TUT_ENSURE_EQUAL(names[1], "com");
        TUT_ENSURE_EQUAL(names[2], "chila");

        TUT_ENSURE_EQUAL(path.top(), "chila");
        TUT_ENSURE_EQUAL(path.pop(), "chila");
        TUT_ENSURE_EQUAL(path.top(), "com");
        TUT_ENSURE_EQUAL(path.pop(), "com");
        TUT_ENSURE_EQUAL(path.top(), "py");
        TUT_ENSURE_EQUAL(path.pop(), "py");
        TUT_ENSURE_THROW(path.top(), libMisc::ElementNotFound);
        TUT_ENSURE_THROW(path.pop(), libMisc::ElementNotFound);

        libMisc::Path path2;
        path.add("lib").add("misc");
        path2.add("lib");
        TUT_ENSURE(path2 < path);
        path2.add("m");
        TUT_ENSURE(path2 < path);
        path2.pop();
        path2.add("n");
        TUT_ENSURE(!(path2 < path));

        std::stringstream str;
        str << path;
        TUT_ENSURE_EQUAL(str.str(), "lib.misc");

        path2 = path + "test";

        TUT_ENSURE_EQUAL(path2, "lib.misc.test");

    }}
}

