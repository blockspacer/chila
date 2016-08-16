/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "CPerformerCreator.hpp"
#include "types.hpp"
#include "exceptions.hpp"
#include "util.hpp"
#include <algorithm>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/exceptions.hpp>


#define libMisc chila::lib::misc

//@TODO Does not check connector arguments' existance for alias association


#include "nspDef.hpp"

MY_NSP_START
{
    namespace xmlppUtils = chila::lib::xmlppUtils;

    cPerformer::ConnectionPerformer &CPerformerCreator::create()
    {
        xmlpp::DomParser parser(file.string().c_str());
        auto &document = *parser.get_document();
        auto root = chila::lib::misc::checkNotNull(document.get_root_node());

        if (!root || root->get_name() != std::string("cPerformer"))
        {
            CPerformerNotFound ex;
            ex << chila::lib::misc::ExceptionInfo::XPath("/cPerformer");
            if (root) ex << chila::lib::misc::ExceptionInfo::Row(root->get_line());

            BOOST_THROW_EXCEPTION(ex);
        }

        // Creates the namespace
        libMisc::Path nspPath(xmlppUtils::getAttribute<std::string>(*root, "name"));
        auto cPerformerName = nspPath.pop();

        // Creates the ConnectionPerformer
        auto &cPerformerNsp = createNamespaceFromHere(nspBase, nspPath);
        auto &cPerf = cPerformerNsp.add<cPerformer::ConnectionPerformer>(cPerformerName);

        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "arguments"))
            parseArguments(cPerf, *cur);

        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "connectorAliases"))
            parseConnectorAliases(cPerf, *cur);

        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "argumentProviderCreators"))
            parseArgProviderCreators(cPerf, *cur);

        if (auto *cur = chila::lib::xmlppUtils::getUniqueChildElementPtr(*root, "connectors"))
            parseConnectorInstances(cPerf, *cur);

        return cPerf;
    }

    void CPerformerCreator::parseArguments(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &argumentsElem)
    {
        parseGrouped<cPerformer::ArgumentGroup>(cPerformer.arguments(), argumentsElem, "argument",
            [this](cPerformer::ArgumentMap &map, const xmlpp::Element &element)
            {
                auto name = xmlppUtils::getAttribute<std::string>(element, "name");
                auto &arg = map.add<cPerformer::Argument>(name);

                arg.description().value = xmlppUtils::getAttribute<std::string>(element, "description", "");
                arg.unique().value = xmlppUtils::getAttribute<bool>(element, "unique", false);
            });
    }

    template <typename AdderFun>
    void parseArgAliases(const xmlpp::Element &root, const std::string &elemStr, const AdderFun &adderFun)
    {
        xmlppUtils::iterateChildren(root, [&](const xmlpp::Element &element)
        {
            auto name = xmlppUtils::getAttribute<std::string>(element, "name");
            auto aliasName = xmlppUtils::getAttribute<std::string>(element, "cpName");

            adderFun(name, aliasName);
        });
    }

    template <typename AliasMap>
    void parseFunAliases(AliasMap &map, const xmlpp::Element &root, const std::string &elemStr)
    {
        xmlppUtils::iterateChildren(root, elemStr, [&](const xmlpp::Element &element)
        {
            auto name = xmlppUtils::getAttribute<std::string>(element, "name");
            auto description = xmlppUtils::getAttribute<std::string>(element, "description", "");

            map.add(name).description().value = description;
        });
    }

    void CPerformerCreator::parseConnectorAliases(cPerformer::ConnectionPerformer &cPerf, const xmlpp::Element &aliasesElem)
    {
        xmlppUtils::iterateChildren(aliasesElem, [&](const xmlpp::Element &aliasElem)
        {
            if (aliasElem.get_name() == "alias")
            {
                auto aliasName = xmlppUtils::getAttribute<std::string>(aliasElem, "name");

                auto &connectorAlias = cPerf.connectorAliases().add(aliasName);

                connectorAlias.connector().value = xmlppUtils::getAttribute<std::string>(aliasElem, "connectorPath", "");
                connectorAlias.description().value = xmlppUtils::getAttribute<std::string>(aliasElem, "description", "");

                auto &argElem = xmlppUtils::getUniqueChildElement(aliasElem, "arguments");
                auto &eventsElem = xmlppUtils::getUniqueChildElement(aliasElem, "events");
                auto &actionsElem = xmlppUtils::getUniqueChildElement(aliasElem, "actions");

                parseArgAliases(argElem, "argument", [&](const std::string &name, const std::string &aliasName)
                {
                    connectorAlias.arguments().add(name).cpRef().value = clMisc::Path(aliasName, ":");
                });

                parseFunAliases(connectorAlias.events(), eventsElem, "event");
                parseFunAliases(connectorAlias.actions(), actionsElem, "action");
            }
            else chila::lib::xmlppUtils::throwException(chila::lib::xmlppUtils::InvalidTagName(), aliasElem);
        });
    }

    void loadAPCArgs(cPerformer::ArgVRefMap &args, const StringVec &vec)
    {
        for (const auto &arg : vec)
        {
            args.add(arg);
        }
    }



    void CPerformerCreator::parseArgProviderCreators(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &aProvCreatorsElem)
    {
        parseGrouped<cPerformer::AProviderCreatorGroup>(cPerformer.aProvCreators(), aProvCreatorsElem, "creator",
            [this](cPerformer::AProviderCreatorMap &map, const xmlpp::Element &element)
            {
                auto elementName = xmlppUtils::getAttribute<std::string>(element, "name");
                auto requires = xmlppUtils::getAttribute<std::string>(element, "requires", "");
                auto provides = xmlppUtils::getAttribute<std::string>(element, "provides", "");

                auto &apc = map.add<cPerformer::AProviderCreator>(elementName);

                loadAPCArgs(apc.requires(), getIdVec(requires, ","));
                loadAPCArgs(apc.provides(), getIdVec(provides, ","));
            });
    }


    /** Parses the ConnectorInstances. */
    void CPerformerCreator::parseConnectorInstances(cPerformer::ConnectionPerformer &cPerformer, const xmlpp::Element &instancesElem)
    {
        parseGrouped<cPerformer::ConnectorInstanceGroup>(cPerformer.connInstances(), instancesElem, "instance",
            [this](cPerformer::ConnectorInstanceMap &map, const xmlpp::Element &element)
            {
                auto instanceName = xmlppUtils::getAttribute<std::string>(element, "name");
                auto connAliasName = xmlppUtils::getAttribute<std::string>(element, "connectorAlias", "");
                auto description = xmlppUtils::getAttribute<std::string>(element, "description", "");

                auto &connInstance = map.add<cPerformer::ConnectorInstance>(instanceName);
                connInstance.connAlias().value = connAliasName;
                connInstance.description().value = description;

                xmlppUtils::iterateChildren(element, "event", [&](const xmlpp::Element &eventElem)
                {
                    auto eventName = xmlppUtils::getAttribute<std::string>(eventElem, "name");
                    auto &apcsElem = xmlppUtils::getUniqueChildElement(eventElem, "aProviderCreators");
                    auto &actionsElem = xmlppUtils::getUniqueChildElement(eventElem, "actions");

                    auto &eventCall = connInstance.events().add(eventName);

                    eventCall.description().value = xmlppUtils::getAttribute<std::string>(eventElem, "description", "");

                    xmlppUtils::iterateChildren(apcsElem, "apc", [&](const xmlpp::Element &apcElem)
                    {
                        eventCall.aProvCreators().add(xmlppUtils::getAttribute<std::string>(apcElem, "name"));
                    });

                    xmlppUtils::iterateChildren(actionsElem, "action", [&](const xmlpp::Element &actionElem)
                    {
                        auto &accInstance = eventCall.actions().add();
                        accInstance.connInstance().value = clMisc::Path(xmlppUtils::getAttribute<std::string>(actionElem, "connector"), ":");
                        accInstance.action().value = clMisc::Path(xmlppUtils::getAttribute<std::string>(actionElem, "name"), ":");
                        accInstance.description().value = xmlppUtils::getAttribute<std::string>(actionElem, "description", "");
                        accInstance.determinesOrder().value = xmlppUtils::getAttribute<bool>(actionElem, "determinesOrder", true);
                    });
                });
            });
    }

    /** Parses 'actionStr' and loads the action name and it's associated AProvCreators' names,
     * and returns the connector name. */
    std::string CPerformerCreator::parseAction(const std::string &actionStr, std::string &actionName)
    {
        // Loads the connector instance name
        std::string modInstanceName;
        auto itStart = actionStr.begin(), itEnd = std::find(itStart, actionStr.end(), '.');

        my_assert(itEnd != actionStr.end());
        modInstanceName = std::string(itStart, itEnd++);
        itStart = itEnd;

        // Loads the action name
        itEnd = std::find(itStart, actionStr.end(), '[');
        actionName.assign(itStart, itEnd);

        return modInstanceName;
    }

}
MY_NSP_END
