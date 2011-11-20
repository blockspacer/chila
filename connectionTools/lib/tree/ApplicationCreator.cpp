/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ApplicationCreator.hpp"
#include "Application.hpp"
#include "namespace.hpp"
#include "ArgumentAliases.hpp"
#include "ConnectorAliases.hpp"
#include "ConnectorInstances.hpp"
#include "ArgProviderCreators.hpp"
#include "ConnectorInstances.hpp"
#include <algorithm>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/misc/macrosDef.hpp>
#include <chila/lib/tinyXMLUtils/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define push_tag(name) PushPath pp_##name(currPath, #name);

#define check_tag_and_push(elem, name) checkTag(elem, #name); push_tag(name)

#define libMisc chila::lib::misc
#define tixml_iterate_elements CHILA_LIB_TINYXMLUTILS__TIXML_ITERATE_ELEMENTS



DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    /** Creates an Application. */
    Application &ApplicationCreator::create()
    {
        TiXmlDocument doc;
        doc.LoadFile(file.string().c_str());
        chila::lib::misc::check(doc);

        TiXmlElement *root = doc.RootElement();

        // Checks the application tag
        check_tag_and_push(root, application);

        // Takes the name
        const char *appFullName = getAttrAndCheck(root, "name");

        // Creates the namespace
        libMisc::Path nspPath(appFullName);
        std::string appCreatorName = nspPath.pop();

        // Creates the Application
        NspBase &appCreatorNsp = nspBase.createNamespaceFromHere(nspPath);
        Application &application = appCreatorNsp.setApplication(appCreatorName);

        const TiXmlElement *cur = root->FirstChildElement();
        parseArgumentAliases(application, cur); cur = cur->NextSiblingElement();
        parseConnectorAliases(application, cur); cur = cur->NextSiblingElement();
        parseArgProviderCreators(application, cur); cur = cur->NextSiblingElement();
        parseConnectorInstances(application, cur);

        return application;
    }

    /** Parses the ArgumentAliases. */
    void ApplicationCreator::parseArgumentAliases(Application &application, const TiXmlElement *aliasElem)
    {
        // Checks the argumentAliases tag
        check_tag_and_push(aliasElem, argumentAliases);

        tixml_iterate_elements(aliasElem, aliasEntryElem)
        {
            check_tag_and_push(aliasEntryElem, alias);

            const char *name = getAttrAndCheck(aliasEntryElem, "name");
            const char *description = getAttrAndCheck(aliasEntryElem, "description");

            application.setArgumentAlias(name, description);
        }
    }

    /** Parses the ConnectorInstances. */
    void ApplicationCreator::parseConnectorAliases(Application &application, const TiXmlElement *aliasesElem)
    {
        // Checks the connectorInstances tag
        check_tag_and_push(aliasesElem, connectorAliases);

        tixml_iterate_elements(aliasesElem, aliasElem)
        {
            check_tag_and_push(aliasElem, alias);
            const char *aliasName = getAttrAndCheck(aliasElem, "name");
            const char *connectorPath = getAttrAndCheck(aliasElem, "connectorPath");

            ConnectorAlias &connectorAlias = application.setConnectorAlias(aliasName, connectorPath);

            tixml_iterate_elements(aliasElem, argumentElem)
            {
                check_tag_and_push(argumentElem, argument);
                const char *argName = getAttrAndCheck(argumentElem, "name");
                const char *argumentAliasName = getAttrAndCheck(argumentElem, "argumentAlias");

                connectorAlias.setLink(argName, argumentAliasName);
            }
        }
    }

    /** Parses the ArgProviderCreators. */
    void ApplicationCreator::parseArgProviderCreators(Application &application, const TiXmlElement *aProvCreatorsElem)
    {
        // Checks the argumentProviderCreators tag
        check_tag_and_push(aProvCreatorsElem, argumentProviderCreators);

        tixml_iterate_elements(aProvCreatorsElem, aProvCreatorElem)
        {
            check_tag_and_push(aProvCreatorElem, creator);
            const char *name = getAttrAndCheck(aProvCreatorElem, "name");
            const char *requires = getAttrAndCheck(aProvCreatorElem, "requires");
            const char *provides = getAttrAndCheck(aProvCreatorElem, "provides");

            application.setArgProviderCreator(name, getIdVec(requires, ","), getIdVec(provides, ","));
        }
    }

    /** Parses the ConnectorInstances. */
    void ApplicationCreator::parseConnectorInstances(Application &application,
            const TiXmlElement *instancesElem)
    {
        // Checks the argumentProviderCreators tag
        check_tag_and_push(instancesElem, connectors);

        tixml_iterate_elements(instancesElem, instanceElem)
        {
            check_tag_and_push(instanceElem, instance);
            const char *instanceName = getAttrAndCheck(instanceElem, "name");
            const char *connAliasName = getAttrAndCheck(instanceElem, "connectorAlias");

            ConnectorInstance &connInstance = application.setConnectorInstance(instanceName, connAliasName);

            tixml_iterate_elements(instanceElem, eventElem)
            {
                check_tag_and_push(eventElem, event);
                const char *eventName = getAttrAndCheck(eventElem, "name");
                const char *eventActions = getAttrAndCheck(eventElem, "actions");
                const char *eventCreators = eventElem->Attribute("aProviderCreators");

                FunctionConnection &functionConnection = connInstance.setConnection(eventName);

                StringVec actionsStr = getIdVec(eventActions, ",");

                if (eventCreators)
                {
                    StringVec creatorsStr = getIdVec(eventCreators, ",");

                    unsigned pos = 0;
                    BOOST_FOREACH(const std::string &creator, creatorsStr)
                    {
                        functionConnection.aProvCreators.setCreator(creator, pos++);
                    }
                }

                unsigned pos = 0;
                BOOST_FOREACH(const std::string &actionStr, actionsStr)
                {
                    StringVec creators;
                    std::string actionName;
                    std::string destModInstanceName = parseAction(actionStr, actionName);

                    functionConnection.setDestination(destModInstanceName, actionName, pos++);
                }
            }
        }
    }
//
    /** Parses 'actionStr' and loads the action name and it's associated ArgumentProviderCreators' names,
     * and returns the connector name. */
    std::string ApplicationCreator::parseAction(const std::string &actionStr, std::string &actionName)
    {
        // Loads the connector instance name
        std::string modInstanceName;
        std::string::const_iterator itStart = actionStr.begin(),
                                    itEnd = std::find(itStart, actionStr.end(), '.');
        assert(itEnd != actionStr.end());
        modInstanceName = std::string(itStart, itEnd++);
        itStart = itEnd;

        // Loads the action name
        itEnd = std::find(itStart, actionStr.end(), '[');
        actionName.assign(itStart, itEnd);

        return modInstanceName;
    }

}}}}

