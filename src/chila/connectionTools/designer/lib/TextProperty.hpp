/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_LIB__TEXTPROPERTY_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_LIB__TEXTPROPERTY_HPP

#include "fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    struct TextProperty
    {
        virtual ~TextProperty() {}
    };

    namespace textProperty
    {
        struct NodePath : public TextProperty
        {
            clMisc::Path path;
            NodePath(clMisc::Path path) : path(rvalue_cast(path)) {}
        };

        struct Color : public TextProperty
        {
            float red, green, blue;
            Color(float red, float green, float blue) : red(red), green(green), blue(blue) {}
        };

        struct Bold : public TextProperty {};
        struct Italic : public TextProperty {};
        struct Underline : public TextProperty {};
    }
}
MY_NSP_END

#undef def_action_base
#undef def_action
#include "macros.fgen.hpp"


#endif
