#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/lib/misc/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,misc)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,lib,misc)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define DEF_EXCEPTION \
        CHILA_LIB_MISC__DEF_EXCEPTION

    #define check_call_errno \
        CHILA_LIB_MISC__CHECK_CALL_ERRNO

    #define DEF_RUNTIME_ERROR_WT \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT

    #define DEF_RUNTIME_ERROR \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef DEF_EXCEPTION
    #undef check_call_errno
    #undef DEF_RUNTIME_ERROR_WT
    #undef DEF_RUNTIME_ERROR

#endif

