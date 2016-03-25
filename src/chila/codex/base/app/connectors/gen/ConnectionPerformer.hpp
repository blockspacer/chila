// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/call_traits.hpp>
#include <chila/lib/misc/Path.hpp>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <chila/connectionTools/lib/codegen/convert.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define CREATE_ARG          CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_ARG
#define CREATE_APROVIDER    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_APROVIDER
#define PASS_ARG            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_PASS_ARG
#define EXECUTE_ACTION      CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_EXECUTE_ACTION
#define GET_ARGUMENT        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_GET_ARGUMENT


// ------------------------------- Argument aliases utility macros ------------------------------------
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ \
    (notebook_tabName) \
    (notebook_tabTooltip) \
    (notebook_tabWidget) \
    (nullObject) \
    (cmdNetServer_clientId) \
    (cmdNetServer_rcvBuffer) \
    (cmdNetServer_sndBuffer) \
    (cmdNetServer_endpoint) \
    (cmdNetServer_address) \
    (cmdNetServer_host) \
    (cmdNetServer_msgId) \
    (cmdNetServer_funPath) \
    (cmdNetServer_funArgs) \
    (cmdNetServer_message) \
    (cmdNetServer_msgBuffer) \
    (errorMsg) \
    (actionPath)

// ----------------------------- ConnectorAliases utility macros ----------------------------------
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_SEQ \
    (Application)(MainWindow)(CmdNetServer)(CmdNetTextMsgCreator)(FunDynExecuter) \
    (FunDynXMLParser)(FileChooser)(ActionExecuter)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_Application \
    ((notebook:tabName)(notebook_tabName)) \
    ((notebook:tabWidget)(notebook_tabWidget))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_MainWindow \
    ((notebook:tabName)(notebook_tabName)) \
    ((notebook:tabWidget)(notebook_tabWidget)) \
    ((actionPath)(actionPath)) \
    ((notebook:tabTooltip)(notebook_tabTooltip))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_CmdNetServer \
    ((clientId)(cmdNetServer_clientId)) \
    ((recvBuffer)(cmdNetServer_rcvBuffer)) \
    ((sndBuffer)(cmdNetServer_sndBuffer)) \
    ((errorMsg)(errorMsg)) \
    ((endpoint)(cmdNetServer_endpoint)) \
    ((address)(cmdNetServer_address)) \
    ((host)(cmdNetServer_host))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_CmdNetTextMsgCreator \
    ((sessionId)(cmdNetServer_clientId)) \
    ((buffer)(cmdNetServer_rcvBuffer)) \
    ((msgId)(cmdNetServer_msgId)) \
    ((errorMsg)(errorMsg)) \
    ((message)(cmdNetServer_msgBuffer))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FunDynExecuter \
    ((funPath)(cmdNetServer_funPath)) \
    ((arguments)(cmdNetServer_funArgs)) \
    ((errorMsg)(errorMsg))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FunDynXMLParser \
    ((text)(cmdNetServer_message)) \
    ((funPath)(cmdNetServer_funPath)) \
    ((arguments)(cmdNetServer_funArgs)) \
    ((errorMsg)(errorMsg))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FileChooser \
    ((errorMsg)(errorMsg))

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_ActionExecuter \
    ((actionPath)(actionPath))


// ----------------------------- ArgumentProvider utility macros ---------------------------------------
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__APCREATORS_SEQ \
    (nullObjectCreator) \
    (cmdNetServer_msgCreatorFromBuff)

// nullObjectCreator
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARGPROV_RARG_SEQ_nullObjectCreator

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARGPROV_PARG_SEQ_nullObjectCreator \
    (nullObject)

// cmdNetServer_msgCreatorFromBuff
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARGPROV_RARG_SEQ_cmdNetServer_msgCreatorFromBuff \
    (cmdNetServer_msgBuffer)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARGPROV_PARG_SEQ_cmdNetServer_msgCreatorFromBuff \
    (cmdNetServer_message)

