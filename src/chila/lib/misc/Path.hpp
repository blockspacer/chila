/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.lib'
 *
 * 'chila.lib' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.lib' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.lib'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_LIB_MISC__PATH_HPP
#define CHILA_LIB_MISC__PATH_HPP

#include "fwd.hpp"
#include <iostream>
#include "exceptions.hpp"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <chila/lib/misc/util.hpp>
#include "macrosExp.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    class Path
    {
        public:
            typedef std::vector<std::string> StringVec;

        private:
            StringVec names;

            void load(const std::string &path, const std::string &sep);

        public:
            using iterator = StringVec::iterator;
            using const_iterator = StringVec::const_iterator;

            Path() {}
            Path(const_iterator begin, const_iterator end) : names(begin, end) {}

            Path(const char *path, const std::string &sep = ".") { load(path, sep); }
            Path(const std::string &path, const std::string &sep = ".") { load(path, sep); }
            Path(const Path &rhs) = default;
            Path(Path &&rhs) = default;

            const StringVec &getNames() const { return names; }

            iterator begin() { return names.begin(); }
            iterator end() { return names.end(); }

            const_iterator begin() const { return names.begin(); }
            const_iterator end() const   { return names.end(); }

            const_iterator cbegin() const { return names.begin(); }
            const_iterator cend() const   { return names.end(); }

            const std::string &front() const { return *cbegin(); }
            const std::string &back() const { return *(cend() - 1); }

            Path &reverse();

            Path &add(const std::string &name)
            {
                if (!name.empty())
                    names.push_back(name);

                return *this;
            }

            std::string pop();

            std::string top() const;

            Path parent() const
            {
                Path ret = *this;

                if (!ret.empty())
                    ret.pop();

                return ret;
            }

            Path &operator=(const Path &rhs);

            std::string getStringRep(const std::string &delim = ".") const;

            Path relative(const Path &to) const;

            Path commonParent(const Path &to) const;

            bool operator<(const Path &rhs) const { return names < rhs.names; }
            bool operator==(const Path &rhs) const { return names == rhs.names; }
            bool operator!=(const Path &rhs) const { return names != rhs.names; }

            Path &operator+=(const Path &rhs);

            bool empty() const { return names.empty(); }

            operator bool() const { return !empty(); }

            bool startsWith(const Path &rhs) const;

            std::size_t size() const { return names.size(); }

            void clear() { names.clear(); }
    };

    inline Path operator+(Path lhs, const char *name)
    {
        return rvalue_cast(lhs.add(name));
    }

    inline Path operator+(Path lhs, const std::string &name)
    {
        return rvalue_cast(lhs.add(name));
    }

    inline Path operator+(Path lhs, Path rhs)
    {
        return rvalue_cast(lhs += rhs);
    }

    inline std::ostream &operator<<(std::ostream &out, const Path &path)
    {
        return out << path.getStringRep();
    }

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

