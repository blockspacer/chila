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

#include "../Path.hpp"
#include "../exceptions.hpp"
#include "../util.hpp"
#include <iostream>
#include "common.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

namespace tut
{
    struct PathData {};
    CHILA_LIB_TUT__DEF_TEST_GROUP(Path)

    CHILA_LIB_TUT__DEF_TEST(1, "Path")
    {
        libMisc::Path path;
        path << "py" << "com" << "chila";

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
        path << "lib" << "misc";
        path2 << "lib";
        TUT_ENSURE(path2 < path);
        path2 << "m";
        TUT_ENSURE(path2 < path);
        path2.pop();
        path2 << "n";
        TUT_ENSURE(!(path2 < path));

        std::stringstream str;
        str << path;
        TUT_ENSURE_EQUAL(str.str(), "lib.misc");

        path2 = path + "test";

        TUT_ENSURE_EQUAL(path2, "lib.misc.test");

    }}
}

