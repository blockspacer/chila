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

#ifndef CHILA_CONNECTIONTOOLS_LIB_PRINT_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_PRINT_HPP

#include "fwd.hpp"
#include "namespace.hpp"
#include "Application.hpp"
#include <boost/foreach.hpp>
#include <chila/lib/misc/SimplePrinter.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc

#define START_SCOPE  out.printIndent(); out << "{\n"; { IGuard iGuard(out);
#define END_SCOPE    } out.printIndent(); out << "}\n";

DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    template <typename Sink>
    void printFunction(libMisc::SimplePrinter<Sink> &out, const Connector &connector, const Function &fun)
    {
        out.printIndent(); out << fun.getName() << "(";
        bool first = true;

        FunctionArgumentCVec funArgs = fun.getArguments();
        BOOST_FOREACH(const FunctionArgument *funArg, funArgs)
        {
            assert(funArg);
            if (first) first = false;
            else out << ", ";
            out << funArg->getName();
        }

        out << ")\n";

        out.get().flush();
    }


    template <typename Sink>
    libMisc::SimplePrinter<Sink> &operator<<(libMisc::SimplePrinter<Sink> &out, const Connector &connector)
    {
        typedef libMisc::IndentGuard<Sink> IGuard;
        out.printIndent(); out << connector.getName() << ":\n";
        out.printIndent(); out << "{\n";

        {
            // Prints the arguments
            IGuard iGuard(out);
            out.printIndent(); out << "Arguments:"  << "\n";
            out.printIndent(); out << "{\n";

            ArgumentCVec arguments = connector.getArguments();
            BOOST_FOREACH(const Argument *arg, arguments)
            {
                IGuard iGuard(out);

                out.printIndent(); out << arg->getName() << "\n"; // << ": " << arg->getType() << " "
//                        << (arg->isConst() ? "(const)" : "")
//                        << (arg->isRef() ? "(ref)" : "") << "\n";

            }
            out.printIndent(); out << "}\n";

            // Prints the actions
            out.printIndent(); out << "Actions:"  << "\n";
            out.printIndent(); out << "{\n";

            FunctionCVec actions = connector.actions.getFunctions();
            BOOST_FOREACH(const Function *action, actions)
            {
                assert(action);

                IGuard iGuard(out);
                printFunction(out, connector, *action);
            }
            out.printIndent(); out << "}\n";

            // Prints the events
            out.printIndent(); out << "events:"  << "\n";
            out.printIndent(); out << "{\n";
            FunctionCVec events = connector.events.getFunctions();
            BOOST_FOREACH(const Function *event, events)
            {
                assert(event);

                IGuard iGuard(out);
                printFunction(out, connector, *event);
            }
            out.printIndent(); out << "}\n";
        }

        out.printIndent(); out << "}\n";

        return out;
    }

    template <typename Sink>
    libMisc::SimplePrinter<Sink> &operator<<(libMisc::SimplePrinter<Sink> &out, const Application &app)
    {
        bool first;

        typedef libMisc::IndentGuard<Sink> IGuard;
        out.printIndent(); out << app.getName() << ":\n";

        START_SCOPE

            out.printIndent(); out << "ArgumentAliases:"  << "\n";

            START_SCOPE
                ArgumentAliasCVec aliases = app.getArgumentAliases();
                BOOST_FOREACH(const ArgumentAlias *alias, aliases)
                {
                    assert(alias);
                    out.printIndent(); out << alias->getName()  << "\n";
                }
            END_SCOPE


            out.printIndent(); out << "ConnectorAliases:"  << "\n";
            START_SCOPE
                ConnectorAliasCVec alGroups = app.getConnectorAliases();
                BOOST_FOREACH(const ConnectorAlias *conAlias, alGroups)
                {
                    assert(conAlias);
                    out.printIndent(); out << conAlias->getName()  << "\n";

                    START_SCOPE
                        ArgumentAliasLinkCVec aLinks = conAlias->getLinks();
                        BOOST_FOREACH(const ArgumentAliasLink *link, aLinks)
                        {
                            assert(link);
                            out.printIndent(); out << "arg: " << link->getName() << " --> alias: "
                                    << link->getAliasName() << "\n";
                        }
                    END_SCOPE
                }
            END_SCOPE


            out.printIndent(); out << "ArgumentProviderCreators:"  << "\n";
            START_SCOPE
                ArgProviderCreatorCVec argProviderCreators = app.getArgProviderCreators();
                BOOST_FOREACH(const ArgProviderCreator *creator, argProviderCreators)
                {
                    assert(creator);
                    out.printIndent(); out << creator->getName()  << "\n";
                    START_SCOPE
                        out.printIndent(); out << "requires: ";
                        first = true;
                        APCArgumentCVec apcReqArguments = creator->getRequiredArguments().getArguments();
                        BOOST_FOREACH(const APCArgument *argument, apcReqArguments)
                        {
                            if (first) first = false;
                            else out << ", ";
                            out << argument->getName();
                        }
                        out << "\n";

                        out.printIndent(); out << "provides: ";
                        first = true;
                        APCArgumentCVec apcProvArguments = creator->getProvidedArguments().getArguments();
                        BOOST_FOREACH(const APCArgument *argument, apcProvArguments)
                        {
                            if (first) first = false;
                            else out << ", ";
                            out << argument->getName();
                        }
                        out << "\n";
                    END_SCOPE
                }
            END_SCOPE

            out.printIndent(); out << "ConnectorInstances:\n";
            START_SCOPE
            ConnectorInstanceCVec connInstances = app.getConnectorInstances();
            BOOST_FOREACH(const ConnectorInstance *instance, connInstances)
            {
                assert(instance);
                out.printIndent(); out << instance->getName() << ": " <<
                        instance->getAliasName() << "\n";

                START_SCOPE
                    FunctionConnectionCVec fConnections = instance->getConnections();
                    BOOST_FOREACH(const FunctionConnection *fConn, fConnections)
                    {
                        assert(fConn);
                        out.printIndent(); out << fConn->getName() << "\n";

                        START_SCOPE
                            FunConnDestinationCVec destinations = fConn->getDestinations();

                            out.printIndent(); out << "Creators: ";
                            FunConnArgProvCreatorCVec creators = fConn->aProvCreators.getCreators();
                            if (!creators.empty())
                            {
                                bool first = true;
                                BOOST_FOREACH(const FunConnArgProvCreator *creator, creators)
                                {
                                    assert(creator);
                                    if (first) first = false;
                                    else out << ", ";

                                    out << creator->getName();
                                }
                            }
                            out << "\n";

                            out.printIndent(); out << "Actions: \n";
                            START_SCOPE
                                BOOST_FOREACH(const FunConnDestination *dest, destinations)
                                {
                                    assert(dest);
                                    out.printIndent(); out << dest->getDestInstanceName()
                                                            << "." << dest->getActionName();

                                    out << "\n";
                                }
                            END_SCOPE
                        END_SCOPE
                    }
                END_SCOPE
            }
            END_SCOPE

        END_SCOPE

    }

    template <typename Sink>
    libMisc::SimplePrinter<Sink> &operator<<(libMisc::SimplePrinter<Sink> &out, const NspBase &nspBase)
    {
        typedef libMisc::IndentGuard<Sink> IGuard;
        bool isNamespace = false;

        if (const Namespace *nsp = dynamic_cast<const Namespace*>(&nspBase))
        {
            out.printIndent(); out << nsp->getName() << ":\n";
            out.printIndent(); out << "{\n";
            isNamespace = true;
        }

        {
            IGuard iGuard(out);

            // Prints the Namespaces
            NamespaceCVec namespaces = nspBase.getNamespaces();
            BOOST_FOREACH(const Namespace *nsp, namespaces)
            {
                assert(nsp);
                out << *nsp;
            }

            // Prints the Connectors
            ConnectorCVec connectors = nspBase.getConnectors();
            BOOST_FOREACH(const Connector *connector, connectors)
            {
                assert(connector);
                out << *connector;
            }

            // Prints the Application
            ApplicationCVec applications = nspBase.getApplications();
            BOOST_FOREACH(const Application *app, applications)
            {
                assert(app);
                out << *app;
            }

        }

        if (isNamespace)
        {
            out.printIndent(); out << "}\n";
        }

        return out;
    }
}}}}

#undef DEF_NAMESPACE
#undef libMisc
#include <chila/lib/misc/macrosUndef.hpp>
#endif

