#include "ExecuterMap.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    void ExecuterMap::execute(const chila::lib::misc::Path &path, const ArgumentStrMap &arguments) const
    {
        auto it = funMap.find(path);
        my_assert(it != funMap.end());

        it->second(arguments);
    }

}
MY_NSP_END

