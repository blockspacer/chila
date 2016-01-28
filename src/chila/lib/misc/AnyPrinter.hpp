/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__ANYPRINTER_HPP
#define CHILA_LIB_MISC__ANYPRINTER_HPP

#include "fwd.hpp"
#include "exceptions.hpp"
#include <map>
#include <boost/any.hpp>
#include <typeindex>
#include <chila/lib/misc/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    class AnyPrinter
    {
        public:
            using PrinterFun = std::function<void(std::ostream &out, const boost::any &value)>;

            void addFun(std::type_index index, PrinterFun fun)
            {
                my_assert(map.insert({rvalue_cast(index), rvalue_cast(fun)}).second);
            }

            template <typename Type>
            void addFun(PrinterFun fun)
            {
                addFun(std::type_index(typeid(Type)), rvalue_cast(fun));
            }

            template <typename Type, typename Printer>
            void add(const Printer &printer)
            {
                addFun<Type>([printer](std::ostream &out, const boost::any &value)
                {
                    printer(out, boost::any_cast<Type>(value));
                });
            }

            void stream(std::ostream &out, const boost::any &value) const;

        private:
            using Map = std::map<std::type_index, PrinterFun>;
            Map map;
    };

    template <typename Type, typename Printer>
    void addFunWR(AnyPrinter &anyPrinter, const Printer &printer)
    {
        anyPrinter.add<Type>([printer](std::ostream &out, const Type &val)
        {
            printer(out, val);
        });

        anyPrinter.add<boost::reference_wrapper<const Type>>([printer](std::ostream &out, const Type &val)
        {
            printer(out, boost::unwrap_ref(val));
        });
    }
}
MY_NSP_END

#include "macros.fgen.hpp"
#endif
