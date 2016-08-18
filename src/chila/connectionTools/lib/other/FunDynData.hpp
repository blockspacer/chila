#ifndef CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNDYNDATA_HPP
#define CHILA_CONNECTIONTOOLS_LIB_OTHER__FUNDYNDATA_HPP

#include <map>
#include <vector>
#include <boost/any.hpp>

#include "macrosExp.hpp"
#include <chila/lib/misc/macrosExp.hpp>

#define FWDEC_STPR      CHILA_LIB_MISC__FWDEC_SPTR

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct FunDynData
    {
        struct ArgData
        {
            std::string name;
            boost::any value;

            ArgData(std::string name, boost::any value) :
                name(rvalue_cast(name)), value(rvalue_cast(value)) {}
        };

        using ArgVec = std::vector<ArgData>;

        ArgVec argVec;

        std::string name;

        FunDynData(std::string name) : name(rvalue_cast(name)) {}

        void push(std::string name, boost::any value)
        {
            argVec.push_back({rvalue_cast(name), rvalue_cast(value)});
        }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"
#undef FWDEC_STPR
#endif
