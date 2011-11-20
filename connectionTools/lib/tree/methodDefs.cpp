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

#include "namespace.hpp"
#include <chila/lib/misc/exceptions.hpp>
#include <boost/bind.hpp>
#include "ArgumentNamesGetterProv.hpp"
#include "ArgumentNamesSetterReq.hpp"
#include "APCNamesReqProv.hpp"
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

#define DEF_GETTER_FUNCTOR(Name, Class, method, ResultType)             \
    struct Name                                                         \
    {                                                                   \
        typedef ResultType result_type;                                 \
        const Class &object;                                            \
                                                                        \
        Name(const Class &object) : object(object) {}                   \
                                                                        \
        ResultType operator()() const { return object.method(); }       \
    }

#define catch_element_not_found_msg                                                                 \
    catch (const chila::lib::misc::ElementNotFound &ex)                            \
    {                                                                                               \
        if (const libMisc::Path *path = boost::get_error_info<ErrorInfo::Path>(ex))                          \
        {                                                                                           \
            throw CheckErrorElement(getPath(), "element not found '" + path->getStringRep() + "'"); \
        }                                                                                           \
        else throw;                                                                                 \
    }

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    template <typename Functor>
    typename Functor::result_type checkRaiseExp(Functor fun, const libMisc::Path &path) try
    {
        return fun();
    }
    catch (const chila::lib::misc::ElementNotFound &ex)
    {
        if (const libMisc::Path *exPath = boost::get_error_info<ErrorInfo::Path>(ex))
        {
            throw CheckErrorElement(path, "element not found: '" + exPath->getStringRep() + "'");
        }
        else throw;
    }

    // ----------------------------------------- NspBase ------------------------------------------------

    // Finds an inner namespace
    Namespace &NspBase::findNamespacePv(StringVec::const_iterator cur, StringVec::const_iterator end)
    {
        if (cur == end)
            return dynamic_cast<Namespace&>(*this);

        return getNamespace(*cur++).findNamespacePv(cur, end);
    }

    // Finds an inner namespace
    const Namespace &NspBase::findNamespacePv(StringVec::const_iterator cur,
            StringVec::const_iterator end) const
    {
        if (cur == end)
            return dynamic_cast<const Namespace&>(*this);

        return getNamespace(*cur++).findNamespacePv(cur, end);
    }

    // ------------------------------------- FunctionArgument ---------------------------------------------

    Argument &FunctionArgument::getArgument()
    {
        return container.container.container.getArgument(name);
    }

    const Argument &FunctionArgument::getArgument() const
    {
        return container.container.container.getArgument(name);
    }

    void FunctionArgument::check() const
    {
        try { getArgument(); } catch_element_not_found_msg
    }

    // -------------------------------------- ConnectorAlias ----------------------------------------------

    // Returns the referenced Connector
    Connector &ConnectorAlias::getConnector()
    {
        libMisc::Path nspPath = connectorPath;
        std::string connName = nspPath.pop();

        return container.getGlobalNsp().findNamespace(nspPath).getConnector(connName);
    }

    // Returns the referenced Connector
    const Connector &ConnectorAlias::getConnector() const
    {
        libMisc::Path nspPath = connectorPath;
        std::string connName = nspPath.pop();

        return container.getGlobalNsp().findNamespace(nspPath).getConnector(connName);
    }

    // Checks the validity of the object
    void ConnectorAlias::check() const
    {
        try { getConnector(); } catch_element_not_found_msg
        ObjectContainer::checkObjects();
    }

    // ------------------------------------ ArgumentAliasLink ---------------------------------------------

    // Returns the referenced Alias
    const ArgumentAlias &ArgumentAliasLink::getAlias() const
    {
        return container.container.getArgumentAlias(aliasName);
    }

    // Returns the referenced Argument
    const Argument &ArgumentAliasLink::getArgument() const
    {
        return container.getConnector().getArgument(name);
    }

    // Checks the validity of the ArgumentAliasLink
    void ArgumentAliasLink::check() const
    {
        const Application &app = container.container;
        libMisc::Path connPath = container.getConnector().getPath();

        try { app.getArgumentAlias(aliasName);  } catch_element_not_found_msg
        try { getArgument();                    } catch_element_not_found_msg
    }

    // ---------------------------------------- APCArgument ---------------------------------------------

    /** Returns the refered alias. */
    const ArgumentAlias &APCArgument::getAlias() const
    {
        const Application &app = container.container.container;
        return app.getArgumentAlias(name);
    }

    // Checks the validity of the argument
    void APCArgument::check() const
    {
        Application &app = container.container.container;
        try { getAlias(); } catch_element_not_found_msg
    }

    // ------------------------------------ ConnectorInstance ---------------------------------------------

    // Returns the referenced ConnectorAlias
    ConnectorAlias &ConnectorInstance::getAlias()
    {
        return container.getConnectorAlias(aliasName);
    }

    // Returns the referenced ConnectorAlias
    const ConnectorAlias &ConnectorInstance::getAlias() const
    {
        return container.getConnectorAlias(aliasName);
    }

    // Checks the validity of the object
    void ConnectorInstance::check() const
    {
        try { getAlias(); } catch_element_not_found_msg
        ObjectContainer::checkObjects();
    }

    // ------------------------------------ FunctionConnection --------------------------------------------
    const Function &FunctionConnection::getEvent() const
    {
        const Connector &connector = container.getAlias().getConnector();
        return connector.events.getFunction(name);
    }

    DEF_GETTER_FUNCTOR(ConnInstance_GetConnAlias, ConnectorInstance, getAlias, const ConnectorAlias&);
    DEF_GETTER_FUNCTOR(FunConnAPC_GetArgProvCreator, FunConnArgProvCreator, getCreator, const ArgProviderCreator&);


    void FunctionConnection::check() const
    {
        libMisc::Path path = getPath();

        const ConnectorAlias &connAlias = checkRaiseExp(ConnInstance_GetConnAlias(container), path);
        const Function &event = checkRaiseExp(boost::bind(&FunctionConnection::getEvent, this), path);

        IArgNamesReqOrProvVec aNamesRPVec;

        // Loads the first element, a provider interface between the caller and the creators and callee
        IArgNamesReqOrProvSCPtr anGetterProv;
        try
        {
            aNamesRPVec.push_back(boost::make_shared<const ArgumentNamesGetterProv>(connAlias, event));
        }
        catch_element_not_found_msg

        // Loads the vector from the creators
        FunConnArgProvCreatorCVec creators = aProvCreators.getCreators();
        BOOST_FOREACH(const FunConnArgProvCreator *creator, creators)
        {
            assert(creator);
            const ArgProviderCreator &argProvCreator =
                checkRaiseExp(FunConnAPC_GetArgProvCreator(*creator), path);

            aNamesRPVec.push_back(boost::make_shared<APCNamesReqProv>(argProvCreator));
        }

        CheckErrorGroup errorGroup;
        bool hasErrors = false;

        // Checks every destination
        FunConnDestinationCVec destinations = getDestinations();
        BOOST_FOREACH(const FunConnDestination *dest, destinations)
        {
            assert(dest);

            // Loads the last element, a requirer interface between the callee and the creators and caller
            try
            {
                aNamesRPVec.push_back(boost::make_shared<const ArgumentNamesSetterReq>(*dest));
            }
            catch_element_not_found_msg

            // Checks that every requirer can get its required arguments
            for (unsigned i = aNamesRPVec.size() - 1; i > 0; --i)
            {
                const IArgumentNamesRequirer &req =
                    dynamic_cast<const IArgumentNamesRequirer&>(*(aNamesRPVec[i]));

                // Checks every requirer's argument for a provider's match
                const StringSet &reqArgNames = req.getRequiredArgNames();
                BOOST_FOREACH(const std::string &reqArg, reqArgNames)
                {
                    static unsigned runCount = 0;
                    runCount++;
                    bool found = false;
                    for (unsigned j = 0; j < i; ++j)
                    {
                        const IArgumentNamesProvider &prov =
                            dynamic_cast<const IArgumentNamesProvider&>(*(aNamesRPVec[i - j - 1]));

                        const StringSet &provArgs = prov.getProvidedArgNames();

                        if (provArgs.find(reqArg) != provArgs.end())
                            found = true;
                    }

                    if (!found)
                    {
                        CheckFunConnError errElement(path, "Could not find a provider for '" +
                            req.getPath().getStringRep() + ": " + reqArg + "'", aNamesRPVec);

                        errorGroup.addError(errElement);
                        hasErrors = true;
                    }
                }
            }

            // Removes the last element, for the next iteration
            aNamesRPVec.pop_back();
        }

        if (hasErrors) throw errorGroup;
    }

    // ---------------------------------- FunConnDestination ---------------------------------------------

    ConnectorInstance &FunConnDestination::getInstance()
    {
        Application &app = container.container.container;
        return app.getConnectorInstance(destInstanceName);
    }

    const ConnectorInstance &FunConnDestination::getInstance() const
    {
        const Application &app = container.container.container;
        return app.getConnectorInstance(destInstanceName);
    }

    Function &FunConnDestination::getAction()
    {
        return getInstance().getAlias().getConnector().actions.getFunction(actionName);
    }

    const Function &FunConnDestination::getAction() const
    {
        return getInstance().getAlias().getConnector().actions.getFunction(actionName);
    }

    // ---------------------------------- FunConnArgProvCreator -----------------------------------------
    ArgProviderCreator &FunConnArgProvCreator::getCreator()
    {
        Application &app = container.container.container.container;
        return app.getArgProviderCreator(name);
    }

    const ArgProviderCreator &FunConnArgProvCreator::getCreator() const
    {
        const Application &app = container.container.container.container;
        return app.getArgProviderCreator(name);
    }


    // --------------------------------------- NspBase --------------------------------------------------

    /** Adds a namespace. */
    Namespace &NspBase::setNamespace(const std::string &name)
    {
        return setObject(new Namespace(*this, name));
    }

    /** Returns a namespace from 'path' that starts from this namespace. If the namespace exists,
     * it returns it; if not, it creates it and all the intermediate namespaces to it.
     */
    NspBase &NspBase::createNamespaceFromHerePv(StringVec::const_iterator cur,
            StringVec::const_iterator end)
    {
        if (cur == end) return *this;

        const std::string &childName = *cur;

        try
        {
            NspBase &nsp = getObject<NspBase>(childName);
            return nsp.createNamespaceFromHerePv(++cur, end);
        }
        catch (const chila::lib::misc::ElementNotFound &ex)
        {
            Namespace &nsp = setNamespace(childName);
            return nsp.createNamespaceFromHerePv(++cur, end);
        }
    }

    /** Returns the corresponding aliases of */
    StringSet getAliasesOfFunction(const ConnectorAlias &connAlias, const Function &function)
    {
        FunctionArgumentCVec args = function.getArguments();

        StringSet ret;
        BOOST_FOREACH(const FunctionArgument *funArg, args)
        {
            assert(funArg);
            const ArgumentAliasLink &aaLink = connAlias.getLink(funArg->getName());
            ret.insert(aaLink.getAlias().getName());
        }

        return ret;
    }


}}}}

