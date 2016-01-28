/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__FWD_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__FWD_HPP


#include <map>
#include <boost/any.hpp>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/misc/fwd.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    CHILA_LIB_MISC__FWDEC_TYPE(ActionElement);
    CHILA_LIB_MISC__FWDEC_TYPE(Action);
    CHILA_LIB_MISC__FWDEC_TYPE(ActionWithValue);
    CHILA_LIB_MISC__FWDEC_TYPE(ActionWithPos);
    CHILA_LIB_MISC__FWDEC_TYPE(ActionMap);
    CHILA_LIB_MISC__FWDEC_TYPE(AddPosibilities);
    CHILA_LIB_MISC__FWDEC_TYPE(TextProperty);

    using TextProperties = std::vector<TextPropertySCPtr>;
    CHILA_LIB_MISC__FWDEC_SPTR(TextProperties);


    struct ActionElement
    {
        ActionMap *parent;
        std::string id;

        ActionElement(std::string id = "", ActionMap *parent = nullptr) : id(rvalue_cast(id)), parent(parent) {}
        virtual ~ActionElement() {}
    };

    enum class AddType
    {
        NONE,
        SIMPLE,
        WITH_POS,
        WITH_VAL
    };


}
MY_NSP_END

#undef FWDEC_SPTR

#include "macros.fgen.hpp"


#endif