// ----------------------------- Connector instances utility macros ---------------------------------------
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ \
    ((Application)(base_application)) \
    ((MainWindow)(base_mainWindow)) \
    ((FunDynExecuter)(base_appCommand_funDynExecuter)) \
    ((FunDynXMLParser)(base_appCommand_funDynXMLParser)) \
    ((CmdNetTextMsgCreator)(base_appCommand_msgCreator)) \
    ((CmdNetServer)(base_appCommand_netServer)) \
    ((ActionExecuter)(base_actionExecuter)) \
    ((FileChooser)(base_fileChooser_open)) \
    ((FileChooser)(base_fileChooser_saveAs))


#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_application Application
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_mainWindow MainWindow
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_appCommand_funDynExecuter FunDynExecuter
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_appCommand_funDynXMLParser FunDynXMLParser
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_appCommand_msgCreator CmdNetTextMsgCreator
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_appCommand_netServer CmdNetServer
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_actionExecuter ActionExecuter
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_fileChooser_open FileChooser
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_fileChooser_saveAs FileChooser

// -------------------------------------- Namespace start ----------------------------------------------
#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,codex,base,app,connectors,gen))
{

    template <typename ArgTypes, typename Connectors>
    struct ConnectionPerformer
    {
        static chila::lib::misc::Path path() { return "chila.codex.base.app.connectors.gen.ConnectionPerformer"; }

        // ArgAliases
        struct ArgAliases
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES(CHILA_CODEX_BASE_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ)
        };

        // base_mainWindow_projectButtonPressed ------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_projectButtonPressed {};

                                struct Ex_base_mainWindow_projectButtonPressed
        {
            typedef void result_type;


            Ex_base_mainWindow_projectButtonPressed
            (
            ) 
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
            }
        };

                        inline static Ex_base_mainWindow_projectButtonPressed
                        ex_base_mainWindow_projectButtonPressed
        (
        )
        {
            return Ex_base_mainWindow_projectButtonPressed
                            (
            );
        }

        // base_mainWindow_actionExecuted ------------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_actionExecuted {};

        template
        <
            typename Action_base_actionExecuter_execute
        >
        struct Ex_base_mainWindow_actionExecuted
        {
            typedef void result_type;

            const Action_base_actionExecuter_execute &act_base_actionExecuter_execute;

            Ex_base_mainWindow_actionExecuted
            (
                const Action_base_actionExecuter_execute &act_base_actionExecuter_execute
            ) :
                act_base_actionExecuter_execute(act_base_actionExecuter_execute)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &actionPath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(actionPath, actionPath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_actionExecuter.actions.execute
                EXECUTE_ACTION
                (
                    base_actionExecuter, execute,
                    PASS_ARG(base_actionExecuter, execute, actionPath, actionPath)
                );

            }
        };

        template
<
            typename Action_base_actionExecuter_execute
        >
        inline static Ex_base_mainWindow_actionExecuted
        <
            Action_base_actionExecuter_execute
        >
        ex_base_mainWindow_actionExecuted
        (
            const Action_base_actionExecuter_execute &act_base_actionExecuter_execute
        )
        {
            return Ex_base_mainWindow_actionExecuted
            <
                Action_base_actionExecuter_execute
            >
            (
                act_base_actionExecuter_execute
            );
        }

        // base_appCommand_funDynXMLParser_parsed ----------------------------------------------------------------------------------
        struct Tag_base_appCommand_funDynXMLParser_parsed {};

        template
        <
            typename Action_base_appCommand_funDynExecuter_execute
        >
        struct Ex_base_appCommand_funDynXMLParser_parsed
        {
            typedef void result_type;

            const Action_base_appCommand_funDynExecuter_execute &act_base_appCommand_funDynExecuter_execute;

            Ex_base_appCommand_funDynXMLParser_parsed
            (
                const Action_base_appCommand_funDynExecuter_execute &act_base_appCommand_funDynExecuter_execute
            ) :
                act_base_appCommand_funDynExecuter_execute(act_base_appCommand_funDynExecuter_execute)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &funPath_in,
                const InArg1 &arguments_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(arguments, cmdNetServer_funArgs);
                CREATE_ARG(funPath, cmdNetServer_funPath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_appCommand_funDynExecuter.actions.execute
                EXECUTE_ACTION
                (
                    base_appCommand_funDynExecuter, execute,
                    PASS_ARG(base_appCommand_funDynExecuter, execute, funPath, cmdNetServer_funPath),
                    PASS_ARG(base_appCommand_funDynExecuter, execute, arguments, cmdNetServer_funArgs)
                );

            }
        };

        template
