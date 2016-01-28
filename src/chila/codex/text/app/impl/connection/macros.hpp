/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/misc/macrosExp.hpp>

#ifndef MY_NSP
    #define MY_NSP chila,codex,text,app,impl,connection

    #define MY_NSP_START        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(MY_NSP)
    #define MY_NSP_END          CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(MY_NSP)

    #define my_assert           CHILA_LIB_MISC__ASSERT

    #define FWDEC_SPTR          CHILA_LIB_MISC__FWDEC_SPTR

    #define dec_my_cons_prov        PY_COM_PERSONAL_APPLICATION_LIB__DEC_CONS_PROV
    #define dec_custom_prov         PY_COM_PERSONAL_APPLICATION_LIB__DEC_CUSTOM_PROV
    #define my_get_connector(Type)  Type::Connector


#else
    #undef MY_NSP
    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef FWDEC_SPTR

    #undef dec_my_cons_prov
    #undef dec_custom_prov
    #undef my_get_connector

    #undef my_assert
#endif
