/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FileChooser.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <chila/lib/gtkmm/util.hpp>
#include <chila/lib/misc/util.hpp>
#include <sigc++-2.0/sigc++/connection.h>
#include <boost/filesystem/path.hpp>


#define MODULE_NAME FileChooser

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace clGtkmm = chila::lib::gtkmm;

    FileChooser::FileChooser(module_args_ex) :
        connection::FileChooser::CProvider(instanceName),
        type(type),
        postFun(postFun)
    {
        connector.bindActions(*this);

        switch (type)
        {
            case Type::OPEN:
                objects.dialog = boost::make_unique<Gtk::FileChooserDialog>("Open", Gtk::FILE_CHOOSER_ACTION_OPEN);
                objects.dialog->set_select_multiple(true);
                break;

            case Type::SAVE:
                objects.dialog = boost::make_unique<Gtk::FileChooserDialog>("Save as", Gtk::FILE_CHOOSER_ACTION_SAVE);
                objects.dialog->set_do_overwrite_confirmation(true);
                break;

            default:
                abort();
                break;
        }

        objects.dialog->set_create_folders(true);
        objects.dialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
        objects.dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    }


    void FileChooser::MOD_ACTION_SIG(launcher_start)
    {
        execute_event(launcher_started)();
    }

    void FileChooser::MOD_ACTION_SIG(open)
    {
        objects.dialog->signal_response().connect_notify([this, eventExecuter](int response)
        {
            postFun("objects.dialog->signal_response()", [this, eventExecuter, response]
            {
                lastFolder = objects.dialog->get_current_folder();
                objects.dialog->hide();

                if (response == Gtk::RESPONSE_OK)
                {
                    for (auto fileName : objects.dialog->get_filenames())
                    {
                        execute_event(fileChosen)(fileName);
                    }
                }
            });
        });

        if (!lastFolder.empty())
            objects.dialog->set_current_folder(lastFolder.string());

        objects.dialog->show_all();
    }

    void FileChooser::MOD_ACTION_SIG(setFileName)
    {
        objects.dialog->set_filename(fileName.string());
    }


    void FileChooser::MOD_ACTION_SIG(launcher_finish)
    {
        execute_event(launcher_finished)();
    }

    connection::FileChooser::CProviderUPtr connection::FileChooser::create(module_args_ex)
    {
        return boost::make_unique<impl::FileChooser>(module_pass_args_ex);
    }
}
MY_NSP_END
