#!/usr/bin/env python

import chila.lib.misc.util as clmUtil

def genIndent(indent):
    ret = ""
    for i in range(0, indent):
        ret += "    "
    return ret

def repeatText(text, argCount, cutCount, indent, addIndex):
    ret = "\n" + genIndent(indent) + "(";
    for i in range(0, argCount):
        ret += (", " if i else "") + \
               (("\n" + genIndent(indent + 1)) if i % cutCount == 0 else "") + \
                text + (`i` if addIndex else "");

    return ret + "\n" + genIndent(indent) + ")"

def genClass(argCount):
    print \
        "    // Args: " + `i` + " ---------------------------------------------------------------------------\n" + \
        "    class SigConn" + `argCount` + " : public QObject, public SigConn\n" + \
        "    {\n" + \
        "        Q_OBJECT\n" + \
        "\n" + \
        "        public:\n" + \
        "            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(" + `argCount` + ", const QVariant &arg))>;\n" + \
        "\n" + \
        "            Fun fun;\n" + \
        "            QMetaObject::Connection connection;\n" + \
        "            QQmlProperty property;\n" + \
        "\n" + \
        "            SigConn" + `argCount` + "(QQmlProperty property, Fun fun = Fun()) :\n" + \
        "                property(rvalue_cast(property)),\n" + \
        "                fun(rvalue_cast(fun))\n" + \
        "            {\n" + \
        "                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(\n" + \
        "                    slot(BOOST_PP_REPEAT(" + `argCount` + ", CHILA_LIB_MISC__TEXTREP, QVariant)))));\n" + \
        "            }\n" + \
        "\n" + \
        "            SigConn" + `argCount` + "(QObject &object, const char *signal, Fun fun = Fun()) :\n" + \
        "                fun(rvalue_cast(fun)),\n" + \
        "                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(\n" + \
        "                    slot(BOOST_PP_REPEAT(" + `argCount` + ", CHILA_LIB_MISC__TEXTREP, QVariant))))) {}\n" + \
        "\n" + \
        "        public slots:\n" + \
        "            void slot" + repeatText("const QVariant &arg", argCount, 5, 3, True) + " const\n" + \
        "            {\n" + \
        "                if (enabled) fun(BOOST_PP_ENUM_PARAMS(" + `argCount` + ", arg));\n" + \
        "            }\n" + \
        "    };\n" + \
        "\n" + \
        "    template <> struct TSigConn<" + `argCount` + "> { using type = SigConn" + `argCount` + "; };\n"

print \
    "#ifndef CHILA_LIB_QT__SIGCONN_FGEN_HPP\n" + \
    "#define CHILA_LIB_QT__SIGCONN_FGEN_HPP\n" + \
    "\n" + \
    "#include <iostream>\n" + \
    "#include <chila/lib/misc/util.hpp>\n" + \
    "#include \"fwd.hpp\"\n" + \
    "\n" + \
    "#include <QObject>\n" + \
    "#include <QVariant>\n" + \
    "#include <QQmlProperty>\n" + \
    "\n" + \
    "#undef QT_BEGIN_MOC_NAMESPACE\n" + \
    "#undef QT_END_MOC_NAMESPACE\n" + \
    "\n" + \
    "#include \"macros.fgen.hpp\"\n" + \
    "\n" + \
    "MY_NSP_START\n" + \
    "{\n" + \
    "    using misc::rvalue_cast;\n" + \
    "\n"

for i in range(0, 20):
    genClass(i)

print \
    "}\n" + \
    "MY_NSP_END\n" + \
    "\n" + \
    "#include \"macros.fgen.hpp\"\n" + \
    "\n" + \
    "#endif\n"
