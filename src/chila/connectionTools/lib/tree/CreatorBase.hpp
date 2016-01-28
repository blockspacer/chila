/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__CREATORBASE_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__CREATORBASE_HPP

#include "fwd.hpp"
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <chila/lib/xmlppUtils/util.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    class CreatorBase
    {
        protected:
            boost::filesystem::path file;
            Namespace &nspBase;

        public:
            CreatorBase(Namespace &nspBase, const boost::filesystem::path &file) :
                file(file), nspBase(nspBase) {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif


