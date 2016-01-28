/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ModActions.hpp"
#include <boost/make_shared.hpp>
#include <QJsonObject>
#include <chila/lib/misc/Path.hpp>
#include <QJsonArray>
#include <chila/lib/qt/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    QJsonObject createJSAction(const std::string &name, const std::string &text, const std::string &tooltip, const std::string &shortcut)
    {
        return QJsonObject
        {
            { "name", name.c_str() },
            { "text", text.c_str() },
            { "tooltip", tooltip.c_str() },
            { "shortcut", shortcut.c_str() },
        };
    }

    QJsonObject createPItem(const std::string &name, const std::string &text)
    {
        return QJsonObject
        {
            { "name", name.c_str() },
            { "text", text.c_str() }
        };
    }

    void ModActions::addAction(
        const ActionPathDataList &list,
        const std::string &name,
        const std::string &text,
        const std::string &tooltip,
        const std::string &shortcut)
    {
        QVariant action;
        QJsonArray qPath;
        clMisc::Path aPath;

        for (const auto &elem : list)
        {
            qPath.append(createPItem(elem.name, elem.label));
            aPath.add(elem.name);
        }

        aPath.add(name);

        QMetaObject::invokeMethod(&object, "addAction",
            Q_RETURN_ARG(QVariant, action),
            Q_ARG(QVariant, qPath),
            Q_ARG(QVariant, createJSAction(name, text, tooltip, shortcut)));

        auto &actionObj = *action.value<QObject*>();

        auto router = clQt::connectSignal<0>(actionObj,  SIGNAL(triggered()), [this, aPath]
        {
            if (actionExecutedFun)
                actionExecutedFun(aPath);
        });

        sigConnList.push_back(rvalue_cast(router));
    }

    void ModActions::addSeparator(const ActionPathDataList &list)
    {
        QJsonArray qPath;

        for (const auto &elem : list)
        {
            qPath.append(createPItem(elem.name, elem.label));
        }

        QMetaObject::invokeMethod(&object, "addAction",
            Q_ARG(QVariant, qPath),
            Q_ARG(QVariant, QJsonObject()));
    }

}
MY_NSP_END
