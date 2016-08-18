#include "ExecuterMap.hpp"
#include "util.hpp"
#include <chila/lib/xmlppUtils/util.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    namespace xmlppUtils = chila::lib::xmlppUtils;

    XMLResult parseXML(const xmlpp::Element &element)
    {
        auto path = xmlppUtils::getAttribute<std::string>(element, "path");
        ArgumentStrMap argMap;

        xmlppUtils::iterateChildren(element, "arg", [&](const xmlpp::Element &childElem)
        {
            auto name = xmlppUtils::getAttribute<std::string>(childElem, "name");
            auto valuePtr = childElem.get_child_text();
            auto value = valuePtr ? valuePtr->get_content() : "";

            my_assert(argMap.insert({name, value}).second);
        });

        return { path, argMap };
    }


}
MY_NSP_END

