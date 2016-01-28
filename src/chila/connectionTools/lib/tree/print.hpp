/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__PRINT_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__PRINT_HPP

#include "fwd.hpp"
#include "types.hpp"
#include <boost/foreach.hpp>
#include <chila/lib/misc/SimplePrinter.hpp>


#define START_SCOPE  out.printIndent(); out << "{\n"; { IGuard iGuard(out);
#define END_SCOPE    } out.printIndent(); out << "}\n";

#define DYN_PRINT(Type, data) \
        if (const auto *typed = dynamic_cast<const Type*>(&data)) { out << *typed; }

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename Sink>
    void printFunction(clMisc::SimplePrinter<Sink> &out, const connector::Function &fun)
    {
        out.printIndent(); out << fun.name() << "(";
        bool first = true;

        for (const auto &funArg : fun.arguments())
        {
            if (first) first = false;
            else out << ", ";
            out << funArg.name();
        }

        out << ")\n";
        out.printIndent(); out << "- desc: [" << fun.description().value << "]" << "\n";

        out.get().flush();
    }


    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const connector::Connector &connector)
    {
//        using IGuard = clMisc::IndentGuard<Sink>;
//
//        out.printIndent(); out << connector.name() << ":\n";
//        out.printIndent(); out << "{\n";
//
//        {
//            // Prints the arguments
//            IGuard iGuard(out);
//            out.printIndent(); out << "arguments:"  << "\n";
//            out.printIndent(); out << "{\n";
//
//            for (const auto &arg : connector.arguments())
//            {
//                IGuard iGuard(out);
//                out.printIndent(); out << arg.name() << ": [" << arg.description().value << "]\n";
//            }
//            out.printIndent(); out << "}\n";
//
//            // Prints the actions
//            out.printIndent(); out << "actions:"  << "\n";
//            out.printIndent(); out << "{\n";
//
//            for (const auto &action : connector.actions())
//            {
//                IGuard iGuard(out);
//                printFunction(out, action);
//            }
//            out.printIndent(); out << "}\n";
//
//
//            // Prints the events
//            out.printIndent(); out << "events:"  << "\n";
//            out.printIndent(); out << "{\n";
//            for (const auto &event : connector.events())
//            {
//                IGuard iGuard(out);
//                printFunction(out, event);
//            }
//            out.printIndent(); out << "}\n";
//        }
//
//        out.printIndent(); out << "}\n";

        return out;
    }

    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const cPerformer::ConnectorInstanceMap &cInsMap)
    {
        using IGuard = clMisc::IndentGuard<Sink>;

        for (const auto &insBase : cInsMap)
        {
            DYN_PRINT(cPerformer::ConnectorInstance, insBase)
            else DYN_PRINT(cPerformer::ConnectorInstanceGroup, insBase)
            else abort();
        }

        return out;
    }

    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const cPerformer::ConnectionPerformer &cPerformer)
    {
//        bool first;
//
//        using IGuard = clMisc::IndentGuard<Sink>;
//        out.printIndent(); out << cPerformer.name() << ":\n";
//
//        START_SCOPE
//
//            out.printIndent(); out << "ArgAliases:"  << "\n";
//
//            START_SCOPE
//                for (const auto &arg : cPerformer.arguments())
//                {
//                    out.printIndent(); out << arg.name()  << "\n";
//                    out.printIndent(); out << "- desc: " << arg.description().value  << "\n";
//                }
//            END_SCOPE
//
//
//            out.printIndent(); out << "ConnectorAliases:"  << "\n";
//            START_SCOPE
//                for (const auto &connAlias : cPerformer.connectorAliases())
//                {
//                    out.printIndent(); out << connAlias.name()  << "\n";
//
//                    START_SCOPE
//                        for (const auto &caArgAlias : connAlias.argAliases())
//                        {
//                            out.printIndent(); out << "arg: " << caArgAlias.name() << " --> alias: "
//                                    << caArgAlias.argRef().value << "\n";
//                        }
//                    END_SCOPE
//                }
//            END_SCOPE
//

//            out.printIndent(); out << "AProvCreators:"  << "\n";
//            START_SCOPE
//                for (const auto &creator : cPerformer.aProvCreators())
//                {
//                    out.printIndent(); out << creator.name()  << "\n";
//                    START_SCOPE
//                        out.printIndent(); out << "requires: [";
//                        first = true;
//                        for (const auto &argument : creator.requires())
//                        {
//                            if (first) first = false;
//                            else out << ", ";
//                            out << argument.name();
//                        }
//                        out << "]\n";
//
//                        out.printIndent(); out << "provides: [";
//                        first = true;
//                        for (const auto &argument : creator.provides())
//                        {
//                            if (first) first = false;
//                            else out << ", ";
//                            out << argument.name();
//                        }
//                        out << "]\n";
//                    END_SCOPE
//                }
//            END_SCOPE
//
//            out.printIndent(); out << "ConnectorInstances:\n";
//            START_SCOPE
//                out << cPerformer.connInstances();
//            END_SCOPE
//        END_SCOPE

        return out;
    }


    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const cPerformer::ConnectorInstance &instance)
    {
        using IGuard = clMisc::IndentGuard<Sink>;

        out.printIndent(); out << instance.name() << ": " << instance.connAlias().value << "\n";

        START_SCOPE
            for (const auto &eCall : instance.events())
            {
                out.printIndent(); out << eCall.name() << "\n";

                START_SCOPE
                    out.printIndent(); out << "Creators: ";
                    const auto &creators = eCall.aProvCreators();
                    if (!creators.empty())
                    {
                        bool first = true;
                        for (const auto &creator : creators)
                        {
                            if (first) first = false;
                            else out << ", ";

                            out << creator.name();
                        }
                    }
                    out << "\n";

                    out.printIndent(); out << "Actions: \n";
                    START_SCOPE
                        for (const auto &dest : eCall.actions())
                        {
                            out.printIndent(); out << dest.connInstance().value.getStringRep() << "." << dest.action().value;

                            out << "\n";
                        }
                    END_SCOPE
                END_SCOPE
            }
        END_SCOPE

        return out;
    }

    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const cPerformer::ConnectorInstanceGroup &group)
    {
        using IGuard = clMisc::IndentGuard<Sink>;

        out.printIndent(); out << group.name() << "\n";

//        START_SCOPE
//            out << group.connInstances();
//        END_SCOPE

        return out;
    }

    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const NspElement &elem)
    {
        DYN_PRINT(Namespace, elem)
        else DYN_PRINT(connector::Connector, elem)
        else DYN_PRINT(cPerformer::ConnectionPerformer, elem)
        else abort();

        return out;
    }

    template <typename Sink>
    clMisc::SimplePrinter<Sink> &operator<<(clMisc::SimplePrinter<Sink> &out, const Namespace &nsp)
    {
        using IGuard = clMisc::IndentGuard<Sink>;

        if (!nsp.name().empty())
        {
            out.printIndent(); out << nsp.name() << ":\n";
            out.printIndent(); out << "{\n";
            ++out;
        }

        // Prints the elements
        for (const auto &nspElem : nsp)
        {
            out << nspElem;
        }

        if (!nsp.name().empty())
        {
            --out;
            out.printIndent(); out << "}\n";
        }

        return out;
    }
}
MY_NSP_END

#include "nspUndef.hpp"

#undef DYN_PRINT

#endif

