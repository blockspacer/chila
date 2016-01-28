#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/translate/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,translate)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,translate)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define xml_iterate_children(root, name, child) \
        chila::lib::xmlppUtils::iterateChildren(root, name, [&](const xmlpp::Element &child)

    #define ct_apperror_element_nf(exp, msg) \
        CHILA_LIB_MISC__CATCHTHROW_APPERROR(chila::lib::misc::ElementNotFound, msg, exp)

    #define ct_apperror_element_nf_ref(exp, msg) \
        CHILA_LIB_MISC__CATCHTHROW_APPERROR_REF(chila::lib::misc::ElementNotFound, msg, exp)

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef xml_iterate_children
    #undef ct_apperror_element_nf
    #undef ct_apperror_element_nf_ref

#endif

