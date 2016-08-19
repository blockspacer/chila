#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

def getVarName(conn):
    return conn.replace('.', '_')

def getGroupedName(conn):
    return conn.replace('.', ':')

def addDFF(indent, valueStreamer, provsOwner, object, objectName, type, function, msg):
    ind = clmUtil.indent(indent)
    fun = provsOwner + '.' + getVarName(object) + '->connector.{type}##s.{function}'.format(**locals())

    return(\
        '{ind}{fun}.passFunAndSet\n'
        '{ind}(\n'
        '{ind}    chila::connectionTools::lib::other::DebugFileFunPFS<decltype({fun})>\n'
        '{ind}    (\n'
        '{ind}        *debugLogFile, valueStreamer, "{objectName}", "{type}", showArguments, {msg}\n'
        '{ind}    )\n'
        '{ind});\n'
        ).format(**locals())

def setPostFunction(indent, valueStreamer, provsOwner, object, objectName, type, function, queue, queueName):
    ind = clmUtil.indent(indent)

    return (
        '{ind}' + provsOwner + '.' + getVarName(object) + '->connector.{type}##s.{function}.passFunAndSet(chila::lib::misc::SetPostFun({queue}));\n'
        '{ind}if (debugLogFile)\n'
        '{ind}{{\n'
                  + addDFF(indent + 1, valueStreamer, provsOwner, object, objectName, type, function, '"posted in \'{queueName}\'"') +
        '{ind}}}\n'
        ).format(**locals())


def addDebugFFToConnector(indent, valueStreamer, provsOwner, object, objectName):
    ind = clmUtil.indent(indent)
    return (\
        '{ind}if (debugLogFile)\n'
        '{ind}{{\n'
        '{ind}    chila::connectionTools::lib::other::addDebugFileFunToFunctions(\n'
        '{ind}        *debugLogFile, valueStreamer, "{objectName}", "action",\n'
        '{ind}        ' + provsOwner + '.' + getVarName(object) + '->connector.actions.list(), showArguments);\n'
        '{ind}    chila::connectionTools::lib::other::addDebugFileFunToFunctions(\n'
        '{ind}        *debugLogFile, valueStreamer, "{objectName}", "event",\n'
        '{ind}        ' + provsOwner + '.' + getVarName(object) + '->connector.events.list(), showArguments);\n'
        '{ind}}}\n').format(**locals())

def postInitFinishFunsToConnector(indent, valueStreamer, provsOwner, object, objectName, queue, queueName):
    ind = clmUtil.indent(indent)
    return setPostFunction(indent, valueStreamer, provsOwner, object, objectName, 'action', 'launcher_start', queue, queueName) + \
           setPostFunction(indent, valueStreamer, provsOwner, object, objectName, 'action', 'launcher_deactivate', queue, queueName) + \
           setPostFunction(indent, valueStreamer, provsOwner, object, objectName, 'action', 'launcher_finish', queue, queueName)

def getCToolsMacros(genNsp):
    return [['execute_event',                                       'CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT'],
            ['execute_event_tn',                                    'CHILA_CONNECTIONTOOLS_LIB_OTHER__EXECUTE_EVENT_TN'],
            ['call_ev_fatal',                                       'CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL'],
            ['call_ev_fatal_tn',                                    'CHILA_CONNECTIONTOOLS_LIB_OTHER__CALL_EV_FATAL_TN'],
            ['ct_assert',                                           'CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT'],
            ['ct_assert_tn',                                        'CHILA_CONNECTIONTOOLS_LIB_OTHER__ASSERT_TN'],
            ['ev_executer_arg',                                     'CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_ARG'],
            ['ev_executer_type',                                    'CHILA_CONNECTIONTOOLS_LIB_OTHER__EV_EXECUTER_TYPE'],
            ['catch_inv_state_tf',                                  'CHILA_CONNECTIONTOOLS_LIB_OTHER__CATCH_INV_STATE_TF'],
            ['check_state(...)',                                    'catch_inv_state_tf( checkState({__VA_ARGS__},           __func__, __FILE__, __LINE__) )'],
            ['check_state_lm(mutex, ...)',                          'catch_inv_state_tf( checkStateLM(mutex, {__VA_ARGS__},  __func__, __FILE__, __LINE__) )'],
            ['set_state(state)',                                    'catch_inv_state_tf( setState(state,                     __func__, __FILE__, __LINE__) )'],
            ['set_state_lm(mutex, state)',                          'catch_inv_state_tf( setState(mutex, state,              __func__, __FILE__, __LINE__) )'],
            ['MOD_ACTION_SIG(action)',                              'CHILA_CONNECTIONTOOLS_LIB_OTHER__CONNECTOR_ACTION_SIG(' + genNsp + ', MODULE_NAME, action)'],
            ['APROV_DEF_PROVIDER_BASE_FOR(prov)',                   'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR(' + genNsp + ', prov)'],
            ['APROV_DEF_PROVIDER_BASE_FOR_WC(prov, customArgs)',    'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_PROVIDER_BASE_FOR_WC(' + genNsp + ', prov, customArgs)'],
            ['APROV_CONS_PARAMS_FOR(prov)',                         'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_CONS_PARAMS_FOR(' + genNsp + ', prov)'],
            ['APROV_PASS_REQ_PARAMS_FOR(prov)',                     'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_PASS_REQ_PARAMS_FOR(' + genNsp + ', prov)'],
            ['APROV_DEF_CREATOR_WITH_ARGS(prov, argSeq)',           'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_DEF_CREATOR_WITH_ARGS(' + genNsp + ', prov, argSeq)'],
            ['APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(prov)',            'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROV_COMMA_IF_HAS_CONS_PARAMS_FOR(' + genNsp + ', prov)'],
            ['APROVIDER_DEC',                                               'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC'],
            ['DEF_APC_ENCAPSULATOR_CR(creatorName, readerName, EncType)',   'CHILA_CONNECTIONTOOLS_LIB_OTHER__DEF_APC_ENCAPSULATOR_CR(' + genNsp + ', creatorName, readerName, EncType)'],
            ['APROVIDER_DEC_EX(prov, customArgs)',                          'CHILA_CONNECTIONTOOLS_LIB_OTHER__APROVIDER_DEC_EX(' + genNsp + ', prov, customArgs)']]

def addDFFToConnectorsAndPostDefEv(connInstanceSeq, provsOwner, valueStreamer, queue, queueName):
    ret = ''

    for Type,conn in connInstanceSeq:
        ret += addDebugFFToConnector(1, valueStreamer, provsOwner, conn, getGroupedName(conn)) + \
               postInitFinishFunsToConnector(1, valueStreamer, provsOwner, conn, getGroupedName(conn), queue, queueName)

    return ret