<
            typename Action_base_appCommand_funDynExecuter_execute
        >
        inline static Ex_base_appCommand_funDynXMLParser_parsed
        <
            Action_base_appCommand_funDynExecuter_execute
        >
        ex_base_appCommand_funDynXMLParser_parsed
        (
            const Action_base_appCommand_funDynExecuter_execute &act_base_appCommand_funDynExecuter_execute
        )
        {
            return Ex_base_appCommand_funDynXMLParser_parsed
            <
                Action_base_appCommand_funDynExecuter_execute
            >
            (
                act_base_appCommand_funDynExecuter_execute
            );
        }

        // base_appCommand_msgCreator_messageObtained ------------------------------------------------------------------------------
        struct Tag_base_appCommand_msgCreator_messageObtained {};

        template
        <
            typename APC_cmdNetServer_msgCreatorFromBuff,
            typename Action_base_appCommand_funDynXMLParser_take
        >
        struct Ex_base_appCommand_msgCreator_messageObtained
        {
            typedef void result_type;

            APC_cmdNetServer_msgCreatorFromBuff apc_cmdNetServer_msgCreatorFromBuff;
            const Action_base_appCommand_funDynXMLParser_take &act_base_appCommand_funDynXMLParser_take;

            Ex_base_appCommand_msgCreator_messageObtained
            (
                const APC_cmdNetServer_msgCreatorFromBuff &apc_cmdNetServer_msgCreatorFromBuff,
                const Action_base_appCommand_funDynXMLParser_take &act_base_appCommand_funDynXMLParser_take
            ) :
                apc_cmdNetServer_msgCreatorFromBuff(apc_cmdNetServer_msgCreatorFromBuff),
                act_base_appCommand_funDynXMLParser_take(act_base_appCommand_funDynXMLParser_take)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &message_in,
                const InArg1 &sessionId_in,
                const InArg2 &msgId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(message, cmdNetServer_msgBuffer);

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    cmdNetServer_msgCreatorFromBuff,
                    cmdNetServer_msgBuffer
                );

                // Actions -------------------------------------------------------------------
                // base_appCommand_funDynXMLParser.actions.take
                EXECUTE_ACTION
                (
                    base_appCommand_funDynXMLParser, take,
                    PASS_ARG(base_appCommand_funDynXMLParser, take, text, GET_ARGUMENT(cmdNetServer_msgCreatorFromBuff, cmdNetServer_message))
                );

            }
        };

        template
<
            typename APC_cmdNetServer_msgCreatorFromBuff,
            typename Action_base_appCommand_funDynXMLParser_take
        >
        inline static Ex_base_appCommand_msgCreator_messageObtained
        <
            APC_cmdNetServer_msgCreatorFromBuff,
            Action_base_appCommand_funDynXMLParser_take
        >
        ex_base_appCommand_msgCreator_messageObtained
        (
            const APC_cmdNetServer_msgCreatorFromBuff &apc_cmdNetServer_msgCreatorFromBuff,
            const Action_base_appCommand_funDynXMLParser_take &act_base_appCommand_funDynXMLParser_take
        )
        {
            return Ex_base_appCommand_msgCreator_messageObtained
            <
                APC_cmdNetServer_msgCreatorFromBuff,
                Action_base_appCommand_funDynXMLParser_take
            >
            (
                apc_cmdNetServer_msgCreatorFromBuff,
                act_base_appCommand_funDynXMLParser_take
            );
        }

        // base_appCommand_netServer_msgRead ---------------------------------------------------------------------------------------
        struct Tag_base_appCommand_netServer_msgRead {};

        template
        <
            typename Action_base_appCommand_msgCreator_takeBuffer
        >
        struct Ex_base_appCommand_netServer_msgRead
        {
            typedef void result_type;

            const Action_base_appCommand_msgCreator_takeBuffer &act_base_appCommand_msgCreator_takeBuffer;

            Ex_base_appCommand_netServer_msgRead
            (
                const Action_base_appCommand_msgCreator_takeBuffer &act_base_appCommand_msgCreator_takeBuffer
            ) :
                act_base_appCommand_msgCreator_takeBuffer(act_base_appCommand_msgCreator_takeBuffer)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &clientId_in,
                const InArg1 &recvBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(clientId, cmdNetServer_clientId);
                CREATE_ARG(recvBuffer, cmdNetServer_rcvBuffer);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_appCommand_msgCreator.actions.takeBuffer
                EXECUTE_ACTION
                (
                    base_appCommand_msgCreator, takeBuffer,
                    PASS_ARG(base_appCommand_msgCreator, takeBuffer, buffer, cmdNetServer_rcvBuffer),
                    PASS_ARG(base_appCommand_msgCreator, takeBuffer, sessionId, cmdNetServer_clientId)
                );

            }
        };

        template
