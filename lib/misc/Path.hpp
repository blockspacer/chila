/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA__LIB_MISC_PATH_HPP
#define	CHILA__LIB_MISC_PATH_HPP

#include "fwd.hpp"
#include <iostream>
#include "exceptions.hpp"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "macrosDef.hpp"

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{
    class Path
    {
        public:
            typedef std::vector<std::string> StringVec;

        private:
            StringVec names;

            void load(const std::string &path)
            {
                typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
                boost::char_separator<char> sep(".");
                Tokenizer tokens(path, sep);

                BOOST_FOREACH(const std::string &name, tokens)
                {
                    names.push_back(name);
                }
            }

        public:
            Path() {}
            Path(const char *path) { load(path); }
            Path(const std::string &path) { load(path); }

            const StringVec &getNames() const { return names; }

            Path &operator<<(const std::string &name)
            {
                names.push_back(name);
                return *this;
            }

            std::string pop()
            {
                if (names.empty())
                    throw chila::lib::misc::ElementNotFound();

                std::string ret = names.back();
                names.pop_back();
                return ret;
            }

            std::string top() const
            {
                if (names.empty())
                    throw chila::lib::misc::ElementNotFound();

                return names.back();
            }

            Path &operator=(const Path &rhs)
            {
                this->names = rhs.names;
            }

            std::string getStringRep(const std::string &delim = ".") const
            {
                std::string ret;
                bool first = true;
                BOOST_FOREACH(const std::string &name, names)
                {
                    if (first) first = false;
                    else ret += delim;
                    ret += name;
                }

                return ret;
            }

            bool operator<(const Path &rhs) const { return names < rhs.names; }
            bool operator==(const Path &rhs) const { return names == rhs.names; }
            bool operator!=(const Path &rhs) const { return names != rhs.names; }
    };

    inline Path operator+(Path lhs, const std::string &name)
    {
        return lhs << name;
    }

    inline std::ostream &operator<<(std::ostream &out, const Path &path)
    {
        return out << path.getStringRep();
    }

}}}

#undef DEF_NAMESPACE
#include "macrosUndef.hpp"
#endif

