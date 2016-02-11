#include "Version.hpp"
#include "util.hpp"
#include <boost/array.hpp>
#include <chila/lib/misc/exceptions.hpp>


#include "macros.fgen.hpp"

MY_NSP_START
{
    Version::Version(const std::string &version)
    {
        my_assert(!version.empty());

        boost::array<unsigned, 3> values;
        values.fill(0);
        parseNumbers(version, values);

        may = values[0];
        min = values[1];
        maint = values[2];
    }
}
MY_NSP_END
