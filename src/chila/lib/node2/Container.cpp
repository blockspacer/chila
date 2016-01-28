/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Container.hpp"
#include <chila/lib/misc/RepeatText.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{

    void Container::stream(std::ostream &out, unsigned indent) const
    {
        out << std::endl;
        for (const auto &it : itVec)
        {
            out << chila::lib::misc::repeatText(indent, " ") << "- " << it->first << ": ";
            it->second->stream(out, indent + 1);
            out << std::endl;
        }
    }
}
MY_NSP_END
