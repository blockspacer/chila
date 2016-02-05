#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/lib/misc/fusion/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,misc,fusion)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,lib,misc,fusion)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define DEF_EXCEPTION \
        CHILA_LIB_MISC__DEF_EXCEPTION

    #define DEF_RUNTIME_ERROR \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef DEF_EXCEPTION
    #undef DEF_RUNTIME_ERROR

#endif

