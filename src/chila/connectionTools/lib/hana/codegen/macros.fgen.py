#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert',                     'CHILA_LIB_MISC__ASSERT'],
          ['DEF_RUNTIME_ERROR',             'CHILA_LIB_MISC__DEF_RUNTIME_ERROR'],
          ['DEF_EXCEPTION',                 'CHILA_LIB_MISC__DEF_EXCEPTION'],
          ['DEF_RUNTIME_ERROR_WT',          'CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT'],
          ['DEF_RUNTIME_ERROR_FROM_BASE',   'CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE']]

clmUtil.generateMacrosDefUndef(macros)
