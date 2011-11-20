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

#include "ConnectorCreator.hpp"
#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include "Arguments.hpp"
#include "Functions.hpp"
#include <boost/bind.hpp>
#include "Connector.hpp"
#include "namespace.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/tokenizer.hpp>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/tinyXMLUtils/macrosDef.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE           CHILA_LIB_MISC__DEF_NAMESPACE
#define tixml_iterate_elements  CHILA_LIB_TINYXMLUTILS__TIXML_ITERATE_ELEMENTS

#define push_tag(name) PushPath pp_##name(currPath, #name);

#define check_tag_and_push(elem, name) checkTag(elem, #name); push_tag(name)


#define libMisc chila::lib::misc



DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    /** Creates a connector from the XML file. */
    Connector &ConnectorCreator::create()
    {
        TiXmlDocument doc;
        doc.LoadFile(file.string().c_str());
        chila::lib::misc::check(doc);

        TiXmlElement *root = doc.RootElement();

        // Checks the connector tag
        check_tag_and_push(root, connector);

        // Takes the name
        const char *modFullName = getAttrAndCheck(root, "name");

        // Creates the namespace
        libMisc::Path nspPath(modFullName);
        std::string modName = nspPath.pop(),
                    description = getAttrAndCheck(root, "description");

        // Creates the connector
        NspBase &modNsp = nspBase.createNamespaceFromHere(nspPath);
        Connector &connector = modNsp.setConnector(modName, description);

        const TiXmlElement *cur = root->FirstChildElement();

        // Gets the arguments
        if (cur && (strcmp(cur->Value(), "arguments") == 0))
        {
            loadArguments(cur, connector);
            cur = cur->NextSiblingElement();
        }

        // Gets the actions
        if (cur && (strcmp(cur->Value(), "actions") == 0))
        {
            push_tag(actions);
            Functions &actions = connector.actions;
            loadFunctions(cur, connector,
                boost::bind(&Functions::setFunction, boost::ref(actions), _1, _2, _3), "action");
            cur = cur->NextSiblingElement();
        }


        // Gets the events
        if (cur && (strcmp(cur->Value(), "events") == 0))
        {
            push_tag(events);
            Functions &events = connector.events;
            loadFunctions(cur, connector,
                boost::bind(&Functions::setFunction, boost::ref(events), _1, _2, _3), "event");
        }

        return connector;
    }



    /** Loads the possible arguments. */
    void ConnectorCreator::loadArguments(const TiXmlElement *root, Connector &connector)
    {
        push_tag(arguments);

        // Loads the arguments
        tixml_iterate_elements(root, argElem)
        {
            check_tag_and_push(argElem, arg);

            // Gets the name and description
            const char *argName = getAttrAndCheck(argElem, "name");
            const char *argDesc = argElem->Attribute("description");

            // Adds the argument
            try
            {
                connector.setArgument(argName, argDesc ? argDesc : "");
            }
            catch (const chila::lib::misc::ElementAlreadyExists &ex)
            {
                throwAttributeError(argName, argElem, "already exists");
            }
        }
    }



    /** Loads functions contained inside an element. */
    void ConnectorCreator::loadFunctions(const TiXmlElement *root, Connector &connector,
            const AddFunction &addFun, const char *tagName)
    {
        // Loads the functions
        tixml_iterate_elements(root, funElem)
        {
            checkTag(funElem, tagName);
            PushPath pp_tagName(currPath, tagName);

            // Gets the name
            const char *name = getAttrAndCheck(funElem, "name");

            // Gets the description;
            const char *desc = funElem->Attribute("description");

            StringVec argNames;
            getSignature(funElem, argNames);

            // Adds the function
            addFun(name, argNames, desc ? desc : "");
        }
    }

    /** Loads the signature data and returns it. */
    void ConnectorCreator::getSignature(const TiXmlElement *root, StringVec &argNames)
    {
        const char *arguments = getAttrAndCheck(root, "arguments");
        if (arguments)
            argNames = getIdVec(arguments, ",");
    }


}}}}

