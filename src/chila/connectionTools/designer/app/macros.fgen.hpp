#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/designer/app/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,designer,app)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,designer,app)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define ipss \
        CHILA_LIB_MISC__IPSS

    #define ipss_end \
        CHILA_LIB_MISC__IPSS_END

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef ipss
    #undef ipss_end

#endif

