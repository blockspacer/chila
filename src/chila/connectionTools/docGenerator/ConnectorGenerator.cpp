/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#include "ConnectorGenerator.hpp"
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/algorithm/string/case_conv.hpp>
//#include <boost/assign/list_of.hpp>
//#include <chila/lib/misc/util.hpp>
//#include <chila/lib/misc/RepeatText.hpp>
//#include <boost/bind.hpp>
//#include <chila/connectionTools/lib/tree/namespace.hpp>
//
////@TODO Trimear todo
//
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//#define PREFIX libMisc::repeatText(indent, "    ")
//#define INC_INDENT IncIndent incIndent(indent)
//
//#define libMisc chila::lib::misc
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    typedef std::vector<std::string> StringVec;
//    namespace cclTree = chila::connectionTools::lib::tree;
//
//    /** Generates the document. */
//    void ConnectorGenerator::generate()
//    {
//        out << "<?xml version='1.0'?>\n\n";
//
//        // Connector
//        {
//            std::string connFullName = connector.getPath().getStringRep();
//            Closer closer(startSection(connFullName, "xml:id='" + connFullName + "'"));
//            out <<         "    <para>" << connector.getDescription() << "</para>\n";
//            {
//                Closer closer(startTable(boost::assign::list_of
//                    (ColData("argument", 80, "Section"))
//                    (ColData("value", 0, ""))
//                    ));
//                {
//                    // Arguments
//                    Closer closer(startTag("row"));
//                    {
//                        {
//                            Closer closer(startTag("entry"));
//                            out << "Arguments\n";
//                        }
//                        Closer closer(startTag("entry"));
//                        {
//                            Closer closer(startTable(boost::assign::list_of
//                                (ColData("name", 80, "Name"))
//                                (ColData("desc", 0, "Description"))
//                                ));
//                            {
//                                cclTree::ArgumentCVec arguments = connector.getArguments();
//                                for (const auto *argument : arguments)
//                                {
//                                    my_assert(argument);
//                                    out << PREFIX << "<row xml:id='"<< *argument << "'>\n";
//                                    {
//                                        INC_INDENT;
//                                        out << PREFIX << "<entry>" << argument->getName() << "</entry>\n"
//                                            << PREFIX << "<entry>" << argument->getDescription() << "</entry>\n";
//                                    }
//                                    out << PREFIX << "</row>\n";
//                                }
//                            }
//                        }
//                    }
//                }
//
//                // Actions
//                generateFunctions(connector.actions.getFunctions(), "Actions");
//
//                // Events
//                generateFunctions(connector.events.getFunctions(), "Events");
//            }
//        }
//    }
//
//    // Generates functions
//    void ConnectorGenerator::generateFunctions(const cclTree::FunctionCVec &functions, const std::string &title)
//    {
//        if (!functions.empty())
//        {
//            Closer closer(startTag("row"));
//            {
//                {
//                    Closer closer(startTag("entry"));
//                    out << title << "\n";
//                }
//                {
//                    Closer closer(startTag("entry"));
//                    {
//                        Closer closer(startTable(boost::assign::list_of
//                            (ColData("name", 80, "Name"))
//                            (ColData("arguments", 0, "Arguments"))
//                            (ColData("desc", 0, "Description"))
//                            ));
//
//                        for (const auto *action : functions)
//                        {
//                            my_assert(action);
//                            out << PREFIX << "<row>\n";
//                            {
//                                INC_INDENT;
//                                out << PREFIX << "<entry xml:id='" << *action << "'>" << action->getName() << "</entry>\n"
//                                    << PREFIX << "<entry>\n";
//
//                                {
//                                    INC_INDENT;
//                                    generateArgumentList(*action);
//                                }
//                                out << PREFIX << "</entry>\n"
//                                    << PREFIX << "<entry>" << action->getDescription() << "</entry>\n";
//
//                            }
//                            out << PREFIX << "</row>\n";
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    /** Generates an argument list. */
//    void ConnectorGenerator::generateArgumentList(const cclTree::Function &fun)
//    {
//        cclTree::FunctionArgumentCVec funArgs = fun.getArguments();
//        bool first = true;
//
//        for (const auto *funArg : funArgs)
//        {
//            assert(funArg);
//
//            if (first) first = false;
//            else out << ",\n";
//
//            out << PREFIX << printLink(funArg->getArgument());
//        }
//        out << "\n";
//    }
//
//}}}
