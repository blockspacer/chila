#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert',  'CHILA_LIB_MISC__ASSERT'],
          ['app_assert', 'CHILA_LIB_MISC__APP_ASSERT'],
          ['add_to_event(module, event)', 'cclOther::addToConnFunction(module->getConnector().events.event,']]

clmUtil.generateMacrosDefUndef(macros)

