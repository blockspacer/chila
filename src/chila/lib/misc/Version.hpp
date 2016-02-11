#ifndef CHILA_LIB_MISC__VERSION_HPP
#define CHILA_LIB_MISC__VERSION_HPP

#include <ostream>


#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Version
    {
        unsigned may, min, maint;

        Version() : may(0), min(0), maint(0) {}
        Version(const std::string &version);
        Version(unsigned may, unsigned min, unsigned maint) :
                may(may), min(min), maint(maint) {}
    };

    inline std::ostream &operator<<(std::ostream &out, const Version &version)
    {
        return out << version.may << "." << version.min << "." << version.maint;
    }
}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
