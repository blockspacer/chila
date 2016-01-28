/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#warning Not tested

#ifndef CHILA_LIB_MISC__PRINTER_HPP
#define CHILA_LIB_MISC__PRINTER_HPP

#include <limits>
#include <boost/foreach.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <vector>
#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    static const unsigned noTag = std::numeric_limits<int>::max();

    class Printer
    {
        public:
            std::ostream &out;

            virtual void startField(unsigned tag, const char *name) = 0;
            virtual void startElement(unsigned index)= 0;
            virtual void end() = 0;
            virtual void startValue() = 0;
            virtual void endValue() = 0;

        protected:
            Printer(std::ostream &out) : out(out) {}
    };

    template <typename Derived>
    class PrinterBase: public Printer
    {
        public:
            Derived &getDerived() { return static_cast<Derived&>(*this); }
            const Derived &getDerived() const { return static_cast<const Derived&>(*this); }

            void startField(unsigned tag, const char *name)
            {
                pushTag(tag);
                getDerived().startFieldImpl(name);
            }

            void startElement(unsigned index)
            {
                pushIndex(index);
                getDerived().startElementImpl();
            }

            void end()
            {
                pop();
            }

            void startValue() { getDerived().startValueImpl(); }
            void endValue() { getDerived().endValueImpl(); }

        protected:
            void pushTag(unsigned tag) { prefixes.push_back(tag); }
            void pushIndex(unsigned index) { prefixes.push_back(-int(index+1)); }
            void pop() { prefixes.pop_back(); }

            PrinterBase(std::ostream &out, unsigned iniPrefSize = 64) : Printer(out)
            {
                prefixes.reserve(iniPrefSize);
            }

            typedef std::vector<int> PrefixVec;
            PrefixVec prefixes;

            struct PrintPrefixVec final: public chila::lib::misc::SinkInserter<PrintPrefixVec>
            {
                const PrefixVec &prefixes;

                PrintPrefixVec(const PrefixVec &prefixes) : prefixes(prefixes) {}

                std::ostream &write(std::ostream &out) const
                {
                    bool first = true;

                    for (int value : prefixes)
                    {
                        if (value >= 0)
                        {
                            if (first)
                                first = false;
                            else
                                out << ".";

                            if (value == noTag)
                                out << "?";
                            else
                                out << value;
                        }
                        else
                        {
                            out << "{" << -(value+1) << "}";
                        }
                    }
                    return out;
                }
            };

            PrintPrefixVec printPrefixVec() const { return PrintPrefixVec(prefixes); }
    };

    class PrettyPrinter final: public PrinterBase<PrettyPrinter>
    {
        public:
            PrettyPrinter(std::ostream &out, unsigned iniPrefSize = 64) :
                PrinterBase<PrettyPrinter>(out, iniPrefSize), atStart(true) {}

            void newLine() { if (atStart == false) { out << "\n"; atStart = true; } }

            void startFieldImpl(const char *name)
            {
                newLine();
                out << "<" << printPrefixVec() << "> - " << name << ": ";
                atStart = false;
            }

            void startElementImpl()
            {
                newLine();
                out << "<" << printPrefixVec() << ">: ";
                atStart = false;
            }

            void startValueImpl() { out << "["; }
            void endValueImpl() { out << "]"; }

        private:
            bool atStart;
    };

    class LinePrinter final: public PrinterBase<LinePrinter>
    {
        public:
            LinePrinter(std::ostream &out, unsigned iniPrefSize = 64) :
                PrinterBase<LinePrinter>(out, iniPrefSize) {}

            void startFieldImpl(const char *name)   {}
            void startElementImpl()                 {}

            void startValueImpl()                   { out << "[<" << printPrefixVec() << ">("; }
            void endValueImpl()                     { out << ")]"; }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif
