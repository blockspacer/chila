/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "CodeGenerator.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include <chila/connectionTools/lib/tree/util.hpp>

//@TODO Trimear todo

#define INS_DEF_ALIAS(NAME) \
    "#define " << NAME << " CHILA_CONNECTIONTOOLS_LIB_CODEGEN__" << NAME << "\n"

#define INS_UNDEF_ALIAS(NAME) "#undef " << NAME << "\n"

#include "nspDef.hpp"

MY_NSP_START
{
    using StringVec = std::vector<std::string>;
    namespace libMisc = chila::lib::misc;
    namespace cclTree = chila::connectionTools::lib::tree;
    using chila::connectionTools::lib::tree::generateGrouped;



    /** Constructor. */
    CodeGenerator::CodeGenerator(const cclTree::connector::Connector &connector, std::ostream &out) :
        connector(connector), out(out)
    {
        modNspPath = connector.path();
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

    std::string CodeGenerator::argSeqName() const
    {
        std::stringstream str;

        str << cclTree::NspInserter(modNspPath) << "__CONNECTOR_ARGS_" << connector.name();
        return str.str();
    }

    std::string CodeGenerator::funSeqName(const std::string &name) const
    {
        std::string upperName = boost::to_upper_copy(name);
        std::stringstream str;

        str << cclTree::NspInserter(modNspPath) << "__CONNECTOR_" << upperName << "S_" << connector.name();
        return str.str();
    }

    std::string CodeGenerator::funArgECSeqName(const std::string &name, const std::string &prefix, const std::string &funName) const
    {
        std::string upperName = boost::to_upper_copy(name);
        std::stringstream str;

        str << cclTree::NspInserter(modNspPath) << "__CONNECTOR_" << upperName << prefix << connector.name() << "_" << funName;
        return str.str();
    }

    void CodeGenerator::generateArgSeq(const cclTree::connector::ArgumentMap &arguments)
    {
        // Generates the argument defines
        out <<     "\n// Arguments defines\n"
            <<     "#define " << argSeqName();

        generateGrouped
        <
            cclTree::connector::ArgumentGroup,
            cclTree::connector::Argument
        >(2, arguments, true, "", "_",
            [&](unsigned indent, bool first, const std::string &prefix, const cclTree::connector::Argument &argument)
            {
                out << " \\\n    (" << prefix << argument.name() << ")";
            });

        out << "\n";
    }

    template <typename Function, typename Group, typename Map>
    void CodeGenerator::generateFunSeqs(const Map &functions, const std::string &name)
    {
        if (!functions.empty())
        {
            out <<          "\n// " << name << " defines\n"
                <<          "#define " << funSeqName(name);

            generateGrouped<Group, Function>(2, functions, true, "", "_",
                [&](unsigned indent, bool first, const std::string &prefix, const Function &function)
                {
                    out << " \\\n    (" << prefix << function.name() << ")";
                });
            out << "\n" << std::endl;

            generateGrouped<Group, Function>(2, functions, true, "", "_",
                [&](unsigned indent, bool first, const std::string &prefix, const Function &function)
                {
                    out << "#define " << funArgECSeqName(name, "_ARGS_", prefix + function.name()) << " \\\n"
                        << (function.arguments().empty() ? "" :  "    ") << cclTree::ArgListInserter(function, "") << std::endl;
                });
        }
    }

    void CodeGenerator::generateActionEvCalled(const cclTree::connector::ActionMap &functions)
    {
        out <<          "\n// Actions' called events\n";

        generateGrouped<cclTree::connector::ActionGroup, cclTree::connector::Action>(2, functions, true, "", "_",
            [&](unsigned indent, bool first, const std::string &prefix, const cclTree::connector::Action &function)
            {
                out <<      "#define " << funArgECSeqName("ACTION", "_EVCALLED_", prefix + function.name()) << " \\\n"
                    <<      (function.events().empty() ? "" :  "    ") << cclTree::EvCalledInserter(function, "") << "\n" << std::endl;
            });
    }


    void CodeGenerator::generateStrFunSeqs(const std::string &name, bool isAction)
    {
        std::string upperName = boost::to_upper_copy(name),
                    lowerName = boost::to_lower_copy(name);

        out <<     "        // " << name << "s\n"
                   "        struct " << name << "s\n"
                   "        {\n"
            <<     "            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(\n"
            <<     "                " << cclTree::NspInserter(modNspPath) << ", " << upperName << ", " << connector.name() << ")\n\n"
            <<     "            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(\n"
            <<     "                " << cclTree::NspInserter(modNspPath) << ", " << upperName << ", " << connector.name() << ")\n";

        if (isAction)
        {
            out << "\n"
                << "            Actions(Connector &connector) :\n"
                << "                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(\n"
                << "                    " << cclTree::NspInserter(modNspPath) << ", " << connector.name() << ") {}\n";
        }

        out <<     "        } " << lowerName << "s;\n\n";
    };

    /** Generates the header. */
    void CodeGenerator::generateHeader()
    {
        std::string modNameUpper = connector.name();
        boost::to_upper(modNameUpper);

        // Generates the header
        out << "// ******************************************************************\n"
            << "// *                 This is auto-generated code                    *\n"
            << "// *                    - DO NOT MODIFY -                           *\n"
            << "// ******************************************************************\n\n"
            << "#ifndef " << cclTree::NspInserter(modNspPath) << "__" << modNameUpper << "_HPP\n"
            << "#define " << cclTree::NspInserter(modNspPath) << "__" << modNameUpper << "_HPP\n"
            << "\n"
            << "#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS\n"
            << "#undef FUSION_MAX_VECTOR_SIZE\n"
            << "#undef BOOST_MPL_LIMIT_VECTOR_SIZE\n"
            << "#define FUSION_MAX_VECTOR_SIZE 50\n"
            << "#define BOOST_MPL_LIMIT_VECTOR_SIZE 50\n"
            << "#include <boost/call_traits.hpp>\n"
            << "#include <boost/function.hpp>\n"
            << "#include <chila/lib/misc/MemFnExecuter.hpp>\n"
            << "#include <chila/lib/misc/Path.hpp>\n"
            << "#include <string>\n\n"
            << "#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/EventExecuter.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/Connector.hpp>\n"
            << "#include <chila/connectionTools/lib/other/macrosExp.hpp>\n"
            << "#include <chila/connectionTools/lib/codegen/macrosDef.hpp>\n"
            << "#include <chila/lib/misc/macrosExp.hpp>\n\n"
            << "#define MY_BIND_ACTION(name) \\\n"
               "        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name)\n"
            << INS_DEF_ALIAS("DEF_CONNECTOR_ARGUMENT")
            << INS_DEF_ALIAS("DEF_CONNECTOR_FUNCTION")
            << INS_DEF_ALIAS("DEF_ARG_ALIAS")
            << INS_DEF_ALIAS("DEF_ARG_ALIAS_LINK");


        generateArgSeq(connector.arguments());
        generateFunSeqs<cclTree::connector::Event, cclTree::connector::EventGroup>(connector.events(), "Event");
        generateFunSeqs<cclTree::connector::Action, cclTree::connector::ActionGroup>(connector.actions(), "Action");
        generateActionEvCalled(connector.actions());

        out << "\nCHILA_LIB_MISC__DEF_NAMESPACE(" << modNspPath.getNames().size()
            << ", (" << cclTree::PathInserter(modNspPath, ",") << "))" << std::endl;
        out << "{" << std::endl;

    }

    /** Generates the footer. */
    void CodeGenerator::generateFooter()
    {
        unsigned nspCount = modNspPath.getNames().size();
        for (unsigned i = 0; i < nspCount; ++i) out << "}"; out << "\n" << std::endl;
        out << "\n"
            << "#undef MY_BIND_ACTION\n"
            << INS_UNDEF_ALIAS("DEF_CONNECTOR_ARGUMENT")
            << INS_UNDEF_ALIAS("DEF_CONNECTOR_FUNCTION")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS_LINK")
            << "\n#endif" << std::endl;
    }

    /** Generates the Connector. */
    void CodeGenerator::generateConnector()
    {
        // Generates the start of the class
        out << "    /** This class serves as a event and action connector for the connector.\n"
               "      * Connectors should hold an instance of this class and connect their actions\n"
               "      * in the constructor.\n"
               "      */\n"
               "    template <typename _ArgTypes>\n"
               "    struct " << connector.name() << " final: public chila::connectionTools::lib::codegen::ConnectorImpl<" << connector.name() << "<_ArgTypes>>\n"
               "    {\n"
               "        static chila::lib::misc::Path path() { return \"" << connector.path() << "\"" << "; }\n\n"
               "        typedef " << connector.name() << " Connector;\n"
               "        typedef _ArgTypes ArgTypes;\n\n";

        // Generates the argument metadata
        out <<     "        // Arguments\n"
            <<     "        struct Arguments\n"
            <<     "        {\n"
            <<     "            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \\\n"
            <<     "                " << cclTree::NspInserter(modNspPath) << ", " << connector.name() << ")\n"
            <<     "        };\n";

        generateStrFunSeqs("Event", false);

        generateStrFunSeqs("Action", true);

        // Generates the constructor
        out <<     "\n"
            <<     "        " << connector.name() << "() : actions(*this) {}\n";

        // Generates the action metadata and 'bindActions'
        const auto &actions = connector.actions();
        if (!actions.empty())
        {
            out <<   "\n        // Binds the actions to 'target'\n"
                       "        template <typename Target>\n"
                       "        void bindActions(Target &target)\n"
                       "        {\n";

            generateGrouped<cclTree::connector::ActionGroup, cclTree::connector::Action>(3, actions, true, "", "_",
                [&](unsigned indent, bool first, const std::string &prefix, const cclTree::connector::Action &action)
                {
                    out << "            MY_BIND_ACTION(" << prefix + action.name() <<  ");\n";
                });

//            for (const auto &action : actions)
//            {
//                out << "            MY_BIND_ACTION(" << action.name() <<  ", " << action.arguments().size() << ");\n";
//            }
            out <<     "        }\n";
        }

        out << "    };" << std::endl;
    }

}
MY_NSP_END

