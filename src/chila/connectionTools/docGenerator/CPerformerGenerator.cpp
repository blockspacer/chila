/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//#include "CPerformerGenerator.hpp"
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/algorithm/string/case_conv.hpp>
//#include <boost/assign/list_of.hpp>
//#include <chila/lib/misc/util.hpp>
//#include <chila/lib/misc/RepeatText.hpp>
//#include <boost/bind.hpp>
//#include <chila/connectionTools/lib/tree/namespace.hpp>
//
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define PREFIX libMisc::repeatText(indent, "    ")
//#define INC_INDENT IncIndent incIndent(indent)
//
//#define start_super_table(id, Name) \
//    Closer closer(startTable(boost::assign::list_of \
//        (ColData(id, 80, Name))                     \
//        (ColData("value", 0, ""))                   \
//        ));
//
//#define start_section(title) {Closer closer(startSection(title));
//#define start_section_ex(title, extra) {Closer closer(startSection(title, extra));
////#define start_section_ex(title, id, xmlns) {Closer closer(startSection(title, id, xmlns));
//#define end_section }
//
//#define libMisc chila::lib::misc
//
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    typedef std::vector<std::string> StringVec;
//    namespace cclTree = chila::connectionTools::lib::tree;
//
//    template <typename Object, typename PrintFun>
//    struct GenerateObjectList final: public libMisc::SinkInserter< GenerateObjectList<Object, PrintFun> >
//    {
//        typedef std::vector<Object*> ObjectVec;
//        const ObjectVec &objects;
//        const PrintFun printFun;
//        unsigned indent;
//
//        GenerateObjectList(const ObjectVec &objects, const PrintFun &printFun, unsigned indent) :
//            objects(objects), printFun(printFun), indent(indent) {}
//
//        std::ostream &write(std::ostream &out) const
//        {
//            bool first = true;
//
//            for (const auto *object : objects)
//            {
//                if (first) first = false;
//                else out << ",\n";
//
//                printFun(out, *object, indent);
////                out << PREFIX << printLink(printFun(*object));
//            }
//            return out << (objects.empty() ? "" : "\n");
//        }
//    };
//
//    template <typename Object, typename PrintFun>
//    inline GenerateObjectList<Object, PrintFun> generateObjectList(const std::vector<Object*> &objects,
//            const PrintFun &printFun, unsigned indent)
//    {
//        return GenerateObjectList<Object, PrintFun>(objects, printFun, indent);
//    }
//
//    struct aliasPrinter
//    {
//        void operator()(std::ostream &out, const cclTree::APCArgument &apcArg,
//                unsigned indent) const
//        {
//            out << PREFIX << printLink(apcArg.getAlias());
//        }
//    };
//
//    struct apCreatorPrinter
//    {
//        const cclTree::ArgProviderCreator &operator()(std::ostream &out,
//                const cclTree::FunConnArgProvCreator &fcArgProvCreator, unsigned indent) const
//        {
//            out << PREFIX << printLink(fcArgProvCreator.getCreator());
//        }
//    };
//
//    struct destPrinter
//    {
//        const cclTree::ArgProviderCreator &operator()(std::ostream &out,
//                const cclTree::FunConnDestination &fcDest, unsigned indent) const
//        {
//            out << PREFIX << printLink(fcDest.getInstance()) << "." << printLink(fcDest.getAction());
//        }
//    };
//
//    void CPerformerGenerator::generate()
//    {
//        out << "<?xml version='1.0'?>\n\n";
//        std::string connFullName = cPerformerCreator.getPath().getStringRep();
//
//        // ConnectionPerformer
//        start_section_ex
//        (
//            title,
//            "xmlns='http://docbook.org/ns/docbook' "
//            "xmlns:xi='http://www.w3.org/2001/XInclude' "
//            "version='5.0'"
//        )
//        {
//            // ConnectionPerformer
//            start_section_ex(connFullName, "xml:id='" + connFullName + "'");
//            {
//                start_super_table("section", "Section");
//                {
//                    { Closer closer(startTag("row")); generateArgAliases();           }
//                    { Closer closer(startTag("row")); generateConnectorAliases();     }
//                    { Closer closer(startTag("row")); generateArgProviderCreators();  }
//                    { Closer closer(startTag("row")); generateConnectorInstances();   }
//                }
//            }
//            end_section
//
//            // Connectors ---------------------------------------------------------------------------------------------
//            for (const auto &connFile : connectorFiles)
//            {
//                out << PREFIX << "<xi:include href='" << connFile << "'/>\n";
//            }
//
//        }
//        end_section
//    }
//
//    void CPerformerGenerator::generateArgAliases()
//    {
//        {
//            Closer closer(startTag("entry"));
//            out << "Argument Aliases\n";
//        }
//        {
//            Closer closer(startTag("entry"));
//            {
//                Closer closer(startTable(boost::assign::list_of
//                    (ColData("name", 80, "Name"))
//                    (ColData("desc", 0, "Description"))
//                    ));
//
//                {
//                    cclTree::ArgumentAliasCVec aliases = cPerformerCreator.getArgumentAliases();
//                    for (const auto *alias : aliases)
//                    {
//                        my_assert(alias);
//                        Closer closer(startTag("row", "xml:id='" + alias->getPath().getStringRep() + "'>"));
//                        {
//                            INC_INDENT;
//                            out << PREFIX << "<entry>" << alias->getName() << "</entry>\n"
//                                << PREFIX << "<entry>" << alias->getDescription() << "</entry>\n";
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    void CPerformerGenerator::generateConnectorAliases()
//    {
//        {
//            Closer closer(startTag("entry"));
//            out << "Conector Aliases\n";
//        }
//        {
//            Closer closer(startTag("entry"));
//            {
//                start_super_table("connectorAlias", "Connector Alias");
//
//                cclTree::ConnectorAliasCVec aliases = cPerformerCreator.getConnectorAliases();
//                for (const auto *alias : aliases)
//                {
//                    my_assert(alias);
//                    Closer closer(startTag("row", "xml:id='" + alias->getPath().getStringRep() + "'"));
//                    {
//                        {
//                            Closer closer(startTag("entry"));
//                            out << PREFIX << alias->getName() << ": " << printLink(alias->getConnector(), true);
//                        }
//                        {
//                            Closer closer(startTag("entry"));
//                            {
//                                Closer closer(startTable(boost::assign::list_of
//                                    (ColData("name", 80, "Name"))
//                                    (ColData("alias", 0, "Alias"))
//                                    ));
//                                {
//                                    cclTree::ArgumentAliasLinkCVec links = alias->getLinks();
//                                    for (const auto *link : links)
//                                    {
//                                        my_assert(link);
//                                        Closer closer(startTag("row", "xml:id='" + link->getPath().getStringRep() + "'>"));
//                                        {
//                                            INC_INDENT;
//                                            out << PREFIX << "<entry>" << printLink(link->getArgument()) << "</entry>\n"
//                                                << PREFIX << "<entry>" << printLink(link->getAlias()) << "</entry>\n";
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    void CPerformerGenerator::generateArgProviderCreators()
//    {
//        {
//            Closer closer(startTag("entry"));
//            out << "Argument Provider Creators\n";
//        }
//        {
//            Closer closer(startTag("entry"));
//            {
//                Closer closer(startTable(boost::assign::list_of
//                    (ColData("name", 80, "Name"))
//                    (ColData("requires", 0, "Requires"))
//                    (ColData("provides", 0, "Provides"))
//                    ));
//                {
//                    cclTree::ArgProviderCreatorCVec creators = cPerformerCreator.getArgProviderCreators();
//                    for (const auto *creator : creators)
//                    {
//                        my_assert(creator);
//
//                        Closer closer(startTag("row", "xml:id='" + creator->getPath().getStringRep() + "'>"));
//                        {
//                            INC_INDENT;
//                            out << PREFIX << "<entry>\n"
//                                << incInd(indent) << PREFIX << printLink(*creator) << decInd(indent) << "\n"
//                                << PREFIX << "</entry>\n"
//                                << PREFIX << "<entry>\n"
//                                << generateObjectList
//                                (
//                                    creator->getRequiredArguments().getArguments(),
//                                    aliasPrinter(), indent + 1
//                                )
//                                << PREFIX << "</entry>\n"
//                                << PREFIX << "<entry>\n"
//                                << generateObjectList
//                                (
//                                    creator->getProvidedArguments().getArguments(),
//                                    aliasPrinter(), indent + 1
//                                )
//                                << PREFIX << "</entry>\n";
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    void CPerformerGenerator::generateConnectorInstances()
//    {
//        {
//            Closer closer(startTag("entry"));
//            out << "Connector Instances\n";
//        }
//        {
//            Closer closer(startTag("entry"));
//            {
//                start_super_table("connectorInstance", "Connector Instance")
//                {
//                    cclTree::ConnectorInstanceCVec instances = cPerformerCreator.getConnectorInstances();
//                    for (const auto *instance : instances)
//                    {
//                        my_assert(instance);
//
//                        Closer closer(startTag("row", "xml:id='" + instance->getPath().getStringRep() + "'>"));
//                        {
//                            INC_INDENT;
//                            out << PREFIX << "<entry>" << instance->getName() << ": "
//                                << printLink(instance->getAlias()) << "</entry>\n"
//                                << PREFIX << "<entry>\n";
//                            {
//                                INC_INDENT;
//                                Closer closer(startTable(boost::assign::list_of
//                                    (ColData("event", 80, "Event"))
//                                    (ColData("aProviderCreators", 0, "Argument Provider Creators"))
//                                    (ColData("actions", 0, "Actions"))
//                                    ));
//
//                                cclTree::FunctionConnectionCVec connections = instance->getConnections();
//                                for (const auto *connection : connections)
//                                {
//                                    Closer closer(startTag("row", "xml:id='" + connection->getPath().getStringRep() + "'>"));
//                                    {
//                                        INC_INDENT;
//                                        out << PREFIX << "<entry>\n"
//                                            << incInd(indent) << PREFIX << printLink(connection->getEvent()) << decInd(indent) << "\n"
//                                            << PREFIX << "</entry>\n"
//                                            << PREFIX << "<entry>\n"
//                                            << generateObjectList
//                                            (
//                                                connection->aProvCreators.getCreators(),
//                                                apCreatorPrinter(),
//                                                indent + 1
//                                            )
//                                            << PREFIX << "</entry>\n"
//                                            << PREFIX << "<entry>\n"
//                                            << generateObjectList
//                                            (
//                                                connection->getDestinations(),
//                                                destPrinter(),
//                                                indent + 1
//                                            )
//                                            << PREFIX << "</entry>\n";
//                                    }
//                                }
//                            }
//                            out << PREFIX << "</entry>\n";
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//}}}
