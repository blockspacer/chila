#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codexGtk/base/lib/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codexGtk,base,lib)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codexGtk,base,lib)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define add_to_event(module, event) \
        cclOther::addToConnFunction(module->getConnector().events.event,

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef app_assert
    #undef add_to_event

#endif

