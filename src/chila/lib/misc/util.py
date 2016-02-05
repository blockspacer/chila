#!/usr/bin/env python

import sys
import os

def indent(n):
    ind = ''
    for i in range(0, n):
        ind += '    '

    return ind

def dBraces(text):
    return text.replace('{', '{{').replace('}', '}}')

def printMulti(text, prefix, suffix):
    first = True
    for line in text.split('\n'):
        if first:
            first = False
        else:
            print suffix

        if line == '':
            sys.stdout.write(line)
        else:
            sys.stdout.write(prefix + line)

    print


def generateMacrosDefUndef(macros, macrosDef = [], macrosUnd = []):
    if len(macros) == 0:
        return

    print '#ifndef ' + macros[0][0] + '\\\n'

    for name,value in macros:
        print '    #define ' + name + ' \\'
        printMulti(value, indent(2), ' \\')
        print

    print '#else\n'

    for name,value in macros:
        print '    #undef ' + name.split('(')[0]

    for name in macrosUnd:
        print '    #undef ' + name.split('(')[0]

    print '\n#endif\n'

    for name,value in macrosDef:
        print '#define ' + name + ' \\'
        printMulti(value, indent(1), ' \\')
        print


def nspMacros(nsp):
    return [['MY_NSP_START',      'CHILA_LIB_MISC__DEF_NAMESPACE_VAR(' + nsp + ')'],
            ['MY_NSP_END',        'CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(' + nsp + ')']]

def getNamespace(file):
    print '//' + file

    names = []
    started = False
    for name in file.split('/'):
        if name == 'chila' or name == 'py.com.personal' or name == "py_com_personal":
            started = True

        if started:
            if name == "py_com_personal":
                names.append('py.com.personal')
            else:
                names.append(name)

    names.pop()

    ret = ''
    for name in names:
        if len(ret):
            ret += '.'

        ret += name

    return ret

def nspMacrosFF(file):
    return nspMacros(getNamespace(file).replace('.', ','))

def addNspToMacros(nsp, macros):
    ret = []
    upNsp = nsp.replace('.', '_').upper()
    for name,value in macros:
        ret.append([upNsp + "__" + name, value])

    return ret;

def addNspToMacrosFF(file, macros):
    return addNspToMacros(getNamespace(file), macros)

def unstrMacroArg(arg):
    return '" + ' + arg + ' + "'
