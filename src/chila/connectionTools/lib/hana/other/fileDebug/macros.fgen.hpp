#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/lib/hana/other/fileDebug/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,lib,hana,other,fileDebug)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,lib,hana,other,fileDebug)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert

#endif

