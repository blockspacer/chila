#ifndef CHILA_LIB_QT__SIGCONN_FGEN_HPP
#define CHILA_LIB_QT__SIGCONN_FGEN_HPP

#include <iostream>
#include <chila/lib/misc/util.hpp>
#include "fwd.hpp"

#include <QObject>
#include <QVariant>
#include <QQmlProperty>

#undef QT_BEGIN_MOC_NAMESPACE
#undef QT_END_MOC_NAMESPACE

#include "macros.fgen.hpp"

MY_NSP_START
{
    using misc::rvalue_cast;


    // Args: 0 ---------------------------------------------------------------------------
    class SigConn0 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(0, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn0(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(0, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn0(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(0, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(0, arg));
            }
    };

    template <> struct TSigConn<0> { using type = SigConn0; };

    // Args: 1 ---------------------------------------------------------------------------
    class SigConn1 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(1, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn1(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(1, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn1(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(1, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(1, arg));
            }
    };

    template <> struct TSigConn<1> { using type = SigConn1; };

    // Args: 2 ---------------------------------------------------------------------------
    class SigConn2 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(2, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn2(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(2, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn2(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(2, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(2, arg));
            }
    };

    template <> struct TSigConn<2> { using type = SigConn2; };

    // Args: 3 ---------------------------------------------------------------------------
    class SigConn3 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(3, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn3(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(3, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn3(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(3, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(3, arg));
            }
    };

    template <> struct TSigConn<3> { using type = SigConn3; };

    // Args: 4 ---------------------------------------------------------------------------
    class SigConn4 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(4, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn4(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(4, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn4(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(4, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(4, arg));
            }
    };

    template <> struct TSigConn<4> { using type = SigConn4; };

    // Args: 5 ---------------------------------------------------------------------------
    class SigConn5 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(5, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn5(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(5, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn5(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(5, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(5, arg));
            }
    };

    template <> struct TSigConn<5> { using type = SigConn5; };

    // Args: 6 ---------------------------------------------------------------------------
    class SigConn6 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(6, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn6(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(6, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn6(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(6, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(6, arg));
            }
    };

    template <> struct TSigConn<6> { using type = SigConn6; };

    // Args: 7 ---------------------------------------------------------------------------
    class SigConn7 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(7, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn7(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(7, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn7(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(7, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(7, arg));
            }
    };

    template <> struct TSigConn<7> { using type = SigConn7; };

    // Args: 8 ---------------------------------------------------------------------------
    class SigConn8 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(8, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn8(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(8, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn8(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(8, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(8, arg));
            }
    };

    template <> struct TSigConn<8> { using type = SigConn8; };

    // Args: 9 ---------------------------------------------------------------------------
    class SigConn9 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(9, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn9(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(9, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn9(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(9, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(9, arg));
            }
    };

    template <> struct TSigConn<9> { using type = SigConn9; };

    // Args: 10 ---------------------------------------------------------------------------
    class SigConn10 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(10, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn10(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(10, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn10(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(10, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(10, arg));
            }
    };

    template <> struct TSigConn<10> { using type = SigConn10; };

    // Args: 11 ---------------------------------------------------------------------------
    class SigConn11 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(11, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn11(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(11, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn11(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(11, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(11, arg));
            }
    };

    template <> struct TSigConn<11> { using type = SigConn11; };

    // Args: 12 ---------------------------------------------------------------------------
    class SigConn12 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(12, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn12(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(12, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn12(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(12, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(12, arg));
            }
    };

    template <> struct TSigConn<12> { using type = SigConn12; };

    // Args: 13 ---------------------------------------------------------------------------
    class SigConn13 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(13, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn13(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(13, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn13(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(13, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(13, arg));
            }
    };

    template <> struct TSigConn<13> { using type = SigConn13; };

    // Args: 14 ---------------------------------------------------------------------------
    class SigConn14 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(14, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn14(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(14, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn14(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(14, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(14, arg));
            }
    };

    template <> struct TSigConn<14> { using type = SigConn14; };

    // Args: 15 ---------------------------------------------------------------------------
    class SigConn15 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(15, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn15(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(15, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn15(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(15, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13, const QVariant &arg14
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(15, arg));
            }
    };

    template <> struct TSigConn<15> { using type = SigConn15; };

    // Args: 16 ---------------------------------------------------------------------------
    class SigConn16 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(16, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn16(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(16, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn16(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(16, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13, const QVariant &arg14, 
                const QVariant &arg15
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(16, arg));
            }
    };

    template <> struct TSigConn<16> { using type = SigConn16; };

    // Args: 17 ---------------------------------------------------------------------------
    class SigConn17 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(17, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn17(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(17, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn17(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(17, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13, const QVariant &arg14, 
                const QVariant &arg15, const QVariant &arg16
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(17, arg));
            }
    };

    template <> struct TSigConn<17> { using type = SigConn17; };

    // Args: 18 ---------------------------------------------------------------------------
    class SigConn18 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(18, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn18(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(18, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn18(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(18, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13, const QVariant &arg14, 
                const QVariant &arg15, const QVariant &arg16, const QVariant &arg17
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(18, arg));
            }
    };

    template <> struct TSigConn<18> { using type = SigConn18; };

    // Args: 19 ---------------------------------------------------------------------------
    class SigConn19 : public QObject, public SigConn
    {
        Q_OBJECT

        public:
            using Fun = std::function<void(BOOST_PP_ENUM_PARAMS(19, const QVariant &arg))>;

            Fun fun;
            QMetaObject::Connection connection; 
            QQmlProperty property; 

            SigConn19(QQmlProperty property, Fun fun = Fun()) :
                property(rvalue_cast(property)),
                fun(rvalue_cast(fun))
            {
                my_assert(property.connectNotifySignal(this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(19, CHILA_LIB_MISC__TEXTREP, QVariant)))));
            }

            SigConn19(QObject &object, const char *signal, Fun fun = Fun()) : 
                fun(rvalue_cast(fun)), 
                connection(QObject::connect(&object, signal, this, CHILA_LIB_QT__SLOT(
                    slot(BOOST_PP_REPEAT(19, CHILA_LIB_MISC__TEXTREP, QVariant))))) {} 

        public slots:
            void slot
            (
                const QVariant &arg0, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4, 
                const QVariant &arg5, const QVariant &arg6, const QVariant &arg7, const QVariant &arg8, const QVariant &arg9, 
                const QVariant &arg10, const QVariant &arg11, const QVariant &arg12, const QVariant &arg13, const QVariant &arg14, 
                const QVariant &arg15, const QVariant &arg16, const QVariant &arg17, const QVariant &arg18
            ) const
            {
                if (enabled) fun(BOOST_PP_ENUM_PARAMS(19, arg));
            }
    };

    template <> struct TSigConn<19> { using type = SigConn19; };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif

