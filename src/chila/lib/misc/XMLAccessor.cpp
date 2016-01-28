/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "XMLAccessor.hpp"
#include <chila/lib/xmlppUtils/util.hpp>
#include "util.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    const xmlpp::Node &XMLAccessor::getNode(const std::string &path) const try
    {
        auto nodes = element.find(path);

        if (nodes.empty())
            xmlppUtils::throwException(XMLElementNotFound(), element);
        else if (nodes.size() > 1)
            xmlppUtils::throwException(ManyXMLElementsFound(), element);
        else
            return chila::lib::misc::deref(nodes.front());
    }
    catch (const boost::exception &ex)
    {
        ex << ExceptionInfo::XPath(path);
        throw;
    }

    const xmlpp::Element &XMLAccessor::getElement(const std::string &path) const try
    {
        return dynamic_cast<const xmlpp::Element&>(getNode(path));
    }
    catch (const std::bad_cast &ex)
    {
        xmlppUtils::throwException(XMLNodeIsNotElement() << ExceptionInfo::XPath(path), element);
    }

    const xmlpp::Attribute &XMLAccessor::getAttribute(const std::string &path) const try
    {
        return dynamic_cast<const xmlpp::Attribute&>(getNode(path));
    }
    catch (const std::bad_cast &ex)
    {
        xmlppUtils::throwException(XMLNodeIsNotAttribute() << ExceptionInfo::XPath(path), element);
    }

}
MY_NSP_END
