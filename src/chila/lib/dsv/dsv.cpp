/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "dsv.hpp"

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <chila/lib/misc/macrosExp.hpp>



#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE
#define SHOW            CHILA_LIB_MISC__//SHOW
#define CLM_ASSERT      CHILA_LIB_MISC__ASSERT

DEF_NAMESPACE(3, (chila,lib,dsv))
{

    template <>
    void load(std::istream &in, bool &data, char delim)
    {
        char c;
        CLM_ASSERT(nextField(&c, &c + 1, in, delim) - &c == 1);
        if (c == '0')
            data = false;
        else if (c == '1')
            data = true;
        else
            abort();
    }

    template <>
    void load(std::istream &in, unsigned &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }

    template <>
    void load(std::istream &in, unsigned long &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }

    template <>
    void load(std::istream &in, int &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);

        boost::iostreams::stream<boost::iostreams::array_source> str(buff, end - buff);
        str >> data;
    }


    template <>
    void load(std::istream &in, std::string &data, char delim)
    {
        char buff[1024];
        char *end = nextField(buff, buff + sizeof(buff), in, delim);
        data = std::string(buff, end - buff);
    }


}}}
