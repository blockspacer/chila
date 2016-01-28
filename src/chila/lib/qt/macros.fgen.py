#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert',         'CHILA_LIB_MISC__ASSERT'],
          ['DEF_EXCEPTION',     'CHILA_LIB_MISC__DEF_EXCEPTION'],
          ['check_call_errno',  'CHILA_LIB_MISC__CHECK_CALL_ERRNO'],
          ['QT_BEGIN_MOC_NAMESPACE', 'MY_NSP_START {'],
          ['QT_END_MOC_NAMESPACE',   '} MY_NSP_END'],
          ['DEF_RUNTIME_ERROR', 'CHILA_LIB_MISC__DEF_RUNTIME_ERROR']]


clmUtil.generateMacrosDefUndef(macros)

