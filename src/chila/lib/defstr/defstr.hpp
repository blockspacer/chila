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

#ifndef CHILA_LIB_DEFSTR__DEFSTR_HPP
#define CHILA_LIB_DEFSTR__DEFSTR_HPP

#include <boost/foreach.hpp>
#include <chila/lib/misc/printer.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <boost/optional.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
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

    template <typename Printer, typename Object>
    struct Print : chila::lib::misc::SinkInserter<Print<Printer, Object>>
    {
        const Object &object;

        Print(const Object &object) :
            object(object) {}

        void write(std::ostream &out) const
        {
            Printer printer(out);
            print(printer, object);
        }
    };

    template <typename Object>
    inline Print<chila::lib::misc::LinePrinter, Object> linePrint(const Object &object)
    {
        return Print<chila::lib::misc::LinePrinter, Object>(object);
    }

    template <typename Object>
    inline Print<chila::lib::misc::PrettyPrinter, Object> prettyPrint(const Object &object)
    {
        return Print<chila::lib::misc::PrettyPrinter, Object>(object);
    }

}}}

#undef libMisc
#undef DEF_NAMESPACE
#endif

