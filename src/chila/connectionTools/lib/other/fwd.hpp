/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <map>

#define FWDEC_TYPE  CHILA_LIB_MISC__FWDEC_TYPE

#include "macros.fgen.hpp"

MY_NSP_START
{
    FWDEC_TYPE(CompletionScanner);
    FWDEC_TYPE(Launcher);
    FWDEC_TYPE(DataMap);

    enum class ModuleState
    {
        NONE,
        STARTING,
        STARTED,
        DEACTIVATING,
        DEACTIVATED,
        FINISHING,
        FINISHED
    };

    typedef std::pair<std::string, chila::lib::misc::StringVec> Parameter;
    typedef std::vector<Parameter> ParameterList;
    using ArgumentStrMap = std::map<std::string, std::string>;

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef FWDEC_TYPE
#endif
