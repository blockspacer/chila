#!/usr/bin/env python

# Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
# (C.I.: 1.439.390 - Paraguay)

import chila.lib.misc.util as clmUtil
import chila.connectionTools.lib.other.util as ccloUtil

print '#include <chila/lib/misc/macrosExp.hpp>\n'

connectionNsp = 'CHILA_CODEX_BASE_APP_IMPL_CONNECTION'

macros = clmUtil.nspMacrosFF(__file__) + \
         ccloUtil.getCToolsMacros('CHILA_CODEX_BASE_APP_CONNECTORS_GEN') + \
         [['my_assert',           'CHILA_LIB_MISC__ASSERT'],
          ['app_assert',          'CHILA_LIB_MISC__APP_ASSERT'],
          ['my_get_widget(name)', 'builder->get_widget(BOOST_PP_STRINGIZE(name), objects.name);\n' + \
                                  'my_assert(objects.name)'],
          ['my_get_object(Type, name)', 'objects.name = Glib::RefPtr<Gtk::Type>::cast_dynamic(builder->get_object(BOOST_PP_STRINGIZE(name)));\n' + \
                                  'my_assert(objects.name)'],
          ['module_args_ex',                  'CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_ARGS_EX(' + connectionNsp + ', MODULE_NAME)'],
          ['module_pass_args_ex',             'CHILA_CONNECTIONTOOLS_LIB_OTHER__MODULE_PASS_ARGS_EX(' + connectionNsp + ', MODULE_NAME)'],
          ['add_to_event(module, event)', 'cclOther::addToConnFunction(module->connector.events.event,']]


clmUtil.generateMacrosDefUndef(macros, [], ['MODULE_NAME'])

