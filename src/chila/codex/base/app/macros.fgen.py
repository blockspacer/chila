#!/usr/bin/env python

# Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import chila.codex.base.app.connectors.gen.ConnectionPerformer as codexCPerformer
import chila.connectionTools.lib.other.util as cToolsUtil
import chila.lib.misc.util as clmUtil

nsp = 'CHILA_CODEX_BASE_APP_CONNECTORS_GEN'

print '#include <chila/lib/misc/macrosExp.hpp>\n'

macros = clmUtil.nspMacrosFF(__file__) + \
         [['my_assert',  'CHILA_LIB_MISC__ASSERT'],
          ['app_assert', 'CHILA_LIB_MISC__APP_ASSERT'],
          ['add_default_anyprinter(Type)',      'CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER(valueStreamer, Type)'],
          ['add_default_anyprinter_sptr(Type)', 'CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR(valueStreamer, Type)'],
          ['add_default_anyprinter_sptr_get(Type)', 'CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR_GET(valueStreamer, Type)'],
          ['ADD_DFF_AND_POST(provsOwner)',
                cToolsUtil.addDFFToConnectorsAndPostDefEv(codexCPerformer.connInstanceSeq, 'provsOwner', 'valueStreamer', 'ioService', 'events')],
          ['create_module_wa(name, ...)',   'CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_WA(CPModTypes, ' + nsp + ', name, __VA_ARGS__)'],
          ['create_module_na(name)',        'CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_NA(CPModTypes, ' + nsp + ', name)'],
          ['set_dff_post_functions(object, type, queueName, functions)',
                'CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS(providers, object, type, queueName, valueStreamer, functions)'],
          ['postfun_and_dff(module, funType, fun)',     'CHILA_CONNECTIONTOOLS_LIB_OTHER__POSTFUN_AND_DFF(providers, module, funType, \
                                                            fun, debugLogFile, ioService, valueStreamer, showArguments)'],

          ['add_to_event(module, event)', 'cclOther::addToConnFunction(module->connector.events.event,']]

clmUtil.generateMacrosDefUndef(macros)


