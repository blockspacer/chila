#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         ccloUtil.getCToolsMacros('CHILA_CONNECTIONTOOLS_COMMON_CONNECTORS_GEN') + \
         [['my_assert',       'CHILA_LIB_MISC__ASSERT'],
          ['ct_assert',       'CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT']]

clmUtil.generateMacrosDefUndef(macros)

