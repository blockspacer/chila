#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/lib/hana/codegen/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,lib,hana,codegen)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,lib,hana,codegen)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define DEF_RUNTIME_ERROR \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR

    #define DEF_EXCEPTION \
        CHILA_LIB_MISC__DEF_EXCEPTION

    #define DEF_RUNTIME_ERROR_WT \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT

    #define DEF_RUNTIME_ERROR_FROM_BASE \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef DEF_RUNTIME_ERROR
    #undef DEF_EXCEPTION
    #undef DEF_RUNTIME_ERROR_WT
    #undef DEF_RUNTIME_ERROR_FROM_BASE

#endif

