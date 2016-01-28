/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_DEFSTR__DEFSTR_HPP
#define CHILA_LIB_DEFSTR__DEFSTR_HPP

#include <boost/foreach.hpp>
#include <chila/lib/misc/printer.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <boost/optional.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE
#define libMisc         py::com::personal::lib::misc

DEF_NAMESPACE(3, (chila,lib,defstr))
{

    template <typename Type>
    inline void print(chila::lib::misc::Printer &printer, const Type &data)
    {
        printer.startValue();
        printer.out << data;
        printer.endValue();
    }


    template <typename Type>
    void print(chila::lib::misc::Printer &printer, const std::vector<Type> &data)
    {
        unsigned i = 0;
        for (const auto &elem : data)
        {
            printer.startElement(i++);
            print(printer, elem);
            printer.end();
        }
    }


    template <typename Type>
    inline void printField(chila::lib::misc::Printer &printer, unsigned tag, const char *name, const Type &data)
    {
        printer.startField(tag, name);
        print(printer, data);
        printer.end();
    }

    template <typename Type>
    void printField(chila::lib::misc::Printer &printer, unsigned tag, const char *name, const boost::optional<Type> &data)
    {
        if (data)
            printField(printer, tag, name, *data);
    }






}}}

#undef libMisc
#undef DEF_NAMESPACE
#endif

