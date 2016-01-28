#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codexGtk/text/app/impl/connection/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codexGtk,text,app,impl,connection)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codexGtk,text,app,impl,connection)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define FWDEC_SPTR \
        CHILA_LIB_MISC__FWDEC_SPTR

    #define dec_my_cons_prov \
        PY_COM_PERSONAL_APPLICATION_LIB__DEC_CONS_PROV

    #define dec_custom_prov \
        PY_COM_PERSONAL_APPLICATION_LIB__DEC_CUSTOM_PROV

    #define DEF_CPROVIDER \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_CPROVIDER(connectors::gen::MODULE_NAME<ArgTypes>)

    #define module_args_ex \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(CHILA_CODEX_TEXT_APP_IMPL_CONNECTION, MODULE_NAME)

    #define my_get_connector(Type) \
        Type::CProvider::Connector

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef app_assert
    #undef FWDEC_SPTR
    #undef dec_my_cons_prov
    #undef dec_custom_prov
    #undef DEF_CPROVIDER
    #undef module_args_ex
    #undef my_get_connector

#endif

