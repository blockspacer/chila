/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_XMLPPUTILS__UTIL_HPP
#define CHILA_LIB_XMLPPUTILS__UTIL_HPP

#include "exceptions.hpp"
#include <boost/lexical_cast.hpp>
#include <libxml++/libxml++.h>
#include <chila/lib/misc/util.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Type>
    const Type &addExceptionInfo(const Type &exception, const xmlpp::Element &element)
    {
        return exception << chila::lib::misc::ExceptionInfo::XPath(element.get_path())
                         << chila::lib::misc::ExceptionInfo::Row(unsigned(element.get_line()));
    }

    template <typename Type>
    void throwException[[noreturn]](const Type &exception, const xmlpp::Element &element)
    {
        BOOST_THROW_EXCEPTION(addExceptionInfo(exception, element));
    }

    inline void throwInvalidAttributeValue[[noreturn]](const std::string &text, const xmlpp::Element &element)
    {
        throwException(InvalidAttributeValue(text), element);
    }

    void checkTagName(const xmlpp::Element &element, const std::string &name);
    const xmlpp::Element &getUniqueChildElement(const xmlpp::Element &element, const std::string &name);
    const xmlpp::Element *getUniqueChildElementPtr(const xmlpp::Element &element, const std::string &name);

    template <typename Type>
    inline Type getAttribute(const xmlpp::Element &element, const std::string &name) try
    {
        std::string ret = element.get_attribute_value(name);
        if (ret.empty())
            throwException(InvalidAttributeValue("'" + name + "' is empty"), element);

        return boost::lexical_cast<Type>(ret);
    }
    catch (const boost::bad_lexical_cast &ex)
    {
        throwException(InvalidAttributeValue("'" + name + "' is invalid"), element);
    }

    template <typename Type>
    inline Type getAttribute(const xmlpp::Element &element, const std::string &name, const Type &defVal) try
    {
        std::string ret = element.get_attribute_value(name);
        if (ret.empty())
            return defVal;

        return boost::lexical_cast<Type>(ret);
    }
    catch (const boost::bad_lexical_cast &ex)
    {
        throwException(InvalidAttributeValue("'" + name + "' is invalid"), element);
    }

    inline bool parseBool(const xmlpp::Element &element, const std::string &name, const std::string &strVal)
    {
        if (strVal == "true")
        {
            return true;
        }
        else if (strVal == "false")
        {
            return false;
        }
        else
        {
            chila::lib::xmlppUtils::throwInvalidAttributeValue("'" + name + "' must be 'true' or 'false'", element);
            return false;
        }
    }

    template <>
    inline bool getAttribute<bool>(const xmlpp::Element &element, const std::string &name)
    {
        return parseBool(element, name, element.get_attribute_value(name));
    }

    template <>
    inline bool getAttribute<bool>(const xmlpp::Element &element, const std::string &name, const bool &defVal)
    {
        std::string strVal = element.get_attribute_value(name);

        if (strVal.empty())
            return defVal;

        return parseBool(element, name, strVal);
    }

    void writeIndent(xmlpp::Element &element, unsigned indent);

    template <typename BodyFun>
    void addElementWithFormat(xmlpp::Element &root, const std::string &name, unsigned indent, const BodyFun &bodyFun)
    {
        writeIndent(root, indent);
        auto elem = root.add_child(name);

        bodyFun(*elem, indent + 1);

        if (elem->get_children().size())
        {
            writeIndent(*elem, indent);
        }
    }

    template <typename Fun>
    bool iterateChildren(const xmlpp::Element &root, const Fun &fun)
    {
        for (auto _node : root.get_children(""))
            if (auto *child = dynamic_cast<const xmlpp::Element*>(_node))
                if (!chila::lib::misc::executeVoidBoolFun([&] { return fun(*child); }))
                    return false;

        return true;
    }

    template <typename Fun>
    bool iterateChildren(const xmlpp::Element &root, const std::string &mandatoryName, const Fun &fun)
    {
        return iterateChildren(root, [&](const xmlpp::Element &child)
        {
            if (child.get_name() == mandatoryName)
            {
                if (!chila::lib::misc::executeVoidBoolFun([&] { return fun(child); }))
                    return false;
            }
            else throwException(xmlppUtils::InvalidTagName(), child);

            return true;
        });
    }
}
MY_NSP_END

#include "nspUndef.hpp"

#endif
