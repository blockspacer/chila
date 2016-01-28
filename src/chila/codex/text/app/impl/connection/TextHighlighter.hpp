/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TEXTHIGHLIGHTER_HPP
#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__TEXTHIGHLIGHTER_HPP

#include <chila/connectionTools/appTest2/fwd.hpp>
#include "fwd.hpp"

#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/TextHighlighter.hpp"
#include <chila/lib/misc/ValueStreamer.hpp>
#include <boost/asio/io_service.hpp>
#include "../fwd.hpp"
#include "../../../lib/fwd.hpp"

#include "macros.fgen.hpp"

#define MODULE_NAME TextHighlighter

#define CHILA_CODEX_TEXT_APP_IMPL_CONNECTION__MODULE_PARAMS_TextHighlighter \
    ((const std::string&)(instanceName)) \
    ((const lib::ColorMap&)(colorMap))

MY_NSP_START
{
    struct TextHighlighter
    {
        struct TextId : public virtual clMisc::ValueStreamer::Streamable
        {
            virtual bool operator<(const TextId &id) const { return this < &id; }
            virtual ~TextId() {}
        };

        CHILA_LIB_MISC__FWDEC_SPTR(TextId);

        struct ArgTypes
        {
            using fileId        = TextIdSCPtr;
            using tags          = TextTagSet;
            using tagsToApply   = TagApplyList;
            using textBuffer    = BufferRange;
            using errorMsg      = std::string;
            using parserId      = std::string;
        };

        DEF_CPROVIDER;

        static CProviderUPtr create(module_args_ex);
    };
}
MY_NSP_END

#undef MODULE_NAME
#include "macros.fgen.hpp"

#endif
