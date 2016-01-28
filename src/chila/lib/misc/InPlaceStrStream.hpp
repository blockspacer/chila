/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__INPLACESTRSTREAM_HPP
#define CHILA_LIB_MISC__INPLACESTRSTREAM_HPP

#include <boost/utility.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#define CHILA_LIB_MISC__IPSS(size)              chila::lib::misc::InPlaceStrStream<size>()
#define CHILA_LIB_MISC__IPSS_END                chila::lib::misc::InPlaceStrStreamEnd()
#define CHILA_LIB_MISC__IPSS_EXP(size, exp)     \
    chila::lib::misc::InPlaceStrStream<size>() << BOOST_PP_TUPLE_ELEM(1, 0, exp) << chila::lib::misc::InPlaceStrStreamEnd()

#include "macros.fgen.hpp"

MY_NSP_START
{
    class InPlaceStrStreamEnd {};

    template <unsigned maxSize>
    class InPlaceStrStream final: public boost::noncopyable
    {
        private:
            char data[maxSize + 1];

        public:
            boost::iostreams::stream<boost::iostreams::array_sink> str;

            InPlaceStrStream() : str(data, maxSize)
            {
                data[0] = 0;
                str.exceptions(std::ios::badbit | std::ios::failbit);
            }

            template <typename Arg>
            InPlaceStrStream &operator<<(const Arg &arg)
            {
                str << arg;
                data[str.tellp()] = 0;
                return *this;
            }

            const char *get() const { return data; }

            InPlaceStrStream &operator<<( std::ios_base &(*manip)(std::ios_base&) )
            {
                (*manip)(str);
                return *this;
            }

            const char *operator<<(InPlaceStrStreamEnd) { return data; }

            unsigned size()
            {
                return str.tellp();
            }

            operator std::string() const { return get(); }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

