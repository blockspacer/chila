/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__SIGNALSLIGHT_HPP
#define CHILA_LIB_MISC__SIGNALSLIGHT_HPP

#include <boost/preprocessor.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/ref.hpp>
#include <vector>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Functor>
    class SignalsLight
    {
        private:
            typedef std::vector<Functor> FunctorContainer;
            FunctorContainer functions;

        public:
            typedef void result_type;

            SignalsLight &operator+=(const Functor &fun)
            {
                functions.push_back(fun);
                return *this;
            }

            void clear() { functions.clear(); }

            template <typename ...Args>
            void operator()(Args&&... args)
            {
                for (auto &fun : functions) fun(std::forward<Args>(args)...);
            }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
