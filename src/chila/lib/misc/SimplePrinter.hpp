/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__SIMPLEPRINTER_HPP
#define CHILA_LIB_MISC__SIMPLEPRINTER_HPP

#include <iostream>
#include <boost/utility.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "SinkInserter.hpp"
#include <boost/ref.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
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

    struct PrintIndent final: public SinkInserter<PrintIndent>
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



}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
