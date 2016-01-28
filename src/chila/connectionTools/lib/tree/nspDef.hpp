/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/misc/macrosExp.hpp>

#define MY_NSP chila,connectionTools,lib,tree

#define MY_NSP_START      CHILA_LIB_MISC__DEF_NAMESPACE_VAR(MY_NSP)
#define MY_NSP_END    CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(MY_NSP)

#define my_assert CHILA_LIB_MISC__ASSERT

#define ipss     CHILA_LIB_MISC__IPSS
#define ipss_end CHILA_LIB_MISC__IPSS_END
#define ipss_exp CHILA_LIB_MISC__IPSS_EXP

#define my_ipss_exp(...) ipss_exp(32768, (__VA_ARGS__))

#define add_element_wf(root, name, childName) \
    xmlppUtils::addElementWithFormat(root, name, indent, [&](xmlpp::Element &childName, unsigned indent)

#define ADD_CONST_IF(Type)  CHILA_LIB_MISC__ADD_CONST_IF_TN(Type, boost::is_const<InType>::value)

