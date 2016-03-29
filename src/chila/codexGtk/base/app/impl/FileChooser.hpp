/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_BASE_APP_IMPL__FILECHOOSER_HPP
#define CHILA_CODEX_BASE_APP_IMPL__FILECHOOSER_HPP

#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen

#include "connection/FileChooser.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <ctype.h>


#define MODULE_NAME FileChooser

#include "macros.fgen.hpp"

MY_NSP_START
{
    class FileChooser final: public connection::FileChooser::CProvider
    {
        public:
            using PostFun = connection::FileChooser::PostFun;
            using Type = connection::FileChooser::Type;

            FileChooser(module_args_ex);

            void MOD_ACTION_SIG(launcher_start);
            void MOD_ACTION_SIG(launcher_deactivate) { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish);

            void MOD_ACTION_SIG(open);
            void MOD_ACTION_SIG(setFileName);

       private:
            PostFun postFun;
            Type type;
            bfs::path lastFolder;

            using GtkFileChooserDialogUPtr = std::shared_ptr<Gtk::FileChooserDialog>;

            struct
            {
                GtkFileChooserDialogUPtr dialog;
                Gtk::Button *okButton;
                Gtk::Button *cancelButton;
            } objects;

    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

