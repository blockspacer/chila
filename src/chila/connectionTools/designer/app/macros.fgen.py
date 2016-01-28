#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert', 'CHILA_LIB_MISC__ASSERT'],
          ['ipss',      'CHILA_LIB_MISC__IPSS'],
          ['ipss_end',  'CHILA_LIB_MISC__IPSS_END']]

clmUtil.generateMacrosDefUndef(macros)
