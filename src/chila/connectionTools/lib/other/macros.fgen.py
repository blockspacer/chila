#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

nsp = clmUtil.getNamespace(__file__)

macros = clmUtil.nspMacros(nsp.replace('.', ',')) + \
         [['my_assert',         'CHILA_LIB_MISC__ASSERT'],
          ['ipss', 'CHILA_LIB_MISC__IPSS'],
          ['ipss_end', 'CHILA_LIB_MISC__IPSS_END'],
          ['LAUNCHER_ADD_TO_EVENT(Name, name)',
            'void addTo##Name##Event(const Function &action) override\n' + \
            '{\n' + \
            '    if (connector.events.launcher_##name)\n' + \
            '        connector.events.launcher_##name.passFunAndSet(chila::connectionTools::lib::other::funExecSequence(action));\n' + \
            '    else\n' + \
            '        connector.events.launcher_##name = action;\n' + \
            '}\n'],
          ['LAUNCHER_ADD_TO_EVENT_VIRTUAL(Name, name)', 'virtual void addTo##Name##Event(const Function &action) = 0;']]

#macrosDef = clmUtil.addNspToMacros(nsp,
#            [['SET_POST_FUNCTION(anyPrinter, object, type, function, queue, queueName)',
#               ccloUtil.setPostFunction(0, '', 'anyPrinter', 'object',
#                                        clmUtil.unstrMacroArg('chila::lib::misc::replace(#object, "_", ":")'), 'type', 'function', 'queue', 'queueName')]])

clmUtil.generateMacrosDefUndef(macros)
