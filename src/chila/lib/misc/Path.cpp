/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Path.hpp"
#include <boost/range/algorithm/reverse.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    void Path::load(const std::string &path, const std::string &sep)
    {
        typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
        boost::char_separator<char> csep(sep.c_str());
        Tokenizer tokens(path, csep);

        for (const auto &name : tokens)
        {
            names.push_back(name);
        }
    }

    std::string Path::pop()
    {
        if (names.empty())
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        std::string ret = names.back();
        names.pop_back();
        return ret;
    }

    std::string Path::top() const
    {
        if (names.empty())
            BOOST_THROW_EXCEPTION(chila::lib::misc::ElementNotFound());

        return names.back();
    }

    Path &Path::operator=(const Path &rhs)
    {
        this->names = rhs.names;
        return *this;
    }

    std::string Path::getStringRep(const std::string &delim) const
    {
        std::string ret;
        bool first = true;
        for (const auto &name : names)
        {
            if (first) first = false;
            else ret += delim;
            ret += name;
        }

        return ret;
    }

    Path &Path::operator+=(const Path &rhs)
    {
        for (const auto &name : rhs.names)
        {
            names.push_back(name);
        }

        return *this;
    }

    Path &Path::reverse()
    {
        boost::reverse(names);
        return *this;
    }

    Path Path::relative(const Path &to) const
    {
        Path ret;

        auto it = begin(), toIt = to.begin();
        for (; it != names.end() && toIt != to.end() && *it == *toIt;
               ++it, ++toIt);

        for (; it != end(); ++it)
            ret += *it;

        return ret;
    }

    bool Path::startsWith(const Path &rhs) const
    {
        auto lIt = begin(), rIt = rhs.begin();

        for (; lIt != end() && rIt != rhs.end() && *lIt == *rIt; ++lIt, ++rIt);

        return rIt == rhs.end();
    }

}
MY_NSP_END

