/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "CodeGenerator.hpp"
#include <boost/foreach.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/iterator_range.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <boost/lexical_cast.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <chila/connectionTools/lib/tree/types.hpp>
#include <chila/connectionTools/lib/tree/util.hpp>
#include <chila/connectionTools/lib/tree/exceptions.hpp>
#include <boost/bind.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/Construct.hpp>

#include <chila/lib/misc/macrosExp.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <chila/lib/misc/Path.hpp>

#define cclTree chila::connectionTools::lib::tree
#define libMisc chila::lib::misc

#define my_assert CHILA_LIB_MISC__ASSERT

#define FUN_SINK_INSERTER(method, ...) \
    chila::lib::misc::funSinkInserter(boost::bind(&CodeGenerator::method, this, __VA_ARGS__))

#define FUN_SINK_INSERTER2(fun) chila::lib::misc::funSinkInserter([&](std::ostream &out){ fun; })

#define INDENT repeatText(indent, "    ")

#define INS_DEF_ALIAS(NAME) \
    "#define " << NAME << " CHILA_CONNECTIONTOOLS_LIB_CODEGEN__" << NAME << "\n"

#define INS_UNDEF_ALIAS(NAME) "#undef " << NAME << "\n"

#define DEF_DATA_PRINTER(name, exp) \
    template <typename Type> \
    struct Ins_##name final: public chila::lib::misc::SinkInserter< Ins_##name<Type> > \
    { \
        const Type &data; \
        \
        Ins_##name(const Type &data) : data(data) {} \
        \
        template <typename Sink> \
        void write(Sink &sink) const { exp; } \
    }; \
    \
    struct Ins_##name##Constructor \
    { \
        template <typename Type> \
        inline Ins_##name<Type> operator()(const Type &data) const { return Ins_##name<Type>(data); } \
    } name;


#include "nspDef.hpp"

