#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert', 'CHILA_LIB_MISC__ASSERT'],
          ['xml_iterate_children(root, name, child)',
                'chila::lib::xmlppUtils::iterateChildren(root, name, [&](const xmlpp::Element &child)'],
          ['ct_apperror_element_nf(exp, msg)',     'CHILA_LIB_MISC__CATCHTHROW_APPERROR(chila::lib::misc::ElementNotFound, msg, exp)'],
          ['ct_apperror_element_nf_ref(exp, msg)', 'CHILA_LIB_MISC__CATCHTHROW_APPERROR_REF(chila::lib::misc::ElementNotFound, msg, exp)']]

clmUtil.generateMacrosDefUndef(macros)
