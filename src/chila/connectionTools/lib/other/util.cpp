#include "util.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <>
    chila::lib::misc::StringVec toString(const chila::lib::misc::StringSet &set)
    {
        std::string ret;

        bool first = true;
        for (const auto &text : set)
        {
            if (first) first = false;
            else ret += ", ";

            ret += text;
        }

        return { ret };
    }
}
MY_NSP_END