<
            typename Action_base_appCommand_msgCreator_takeBuffer
        >
        inline static Ex_base_appCommand_netServer_msgRead
        <
            Action_base_appCommand_msgCreator_takeBuffer
        >
        ex_base_appCommand_netServer_msgRead
        (
            const Action_base_appCommand_msgCreator_takeBuffer &act_base_appCommand_msgCreator_takeBuffer
        )
        {
            return Ex_base_appCommand_netServer_msgRead
            <
                Action_base_appCommand_msgCreator_takeBuffer
            >
            (
                act_base_appCommand_msgCreator_takeBuffer
            );
        }

        // base_actionExecuter_file_open -------------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_open {};

        template
        <
            typename Action_base_fileChooser_open_open
        >
        struct Ex_base_actionExecuter_file_open
        {
            typedef void result_type;

            const Action_base_fileChooser_open_open &act_base_fileChooser_open_open;

            Ex_base_actionExecuter_file_open
            (
                const Action_base_fileChooser_open_open &act_base_fileChooser_open_open
            ) :
                act_base_fileChooser_open_open(act_base_fileChooser_open_open)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_fileChooser_open.actions.open
                EXECUTE_ACTION
                (
                    base_fileChooser_open, open,
                );

            }
        };

        template
<
            typename Action_base_fileChooser_open_open
        >
        inline static Ex_base_actionExecuter_file_open
        <
            Action_base_fileChooser_open_open
        >
        ex_base_actionExecuter_file_open
        (
            const Action_base_fileChooser_open_open &act_base_fileChooser_open_open
        )
        {
            return Ex_base_actionExecuter_file_open
            <
                Action_base_fileChooser_open_open
            >
            (
                act_base_fileChooser_open_open
            );
        }

        // base_actionExecuter_file_saveAs -----------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_saveAs {};

        template
        <
            typename Action_base_fileChooser_saveAs_open
        >
        struct Ex_base_actionExecuter_file_saveAs
        {
            typedef void result_type;

            const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open;

            Ex_base_actionExecuter_file_saveAs
            (
                const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open
            ) :
                act_base_fileChooser_saveAs_open(act_base_fileChooser_saveAs_open)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_fileChooser_saveAs.actions.open
                EXECUTE_ACTION
                (
                    base_fileChooser_saveAs, open,
                );

            }
        };

        template
