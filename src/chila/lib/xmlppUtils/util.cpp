/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include <chila/lib/misc/RepeatText.hpp>

#include <chila/lib/misc/macrosExp.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    void checkTagName(const xmlpp::Element &element, const std::string &name)
    {
        if (element.get_name() != name)
            throwException(InvalidTagName("should be '" + name + "'"), element);
    }

    const xmlpp::Element &getUniqueChildElement(const xmlpp::Element &element, const std::string &name)
    {
        xmlpp::Node::NodeList nodes = element.get_children(name);
        if (nodes.empty())
            throwException(ChildElementNotFound(name), element);
        else if (const xmlpp::Element *ret = dynamic_cast<const xmlpp::Element*>(nodes.front()))
            return *ret;
        else
            throwException(ChildElementNotFound(name), element);
    }

    const xmlpp::Element *getUniqueChildElementPtr(const xmlpp::Element &element, const std::string &name)
    {
        xmlpp::Node::NodeList nodes = element.get_children(name);
        if (nodes.empty())
            return nullptr;

        return dynamic_cast<const xmlpp::Element*>(nodes.front());
    }

    void writeIndent(xmlpp::Element &element, unsigned indent)
    {
        std::stringstream str;
        str << "\n" << chila::lib::misc::repeatText(indent * 4, " ");
        element.add_child_text(str.str());
    }
}
MY_NSP_END

