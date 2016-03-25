#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) 

clmUtil.generateMacrosDefUndef(macros)

