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

#ifndef CHILA_LIB_TUT__VISUALIZATOR_HPP
#define CHILA_LIB_TUT__VISUALIZATOR_HPP

#include <boost/filesystem/path.hpp>
#include <tut/tut.hpp>
#include <stdlib.h>
#include "util.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,tut))
{
    class Visualizator : public ::tut::callback
    {
        public:
            Visualizator() : testCount(0), testOk(0) {}

            void run_started() { }
            void run_completed() { }

            void test_completed(const ::tut::test_result& tr)
            {
                testCount++;
                std::cout << tr.group << "::" << tr.name << " : ";
                switch (tr.result)
                {
                    case ::tut::test_result::ok:
                        std::cout << "OK";
                        testOk++;
                        break;

                    case ::tut::test_result::fail:
                        std::cout << "FAIL: " << tr.message;
                        break;

                    case ::tut::test_result::ex:
                        std::cout << "Exception: " << tr.message;
                        break;

                    case ::tut::test_result::warn:
                        std::cout << "Exception in destructor: " << tr.message;
                        break;

                    case ::tut::test_result::ex_ctor:
                        std::cout << "Exception in constructor: " << tr.message;
                        break;

                    default:
                        abort();
                }

                if (tr.result != ::tut::test_result::ok)
                {
                    boost::filesystem::path filePath = checkPoint().file;
                    std::cout << " [" << filePath.filename() << ", "
                        << checkPoint().line << "]";
                }

                std::cout << std::endl;
            }

            unsigned count() const { return testCount; }
            unsigned ok() const { return testOk; }

            bool end()
            {
                std::cout << "OK (" << testOk << ")" << std::endl;
                return testCount == testOk;
            }

        private:
            unsigned testCount, testOk;
    };
}}}

#include <chila/lib/misc/macrosUndef.hpp>
#undef DEF_NAMESPACE

#endif
