/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_DSV__DSV_HPP
#define CHILA_LIB_DSV__DSV_HPP

#include <boost/foreach.hpp>
#include <vector>
#include <iterator>
#include <iostream>
#include <boost/optional.hpp>
#include <boost/mpl/assert.hpp>
#include <chila/lib/misc/String.hpp>
#include <chila/lib/misc/exceptions.hpp>


#include <chila/lib/misc/macrosExp.hpp>
#include <py.com.personal/lib/misc/defMacros.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE
#define SHOW            CHILA_LIB_MISC__SHOW
#define CLM_ASSERT      CHILA_LIB_MISC__ASSERT

DEF_NAMESPACE(3, (chila,lib,dsv))
{
    // ---------------------------------------------------------------------------------------------------------------
    template <typename ForwardIterator>
    ForwardIterator nextField(ForwardIterator it, ForwardIterator end, std::istream &in, char delim = ',')
    {
        CLM_ASSERT(in.good());

        bool escaped = false;
        while(true)
        {
            char c = in.get();

            if (!in.good())
            {
                CLM_ASSERT(!escaped);
                return it;
            }

            if (c == '\\' && !escaped)
            {
                CLM_ASSERT(it != end);
                escaped = true;
            }
            else
            {
                if (c == delim && !escaped)
                    return it;

                CLM_ASSERT(it != end);
                *it = c;
                it++;
                escaped = false;
            }
        }

        return it;
    }

    template <typename InputIterator>
    void writeEscaped(std::ostream &out, InputIterator begin, InputIterator end, char delim = ',')
    {
        for (; begin != end; ++begin)
        {
            char c = *begin;
            if (c == delim || c == '\\')
                out.put('\\');

            out.put(c);
        }
    }

    inline void writeField(std::ostream &out, const char *buff, unsigned size, char delim)
    {
        writeEscaped(out, buff, buff + size, delim);
    }

    inline void writeField(std::ostream &out, unsigned data, char delim)
    {
        out << data;
    }

    inline void writeField(std::ostream &out, unsigned long data, char delim)
    {
        out << data;
    }

    inline void writeField(std::ostream &out, int data, char delim)
    {
        out << data;
    }

    // ---------------------------------------------------------------------------------------------------------------
    template <typename Type>
    void save(std::ostream &out, const Type &data, char delim = ',')
    {
        BOOST_MPL_ASSERT_MSG(false, invalid_function_call, (Type));
    }

    template <unsigned size>
    inline void save(std::ostream &out, const chila::lib::misc::String<size> &data, char delim)
    {
        writeEscaped(out, data.begin(), data.end(), delim);
    }

    template<>
    inline void save(std::ostream &out, const bool &data, char delim)
    {
        writeField(out, data ? 1 : 0, delim);
    }

    template<>
    inline void save(std::ostream &out, const std::string &data, char delim)
    {
        writeField(out, data.c_str(), data.size(), delim);
    }

    template<>
    inline void save(std::ostream &out, const unsigned &data, char delim)
    {
        writeField(out, data, delim);
    }

    template<>
    inline void save(std::ostream &out, const unsigned long &data, char delim)
    {
        writeField(out, data, delim);
    }

    template<>
    inline void save(std::ostream &out, const int &data, char delim)
    {
        writeField(out, data, delim);
    }


    template <typename Type>
    void save(std::ostream &out, const boost::optional<Type> &data, char delim = ',')
    {
        if (data)
        {
            save(out, true, delim);
            out << delim;
            save(out, *data, delim);
        }
        else
        {
            save(out, false, delim);
        }
    }

    template <typename Type>
    void save(std::ostream &out, const std::vector<Type> &data, char delim = ',')
    {
        out << data.size();

        for (const auto &elem : data)
        {
            out << delim;
            save(out, elem, delim);
        }
    }

    template <unsigned size>
    struct StringPutter
    {
        chila::lib::misc::String<size> *str;

        struct Putter
        {
            StringPutter<size> &pstr;
            Putter(StringPutter<size> &pstr) : pstr(pstr) {}
            void operator=(char c)
            {
                pstr.str->put(c);
                if (pstr.str->full())
                    pstr.str = NULL;
            }
        };


        StringPutter() : str(NULL) {}
        StringPutter(chila::lib::misc::String<size> &str) : str(&str) {}
        StringPutter(const StringPutter<size> &rhs) : str(rhs.str) {}

        void operator++(int) const
        {
        }

        Putter operator*()
        {
            CLM_ASSERT(str);
            return Putter(*this);
        }
    };

    template <unsigned size>
    inline bool operator==(const StringPutter<size> &lhs, const StringPutter<size> &rhs)
    {
        return lhs.str == rhs.str;
    }

    template <unsigned size>
    inline bool operator!=(const StringPutter<size> &lhs, const StringPutter<size> &rhs)
    {
        return lhs.str != rhs.str;
    }

    // ---------------------------------------------------------------------------------------------------------------
    template <typename Type>
    void load(std::istream &in, Type &data, char delim = ',')
    {
        BOOST_MPL_ASSERT_MSG(false, invalid_function_call, (Type));
    }

    template <unsigned size>
    void load(std::istream &in, chila::lib::misc::String<size> &data, char delim)
    {
        StringPutter<size> start(data), end;

        nextField(start, end, in, delim);
    }

    template <>
    void load(std::istream &in, bool &data, char delim);

    template <>
    void load(std::istream &in, std::string &data, char delim);

    template <>
    void load(std::istream &in, unsigned &data, char delim);

    template <>
    void load(std::istream &in, unsigned long &data, char delim);

    template <>
    void load(std::istream &in, int &data, char delim);

    template <typename Type>
    void load(std::istream &in, std::vector<Type> &data, char delim = ',')
    {
        unsigned size;
        load(in, size, delim);

        //SHOW(size);


        for (unsigned i = 0; i < size; ++i)
        {
            data.push_back(Type());
            load(in, data.back(), delim);
        }
    }

    template <typename Type>
    void load(std::istream &in, boost::optional<Type> &data, char delim = ',')
    {
        bool exists;
        load(in, exists, delim);
        if (exists)
        {
            data = Type();
            load(in, *data, delim);
        }
    }
}}}

#undef CLM_ASSERT
#undef SHOW
#undef DEF_NAMESPACE
#endif
