#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

connectionNsp = 'CHILA_CODEX_TEXT_APP_IMPL_CONNECTION'

macros = clmUtil.nspMacrosFF(__file__) + \
           [['my_assert',                       'CHILA_LIB_MISC__ASSERT'],
            ['app_assert',                      'CHILA_LIB_MISC__APP_ASSERT'],
            ['FWDEC_SPTR',                      'CHILA_LIB_MISC__FWDEC_SPTR'],
            ['dec_my_cons_prov',                'PY_COM_PERSONAL_APPLICATION_LIB__DEC_CONS_PROV'],
            ['dec_custom_prov',                 'PY_COM_PERSONAL_APPLICATION_LIB__DEC_CUSTOM_PROV'],
            ['DEF_CPROVIDER',                   'CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_CPROVIDER(connectors::gen::MODULE_NAME<ArgTypes>)'],
            ['module_args_ex',                  'CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(' + connectionNsp + ', MODULE_NAME)'],
            ['my_get_connector(Type)',          'Type::CProvider::Connector']]

clmUtil.generateMacrosDefUndef(macros)
