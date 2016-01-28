#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/lib/qt/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,lib,qt)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,lib,qt)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define DEF_EXCEPTION \
        CHILA_LIB_MISC__DEF_EXCEPTION

    #define check_call_errno \
        CHILA_LIB_MISC__CHECK_CALL_ERRNO

    #define QT_BEGIN_MOC_NAMESPACE \
        MY_NSP_START {

    #define QT_END_MOC_NAMESPACE \
        } MY_NSP_END

    #define DEF_RUNTIME_ERROR \
        CHILA_LIB_MISC__DEF_RUNTIME_ERROR

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef DEF_EXCEPTION
    #undef check_call_errno
    #undef QT_BEGIN_MOC_NAMESPACE
    #undef QT_END_MOC_NAMESPACE
    #undef DEF_RUNTIME_ERROR

#endif

