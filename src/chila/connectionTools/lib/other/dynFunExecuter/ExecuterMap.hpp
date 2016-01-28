/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__EXECUTERMAP_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_DYNFUNEXECUTER__EXECUTERMAP_HPP

#include "fwd.hpp"
#include <map>
#include "ExecuterFun.hpp"
#include <boost/function.hpp>
#include <chila/lib/misc/Path.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class ExecuterMap
    {
        public:
            using ArgumentStrMap = std::map<std::string, std::string>;

            template <typename FunMData>
            void addFunction(const chila::lib::misc::Path &path, const FunMData &fun)
            {
                my_assert(funMap.insert({path, dfExecuterFun(fun)}).second);
            }

            void execute(const chila::lib::misc::Path &path, const ArgumentStrMap &arguments) const;

        private:
            using ExecuterFun = boost::function<void(const ArgumentStrMap &arguments)>;
            using FunMap = std::map<chila::lib::misc::Path, ExecuterFun>;
            FunMap funMap;
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

