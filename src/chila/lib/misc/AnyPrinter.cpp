/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "AnyPrinter.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    void AnyPrinter::stream(std::ostream &out, const boost::any &value) const
    {
        auto it = map.find(std::type_index(value.type()));

        if (it != map.end())
            it->second(out, value);
        else
            out << "<?>";
    }

}
MY_NSP_END

