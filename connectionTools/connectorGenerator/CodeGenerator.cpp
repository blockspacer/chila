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

#include "CodeGenerator.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <chila/connectionTools/lib/tree/namespace.hpp>

//@TODO Trimear todo

#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define mtLibTree chila::connectionTools::lib::tree

#define INS_DEF_ALIAS(NAME) \
    "#define " << NAME << " CHILA_CONNECTIONTOOLS_LIB_CODEGEN__" << NAME << "\n"

#define INS_UNDEF_ALIAS(NAME) "#undef " << NAME << "\n"


DEF_NAMESPACE(3, (chila,connectionTools,baseConnectorCreator))
{
    typedef std::vector<std::string> StringVec;

    /** Constructor. */
    CodeGenerator::CodeGenerator(const mtLibTree::Connector &connector, std::ostream &out) :
        connector(connector), out(out)//, modNspPath(connector.getPath())
    {
        modNspPath = connector.getPath();
        modNspPath.pop();
    }


    /** Generates C++ code corresponding to the connector. */
    void CodeGenerator::generate()
    {
        // Generates the header
        generateHeader();

        // Generates the BaseConnector start
        generateConnector();

        // Generates the footer
        generateFooter();
    }

    /** Generates the header. */
    void CodeGenerator::generateHeader()
    {
        std::string modNameUpper = connector.getName();
        boost::to_upper(modNameUpper);

        // Generates the header
        out << "// ******************************************************************\n"
            << "// *                 This is auto-generated code                    *\n"
            << "// *                    - DO NOT MODIFY -                           *\n"
            << "// ******************************************************************\n\n"
            << "#ifndef "; getGuardRep(out); out << "_" << modNameUpper << "CONNECTOR_HPP\n"
            << "#define "; getGuardRep(out); out << "_" << modNameUpper << "CONNECTOR_HPP\n"
            << "\n"
            << "#include <boost/function.hpp>\n"
            << "#include <boost/mpl/vector.hpp>\n"
            << "#include <chila/lib/misc/MemFnExecuter.hpp>\n"
            << "#include <string>\n\n"
            << "#include <boost/mpl/set.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/macrosDef.hpp>\n"
            << "#include <chila/lib/misc/macrosDef.hpp>\n\n"
            << "#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE\n"
            << "#define MY_BIND_ACTION(name) \\\n"
               "        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name)\n"
            << "#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen\n"
            << INS_DEF_ALIAS("DEF_MODULE_ARGUMENT")
            << INS_DEF_ALIAS("DEF_MODULE_FUNCTION")
            << INS_DEF_ALIAS("DEF_ARG_ALIAS")
            << INS_DEF_ALIAS("DEF_ARG_ALIAS_LINK")
            << "\n";

        out << "DEF_NAMESPACE(" << modNspPath.getNames().size() << ", ("; getDelimRep(out, ","); out << "))" << std::endl;
        out << "{" << std::endl;

    }

    /** Generates the footer. */
    void CodeGenerator::generateFooter()
    {
        unsigned nspCount = modNspPath.getNames().size();
        for (unsigned i = 0; i < nspCount; ++i) out << "}"; out << "\n" << std::endl;
        out << "#include <chila/lib/misc/macrosUndef.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>\n"
            << "#undef DEF_NAMESPACE\n"
            << "#undef MY_BIND_ACTION\n"
            << "#undef MT_CODEGEN_NSP\n"
            << INS_UNDEF_ALIAS("DEF_MODULE_ARGUMENT")
            << INS_UNDEF_ALIAS("DEF_MODULE_FUNCTION")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS_LINK")
            << "\n#endif" << std::endl;
    }

    /** Generates the Connector. */
    void CodeGenerator::generateConnector()
    {
        // Generates the start of the class
        out << "    /** This class serves as a event and action connector for the connector. \n"
               "      * Connectors should hold an instance of this class and connect their actions\n"
               "      * in the constructor. \n"
               "      */\n"
               "    template <typename DataTypes>\n"
               "    struct " << connector.getName() << "\n"
               "    {\n"
               "        typedef " << connector.getName() << " Connector; \n\n";

        // Generates the header code
        BOOST_FOREACH(const std::string &codeLine, connector.headerCode)
        {
            out << "        "  << codeLine << std::endl;
        }

        if (connector.headerCode.size()) out << std::endl;

        // Generates the argument metadata
        out <<     "        // Arguments\n";
        mtLibTree::ArgumentCVec arguments = connector.getArguments();
        BOOST_FOREACH(const mtLibTree::Argument *argument, arguments)
        {
            assert(argument);
            out << "        DEF_MODULE_ARGUMENT(" << argument->getName() << ");\n";
        }

        // Generates the event metadata
        mtLibTree::FunctionCVec events = connector.events.getFunctions();
        if (!events.empty())
        {
            out <<   "\n        // Events\n"
                       "        struct Events\n"
                       "        {\n";
            BOOST_FOREACH(const mtLibTree::Function *event, events)
            {
                assert(event);
                out << "            DEF_MODULE_FUNCTION(" << event->getName();
                generateArgumentList(*event);
                out <<  ");\n";
            }

            out <<     "        } events;\n";
        }

        // Generates the action metadata and 'bindActions'
        mtLibTree::FunctionCVec actions = connector.actions.getFunctions();
        if (!actions.empty())
        {
            out <<   "\n        // Actions\n"
                       "        struct Actions\n"
                       "        {\n";
            BOOST_FOREACH(const mtLibTree::Function *action, actions)
            {
                assert(action);
                out << "            DEF_MODULE_FUNCTION(" << action->getName();
                generateArgumentList(*action);
                out <<  ");\n";
            }
            out <<      "        } actions;\n";

            out <<   "\n        // Binds the actions to 'target'\n"
                       "        template <typename Target>\n"
                       "        void bindActions(Target &target)\n"
                       "        {\n";
            BOOST_FOREACH(const mtLibTree::Function *action, actions)
            {
                assert(action);
                out << "            MY_BIND_ACTION(" << action->getName() <<  ");\n";
            }
            out <<     "        }\n";
        }

        out << "    };" << std::endl;
    }

    /** Generates an argument list. */
    void CodeGenerator::generateArgumentList(const mtLibTree::Function &fun)
    {
        mtLibTree::FunctionArgumentCVec funArgs = fun.getArguments();

        BOOST_FOREACH(const mtLibTree::FunctionArgument *funArg, funArgs)
        {
            assert(funArg);
            out << ", " << funArg->getName();
        }
    }


    void CodeGenerator::getGuardRep(std::ostream &out)
    {
        BOOST_FOREACH(const std::string &name, modNspPath.getNames())
        {
            out << "_";

            boost::to_upper_copy(std::ostream_iterator<char,char>(out),
                    std::make_pair(name.begin(), name.end()));
        }
    }

    void CodeGenerator::getDelimRep(std::ostream &out, const char *delim)
    {
        bool first = true;
        BOOST_FOREACH(const std::string &name, modNspPath.getNames())
        {
            if (first) first = false;
            else out << delim;

            out << name;
        }
    }

}}}
