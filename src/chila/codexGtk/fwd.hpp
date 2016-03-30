/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX__FWD_HPP
#define CHILA_CODEX__FWD_HPP

#include <chila/connectionTools/loader/fwd.hpp>
#include <chila/connectionTools/lib/other/fwd.hpp>
#include <chila/connectionTools/lib/other/common/impl/connection/fwd.hpp>
#include <chila/lib/misc/util.hpp>
#include <boost/filesystem/path.hpp>
#include <chila/lib/xmlppUtils/fwd.hpp>
#include <chila/lib/gtkmm/fwd.hpp>

#include <memory>
#include <memory>

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace ccLoader = chila::connectionTools::loader;
    namespace cclOther = chila::connectionTools::lib::other;
    namespace ccloCIConn = cclOther::common::impl::connection;
    namespace clMisc = chila::lib::misc;
    namespace bfs = boost::filesystem;
    namespace clGtkmm = chila::lib::gtkmm;
    namespace xmlppUtils = chila::lib::xmlppUtils;

    using clMisc::rvalue_cast;

    class CProvider
    {
    };

    CHILA_LIB_MISC__FWDEC_SPTR(CProvider);
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
