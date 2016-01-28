#!/usr/bin/env python

import chila.codex.text.app.connectors.gen.ConnectionPerformer as codexCPerformer
import chila.connectionTools.lib.other.util as cToolsUtil
import chila.lib.misc.util as clmUtil

nsp = 'CHILA_CODEX_TEXT_APP_CONNECTORS_GEN'

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert',  'CHILA_LIB_MISC__ASSERT'],
          ['app_assert', 'CHILA_LIB_MISC__APP_ASSERT'],
          ['create_module_wa(name, ...)',   'CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_WA(CPModTypes, ' + nsp + ', name, __VA_ARGS__)'],
          ['create_module_na(name)',        'CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_NA(CPModTypes, ' + nsp + ', name)'],
          ['add_default_anyprinter_sptr_get(Type)', 'CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR_GET(valueStreamer, Type)'],
          ['app_assert', 'CHILA_LIB_MISC__APP_ASSERT'],
          ['set_post_function(object, type, function, queue, queueName)',
                'CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_POST_FUNCTION(providers, object, type, function, queue, queueName, valueStreamer)'],
          ['set_dff_post_functions(object, type, queueName, functions)',
                'CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS(providers, object, type, queueName, valueStreamer, functions)'],
          ['ADD_DFF_AND_POST(provsOwner)',
            cToolsUtil.addDFFToConnectorsAndPostDefEv(codexCPerformer.connInstanceSeq, 'provsOwner', 'valueStreamer', 'ioService', 'events')]]

clmUtil.generateMacrosDefUndef(macros)

