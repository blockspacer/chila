/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FWD_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_IMPL__FWD_HPP

#include <vector>
#include <chila/lib/misc/RepeatText.hpp>
#include <memory>
#include <chila/lib/misc/Path.hpp>
#include "../../lib/actions.hpp"
#include <chila/connectionTools/lib/other/fwd.hpp>
#include <chila/lib/node/fwd.hpp>
#include "../fwd.hpp"
#include <memory>

#define FWDEC_SPTR CHILA_LIB_MISC__FWDEC_SPTR
#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace cclTree = chila::connectionTools::lib::tree;
    namespace cclOther = chila::connectionTools::lib::other;
    namespace clMisc = chila::lib::misc;
    namespace clNode = chila::lib::node;

    struct Indent
    {
        unsigned &showIndent;

        Indent(unsigned &showIndent) : showIndent(showIndent) { ++showIndent; }
        ~Indent() { --showIndent; }
    };

    using NodePathPair = std::pair<chila::lib::misc::Path, chila::lib::misc::Path>;

}
MY_NSP_END


#include "macros.fgen.hpp"
#endif
