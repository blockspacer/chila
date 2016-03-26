/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FileChooser.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/util.hpp>
#include <boost/filesystem/path.hpp>
#include <chila/lib/qt/util.hpp>


#define MODULE_NAME FileChooser

#define lqt_connect_signal(name, cList, args)  \
        funRouterList.push_back(clMisc::toSharedPtr(CHILA_LIB_QT__CONNECT_SIGNAL(dlgObject, name, cList, args)

#include "macros.fgen.hpp"

MY_NSP_START
{
    FileChooser::FileChooser(module_args_ex) :
        connection::FileChooser::CProvider(instanceName),
        type(type),
        window(window)
    {
        connector.bindActions(*this);
    }


    void FileChooser::MOD_ACTION_SIG(launcher_start)
    {
        execute_event(launcher_started)();
    }

    void FileChooser::MOD_ACTION_SIG(open)
    {
        switch (type)
        {
            case Type::OPEN:
                dialog = clQt::invokeMethod(window, "showOpenDialog");
                break;

            case Type::SAVE:
                dialog = clQt::invokeMethod(window, "showSaveAsDialog");
                break;

            default:
                abort();
                break;
        }

        auto &dlgObject = clMisc::deref(dialog.value<QObject*>());

        lqt_connect_signal(accepted, (this)(&dlgObject)(eventExecuter), )
        {
            auto fileUrls = dlgObject.property("fileUrls").value<QList<QVariant>>();

            for (const auto &fileUrl : fileUrls)
            {
                auto url = fileUrl.value<QUrl>().path().toStdString();

                execute_event(fileChosen)(url);
            }
        })));
    }

    void FileChooser::MOD_ACTION_SIG(setFileName)
    {
//        objects.dialog->set_filename(fileName.string());
    }


    void FileChooser::MOD_ACTION_SIG(launcher_finish)
    {
        execute_event(launcher_finished)();
    }

    connection::FileChooser::CProviderUPtr connection::FileChooser::create(module_args_ex)
    {
        return std::make_unique<impl::FileChooser>(module_pass_args_ex);
    }
}
MY_NSP_END
