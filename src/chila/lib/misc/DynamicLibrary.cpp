/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "DynamicLibrary.hpp"
#include <stdio.h>
#include <dlfcn.h>
#include "exceptions.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    /** Constructor. */
    DynamicLibrary::DynamicLibrary(const boost::filesystem::path &file) try :
        handle(checkCall(dlopen(file.string().c_str(), RTLD_NOW)))
    {
    }
    catch (const DynamicLibraryError &ex)
    {
        BOOST_THROW_EXCEPTION(DynamicLibraryOpenError(file, ex.what()));
    }

    /** Arroja una DynamicLibraryError si 'exp' es nulo. Si no retorna 'exp'. */
    void *DynamicLibrary::checkCall(void *exp)
    {
        if (exp)
            return exp;
        else
            BOOST_THROW_EXCEPTION(DynamicLibraryError(dlerror()));
    }

    /** Retorna el simbolo 'name'. */
    void *DynamicLibrary::getVoidSymbol(const char *name) try
    {
        return checkCall(dlsym(handle, name));
    }
    catch (const DynamicLibraryError &ex)
    {
        BOOST_THROW_EXCEPTION(DynamicLibrarySymbolError(name, ex.what()));
    }

    /** Destructor. */
    DynamicLibrary::~DynamicLibrary()
    {
        dlclose(handle);
    }
}
MY_NSP_END

