#!/usr/bin/env python

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

nsp = 'CHILA_CODEX_BASE_APP_CONNECTORS_GEN'
connectionNsp = 'CHILA_CODEX_BASE_APP_IMPL_CONNECTION'

macros = clmUtil.nspMacrosFF(__file__) + \
         ccloUtil.getCToolsMacros(nsp) + \
         [['my_assert',                     'CHILA_LIB_MISC__ASSERT'],
          ['NSP',                           nsp],
          ['app_assert',                    'CHILA_LIB_MISC__APP_ASSERT'],
          ['FWDEC_SPTR',                    'CHILA_LIB_MISC__FWDEC_SPTR'],
          ['dec_my_cons_prov',              'PY_COM_PERSONAL_APPLICATION_LIB__DEC_CONS_PROV'],
          ['dec_custom_prov',               'PY_COM_PERSONAL_APPLICATION_LIB__DEC_CUSTOM_PROV'],
          ['module_args_ex',                  'CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(' + connectionNsp + ', MODULE_NAME)'],
          ['DEF_CPROVIDER(ConnectorName)',  'CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_CPROVIDER(connectors::gen::ConnectorName<ArgTypes>)'],
          ['my_get_connector(Type)',        'Type::CProvider::Connector']]

clmUtil.generateMacrosDefUndef(macros)
