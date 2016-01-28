/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FILEOPENER_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__FILEOPENER_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "fwd.hpp"
#include <gtkmm.h>
#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/FileOpener.hpp"
#include <chila/lib/misc/ValueStreamer.hpp>
#include <boost/asio/io_service.hpp>
#include "../../../lib/fwd.hpp"
#include "../fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME FileOpener

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__MODULE_PARAMS_FileOpener \
    ((const std::string&)(instanceName)) \
    ((const lib::ExtensionFTypeMap&)(exFTypeMap)) \
    ((const CreateFileIdFun&)(createFileIdFun))

MY_NSP_START
{
    struct FileOpener
    {
        struct FileId : public virtual clMisc::ValueStreamer::Streamable
        {
            virtual bool operator<(const FileId &id) const { return this < &id; }
            virtual ~FileId() {}
        };

        struct TagId
        {
            virtual bool operator<(const TagId &id) const { return this < &id; }
            virtual ~TagId() {}
        };

        CHILA_LIB_MISC__FWDEC_SPTR(FileId);

        struct ArgTypes
        {
            using fileName = bfs::path;
            using fileType = std::string;
            using errorMsg = std::string;
            using fileId = FileIdSCPtr;
            using textBuffer = BufferRange;
        };

        DEF_CPROVIDER;

        using CreateFileIdFun = boost::function<FileIdSCPtr()>;

        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#undef MODULE_NAME
#include "macros.fgen.hpp"

#endif
