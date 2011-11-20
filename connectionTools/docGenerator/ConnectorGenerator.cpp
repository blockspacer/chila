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

#include "ConnectorGenerator.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/assign/list_of.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <boost/bind.hpp>
#include <chila/connectionTools/lib/tree/namespace.hpp>

//@TODO Trimear todo

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define PREFIX libMisc::repeatText(indent, "    ")
#define INC_INDENT IncIndent incIndent(indent)

#define libMisc chila::lib::misc

DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
{
    typedef std::vector<std::string> StringVec;
    namespace mtLibTree = chila::connectionTools::lib::tree;

    /** Generates the document. */
    void ConnectorGenerator::generate()
    {
        out << "<?xml version='1.0'?>\n\n";

        // Connector
        {
            std::string connFullName = connector.getPath().getStringRep();
            Closer closer(startSection(connFullName, "xml:id='" + connFullName + "'"));
            out <<         "    <para>" << connector.getDescription() << "</para>\n";
            {
                Closer closer(startTable(boost::assign::list_of
                    (ColData("argument", 80, "Section"))
                    (ColData("value", 0, ""))
                    ));
                {
                    // Arguments
                    Closer closer(startTag("row"));
                    {
                        {
                            Closer closer(startTag("entry"));
                            out << "Arguments\n";
                        }
                        Closer closer(startTag("entry"));
                        {
                            Closer closer(startTable(boost::assign::list_of
                                (ColData("name", 80, "Name"))
                                (ColData("desc", 0, "Description"))
                                ));
                            {
                                mtLibTree::ArgumentCVec arguments = connector.getArguments();
                                BOOST_FOREACH(const mtLibTree::Argument *argument, arguments)
                                {
                                    assert(argument);
                                    out << PREFIX << "<row xml:id='"<< *argument << "'>\n";
                                    {
                                        INC_INDENT;
                                        out << PREFIX << "<entry>" << argument->getName() << "</entry>\n"
                                            << PREFIX << "<entry>" << argument->getDescription() << "</entry>\n";
                                    }
                                    out << PREFIX << "</row>\n";
                                }
                            }
                        }
                    }
                }

                // Actions
                generateFunctions(connector.actions.getFunctions(), "Actions");

                // Events
                generateFunctions(connector.events.getFunctions(), "Events");
            }
        }
    }

    // Generates functions
    void ConnectorGenerator::generateFunctions(const mtLibTree::FunctionCVec &functions, const std::string &title)
    {
        if (!functions.empty())
        {
            Closer closer(startTag("row"));
            {
                {
                    Closer closer(startTag("entry"));
                    out << title << "\n";
                }
                {
                    Closer closer(startTag("entry"));
                    {
                        Closer closer(startTable(boost::assign::list_of
                            (ColData("name", 80, "Name"))
                            (ColData("arguments", 0, "Arguments"))
                            (ColData("desc", 0, "Description"))
                            ));

                        BOOST_FOREACH(const mtLibTree::Function *action, functions)
                        {
                            assert(action);
                            out << PREFIX << "<row>\n";
                            {
                                INC_INDENT;
                                out << PREFIX << "<entry xml:id='" << *action << "'>" << action->getName() << "</entry>\n"
                                    << PREFIX << "<entry>\n";

                                {
                                    INC_INDENT;
                                    generateArgumentList(*action);
                                }
                                out << PREFIX << "</entry>\n"
                                    << PREFIX << "<entry>" << action->getDescription() << "</entry>\n";

                            }
                            out << PREFIX << "</row>\n";
                        }
                    }
                }
            }
        }
    }

    /** Generates an argument list. */
    void ConnectorGenerator::generateArgumentList(const mtLibTree::Function &fun)
    {
        mtLibTree::FunctionArgumentCVec funArgs = fun.getArguments();
        bool first = true;

        BOOST_FOREACH(const mtLibTree::FunctionArgument *funArg, funArgs)
        {
            assert(funArg);

            if (first) first = false;
            else out << ",\n";

            out << PREFIX << printLink(funArg->getArgument());
        }
        out << "\n";
    }

}}}
