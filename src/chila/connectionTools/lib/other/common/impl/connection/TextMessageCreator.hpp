/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__TEXTMESSAGECREATOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER_COMMON_IMPL_CONNECTION__TEXTMESSAGECREATOR_HPP

#include "fwd.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/TextMessageCreator.hpp"
#include <chila/lib/misc/macrosExp.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_SPTR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct TextMessageCreator
    {
        struct ArgTypes
        {
            using message   = CharVectorSCPtr;
            using sessionId = unsigned;
            using msgId     = unsigned;
            using buffer    = Buffer;
            using errorMsg  = std::string;
        };

        DEF_CPROVIDER(TextMessageCreator);

        static CProviderUPtr create(const std::string &instanceName, MsgReadCriteriaEnum criteria, unsigned criteriaValue, unsigned bufferSize);
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_SPTR
#undef DEF_NAMESPACE

#endif
