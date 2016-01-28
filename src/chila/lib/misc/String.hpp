/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__STRING_HPP
#define CHILA_LIB_MISC__STRING_HPP

#include <cassert>
#include <stdexcept>
#include <iosfwd>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <unsigned _maxSize>
    class String
    {
        public:
            static const unsigned maxSize = _maxSize;

        private:
            char data[maxSize + 1];
            unsigned _size;

            void copy(const char *source)
            {
                char *dest = data;
                for (_size = 0; *source; ++_size, ++source, ++dest)
                {
                    if (_size >= maxSize) throw std::invalid_argument("source");

                    *dest = *source;
                }

                *dest = 0;
            }

        public:
            String() : _size(0)
            {
                data[0] = 0;
            }

            String(const char *text)
            {
                copy(text);
            }

            String(const std::string &text)
            {
                copy(text.c_str());
            }

            String &operator=(const char *text)
            {
                copy(text);
                return *this;
            }

            const char *begin() const { return data; }
            const char *end() const { return data + _size; }

            char *prepare(unsigned size)
            {
                if (size > maxSize) throw std::invalid_argument("size");
                _size = size;
                data[_size] = 0;
                return data;
            }

            unsigned size() const { return _size; }
            bool empty() const { return data; }

            bool operator==(const char *text) const
            {
                for (const char *cur = begin();; ++cur, ++text)
                {
                    char c = *text;

                    if (*cur != c) return false;

                    if (!c) return cur == end();
                    if (cur == end()) return !c;
                }
            }

            bool operator!=(const char *text) const
            {
                for (const char *cur = begin();; ++cur, ++text)
                {
                    char c = *text;

                    if (*cur == c) return false;

                    if (!c) return cur != end();
                    if (cur == end()) return c;
                }
            }

            template <unsigned rhsSize>
            bool operator==(const String<rhsSize> &rhs) const
            {
                return *this == rhs.begin();
            }

            template <typename ForwardIterator>
            void assign(ForwardIterator first, ForwardIterator last)
            {
                for (this->_size = 0; first != last; ++this->_size, first++)
                {
                    if (this->_size > maxSize)
                        throw std::invalid_argument("first, last");

                    data[this->_size] = *first;
                }

                data[this->_size] = 0;
            }

            inline bool full() const { return _size == _maxSize; }

            void put(char c)
            {
                if (_size == maxSize)
                    throw std::invalid_argument("c");

                data[_size] = c;
                data[++_size] = 0;
            }
    };

    template <unsigned maxSize>
    inline std::ostream &operator<<(std::ostream &out, const String<maxSize> &str)
    {
        return out << str.begin();
    }

    template <unsigned maxSize>
    inline bool operator==(const String<maxSize> &str, const std::string &text)
    {
        return text == str.begin();
    }

    template <unsigned maxSize>
    inline bool operator!=(const String<maxSize> &str, const std::string &text)
    {
        return text != str.begin();
    }

    template <unsigned maxSize>
    inline bool operator==(const std::string &text, const String<maxSize> &str)
    {
        return text == str.begin();
    }

    template <unsigned maxSize>
    inline bool operator!=(const std::string &text, const String<maxSize> &str)
    {
        return text != str.begin();
    }
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
