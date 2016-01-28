/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ConnectorCreator.hpp"
#include "types.hpp"

#include <boost/lexical_cast.hpp>
#include "util.hpp"
#include "exceptions.hpp"
#include <boost/bind.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/tokenizer.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/util.hpp>


#include <libxml++/nodes/node.h>
#include <libxml++/nodes/element.h>

#include "nspDef.hpp"

MY_NSP_START
{
    namespace xmlppUtils = chila::lib::xmlppUtils;

    /** Creates a connector from the XML file. */
    connector::Connector &ConnectorCreator::create()
    {
        xmlpp::DomParser parser(file.string().c_str());
        auto &document = *parser.get_document();
        auto root = chila::lib::misc::checkNotNull(document.get_root_node());

        if (!root || root->get_name() != "connector")
        {
            ConnectorNotFound ex;
            ex << chila::lib::misc::ExceptionInfo::XPath("/connector");
            if (root) ex << chila::lib::misc::ExceptionInfo::Row(root->get_line());

            BOOST_THROW_EXCEPTION(ex);
        }

        // Creates the namespace
        clMisc::Path nspPath(xmlppUtils::getAttribute<std::string>(*root, "name"));
        std::string modName = nspPath.pop(),
                    description = root->get_attribute_value("description");

        // Creates the connector
        Namespace &modNsp = createNamespaceFromHere(nspBase, nspPath);
        connector::Connector &connector = modNsp.add<connector::Connector>(modName);
        connector.description().value = description;

        // Gets the arguments
        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "arguments"))
            loadArguments(*cur, connector);

        // Gets the events
        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "events"))
            loadFunctions<connector::Event, connector::EventGroup>(*cur, connector.events());

        // Gets the actions
        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "actions"))
            loadFunctions<connector::Action, connector::ActionGroup>(*cur, connector.actions());

        return connector;
    }

    /** Loads the possible arguments. */
    void ConnectorCreator::loadArguments(const xmlpp::Element &root, connector::Connector &connector)
    {
        parseGrouped<connector::ArgumentGroup>(connector.arguments(), root, "arg",
            [this](connector::ArgumentMap &map, const xmlpp::Element &element)
            {
                auto name = xmlppUtils::getAttribute<std::string>(element, "name");
                auto &arg = map.add<connector::Argument>(name);

                arg.description().value = xmlppUtils::getAttribute<std::string>(element, "description", "");
            });
    }

    void loadEvents(connector::Event &event, const xmlpp::Element &funElem) {}

    void loadEvents(connector::Action &action, const xmlpp::Element &funElem)
    {
        auto evs = funElem.get_attribute_value("events");

        auto events = getIdVec(evs, ",");

        for (const auto &event : events)
        {
            action.events().add(event);
        }
    }

    template <typename Type> std::string getTagName();
    template <> std::string getTagName<connector::EventMap>() { return "event"; }
    template <> std::string getTagName<connector::ActionMap>() { return "action"; }

    /** Loads functions contained inside an element. */
    template <typename Function, typename FunctionGroup, typename FunctionMap>
    void ConnectorCreator::loadFunctions(const xmlpp::Element &root, FunctionMap &functions)
    {
        std::string tagName = getTagName<FunctionMap>();

        parseGrouped<FunctionGroup>(functions, root, tagName,
            [this](FunctionMap &map, const xmlpp::Element &element)
            {
                auto name = xmlppUtils::getAttribute<std::string>(element, "name");
                auto &fun = map.template add<Function>(name);

                fun.description().value = element.get_attribute_value("description");

                StringVec argNames;
                getSignature(element, argNames);

                auto &faVec = fun.arguments();

                for (const auto &argName : argNames)
                {
                    faVec.add(argName);
                }

                loadEvents(fun, element);
            });


//        // Loads the functions
//        chila::lib::xmlppUtils::iterateChildren(root, tagName, [&](const xmlpp::Element &funElem)
//        {
//            // Gets the name
//            std::string name = xmlppUtils::getAttribute<std::string>(funElem, "name");
//
//            StringVec argNames;
//            getSignature(funElem, argNames);
//
//            // Adds the function
//            auto &fun = functions.add(name);
//            fun.description().value = funElem.get_attribute_value("description");
//
//            auto &faVec = fun.arguments();
//
//            for (const auto &argName : argNames)
//            {
//                faVec.add(argName);
//            }
//
//            loadEvents(fun, funElem);
//        });
    }

    /** Loads the signature data and returns it. */
    void ConnectorCreator::getSignature(const xmlpp::Element &root, StringVec &argNames)
    {
        argNames = getIdVec(xmlppUtils::getAttribute<std::string>(root, "arguments", ""), ",");
    }


}
MY_NSP_END