<
            typename Action_base_fileChooser_saveAs_open
        >
        inline static Ex_base_actionExecuter_file_saveAs
        <
            Action_base_fileChooser_saveAs_open
        >
        ex_base_actionExecuter_file_saveAs
        (
            const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open
        )
        {
            return Ex_base_actionExecuter_file_saveAs
            <
                Action_base_fileChooser_saveAs_open
            >
            (
                act_base_fileChooser_saveAs_open
            );
        }

        // ConnInstances -----------------------------------------------------------------------------------------------------------
        struct ConnInstances
        {
            typename Connectors::Application &base_application;
            typename Connectors::MainWindow &base_mainWindow;
            typename Connectors::FunDynExecuter &base_appCommand_funDynExecuter;
            typename Connectors::FunDynXMLParser &base_appCommand_funDynXMLParser;
            typename Connectors::CmdNetTextMsgCreator &base_appCommand_msgCreator;
            typename Connectors::CmdNetServer &base_appCommand_netServer;
            typename Connectors::ActionExecuter &base_actionExecuter;
            typename Connectors::FileChooser &base_fileChooser_open;
            typename Connectors::FileChooser &base_fileChooser_saveAs;

            ConnInstances(const chila::connectionTools::lib::codegen::ConnectorMap &cMap) :
                base_application(cMap.get<typename Connectors::Application>("base.application")),
                base_mainWindow(cMap.get<typename Connectors::MainWindow>("base.mainWindow")),
                base_appCommand_funDynExecuter(cMap.get<typename Connectors::FunDynExecuter>("base.appCommand.funDynExecuter")),
                base_appCommand_funDynXMLParser(cMap.get<typename Connectors::FunDynXMLParser>("base.appCommand.funDynXMLParser")),
                base_appCommand_msgCreator(cMap.get<typename Connectors::CmdNetTextMsgCreator>("base.appCommand.msgCreator")),
                base_appCommand_netServer(cMap.get<typename Connectors::CmdNetServer>("base.appCommand.netServer")),
                base_actionExecuter(cMap.get<typename Connectors::ActionExecuter>("base.actionExecuter")),
                base_fileChooser_open(cMap.get<typename Connectors::FileChooser>("base.fileChooser.open")),
                base_fileChooser_saveAs(cMap.get<typename Connectors::FileChooser>("base.fileChooser.saveAs"))
            {}
        };

        // base_application -------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_application(ConnInstances &cInstances, const Providers &providers)
        {
        }

        // base_mainWindow --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_mainWindow(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_mainWindow.events.projectButtonPressed.addFun(ex_base_mainWindow_projectButtonPressed
            (
            ));
            cInstances.base_mainWindow.events.actionExecuted.addFun(ex_base_mainWindow_actionExecuted
            (
                cInstances.base_actionExecuter.actions.execute
            ));
        }

        // base_appCommand_funDynExecuter ----------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_appCommand_funDynExecuter(ConnInstances &cInstances, const Providers &providers)
        {
        }

        // base_appCommand_funDynXMLParser ---------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_appCommand_funDynXMLParser(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_appCommand_funDynXMLParser.events.parsed.addFun(ex_base_appCommand_funDynXMLParser_parsed
            (
                cInstances.base_appCommand_funDynExecuter.actions.execute
            ));
        }

        // base_appCommand_msgCreator --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_appCommand_msgCreator(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_appCommand_msgCreator.events.messageObtained.addFun(ex_base_appCommand_msgCreator_messageObtained
            (
                providers.cmdNetServer_msgCreatorFromBuff
                ,
                cInstances.base_appCommand_funDynXMLParser.actions.take
            ));
        }

        // base_appCommand_netServer ---------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_appCommand_netServer(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_appCommand_netServer.events.msgRead.addFun(ex_base_appCommand_netServer_msgRead
            (
                cInstances.base_appCommand_msgCreator.actions.takeBuffer
            ));
        }

        // base_actionExecuter ----------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_actionExecuter(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_actionExecuter.events.file_open.addFun(ex_base_actionExecuter_file_open
            (
                cInstances.base_fileChooser_open.actions.open
            ));
            cInstances.base_actionExecuter.events.file_saveAs.addFun(ex_base_actionExecuter_file_saveAs
            (
                cInstances.base_fileChooser_saveAs.actions.open
            ));
        }

        // base_fileChooser_open --------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_fileChooser_open(ConnInstances &cInstances, const Providers &providers)
        {
        }

        // base_fileChooser_saveAs ------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_fileChooser_saveAs(ConnInstances &cInstances, const Providers &providers)
        {
        }

        template <typename Args>
        static void connect(const Args &args)
        {
            ConnInstances cInstances(args.cMap);

            connect_base_application(cInstances, args.providers);
            connect_base_mainWindow(cInstances, args.providers);
            connect_base_appCommand_funDynExecuter(cInstances, args.providers);
            connect_base_appCommand_funDynXMLParser(cInstances, args.providers);
            connect_base_appCommand_msgCreator(cInstances, args.providers);
            connect_base_appCommand_netServer(cInstances, args.providers);
            connect_base_actionExecuter(cInstances, args.providers);
            connect_base_fileChooser_open(cInstances, args.providers);
            connect_base_fileChooser_saveAs(cInstances, args.providers);
        }
    };

}}}}}}



#undef APROVIDER_CREATOR
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK
#undef MAKE_ACTION_VEC
#undef CREATE_ARG
#undef CREATE_APROVIDER
#undef EXECUTE_ACTION
#undef PASS_ARG
#undef GET_ARGUMENT
#endif
