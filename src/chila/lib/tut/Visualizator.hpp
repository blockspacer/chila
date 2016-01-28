/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_TUT__VISUALIZATOR_HPP
#define CHILA_LIB_TUT__VISUALIZATOR_HPP

#include <boost/filesystem/path.hpp>
#include <tut/tut.hpp>
#include <stdlib.h>
#include "util.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    class Visualizator final: public ::tut::callback
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
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