MY_NSP_START
{
    using chila::lib::misc::repeatText;
    using AProvRefRange = boost::iterator_range<cclTree::cPerformer::APCRefMap::const_iterator>;
    using chila::connectionTools::lib::tree::generateGrouped;

    struct delimRep final: public chila::lib::misc::SinkInserter<delimRep>
    {
        libMisc::Path path;
        std::string delim;
        bool upper;

        delimRep(const libMisc::Path &path, const std::string &delim, bool upper) :
            path(path), delim(delim), upper(upper) {}

        std::ostream &write(std::ostream &out) const
        {
            bool first = true;

            for (const auto &name : path.getNames())
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

    template <typename Container, typename Fun>
    void printVec(std::ostream &out, Fun fun, const libMisc::Path &appNsp, const std::string &name, const Container &cont,
            unsigned maxInLine = 5)
    {
        out <<         "#define " << delimRep(appNsp, "_", true) << "__" << name;
        unsigned i = 0;
        for (const auto &vt : cont)
        {
            if (i++ % maxInLine == 0) out << " \\\n    ";
                out <<     "(" << fun(vt) << ")";
        }
        out << "\n\n";
    }

    DEF_DATA_PRINTER(namePrinter, (sink << data.name()));
    DEF_DATA_PRINTER(namePathPrinter, (sink << lib::tree::getImplName(data.name())));
    DEF_DATA_PRINTER(nameDataPrinter, (sink << "(" << data.name() << ")(" << data.value << ")"));
    DEF_DATA_PRINTER(dataPrinter, (sink << data.value));
    DEF_DATA_PRINTER(caArgAliasPrinter, (sink << "(" << data.name() << ")(" << data.cpRef().value.getStringRep("_") << ")"));


    /** Generates the code. */
    void CodeGenerator::generate()
    {
        libMisc::Path appNsp = cPerformer.path();
        std::string appName = appNsp.pop();
        std::string appNameUp = boost::to_upper_copy(appName);

        // **************************************** Header ********************************************

        headerOut <<             "// ******************************************************************\n"
            <<             "// *                 This is auto-generated code                    *\n"
            <<             "// *                    - DO NOT MODIFY -                           *\n"
            <<             "// ******************************************************************\n"
            <<             "\n"
            <<             "#ifndef " << cclTree::NspInserter(appNsp) << "__" << appNameUp << "_HPP\n"
            <<             "#define " << cclTree::NspInserter(appNsp) << "__" << appNameUp << "_HPP\n"
            <<             "\n"
            <<             "#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS\n"
            <<             "#undef FUSION_MAX_VECTOR_SIZE\n"
            <<             "#undef BOOST_MPL_LIMIT_VECTOR_SIZE\n"
            <<             "#define FUSION_MAX_VECTOR_SIZE 50\n"
            <<             "#define BOOST_MPL_LIMIT_VECTOR_SIZE 50\n"
            <<             "#include <boost/call_traits.hpp>\n"
            <<             "#include <chila/lib/misc/Path.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/convert.hpp>\n"
            <<             "#include <chila/connectionTools/lib/codegen/macrosDef.hpp>\n\n"
            <<             "#define CREATE_ARG          CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_ARG\n"
            <<             "#define CREATE_APROVIDER    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_APROVIDER\n"
            <<             "#define PASS_ARG            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_PASS_ARG\n"
            <<             "#define EXECUTE_ACTION      CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_EXECUTE_ACTION\n"
            <<             "#define GET_ARGUMENT        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_GET_ARGUMENT\n"
            <<             "\n\n";

        // ------------------------------- Argument aliases utility macros ------------------------------
        headerOut <<             "// ------------------------------- Argument aliases utility macros ------------------------------------\n"
                           "#define " << delimRep(appNsp, "_", true) << "__ARG_ALIAS_SEQ";
        generateGrouped
        <
            cclTree::cPerformer::ArgumentGroup,
            cclTree::cPerformer::Argument
        >(2, cPerformer.arguments(), true, "", "_",
            [this, &appNsp](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::Argument &argument)
            {
                headerOut << " \\\n    (" << prefix << argument.name() << ")";
            });

        // ------------------------------- ConnectorAliases utility macros ------------------------------
        headerOut <<             "\n\n// ----------------------------- ConnectorAliases utility macros ----------------------------------\n";
        printVec(headerOut, namePrinter, appNsp, "CONN_ALIAS_SEQ", cPerformer.connectorAliases());
        for (const auto &alias : cPerformer.connectorAliases())
        {
            printVec(headerOut, caArgAliasPrinter, appNsp, "CONN_ALIAS_AALINK_SEQ_" + alias.name(), alias.arguments(), 1);
        }
        headerOut << "\n";

        // ------------------------------- ArgumentProvider utility macros-------------------------------
        headerOut <<             "// ----------------------------- ArgumentProvider utility macros ---------------------------------------\n"
                           "#define " << delimRep(appNsp, "_", true) << "__APCREATORS_SEQ";
        generateGrouped
        <
            cclTree::cPerformer::AProviderCreatorGroup,
            cclTree::cPerformer::AProviderCreator
        >(2, cPerformer.aProvCreators(), true, "", "_",
            [this, &appNsp](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::AProviderCreator &creator)
            {
                headerOut << " \\\n    (" << prefix << creator.name() << ")";
            });
        headerOut << "\n\n";

        generateGrouped
        <
            cclTree::cPerformer::AProviderCreatorGroup,
            cclTree::cPerformer::AProviderCreator
        >(2, cPerformer.aProvCreators(), true, "", "_",
            [this, &appNsp](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::AProviderCreator &creator)
            {
                auto name = prefix + creator.name();

                headerOut <<         "// " << name << "\n";

                // Required arguments
                printVec(headerOut, namePathPrinter, appNsp, "ARGPROV_RARG_SEQ_" + name, creator.requires());
                printVec(headerOut, namePathPrinter, appNsp, "ARGPROV_PARG_SEQ_" + name, creator.provides());
            });

        // ----------------------------------- Connector instances utility macros ---------------------------------------
        headerOut <<             "// ----------------------------- Connector instances utility macros ---------------------------------------\n"
                           "#define " << delimRep(appNsp, "_", true) << "__CONN_INSTANCE_SEQ";
        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(2, cPerformer.connInstances(), true, "", "_",
            [&](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                headerOut <<         " \\\n    ((" << cInstance.connAlias().referenced().name() << ")(" << prefix << cInstance.name() << "))";
            });
        headerOut << "\n\n";

        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(2, cPerformer.connInstances(), true, "", "_",
            [&](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                headerOut << "\n#define " << delimRep(appNsp, "_", true)
                            << "__CONN_INSTANCE_ALIAS_OF_" << prefix << cInstance.name()
                            << " " << cInstance.connAlias().referenced().name();
            });
        headerOut << "\n\n";

        // ---------------------------------------- Namespace start    ---------------------------------
        headerOut <<             "// -------------------------------------- Namespace start ----------------------------------------------\n"
            <<             "#include <chila/lib/misc/macrosExp.hpp>\n"
            <<             "\n"
            <<             "CHILA_LIB_MISC__DEF_NAMESPACE(" << appNsp.getNames().size() << ", (" << delimRep(appNsp, ",", false) << "))\n"
            <<             "{\n\n";

        // ************************************** ConnectionPerformer *****************************************
        headerOut <<             "    template <typename ArgTypes, typename Connectors>\n"
            <<             "    struct ConnectionPerformer\n"
            <<             "    {\n"
            <<             "        static chila::lib::misc::Path path() { return \"" << cPerformer.path() << "\"; }\n\n";


        // ------------------------------------ ArgAliases ---------------------------------------
        headerOut <<             "        // ArgAliases\n"
            <<             "        struct ArgAliases\n"
            <<             "        {\n"
            <<             "            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES("
                    << delimRep(appNsp, "_", true) << "__ARG_ALIAS_SEQ)\n"
            <<             "        };\n\n";


        // -------------------------------------- connections ---------------------------------------------
        generateConnections(2);

        // -------------------------------------- ConnInstances -------------------------------------------
        generateConnInstancesClass(2, cPerformer.connInstances());

        // -------------------------------------- connect methods ------------------------------------------
        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(2, cPerformer.connInstances(), true, "", "_",
            [this](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                my_assert(cInstance.name().size() < 120);
                headerOut << "\n"
                    << "        // " << prefix << cInstance.name() << " " << repeatText(120 - cInstance.name().size(), "-") << "\n"
                    << "        template <typename Providers>\n"
                    << "        static void connect_" << prefix << cInstance.name() << "(ConnInstances &cInstances, const Providers &providers)\n"
                    << "        {\n";

                generateConnEventCalls(3, boost::cref(cInstance), prefix + cInstance.name());

                headerOut << "        }\n";
            });

        headerOut <<             "\n"
            <<             "        template <typename Args>\n"
            <<             "        static void connect(const Args &args)\n"
            <<             "        {\n"
            <<             "            ConnInstances cInstances(args.cMap);\n\n";

        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(2, cPerformer.connInstances(), true, "", "_",
            [this](unsigned indent, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                my_assert(cInstance.name().size() < 120);
                headerOut <<         "            connect_" << prefix << cInstance.name() << "(cInstances, args.providers);\n";
            });

        headerOut <<             "        }\n"
            <<             "    };\n\n";

        // **************************************** Footer ***********************************************

        unsigned nspCount = cPerformer.path().getNames().size() - 1;
        for (unsigned i = 0; i < nspCount; ++i) headerOut << "}"; headerOut << "\n\n";

        headerOut << "\n\n"
            << INS_UNDEF_ALIAS("APROVIDER_CREATOR")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS")
            << INS_UNDEF_ALIAS("DEF_ARG_ALIAS_LINK")
            << INS_UNDEF_ALIAS("MAKE_ACTION_VEC")
            << "#undef CREATE_ARG\n"
            << "#undef CREATE_APROVIDER\n"
            << "#undef EXECUTE_ACTION\n"
            << "#undef PASS_ARG\n"
            << "#undef GET_ARGUMENT\n"
            << "#endif" << std::endl;
    }

    void CodeGenerator::generateConnInstancesClass(unsigned indent, const cclTree::cPerformer::ConnectorInstanceMap &cInstances)
    {
        headerOut << INDENT << "// ConnInstances -----------------------------------------------------------------------------------------------------------\n";
        headerOut << INDENT << "struct ConnInstances\n"
            << INDENT << "{\n";

        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(indent, cInstances, true, "", "_",
            [this, indent](unsigned, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                headerOut << INDENT << "    typename Connectors::" << cInstance.connAlias().referenced().name() << " &" << prefix << cInstance.name() << ";\n";
            });

        headerOut << "\n"
            << INDENT << "    ConnInstances(const chila::connectionTools::lib::codegen::ConnectorMap &cMap) :\n";

        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(indent, cInstances, true, "", "_",

            [this, indent](unsigned, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                if (!first) headerOut << ",\n";

                headerOut << INDENT << "        " << prefix << cInstance.name() << "(cMap.get<typename Connectors::"
                        << cInstance.connAlias().referenced().name() << ">(\"" << cclTree::getFullId(cInstance).getStringRep() << "\"))";
            });

        headerOut << "\n"
            << INDENT << "    {}\n"
            << INDENT << "};\n";
    }


    void CodeGenerator::generateConnEventCalls(unsigned indent, const cclTree::cPerformer::ConnectorInstance &connInstance, const std::string &cInstanceName)
    {
        for (const auto &eventCall : connInstance.events())
        {
            generateConnEventCall(indent, cInstanceName, eventCall);
        }
    }

    void CodeGenerator::generateConnEventCall(unsigned indent, const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall)
    {
        auto fullId = getFullId(eventCall.referenced()).getStringRep("_");
        headerOut << INDENT << "cInstances." << connInstanceName << ".events." << fullId << ".addFun(ex_" << connInstanceName << "_" << fullId << "\n"
                  << INDENT << "(\n";

        generateAProvCreators(indent + 1, boost::cref(eventCall));

        if (!eventCall.aProvCreators().empty()) headerOut << INDENT << "    ,\n";

        generateActionVec(indent + 1, connInstanceName, boost::cref(eventCall));

        headerOut << INDENT << "));\n";
    }

    void CodeGenerator::generateAProvCreators(unsigned indent, const cclTree::cPerformer::EventCall &eventCall)
    {
        bool first = true;
        for (const auto &apcRef : eventCall.aProvCreators())
        {
            if (first) first = false;
            else headerOut << ",\n";

            headerOut << INDENT << "providers." << lib::tree::getImplName(apcRef.name());
        }
        if (!first) headerOut << "\n";
    }

    void CodeGenerator::generateActionVec(unsigned indent,
            const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall)
    {
        std::string eventCallName = connInstanceName + "_" + getFullId(eventCall.referenced()).getStringRep("_");

        bool first = true;
        unsigned actionIndex = 0;
        for (const auto &instance : eventCall.actions())
        {
            if (first) first = false;
            else headerOut << ",\n";

            headerOut << INDENT << "cInstances." << cclTree::getFullId(instance.connInstance().referenced()).getStringRep("_")
                                << ".actions." << instance.action().value.getStringRep("_");
        }
        if (!first) headerOut << "\n";
    }


    void CodeGenerator::generateConnections(unsigned indent)
    {
        generateGrouped
        <
            cclTree::cPerformer::ConnectorInstanceGroup,
            cclTree::cPerformer::ConnectorInstance
        >(indent, cPerformer.connInstances(), true, "", "_",
            [this, indent](unsigned, bool first, const std::string &prefix, const cclTree::cPerformer::ConnectorInstance &cInstance)
            {
                for (const auto &eventCall : cInstance.events())
                {
                    generateEventCall(indent, cclTree::getFullId(cInstance).getStringRep("_"), eventCall);
                }
            });
    }

    void CodeGenerator::generateAProvVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
        const cclTree::cPerformer::EventCall &eventCall)
    {
        bool first = true;

        unsigned i = 0;
        for (const auto &aprovRef : eventCall.aProvCreators())
        {
            if (commaSep)
            {
                if (first) first = false;
                else headerOut << ",\n";
            }

            auto apcName = lib::tree::getImplName(aprovRef.name());
            std::string typeName = "APC_" + apcName;
            std::string varName = "apc_" + apcName;

            switch (gen)
            {
                case AAGE_TEMPLATE:         headerOut << INDENT << "typename " << typeName; break;
                case AAGE_FIELD:            headerOut << INDENT << typeName << " " << varName; break;
                case AAGE_ARG:              headerOut << INDENT << "const " << typeName << " &" << varName; break;
                case AAGE_INIT_LIST:        headerOut << INDENT << varName << "(" << varName << ")"; break;
                case AAGE_PASS_ARG_TYPE:    headerOut << INDENT << typeName; break;
                case AAGE_PASS_ARG_VAR:     headerOut << INDENT << varName; break;
                default: abort();
            }

            if (!commaSep) headerOut << ";\n";

            ++i;
        }
   }

    void CodeGenerator::generateActionVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
        const cclTree::cPerformer::EventCall &eventCall)
    {
        bool first = true;
        for (const auto &aInstance : eventCall.actions())
        {
            if (commaSep)
            {
                if (first) first = false;
                else headerOut << ",\n";
            }

            std::string connInstFId = cclTree::getFullId(aInstance.connInstance().referenced()).getStringRep("_");
            std::string typeName = "Action_" + connInstFId + "_" + aInstance.action().value.getStringRep("_");
            std::string varName = "act_" + connInstFId + "_" + aInstance.action().value.getStringRep("_");

            switch (gen)
            {
                case AAGE_TEMPLATE:         headerOut << INDENT << "typename " << typeName; break;
                case AAGE_FIELD:
                case AAGE_ARG:              headerOut << INDENT << "const " << typeName << " &" << varName; break;
                case AAGE_INIT_LIST:        headerOut << INDENT << varName << "(" << varName << ")"; break;
                case AAGE_PASS_ARG_TYPE:    headerOut << INDENT << typeName; break;
                case AAGE_PASS_ARG_VAR:     headerOut << INDENT << varName; break;
                default: abort();
            }

            if (!commaSep) headerOut << ";\n";
        }
        if (commaSep && !first) headerOut << "\n";
    }

    void CodeGenerator::generateApcActionVars(unsigned indent, ApcAcGenEnum gen, bool commaSep,
            const cclTree::cPerformer::EventCall &eventCall)
    {
        generateAProvVars(indent, gen, commaSep, eventCall);

        if (commaSep && !eventCall.aProvCreators().empty())
            headerOut << ",\n";

        generateActionVars(indent, gen, commaSep, eventCall);
    }


    void CodeGenerator::generateEventCall(unsigned indent, const std::string &connInstanceName, const cclTree::cPerformer::EventCall &eventCall)
    {
        const std::string structName = connInstanceName + "_" + getFullId(eventCall.referenced()).getStringRep("_");
        my_assert(structName.size() < 120);

        headerOut << INDENT << "// " << structName << " " << repeatText(120 - structName.size(), "-") << "\n"
            << INDENT << "struct Tag_" << structName << " {};\n\n"
            << INDENT << (eventCall.actions().size() ? "template\n" : "")
            << INDENT << (eventCall.actions().size() ? "<\n" : "")
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 1, AAGE_TEMPLATE, true, boost::cref(eventCall))
            << INDENT << (eventCall.actions().size() ? ">\n" : "")
            << INDENT << "struct Ex_" << structName << "\n"
            << INDENT << "{\n"
            << INDENT << "    typedef void result_type;\n"
            << "\n"
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 1, AAGE_FIELD, false, boost::cref(eventCall))
            << "\n"
            << INDENT << "    Ex_" << structName << "\n"
            << INDENT << "    (\n"
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 2, AAGE_ARG, true, boost::cref(eventCall))
            << INDENT << (eventCall.actions().size() ? "    ) :\n" : "    ) \n")
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 2, AAGE_INIT_LIST, true, boost::cref(eventCall))
            << INDENT << "    {}\n\n"
            << FUN_SINK_INSERTER(generateEventCallOp, indent + 1, boost::cref(eventCall))
            << INDENT << "};\n"
            << "\n"
            << INDENT << (eventCall.actions().size() ? "template\n<\n" : "")
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 1, AAGE_TEMPLATE, true, boost::cref(eventCall))
            << INDENT << (eventCall.actions().size() ? ">\n" : "")
            << INDENT << "inline static Ex_" << structName << "\n"
            << INDENT << (eventCall.actions().size() ? "<\n" : "")
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 1, AAGE_PASS_ARG_TYPE, true, boost::cref(eventCall))
            << INDENT << (eventCall.actions().size() ? ">\n" : "")
            << INDENT << "ex_" << structName << "\n"
            << INDENT << "(\n"
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 1, AAGE_ARG, true, boost::cref(eventCall))
            << INDENT << ")\n"
            << INDENT << "{\n"
            << INDENT << "    return Ex_" << structName << "\n"
            << INDENT << (eventCall.actions().size() ? "    <\n" : "")
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 2, AAGE_PASS_ARG_TYPE, true, boost::cref(eventCall))
            << INDENT << (eventCall.actions().size() ? "    >\n" : "")
            << INDENT << "    (\n"
            << FUN_SINK_INSERTER(generateApcActionVars, indent + 2, AAGE_PASS_ARG_VAR, true, boost::cref(eventCall))
            << INDENT << "    );\n"
            << INDENT << "}\n\n";
    }

    void CodeGenerator::generateEventCallOp(unsigned indent, const cclTree::cPerformer::EventCall &eventCall)
    {
        const auto &args = eventCall.referenced().arguments();

        if (!args.empty())
        {
            headerOut << INDENT << "template\n"
                << INDENT << "<\n"
                << FUN_SINK_INSERTER2(generateEventCallTmplArgs(indent + 1, args))
                << INDENT << ">\n";
        }

        headerOut << INDENT << "void operator()\n"
            << INDENT << "(\n"
            << FUN_SINK_INSERTER2(generateEventCallDeclArgs(indent + 1, args))
            << INDENT << ") const\n"
            << INDENT << "{\n"
            << FUN_SINK_INSERTER2(generateEventCallOpBody(indent + 1, eventCall))
            << INDENT << "}\n";
    }


    // Returns the APC where the argument should be taken, or empty if it should be taken from the event
    template <typename AProvRefRange>
    const cclTree::cPerformer::APCRef *getAPCForArgument(const AProvRefRange &aProvRange, const std::string &cpArg)
    {
        for (const auto &apcRef : aProvRange) //try
        {
            const auto &aaRefMap = apcRef.referenced().provides();

            if (boost::range::find_if
                (
                    aaRefMap,
                    [&cpArg](const cclTree::cPerformer::ArgRefV &argRef) { return argRef.name() == cpArg; }
                ) != aaRefMap.end())
                return &apcRef;
        }
//        catch (const cclTree::NodeNotFound&) { /* try next apc */ }

        return nullptr;
    }

    template <typename AProvRefRange>
    std::string getArgText(const AProvRefRange &range, const std::string &cpArg)
    {
        const auto *apcForArg = getAPCForArgument(range, cpArg);
        if (!apcForArg)
        {
            return lib::tree::getImplName(cpArg);
        }
        else
        {
            return "GET_ARGUMENT(" + lib::tree::getImplName(apcForArg->name()) + ", " + lib::tree::getImplName(cpArg) + ")";
        }
    }

    void generateAPCArgs(std::ostream &out, unsigned indent, const AProvRefRange &aProvRange)
    {
        my_assert(!aProvRange.empty());

        using AProvRefRangeRev = boost::reversed_range<const AProvRefRange>;
        AProvRefRangeRev revRange = aProvRange | boost::adaptors::reversed;

        const auto &apcRef = *revRange.begin();

        bool first = true;
        for (const auto &reqAlias : apcRef.referenced().requires())
        {
            if (first) first = false;
            else out << ",\n";

            AProvRefRangeRev revRangePOne =  revRange;
            revRangePOne.advance_begin(1);

            out << INDENT << getArgText(revRangePOne, reqAlias.name());
        }
        if (!first) out << "\n";
    }

    void generateActionCall(std::ostream &out, unsigned indent,
        const AProvRefRange &aProvRange, const cclTree::cPerformer::ActionInstance &action)
    {
        auto cInsFullId = cclTree::getFullId(action.connInstance().referenced()).getStringRep("_");

        out << INDENT << "// " << cInsFullId << ".actions." << action.action().value << "\n"
            << INDENT << "EXECUTE_ACTION\n"
            << INDENT << "(\n"
            << INDENT << "    " << cInsFullId << ", " << action.action().value.getStringRep("_") << ",\n";

        const auto &arguments =
            action.connInstance().referenced().connAlias().referenced().arguments();

        bool first = true;
        for (const auto &fArg : action.action().referenced().arguments())
        {
            if (first) first = false;
            else out << ",\n";

            auto &cpArg = arguments.get(fArg.name()).cpRef().value;

            out << INDENT << "    PASS_ARG(" << cInsFullId << ", " << action.action().value.getStringRep("_") << ", "
                    << chila::lib::misc::Path(fArg.name(), ":").getStringRep("_") << ", " << getArgText(aProvRange, cpArg.getStringRep(":")) << ")";
        }
        if (!first) out << "\n";

        out << INDENT << ");\n\n";
    }

    using NeededArgsMap = std::map<chila::lib::misc::Path, chila::lib::misc::Path>;
    NeededArgsMap getNeededCPArgs(const cclTree::cPerformer::EventCall &eventCall)
    {
        NeededArgsMap cpArgs, ret;

        const auto &evCAArgAliases =
            eventCall.parent<cclTree::cPerformer::EventCallMap>()
                     .parent<cclTree::cPerformer::ConnectorInstance>().connAlias().referenced().arguments();


        for (const auto &arg : eventCall.referenced().arguments())
        {
            auto &cpArg = evCAArgAliases.get(arg.name()).cpRef().value;
            cpArgs.insert({cpArg, chila::lib::misc::Path(arg.name(), ":")});
        }

        for (auto &apc : eventCall.aProvCreators())
        {
            for (auto &arg : apc.referenced().requires())
            {
                auto argName = chila::lib::misc::Path(arg.name(), ":");
                auto it = cpArgs.find(argName);
                if (it != cpArgs.end())
                    ret.insert(*it);
            }
        }

        for (auto &action : eventCall.actions())
        {
            const auto &acCAArgAliases =
                action.connInstance().referenced().connAlias().referenced().arguments();

            for (auto &arg : action.action().referenced().arguments())
            {
                auto &cpArg = acCAArgAliases.get(arg.name()).cpRef().value;

                auto it = cpArgs.find(cpArg);
                if (it != cpArgs.end())
                    ret.insert(*it);
            }
        }

        return ret;
    }

    void CodeGenerator::generateEventCallOpBody(unsigned indent, const cclTree::cPerformer::EventCall &eventCall)
    {
//        const auto &caArgAliases =
//            eventCall.parent<cclTree::cPerformer::EventCallMap>()
//                     .parent<cclTree::cPerformer::ConnectorInstance>().connAlias().referenced().arguments();

        headerOut << INDENT << "// Arguments -----------------------------------------------------------------\n";
        auto neededArgs = getNeededCPArgs(eventCall);
        for (const auto &vt : neededArgs)
        {
            headerOut << INDENT << "CREATE_ARG(" << vt.second.getStringRep("_") << ", " << vt.first.getStringRep("_") << ");\n";
        }

        headerOut << "\n"
            << INDENT << "// Providers -----------------------------------------------------------------\n";
        const auto &apcRefVec = eventCall.aProvCreators();
        for (auto it = apcRefVec.begin(); it != apcRefVec.end(); ++it)
        {
            const auto &apc = *it;

            auto apcName = lib::tree::getImplName(apc.name());

            auto itAv = it;
            ++itAv;

            headerOut << INDENT << "CREATE_APROVIDER\n"
                << INDENT << "(\n"
                << INDENT << "    " << apcName << ",\n"
                << FUN_SINK_INSERTER2(generateAPCArgs(out, indent + 1, AProvRefRange(apcRefVec.begin(), itAv)))
                << INDENT << ");\n\n";
        }

        headerOut << INDENT << "// Actions -------------------------------------------------------------------\n";
        for (const auto &aInst : eventCall.actions())
        {
            generateActionCall(headerOut, indent,  apcRefVec, aInst);
        }
    }

    void CodeGenerator::generateEventCallTmplArgs(unsigned indent, const cclTree::connector::ArgRefMap &args)
    {
        unsigned i;
        for (i = 0; i < args.size(); ++i)
        {
            if (i) headerOut << ",\n";
            headerOut << INDENT << "typename InArg" << i;
        }
        if (i) headerOut << "\n";
    }

    void CodeGenerator::generateEventCallDeclArgs(unsigned indent, const cclTree::connector::ArgRefMap &args)
    {
        if (args.empty()) return;

        unsigned i = 0;
        for (const auto &arg : args)
        {
            if (i) headerOut << ",\n";

            headerOut << INDENT << "const InArg" << i << " &" << chila::lib::misc::Path(arg.name(), ":").getStringRep("_") << "_in";

            ++i;
        }
        if (i) headerOut << "\n";
    }
}
MY_NSP_END
