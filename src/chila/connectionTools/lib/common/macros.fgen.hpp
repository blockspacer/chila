#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/lib/common/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,lib,common)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,lib,common)

#else

    #undef MY_NSP_START
    #undef MY_NSP_END

#endif

