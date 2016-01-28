/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__DYNAMICLIBRARY_HPP
#define CHILA_LIB_MISC__DYNAMICLIBRARY_HPP

#include <boost/utility.hpp>
#include <boost/filesystem/path.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class DynamicLibrary : boost::noncopyable
    {
        private:
            void *handle;
            void *checkCall(void *exp);
            void *getVoidSymbol(const char *name);

        public:
            DynamicLibrary(const boost::filesystem::path &file);
            ~DynamicLibrary();

            template <typename Type>
            Type *getSymbol(const char *name)
            {
                return reinterpret_cast<Type*>(getVoidSymbol(name));
            }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
