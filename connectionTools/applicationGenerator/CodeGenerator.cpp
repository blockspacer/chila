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
#include <boost/foreach.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <chila/connectionTools/lib/tree/namespace.hpp>
#include <chila/connectionTools/lib/tree/Application.hpp>
#include <chila/connectionTools/lib/tree/ArgumentAliases.hpp>
#include <chila/connectionTools/lib/tree/ConnectorAliases.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <chila/lib/misc/util.hpp>

#include <chila/lib/misc/macrosDef.hpp>

#define mtLibTree chila::connectionTools::lib::tree
#define libMisc chila::lib::misc

#define INS_DEF_ALIAS(NAME) \
    "#define " << NAME << " CHILA_CONNECTIONTOOLS_LIB_CODEGEN__" << NAME << "\n"

#define INS_UNDEF_ALIAS(NAME) "#undef " << NAME << "\n"

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(3, (chila,connectionTools,connectionsGenerator))
{
    using chila::lib::misc::repeatText;

    struct delimRep : public chila::lib::misc::SinkInserter<delimRep>
    {
        libMisc::Path path;
        std::string delim;
        bool upper;

        delimRep(const libMisc::Path &path, const std::string &delim, bool upper) :
            path(path), delim(delim), upper(upper) {}

        std::ostream &write(std::ostream &out) const
        {
            bool first = true;

            BOOST_FOREACH(const std::string &name, path.getNames())
            {
                if (first) first = false;
                else out << delim;

                if (upper)
                {
                    boost::to_upper_copy(std::ostream_iterator<char,char>(out),
                            std::make_pair(name.begin(), name.end()));
                }
                else
                {
                    out << name;
                }
            }

            return out;
        }
    };



    /** Generates the code. */
    void CodeGenerator::generate()
    {
        libMisc::Path appNsp = app.getPath();
        std::string appName = appNsp.pop();

        // **************************************** Header ********************************************

        out <<             "// ******************************************************************\n"
            <<             "// *                 This is auto-generated code                    *\n"
            <<             "// *                    - DO NOT MODIFY -                           *\n"
            <<             "// ******************************************************************\n"
            <<             "\n"
            <<             "#ifndef " << delimRep(appNsp + appName, "_", true) << "_HPP\n"
            <<             "#define " << delimRep(appNsp + appName, "_", true) << "_HPP\n"
            <<             "\n"
            <<             "#include <boost/mpl/map.hpp>\n"
            <<             "#include <boost/fusion/container/vector.hpp>\n"
            <<             "#include <boost/fusion/include/make_vector.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/util.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/ArgumentProviderCreator.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/macrosDef.hpp>\n"
            <<             "\n"
            <<             "#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE\n"
            <<             INS_DEF_ALIAS("APROVIDER_CREATOR")
            <<             INS_DEF_ALIAS("DEF_ARG_ALIAS")
            <<             INS_DEF_ALIAS("DEF_ARG_ALIAS_LINK")
            <<             "#define MT_CODEGEN_NSP chila::connectionTools::lib::codegen\n\n"
            <<             "#include <chila/lib/misc/macrosDef.hpp>\n"
            <<             "\n"
            <<             "DEF_NAMESPACE(" << appNsp.getNames().size() << ", (" << delimRep(appNsp, ",", false) << "))\n"
            <<             "{\n";

        // ************************************** Application *****************************************
        out <<             "    template <typename Connectors>\n"
            <<             "    struct Application\n"
            <<             "    {\n";

        // ------------------------------------ ArgumentAliases ---------------------------------------
        out <<             "        // ArgAliases\n"
            <<             "        struct ArgAliases\n"
            <<             "        {\n";
        mtLibTree::ArgumentAliasCVec argAliases = app.getArgumentAliases();
        BOOST_FOREACH(const mtLibTree::ArgumentAlias *alias, argAliases)
        {
            assert(alias);
            out <<         "            DEF_ARG_ALIAS(" << alias->getName() << ");\n";
        }
        out <<             "        };\n\n";

        // ----------------------------------- ConnectorAliases ---------------------------------------
        mtLibTree::ConnectorAliasCVec connAliases = app.getConnectorAliases();
        BOOST_FOREACH(const mtLibTree::ConnectorAlias *alias, connAliases)
        {
            assert(alias);
            out <<         "        // " << alias->getName() << "\n"
                <<         "        struct " << alias->getName() << "Desc\n"
                <<         "        {\n"
                <<         "            typedef typename Connectors::" << alias->getName()
                                                                       << " Connector;\n\n"
                <<         "            // arg --> alias\n"
                <<         "            typedef boost::mpl::map\n"
                <<         "            <\n";

            mtLibTree::ArgumentAliasLinkCVec argAliasLinks = alias->getLinks();
            bool first = true;
            BOOST_FOREACH(const mtLibTree::ArgumentAliasLink *link, argAliasLinks)
            {
                if (first) first = false;
                else out << ",\n";

                out <<     "                DEF_ARG_ALIAS_LINK(" << link->getName() << ", "
                        << link->getAliasName() << ")";
            }
            out <<       "\n            > ArgAliasLinks;\n"
                <<         "        };\n\n";
        }

        // ---------------------------------------- ConnectorDescMap ------------------------------------
        out <<             "        // ConnectorDescMap\n"
            <<             "        typedef boost::mpl::map\n"
            <<             "        <\n";
        bool first = true;
        BOOST_FOREACH(const mtLibTree::ConnectorAlias *alias, connAliases)
        {
            if (first) first = false;
            else out << ",\n";

            assert(alias);
            out <<         "            boost::mpl::pair<typename Connectors::" << alias->getName()
                                                           << ", " << alias->getName() << "Desc>";
        }
        out <<           "\n        > ConnectorDescMap;\n\n";

        // ---------------------------------- ArgProviderCreators defines -------------------------------
        mtLibTree::ArgProviderCreatorCVec apCreators = app.getArgProviderCreators();
        BOOST_FOREACH(const mtLibTree::ArgProviderCreator *creator, apCreators)
        {
            assert(creator);
            unsigned nameSize = creator->getName().size();

            out <<         "        // " << creator->getName() << "\n"
                <<         "        #define " << creator->getName() << "Def APROVIDER_CREATOR \\\n"
                <<         "        (                                                             \\\n"
                <<         "            args.providers." << creator->getName() << ","
                                                         << repeatText(57 - nameSize, " ") << "\\\n";

            // Required Arguments
            mtLibTree::APCArgumentCVec requiredArgs = creator->getRequiredArguments().getArguments();
            out <<         "            ";
            unsigned totalSize = 0;
            BOOST_FOREACH(const mtLibTree::APCArgument *arg, requiredArgs)
            {
                const std::string &argName = arg->getName();
                out <<     "(" << argName << ")";
                totalSize += argName.size() + 2;
            }
            out <<         "," << repeatText(57 - totalSize, " ") << "\\\n";

            // Provided Arguments
            mtLibTree::APCArgumentCVec providedArgs = creator->getProvidedArguments().getArguments();
            out <<         "            ";
            totalSize = 0;
            BOOST_FOREACH(const mtLibTree::APCArgument *arg, providedArgs)
            {
                const std::string &argName = arg->getName();
                out <<     "(" << argName << ")";
                totalSize += argName.size() + 2;
            }
            out <<         "" << repeatText(58 - totalSize, " ") << "\\\n";


            out <<         "        )\n\n";
        }

        // -------------------------------------- connect method ------------------------------------------
        out <<             "        template <typename Args>\n"
            <<             "        static void connect(const Args &args)\n"
            <<             "        {\n";
        const mtLibTree::ConnectorInstanceCVec &connInstances = app.getConnectorInstances();
        BOOST_FOREACH(const mtLibTree::ConnectorInstance *instance, connInstances)
        {
            out <<         "            // " << instance->getName() << "\n";

            mtLibTree::FunctionConnectionCVec functionConnections = instance->getConnections();
            BOOST_FOREACH(const mtLibTree::FunctionConnection *connection, functionConnections)
            {
                assert(connection);
                out <<     "            MT_CODEGEN_NSP::bindActions<ConnectorDescMap>\n"
                    <<     "            (\n"
                    <<     "                args.connectors." << instance->getName() << ".events."
                                              << connection->getName() << ",\n"
                    <<     "                boost::fusion::make_vector(";

                bool first = true;
                mtLibTree::FunConnArgProvCreatorCVec creators = connection->aProvCreators.getCreators();
                BOOST_FOREACH(const mtLibTree::FunConnArgProvCreator *creator, creators)
                {
                    if (first) first = false; else out << ", ";

                    out << creator->getName() << "Def";
                }
                out << "),\n";

                out <<     "                boost::fusion::make_vector\n"
                    <<     "                (\n";

                mtLibTree::FunConnDestinationCVec destinations = connection->getDestinations();
                first = true;
                BOOST_FOREACH(const mtLibTree::FunConnDestination *dest, destinations)
                {
                    assert(dest);

                    if (first) first = false;
                    else out << ",\n";
                    out << "                    args.connectors." << dest->getDestInstanceName()
                                                                  << ".actions." << dest->getActionName();
                }

                out <<   "\n                )\n";
                out <<     "            );\n\n";
            }
        }

        out <<             "        }\n";

        // ---------------------------------- ArgProviderCreators undefs ---------------------------------
        BOOST_FOREACH(const mtLibTree::ArgProviderCreator *creator, apCreators)
        {
            assert(creator);
            out <<         "        #undef " << creator->getName() << "Def\n";
        }

        out <<             "    };\n";


        // **************************************** Footer ***********************************************

        unsigned nspCount = app.getPath().getNames().size() - 1;
        for (unsigned i = 0; i < nspCount; ++i) out << "}"; out << "\n\n";

        out << "#include <chila/lib/misc/macrosUndef.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/macrosUndef.hpp>\n\n"
            << "#undef DEF_NAMESPACE\n"
            << INS_UNDEF_ALIAS("APROVIDER_CREATOR")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS_LINK")
            << "#undef MT_CODEGEN_NSP\n\n"
            << "#endif" << std::endl;
    }



}}}
