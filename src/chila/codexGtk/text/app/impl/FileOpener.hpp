/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL__FILEOPENER_HPP
#define CHILA_CODEX_TEXT_APP_IMPL__FILEOPENER_HPP

#include "connection/FileOpener.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <boost/make_shared.hpp>
#include <gtkmm.h>
#include <boost/bind.hpp>
#include <ctype.h>


#define MODULE_NAME FileOpener

#include "macros.fgen.hpp"

MY_NSP_START
{
    using Iterator = const char*;

    class FileOpener final: public connection::FileOpener::CProvider
    {
        public:
            using CreateFileIdFun = connection::FileOpener::CreateFileIdFun;

            FileOpener(module_args_ex);

            void MOD_ACTION_SIG(launcher_start)         { execute_event(launcher_started)(); }
            void MOD_ACTION_SIG(launcher_deactivate)    { execute_event(launcher_deactivated)(); }
            void MOD_ACTION_SIG(launcher_finish)        { execute_event(launcher_finished)(); }
            void MOD_ACTION_SIG(openFile);
            void MOD_ACTION_SIG(fileClosed);
            void MOD_ACTION_SIG(saveFile_current);
            void MOD_ACTION_SIG(saveFile_as);
            void MOD_ACTION_SIG(fileSelected);

       private:
            using FileId = connection::FileOpener::FileId;
            using BufferRange = connection::BufferRange;
            using FileIdSCPtr = connection::FileOpener::FileIdSCPtr;
            using FileIdMap = std::map<bfs::path, FileIdSCPtr>;
            using FileIterMap = std::map<connection::FileOpener::FileIdSCPtr, FileIdMap::iterator>;

            CreateFileIdFun createFileIdFun;
            FileIdMap fileIdMap;
            FileIterMap fileIterMap;
            lib::ExtensionFTypeMap exFTypeMap;

            void saveFile(const bfs::path &fileName, const BufferRange &textBuffer);
            std::string getFileType(const bfs::path &fileName) const;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif

