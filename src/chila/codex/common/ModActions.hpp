/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_COMMON__MODACTIONS_HPP
#define CHILA_CODEX_COMMON__MODACTIONS_HPP

#include "fwd.hpp"
#include <QObject>
#include <QVariant>
#include <chila/lib/qt/SigConn.hpp>
#include <chila/lib/misc/util.hpp>
#include "util.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    class ModActions
    {
        public:
            using ActionExecutedFun = boost::function<void(clMisc::Path)>;

            ActionExecutedFun actionExecutedFun;

            ModActions(QObject &object) : object(object) {}

            void addAction(
                const ActionPathDataList &list,
                const std::string &name,
                const std::string &text,
                const std::string &tooltip,
                const std::string &shortcut = "");

            void addSeparator(const ActionPathDataList &list);

        private:
            using SigConnList = std::vector<clQt::SigConnUCPtr>;
            SigConnList sigConnList;

            QObject &object;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
