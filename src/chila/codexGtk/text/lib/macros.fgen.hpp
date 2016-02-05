#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codexGtk/text/lib/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codexGtk,text,lib)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codexGtk,text,lib)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef app_assert

#endif

