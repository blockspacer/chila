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

#ifndef CHILA_LIB_MISC__SIMPLEPRINTER_HPP
#define	CHILA_LIB_MISC__SIMPLEPRINTER_HPP

#include <iostream>
#include <boost/utility.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "SinkInserter.hpp"
#include <boost/ref.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,lib,misc))
{
    template <typename _Sink>
    class SimplePrinter
    {
        public:
            typedef _Sink Sink;
            typedef typename boost::unwrap_reference<Sink>::type UnwrappedSink;

            SimplePrinter(Sink p_out) : out(p_out), indent(0) {}

            SimplePrinter &operator++() { ++indent; return *this; }
            SimplePrinter &operator--() { --indent; return *this; }

            UnwrappedSink &get() { return boost::unwrap_ref(out); }

            SimplePrinter &printIndent()
            {
                if (!indent) return *this;
                UnwrappedSink &output = get();

                for (unsigned i = 0; i < indent; ++i) output << "  ";

                return *this;
            }

        private:
            Sink out;
            unsigned indent;
    };

    template <typename Sink>
    inline SimplePrinter<Sink> printer(const Sink &sink)
    {
        return SimplePrinter<Sink>(sink);
    }

    template <typename Sink>
    struct IndentGuard
    {
        SimplePrinter<Sink> &printer;
        IndentGuard(SimplePrinter<Sink> &printer) : printer(++printer) {}
        ~IndentGuard() { --printer; }
    };

    struct PrintIndent : public SinkInserter<PrintIndent>
    {
        template <typename Sink>
        void write(Sink &printer) const
        {
            printer.printIndent();
        }
    };

    static PrintIndent indent;

    template <typename Sink, typename Derived>
    inline SimplePrinter<Sink> &operator<<(SimplePrinter<Sink> &out, const SinkInserter<Derived> &inserter)
    {
        inserter(out);
        return out;
    }

    template <typename Sink>
    SimplePrinter<Sink> &operator<<(SimplePrinter<Sink> &out, const std::string &object)
    {
        out.get() << object;
        return out;
    }

    template <typename Sink>
    SimplePrinter<Sink> &operator<<(SimplePrinter<Sink> &out, const char *object)
    {
        out.get() << object;
        return out;
    }



}}}

#include <chila/lib/misc/macrosUndef.hpp>
#undef DEF_NAMESPACE

#endif
