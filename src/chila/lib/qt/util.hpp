/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_QT__UTIL_HPP
#define CHILA_LIB_QT__UTIL_HPP

#include "fwd.hpp"
#include "SigConn.hpp"
#include <QVariant>
#include <boost/make_unique.hpp>

#include "macros.fgen.hpp"

#define _CHILA_LIB_QT__QVAR_ARG(r, data, elem) const QVariant &elem

#define CHILA_LIB_QT__CONNECT_SIGNAL(object, name, cList, args) \
    chila::lib::qt::connectSignal<BOOST_PP_SEQ_SIZE(args)>(object, \
        CHILA_LIB_QT__SIGNAL(name(BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(args), CHILA_LIB_MISC__TEXTREP, QVariant))), \
            [BOOST_PP_SEQ_ENUM(cList)](BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_QT__QVAR_ARG,, args))

MY_NSP_START
{
    template <unsigned argCount>
    inline std::unique_ptr<typename TSigConn<argCount>::type>
        connectSignal(QObject &object, const char *signal, typename TSigConn<argCount>::type::Fun fun = {})
    {
        return boost::make_unique<typename TSigConn<argCount>::type>(object, signal, rvalue_cast(fun));
    }

    template <unsigned argCount>
    inline std::unique_ptr<typename TSigConn<argCount>::type>
        connectSignal(QQmlProperty property, typename TSigConn<argCount>::type::Fun fun = {})
    {
        return boost::make_unique<typename TSigConn<argCount>::type>(rvalue_cast(property), rvalue_cast(fun));
    }

    template <typename Type>
    struct QTArg
    {
        using type = Type;
        static const Type &get(const Type &data) { return data; }
    };

    template <>
    struct QTArg<const std::string&>
    {
        using type = QString;
        static QString get(const std::string &data) { return QString(data.c_str()); }
    };

    template <>
    struct QTArg<QObject&>
    {
        using type = QVariant;
        static QVariant get(QObject &data) { return QVariant::fromValue(&data); }
    };


    template <typename Type>
    inline typename QTArg<Type>::type getQTArg(Type &&data)
    {
        return QTArg<Type>::get(std::forward<Type>(data));
    }

    template <typename ...Args>
    inline QVariant invokeMethod(QObject &object, const std::string &name, Args&& ...args)
    {
        QVariant ret;
        QMetaObject::invokeMethod(&object, name.c_str(),
            Q_RETURN_ARG(QVariant, ret),
            QArgument<QVariant>{"QVariant", getQTArg(std::forward<Args>(args))}...);

        return ret;
    }

    struct textInd
    {
        unsigned indent;
        textInd(unsigned indent) : indent(indent) {}

        void operator()(std::ostream &out) const
        {
            for (unsigned i = 0; i < indent; ++i)
                out << " ";
        }
    };

    inline std::ostream &operator<<(std::ostream &out, const textInd &ti)
    {
        ti(out);
        return out;
    }

    void showChildren(const QObject &object, unsigned indent = 0);
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
