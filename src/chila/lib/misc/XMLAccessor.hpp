/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__XMLACCESSOR_HPP
#define CHILA_LIB_MISC__XMLACCESSOR_HPP

#include "fwd.hpp"
#include "exceptions.hpp"
#include <boost/lexical_cast.hpp>
#include <libxml++/libxml++.h>
#include <type_traits>
#include <boost/utility.hpp>

#include "macros.fgen.hpp"

#define disable_if_bool \
    typename boost::disable_if<typename std::is_same<Type, bool>::type, Type>::type

#define enable_if_bool \
    typename boost::enable_if<typename std::is_same<Type, bool>::type, Type>::type

MY_NSP_START
{
    class XMLAccessor
    {
        public:
            const xmlpp::Element &element;

            XMLAccessor(const xmlpp::Element &element) : element(element) {}

            const xmlpp::Element &getElement(const std::string &path) const;
            const xmlpp::Attribute &getAttribute(const std::string &path) const;

            template <typename Type>
            disable_if_bool getValue(const std::string &path) const;

            template <typename Type>
            enable_if_bool getValue(const std::string &path) const;

            template <typename Type>
            Type getValue(const std::string &path, const Type &defVal) const try
            {
                return getValue<Type>(path);
            }
            catch (const XMLElementNotFound &ex)
            {
                return defVal;
            }

            std::string getValue(const std::string &path, const char *defVal) const try
            {
                return getValue<std::string>(path);
            }
            catch (const XMLElementNotFound &ex)
            {
                return defVal;
            }

        private:
            const xmlpp::Node &getNode(const std::string &path) const;
    };

    template <typename Type>
    inline disable_if_bool XMLAccessor::getValue(const std::string &path) const try
    {
        return boost::lexical_cast<Type>(getAttribute(path).get_value());
    }
    catch (const std::bad_cast &ex)
    {
        BOOST_THROW_EXCEPTION(InvalidXMLAttribute() << ExceptionInfo::XPath(path));
    }

    template <typename Type>
    inline enable_if_bool XMLAccessor::getValue(const std::string &path) const
    {
        auto val = getAttribute(path).get_value();
        if (val == "true")
            return true;
        else if (val == "false")
            return false;
        else
            BOOST_THROW_EXCEPTION(InvalidXMLAttribute() << ExceptionInfo::XPath(path));
    }

}
MY_NSP_END

#include "macros.fgen.hpp"

#undef disable_if_bool
#undef enable_if_bool

#endif

