/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/mpl/set.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/call_traits.hpp>
#include <boost/fusion/container/vector.hpp>
#include <chila/lib/misc/Path.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <chila/connectionTools/lib/codegen/ActionExecuter.hpp>
#include <chila/connectionTools/lib/codegen/ConnectorMap.hpp>
#include <chila/connectionTools/lib/codegen/convert.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>

#define CREATE_ARG          CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_ARG
#define CREATE_APROVIDER    CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_CREATE_APROVIDER
#define PASS_ARG            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_PASS_ARG
#define EXECUTE_ACTION      CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_EXECUTE_ACTION
#define GET_ARGUMENT        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__CPERF_GET_ARGUMENT


// ------------------------------- Argument aliases utility macros ------------------------------------
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ \
    (moduleName) \
    (filePath) \
    (nodePath) \
    (nodeId) \
    (name) \
    (value) \
    (cToolsPath) \
    (action) \
    (actionList) \
    (errorText) \
    (outputText) \
    (nodePathPair) \
    (openNode) \
    (isExpandable) \
    (textProperties)

// ----------------------------- ConnectorAliases utility macros ----------------------------------
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_ALIAS_SEQ \
    (Logger)(MainWindow)(FileLoader)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_Logger \
    ((moduleName)(moduleName)) \
    ((cToolsPath)(cToolsPath))

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_MainWindow \
    ((moduleName)(moduleName)) \
    ((nodePath)(nodePath)) \
    ((nodeId)(nodeId)) \
    ((value)(value)) \
    ((action)(action)) \
    ((actionList)(actionList)) \
    ((errorText)(errorText)) \
    ((outputText)(outputText)) \
    ((textProperties)(textProperties)) \
    ((openNode)(openNode)) \
    ((isExpandable)(isExpandable))

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FileLoader \
    ((moduleName)(moduleName)) \
    ((filePath)(filePath)) \
    ((nodePath)(nodePath)) \
    ((nodeId)(nodeId)) \
    ((value)(value)) \
    ((cToolsPath)(cToolsPath)) \
    ((action)(action)) \
    ((actionList)(actionList)) \
    ((errorText)(errorText)) \
    ((outputText)(outputText)) \
    ((textProperties)(textProperties)) \
    ((openNode)(openNode)) \
    ((isExpandable)(isExpandable))


// ----------------------------- ArgumentProvider utility macros ---------------------------------------
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__APCREATORS_SEQ \
    (fileLoaderNameProv) \
    (mainWindowNameProv)

// fileLoaderNameProv
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARGPROV_RARG_SEQ_fileLoaderNameProv

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARGPROV_PARG_SEQ_fileLoaderNameProv \
    (moduleName)

// mainWindowNameProv
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARGPROV_RARG_SEQ_mainWindowNameProv

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARGPROV_PARG_SEQ_mainWindowNameProv \
    (moduleName)

// ----------------------------- Connector instances utility macros ---------------------------------------
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ \
    ((Logger)(logger)) \
    ((MainWindow)(mainWindow)) \
    ((FileLoader)(fileLoader))


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_logger Logger
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_mainWindow MainWindow
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_fileLoader FileLoader

// -------------------------------------- Namespace start ----------------------------------------------
#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,designer,app,connectors,gen))
{
    using chila::connectionTools::lib::codegen::actionExecuter;

    template <typename ArgTypes, typename Connectors>
    struct ConnectionPerformer
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.designer.app.connectors.gen.ConnectionPerformer"; }

        // ArgAliases
        struct ArgAliases
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES(CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ)
        };

        // mainWindow_launcher_started ---------------------------------------------------------------------------------------------
        struct Tag_mainWindow_launcher_started {};

        template
        <
            typename APC_mainWindowNameProv,
            typename Action_logger_moduleStarted,
            typename Action_mainWindow_waitEvent
        >
        struct Ex_mainWindow_launcher_started
        {
            typedef void result_type;

            APC_mainWindowNameProv apc_mainWindowNameProv;
            Action_logger_moduleStarted act_logger_moduleStarted;
            Action_mainWindow_waitEvent act_mainWindow_waitEvent;

            Ex_mainWindow_launcher_started
            (
                const APC_mainWindowNameProv &apc_mainWindowNameProv,
                const Action_logger_moduleStarted &act_logger_moduleStarted,
                const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
            ) :
                apc_mainWindowNameProv(apc_mainWindowNameProv),
                act_logger_moduleStarted(act_logger_moduleStarted),
                act_mainWindow_waitEvent(act_mainWindow_waitEvent)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    mainWindowNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleStarted
                EXECUTE_ACTION
                (
                    logger, moduleStarted,
                    PASS_ARG(logger, moduleStarted, moduleName, GET_ARGUMENT(mainWindowNameProv, moduleName))
                );

                // mainWindow.actions.waitEvent
                EXECUTE_ACTION
                (
                    mainWindow, waitEvent,
                );

            }
        };

        template
<
            typename APC_mainWindowNameProv,
            typename Action_logger_moduleStarted,
            typename Action_mainWindow_waitEvent
        >
        inline static Ex_mainWindow_launcher_started
        <
            APC_mainWindowNameProv,
            Action_logger_moduleStarted,
            Action_mainWindow_waitEvent
        >
        ex_mainWindow_launcher_started
        (
            const APC_mainWindowNameProv &apc_mainWindowNameProv,
            const Action_logger_moduleStarted &act_logger_moduleStarted,
            const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
        )
        {
            return Ex_mainWindow_launcher_started
            <
                APC_mainWindowNameProv,
                Action_logger_moduleStarted,
                Action_mainWindow_waitEvent
            >
            (
                apc_mainWindowNameProv,
                act_logger_moduleStarted,
                act_mainWindow_waitEvent
            );
        }

        // mainWindow_launcher_finished --------------------------------------------------------------------------------------------
        struct Tag_mainWindow_launcher_finished {};

        template
        <
            typename APC_mainWindowNameProv,
            typename Action_logger_moduleFinished
        >
        struct Ex_mainWindow_launcher_finished
        {
            typedef void result_type;

            APC_mainWindowNameProv apc_mainWindowNameProv;
            Action_logger_moduleFinished act_logger_moduleFinished;

            Ex_mainWindow_launcher_finished
            (
                const APC_mainWindowNameProv &apc_mainWindowNameProv,
                const Action_logger_moduleFinished &act_logger_moduleFinished
            ) :
                apc_mainWindowNameProv(apc_mainWindowNameProv),
                act_logger_moduleFinished(act_logger_moduleFinished)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    mainWindowNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleFinished
                EXECUTE_ACTION
                (
                    logger, moduleFinished,
                    PASS_ARG(logger, moduleFinished, moduleName, GET_ARGUMENT(mainWindowNameProv, moduleName))
                );

            }
        };

        template
<
            typename APC_mainWindowNameProv,
            typename Action_logger_moduleFinished
        >
        inline static Ex_mainWindow_launcher_finished
        <
            APC_mainWindowNameProv,
            Action_logger_moduleFinished
        >
        ex_mainWindow_launcher_finished
        (
            const APC_mainWindowNameProv &apc_mainWindowNameProv,
            const Action_logger_moduleFinished &act_logger_moduleFinished
        )
        {
            return Ex_mainWindow_launcher_finished
            <
                APC_mainWindowNameProv,
                Action_logger_moduleFinished
            >
            (
                apc_mainWindowNameProv,
                act_logger_moduleFinished
            );
        }

        // mainWindow_actionRequest ------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_actionRequest {};

        template
        <
            typename Action_fileLoader_performAction,
            typename Action_mainWindow_waitEvent
        >
        struct Ex_mainWindow_actionRequest
        {
            typedef void result_type;

            Action_fileLoader_performAction act_fileLoader_performAction;
            Action_mainWindow_waitEvent act_mainWindow_waitEvent;

            Ex_mainWindow_actionRequest
            (
                const Action_fileLoader_performAction &act_fileLoader_performAction,
                const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
            ) :
                act_fileLoader_performAction(act_fileLoader_performAction),
                act_mainWindow_waitEvent(act_mainWindow_waitEvent)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &action_in,
                const InArg2 &value_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(action, action);
                CREATE_ARG(nodePath, nodePath);
                CREATE_ARG(value, value);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.performAction
                EXECUTE_ACTION
                (
                    fileLoader, performAction,
                    PASS_ARG(fileLoader, performAction, nodePath, nodePath),
                    PASS_ARG(fileLoader, performAction, action, action),
                    PASS_ARG(fileLoader, performAction, value, value)
                );

                // mainWindow.actions.waitEvent
                EXECUTE_ACTION
                (
                    mainWindow, waitEvent,
                );

            }
        };

        template
<
            typename Action_fileLoader_performAction,
            typename Action_mainWindow_waitEvent
        >
        inline static Ex_mainWindow_actionRequest
        <
            Action_fileLoader_performAction,
            Action_mainWindow_waitEvent
        >
        ex_mainWindow_actionRequest
        (
            const Action_fileLoader_performAction &act_fileLoader_performAction,
            const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
        )
        {
            return Ex_mainWindow_actionRequest
            <
                Action_fileLoader_performAction,
                Action_mainWindow_waitEvent
            >
            (
                act_fileLoader_performAction,
                act_mainWindow_waitEvent
            );
        }

        // mainWindow_undoRequest --------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_undoRequest {};

        template
        <
            typename Action_fileLoader_undo
        >
        struct Ex_mainWindow_undoRequest
        {
            typedef void result_type;

            Action_fileLoader_undo act_fileLoader_undo;

            Ex_mainWindow_undoRequest
            (
                const Action_fileLoader_undo &act_fileLoader_undo
            ) :
                act_fileLoader_undo(act_fileLoader_undo)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.undo
                EXECUTE_ACTION
                (
                    fileLoader, undo,
                );

            }
        };

        template
<
            typename Action_fileLoader_undo
        >
        inline static Ex_mainWindow_undoRequest
        <
            Action_fileLoader_undo
        >
        ex_mainWindow_undoRequest
        (
            const Action_fileLoader_undo &act_fileLoader_undo
        )
        {
            return Ex_mainWindow_undoRequest
            <
                Action_fileLoader_undo
            >
            (
                act_fileLoader_undo
            );
        }

        // mainWindow_redoRequest --------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_redoRequest {};

        template
        <
            typename Action_fileLoader_redo
        >
        struct Ex_mainWindow_redoRequest
        {
            typedef void result_type;

            Action_fileLoader_redo act_fileLoader_redo;

            Ex_mainWindow_redoRequest
            (
                const Action_fileLoader_redo &act_fileLoader_redo
            ) :
                act_fileLoader_redo(act_fileLoader_redo)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.redo
                EXECUTE_ACTION
                (
                    fileLoader, redo,
                );

            }
        };

        template
<
            typename Action_fileLoader_redo
        >
        inline static Ex_mainWindow_redoRequest
        <
            Action_fileLoader_redo
        >
        ex_mainWindow_redoRequest
        (
            const Action_fileLoader_redo &act_fileLoader_redo
        )
        {
            return Ex_mainWindow_redoRequest
            <
                Action_fileLoader_redo
            >
            (
                act_fileLoader_redo
            );
        }

        // mainWindow_saveRequest --------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_saveRequest {};

        template
        <
            typename Action_fileLoader_save,
            typename Action_mainWindow_waitEvent
        >
        struct Ex_mainWindow_saveRequest
        {
            typedef void result_type;

            Action_fileLoader_save act_fileLoader_save;
            Action_mainWindow_waitEvent act_mainWindow_waitEvent;

            Ex_mainWindow_saveRequest
            (
                const Action_fileLoader_save &act_fileLoader_save,
                const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
            ) :
                act_fileLoader_save(act_fileLoader_save),
                act_mainWindow_waitEvent(act_mainWindow_waitEvent)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.save
                EXECUTE_ACTION
                (
                    fileLoader, save,
                );

                // mainWindow.actions.waitEvent
                EXECUTE_ACTION
                (
                    mainWindow, waitEvent,
                );

            }
        };

        template
<
            typename Action_fileLoader_save,
            typename Action_mainWindow_waitEvent
        >
        inline static Ex_mainWindow_saveRequest
        <
            Action_fileLoader_save,
            Action_mainWindow_waitEvent
        >
        ex_mainWindow_saveRequest
        (
            const Action_fileLoader_save &act_fileLoader_save,
            const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
        )
        {
            return Ex_mainWindow_saveRequest
            <
                Action_fileLoader_save,
                Action_mainWindow_waitEvent
            >
            (
                act_fileLoader_save,
                act_mainWindow_waitEvent
            );
        }

        // mainWindow_actionListRequired -------------------------------------------------------------------------------------------
        struct Tag_mainWindow_actionListRequired {};

        template
        <
            typename Action_fileLoader_giveActionList,
            typename Action_mainWindow_waitEvent
        >
        struct Ex_mainWindow_actionListRequired
        {
            typedef void result_type;

            Action_fileLoader_giveActionList act_fileLoader_giveActionList;
            Action_mainWindow_waitEvent act_mainWindow_waitEvent;

            Ex_mainWindow_actionListRequired
            (
                const Action_fileLoader_giveActionList &act_fileLoader_giveActionList,
                const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
            ) :
                act_fileLoader_giveActionList(act_fileLoader_giveActionList),
                act_mainWindow_waitEvent(act_mainWindow_waitEvent)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.giveActionList
                EXECUTE_ACTION
                (
                    fileLoader, giveActionList,
                    PASS_ARG(fileLoader, giveActionList, nodePath, nodePath)
                );

                // mainWindow.actions.waitEvent
                EXECUTE_ACTION
                (
                    mainWindow, waitEvent,
                );

            }
        };

        template
<
            typename Action_fileLoader_giveActionList,
            typename Action_mainWindow_waitEvent
        >
        inline static Ex_mainWindow_actionListRequired
        <
            Action_fileLoader_giveActionList,
            Action_mainWindow_waitEvent
        >
        ex_mainWindow_actionListRequired
        (
            const Action_fileLoader_giveActionList &act_fileLoader_giveActionList,
            const Action_mainWindow_waitEvent &act_mainWindow_waitEvent
        )
        {
            return Ex_mainWindow_actionListRequired
            <
                Action_fileLoader_giveActionList,
                Action_mainWindow_waitEvent
            >
            (
                act_fileLoader_giveActionList,
                act_mainWindow_waitEvent
            );
        }

        // mainWindow_flowNodesRequired --------------------------------------------------------------------------------------------
        struct Tag_mainWindow_flowNodesRequired {};

        template
        <
            typename Action_fileLoader_requestFlowNodes
        >
        struct Ex_mainWindow_flowNodesRequired
        {
            typedef void result_type;

            Action_fileLoader_requestFlowNodes act_fileLoader_requestFlowNodes;

            Ex_mainWindow_flowNodesRequired
            (
                const Action_fileLoader_requestFlowNodes &act_fileLoader_requestFlowNodes
            ) :
                act_fileLoader_requestFlowNodes(act_fileLoader_requestFlowNodes)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.requestFlowNodes
                EXECUTE_ACTION
                (
                    fileLoader, requestFlowNodes,
                );

            }
        };

        template
<
            typename Action_fileLoader_requestFlowNodes
        >
        inline static Ex_mainWindow_flowNodesRequired
        <
            Action_fileLoader_requestFlowNodes
        >
        ex_mainWindow_flowNodesRequired
        (
            const Action_fileLoader_requestFlowNodes &act_fileLoader_requestFlowNodes
        )
        {
            return Ex_mainWindow_flowNodesRequired
            <
                Action_fileLoader_requestFlowNodes
            >
            (
                act_fileLoader_requestFlowNodes
            );
        }

        // mainWindow_flowNodeSelected ---------------------------------------------------------------------------------------------
        struct Tag_mainWindow_flowNodeSelected {};

        template
        <
            typename Action_fileLoader_showFNodeInfo
        >
        struct Ex_mainWindow_flowNodeSelected
        {
            typedef void result_type;

            Action_fileLoader_showFNodeInfo act_fileLoader_showFNodeInfo;

            Ex_mainWindow_flowNodeSelected
            (
                const Action_fileLoader_showFNodeInfo &act_fileLoader_showFNodeInfo
            ) :
                act_fileLoader_showFNodeInfo(act_fileLoader_showFNodeInfo)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.showFNodeInfo
                EXECUTE_ACTION
                (
                    fileLoader, showFNodeInfo,
                    PASS_ARG(fileLoader, showFNodeInfo, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_fileLoader_showFNodeInfo
        >
        inline static Ex_mainWindow_flowNodeSelected
        <
            Action_fileLoader_showFNodeInfo
        >
        ex_mainWindow_flowNodeSelected
        (
            const Action_fileLoader_showFNodeInfo &act_fileLoader_showFNodeInfo
        )
        {
            return Ex_mainWindow_flowNodeSelected
            <
                Action_fileLoader_showFNodeInfo
            >
            (
                act_fileLoader_showFNodeInfo
            );
        }

        // mainWindow_checkNodes ---------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_checkNodes {};

        template
        <
            typename Action_fileLoader_checkNodes
        >
        struct Ex_mainWindow_checkNodes
        {
            typedef void result_type;

            Action_fileLoader_checkNodes act_fileLoader_checkNodes;

            Ex_mainWindow_checkNodes
            (
                const Action_fileLoader_checkNodes &act_fileLoader_checkNodes
            ) :
                act_fileLoader_checkNodes(act_fileLoader_checkNodes)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.checkNodes
                EXECUTE_ACTION
                (
                    fileLoader, checkNodes,
                );

            }
        };

        template
<
            typename Action_fileLoader_checkNodes
        >
        inline static Ex_mainWindow_checkNodes
        <
            Action_fileLoader_checkNodes
        >
        ex_mainWindow_checkNodes
        (
            const Action_fileLoader_checkNodes &act_fileLoader_checkNodes
        )
        {
            return Ex_mainWindow_checkNodes
            <
                Action_fileLoader_checkNodes
            >
            (
                act_fileLoader_checkNodes
            );
        }

        // mainWindow_expandFlowNode -----------------------------------------------------------------------------------------------
        struct Tag_mainWindow_expandFlowNode {};

        template
        <
            typename Action_fileLoader_expandFlowNode
        >
        struct Ex_mainWindow_expandFlowNode
        {
            typedef void result_type;

            Action_fileLoader_expandFlowNode act_fileLoader_expandFlowNode;

            Ex_mainWindow_expandFlowNode
            (
                const Action_fileLoader_expandFlowNode &act_fileLoader_expandFlowNode
            ) :
                act_fileLoader_expandFlowNode(act_fileLoader_expandFlowNode)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.expandFlowNode
                EXECUTE_ACTION
                (
                    fileLoader, expandFlowNode,
                    PASS_ARG(fileLoader, expandFlowNode, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_fileLoader_expandFlowNode
        >
        inline static Ex_mainWindow_expandFlowNode
        <
            Action_fileLoader_expandFlowNode
        >
        ex_mainWindow_expandFlowNode
        (
            const Action_fileLoader_expandFlowNode &act_fileLoader_expandFlowNode
        )
        {
            return Ex_mainWindow_expandFlowNode
            <
                Action_fileLoader_expandFlowNode
            >
            (
                act_fileLoader_expandFlowNode
            );
        }

        // mainWindow_moveUpRequest ------------------------------------------------------------------------------------------------
        struct Tag_mainWindow_moveUpRequest {};

        template
        <
            typename Action_fileLoader_moveUp
        >
        struct Ex_mainWindow_moveUpRequest
        {
            typedef void result_type;

            Action_fileLoader_moveUp act_fileLoader_moveUp;

            Ex_mainWindow_moveUpRequest
            (
                const Action_fileLoader_moveUp &act_fileLoader_moveUp
            ) :
                act_fileLoader_moveUp(act_fileLoader_moveUp)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.moveUp
                EXECUTE_ACTION
                (
                    fileLoader, moveUp,
                    PASS_ARG(fileLoader, moveUp, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_fileLoader_moveUp
        >
        inline static Ex_mainWindow_moveUpRequest
        <
            Action_fileLoader_moveUp
        >
        ex_mainWindow_moveUpRequest
        (
            const Action_fileLoader_moveUp &act_fileLoader_moveUp
        )
        {
            return Ex_mainWindow_moveUpRequest
            <
                Action_fileLoader_moveUp
            >
            (
                act_fileLoader_moveUp
            );
        }

        // mainWindow_moveDownRequest ----------------------------------------------------------------------------------------------
        struct Tag_mainWindow_moveDownRequest {};

        template
        <
            typename Action_fileLoader_moveDown
        >
        struct Ex_mainWindow_moveDownRequest
        {
            typedef void result_type;

            Action_fileLoader_moveDown act_fileLoader_moveDown;

            Ex_mainWindow_moveDownRequest
            (
                const Action_fileLoader_moveDown &act_fileLoader_moveDown
            ) :
                act_fileLoader_moveDown(act_fileLoader_moveDown)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // fileLoader.actions.moveDown
                EXECUTE_ACTION
                (
                    fileLoader, moveDown,
                    PASS_ARG(fileLoader, moveDown, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_fileLoader_moveDown
        >
        inline static Ex_mainWindow_moveDownRequest
        <
            Action_fileLoader_moveDown
        >
        ex_mainWindow_moveDownRequest
        (
            const Action_fileLoader_moveDown &act_fileLoader_moveDown
        )
        {
            return Ex_mainWindow_moveDownRequest
            <
                Action_fileLoader_moveDown
            >
            (
                act_fileLoader_moveDown
            );
        }

        // fileLoader_launcher_started ---------------------------------------------------------------------------------------------
        struct Tag_fileLoader_launcher_started {};

        template
        <
            typename APC_fileLoaderNameProv,
            typename Action_logger_moduleStarted
        >
        struct Ex_fileLoader_launcher_started
        {
            typedef void result_type;

            APC_fileLoaderNameProv apc_fileLoaderNameProv;
            Action_logger_moduleStarted act_logger_moduleStarted;

            Ex_fileLoader_launcher_started
            (
                const APC_fileLoaderNameProv &apc_fileLoaderNameProv,
                const Action_logger_moduleStarted &act_logger_moduleStarted
            ) :
                apc_fileLoaderNameProv(apc_fileLoaderNameProv),
                act_logger_moduleStarted(act_logger_moduleStarted)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    fileLoaderNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleStarted
                EXECUTE_ACTION
                (
                    logger, moduleStarted,
                    PASS_ARG(logger, moduleStarted, moduleName, GET_ARGUMENT(fileLoaderNameProv, moduleName))
                );

            }
        };

        template
<
            typename APC_fileLoaderNameProv,
            typename Action_logger_moduleStarted
        >
        inline static Ex_fileLoader_launcher_started
        <
            APC_fileLoaderNameProv,
            Action_logger_moduleStarted
        >
        ex_fileLoader_launcher_started
        (
            const APC_fileLoaderNameProv &apc_fileLoaderNameProv,
            const Action_logger_moduleStarted &act_logger_moduleStarted
        )
        {
            return Ex_fileLoader_launcher_started
            <
                APC_fileLoaderNameProv,
                Action_logger_moduleStarted
            >
            (
                apc_fileLoaderNameProv,
                act_logger_moduleStarted
            );
        }

        // fileLoader_launcher_finished --------------------------------------------------------------------------------------------
        struct Tag_fileLoader_launcher_finished {};

        template
        <
            typename APC_fileLoaderNameProv,
            typename Action_logger_moduleFinished
        >
        struct Ex_fileLoader_launcher_finished
        {
            typedef void result_type;

            APC_fileLoaderNameProv apc_fileLoaderNameProv;
            Action_logger_moduleFinished act_logger_moduleFinished;

            Ex_fileLoader_launcher_finished
            (
                const APC_fileLoaderNameProv &apc_fileLoaderNameProv,
                const Action_logger_moduleFinished &act_logger_moduleFinished
            ) :
                apc_fileLoaderNameProv(apc_fileLoaderNameProv),
                act_logger_moduleFinished(act_logger_moduleFinished)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                CREATE_APROVIDER
                (
                    fileLoaderNameProv,
                );

                // Actions -------------------------------------------------------------------
                // logger.actions.moduleFinished
                EXECUTE_ACTION
                (
                    logger, moduleFinished,
                    PASS_ARG(logger, moduleFinished, moduleName, GET_ARGUMENT(fileLoaderNameProv, moduleName))
                );

            }
        };

        template
<
            typename APC_fileLoaderNameProv,
            typename Action_logger_moduleFinished
        >
        inline static Ex_fileLoader_launcher_finished
        <
            APC_fileLoaderNameProv,
            Action_logger_moduleFinished
        >
        ex_fileLoader_launcher_finished
        (
            const APC_fileLoaderNameProv &apc_fileLoaderNameProv,
            const Action_logger_moduleFinished &act_logger_moduleFinished
        )
        {
            return Ex_fileLoader_launcher_finished
            <
                APC_fileLoaderNameProv,
                Action_logger_moduleFinished
            >
            (
                apc_fileLoaderNameProv,
                act_logger_moduleFinished
            );
        }

        // fileLoader_connectorLoaded ----------------------------------------------------------------------------------------------
        struct Tag_fileLoader_connectorLoaded {};

        template
        <
            typename Action_logger_connectorLoaded
        >
        struct Ex_fileLoader_connectorLoaded
        {
            typedef void result_type;

            Action_logger_connectorLoaded act_logger_connectorLoaded;

            Ex_fileLoader_connectorLoaded
            (
                const Action_logger_connectorLoaded &act_logger_connectorLoaded
            ) :
                act_logger_connectorLoaded(act_logger_connectorLoaded)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &cToolsPath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(cToolsPath, cToolsPath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // logger.actions.connectorLoaded
                EXECUTE_ACTION
                (
                    logger, connectorLoaded,
                    PASS_ARG(logger, connectorLoaded, cToolsPath, cToolsPath)
                );

            }
        };

        template
<
            typename Action_logger_connectorLoaded
        >
        inline static Ex_fileLoader_connectorLoaded
        <
            Action_logger_connectorLoaded
        >
        ex_fileLoader_connectorLoaded
        (
            const Action_logger_connectorLoaded &act_logger_connectorLoaded
        )
        {
            return Ex_fileLoader_connectorLoaded
            <
                Action_logger_connectorLoaded
            >
            (
                act_logger_connectorLoaded
            );
        }

        // fileLoader_cPerformerLoaded ---------------------------------------------------------------------------------------------
        struct Tag_fileLoader_cPerformerLoaded {};

        template
        <
            typename Action_logger_cPerformerLoaded
        >
        struct Ex_fileLoader_cPerformerLoaded
        {
            typedef void result_type;

            Action_logger_cPerformerLoaded act_logger_cPerformerLoaded;

            Ex_fileLoader_cPerformerLoaded
            (
                const Action_logger_cPerformerLoaded &act_logger_cPerformerLoaded
            ) :
                act_logger_cPerformerLoaded(act_logger_cPerformerLoaded)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &cToolsPath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(cToolsPath, cToolsPath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // logger.actions.cPerformerLoaded
                EXECUTE_ACTION
                (
                    logger, cPerformerLoaded,
                    PASS_ARG(logger, cPerformerLoaded, cToolsPath, cToolsPath)
                );

            }
        };

        template
<
            typename Action_logger_cPerformerLoaded
        >
        inline static Ex_fileLoader_cPerformerLoaded
        <
            Action_logger_cPerformerLoaded
        >
        ex_fileLoader_cPerformerLoaded
        (
            const Action_logger_cPerformerLoaded &act_logger_cPerformerLoaded
        )
        {
            return Ex_fileLoader_cPerformerLoaded
            <
                Action_logger_cPerformerLoaded
            >
            (
                act_logger_cPerformerLoaded
            );
        }

        // fileLoader_nodeFound ----------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_nodeFound {};

        template
        <
            typename Action_mainWindow_addNode
        >
        struct Ex_fileLoader_nodeFound
        {
            typedef void result_type;

            Action_mainWindow_addNode act_mainWindow_addNode;

            Ex_fileLoader_nodeFound
            (
                const Action_mainWindow_addNode &act_mainWindow_addNode
            ) :
                act_mainWindow_addNode(act_mainWindow_addNode)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &value_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);
                CREATE_ARG(value, value);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.addNode
                EXECUTE_ACTION
                (
                    mainWindow, addNode,
                    PASS_ARG(mainWindow, addNode, nodePath, nodePath),
                    PASS_ARG(mainWindow, addNode, value, value)
                );

            }
        };

        template
<
            typename Action_mainWindow_addNode
        >
        inline static Ex_fileLoader_nodeFound
        <
            Action_mainWindow_addNode
        >
        ex_fileLoader_nodeFound
        (
            const Action_mainWindow_addNode &act_mainWindow_addNode
        )
        {
            return Ex_fileLoader_nodeFound
            <
                Action_mainWindow_addNode
            >
            (
                act_mainWindow_addNode
            );
        }

        // fileLoader_valueFound ---------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_valueFound {};

        template
        <
            typename Action_mainWindow_setNodeValue
        >
        struct Ex_fileLoader_valueFound
        {
            typedef void result_type;

            Action_mainWindow_setNodeValue act_mainWindow_setNodeValue;

            Ex_fileLoader_valueFound
            (
                const Action_mainWindow_setNodeValue &act_mainWindow_setNodeValue
            ) :
                act_mainWindow_setNodeValue(act_mainWindow_setNodeValue)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &value_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);
                CREATE_ARG(value, value);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.setNodeValue
                EXECUTE_ACTION
                (
                    mainWindow, setNodeValue,
                    PASS_ARG(mainWindow, setNodeValue, nodePath, nodePath),
                    PASS_ARG(mainWindow, setNodeValue, value, value)
                );

            }
        };

        template
<
            typename Action_mainWindow_setNodeValue
        >
        inline static Ex_fileLoader_valueFound
        <
            Action_mainWindow_setNodeValue
        >
        ex_fileLoader_valueFound
        (
            const Action_mainWindow_setNodeValue &act_mainWindow_setNodeValue
        )
        {
            return Ex_fileLoader_valueFound
            <
                Action_mainWindow_setNodeValue
            >
            (
                act_mainWindow_setNodeValue
            );
        }

        // fileLoader_outputText ---------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_outputText {};

        template
        <
            typename Action_mainWindow_addOutputText
        >
        struct Ex_fileLoader_outputText
        {
            typedef void result_type;

            Action_mainWindow_addOutputText act_mainWindow_addOutputText;

            Ex_fileLoader_outputText
            (
                const Action_mainWindow_addOutputText &act_mainWindow_addOutputText
            ) :
                act_mainWindow_addOutputText(act_mainWindow_addOutputText)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &textProperties_in,
                const InArg1 &outputText_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(outputText, outputText);
                CREATE_ARG(textProperties, textProperties);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.addOutputText
                EXECUTE_ACTION
                (
                    mainWindow, addOutputText,
                    PASS_ARG(mainWindow, addOutputText, textProperties, textProperties),
                    PASS_ARG(mainWindow, addOutputText, outputText, outputText)
                );

            }
        };

        template
<
            typename Action_mainWindow_addOutputText
        >
        inline static Ex_fileLoader_outputText
        <
            Action_mainWindow_addOutputText
        >
        ex_fileLoader_outputText
        (
            const Action_mainWindow_addOutputText &act_mainWindow_addOutputText
        )
        {
            return Ex_fileLoader_outputText
            <
                Action_mainWindow_addOutputText
            >
            (
                act_mainWindow_addOutputText
            );
        }

        // fileLoader_clearOutput --------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_clearOutput {};

        template
        <
            typename Action_mainWindow_clearOutput
        >
        struct Ex_fileLoader_clearOutput
        {
            typedef void result_type;

            Action_mainWindow_clearOutput act_mainWindow_clearOutput;

            Ex_fileLoader_clearOutput
            (
                const Action_mainWindow_clearOutput &act_mainWindow_clearOutput
            ) :
                act_mainWindow_clearOutput(act_mainWindow_clearOutput)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.clearOutput
                EXECUTE_ACTION
                (
                    mainWindow, clearOutput,
                );

            }
        };

        template
<
            typename Action_mainWindow_clearOutput
        >
        inline static Ex_fileLoader_clearOutput
        <
            Action_mainWindow_clearOutput
        >
        ex_fileLoader_clearOutput
        (
            const Action_mainWindow_clearOutput &act_mainWindow_clearOutput
        )
        {
            return Ex_fileLoader_clearOutput
            <
                Action_mainWindow_clearOutput
            >
            (
                act_mainWindow_clearOutput
            );
        }

        // fileLoader_actionNotPerformed -------------------------------------------------------------------------------------------
        struct Tag_fileLoader_actionNotPerformed {};

        template
        <
            typename Action_mainWindow_actionNotPerformed
        >
        struct Ex_fileLoader_actionNotPerformed
        {
            typedef void result_type;

            Action_mainWindow_actionNotPerformed act_mainWindow_actionNotPerformed;

            Ex_fileLoader_actionNotPerformed
            (
                const Action_mainWindow_actionNotPerformed &act_mainWindow_actionNotPerformed
            ) :
                act_mainWindow_actionNotPerformed(act_mainWindow_actionNotPerformed)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &errorText_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(errorText, errorText);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.actionNotPerformed
                EXECUTE_ACTION
                (
                    mainWindow, actionNotPerformed,
                    PASS_ARG(mainWindow, actionNotPerformed, errorText, errorText)
                );

            }
        };

        template
<
            typename Action_mainWindow_actionNotPerformed
        >
        inline static Ex_fileLoader_actionNotPerformed
        <
            Action_mainWindow_actionNotPerformed
        >
        ex_fileLoader_actionNotPerformed
        (
            const Action_mainWindow_actionNotPerformed &act_mainWindow_actionNotPerformed
        )
        {
            return Ex_fileLoader_actionNotPerformed
            <
                Action_mainWindow_actionNotPerformed
            >
            (
                act_mainWindow_actionNotPerformed
            );
        }

        // fileLoader_nodeRemoved --------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_nodeRemoved {};

        template
        <
            typename Action_mainWindow_removeNode
        >
        struct Ex_fileLoader_nodeRemoved
        {
            typedef void result_type;

            Action_mainWindow_removeNode act_mainWindow_removeNode;

            Ex_fileLoader_nodeRemoved
            (
                const Action_mainWindow_removeNode &act_mainWindow_removeNode
            ) :
                act_mainWindow_removeNode(act_mainWindow_removeNode)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.removeNode
                EXECUTE_ACTION
                (
                    mainWindow, removeNode,
                    PASS_ARG(mainWindow, removeNode, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_mainWindow_removeNode
        >
        inline static Ex_fileLoader_nodeRemoved
        <
            Action_mainWindow_removeNode
        >
        ex_fileLoader_nodeRemoved
        (
            const Action_mainWindow_removeNode &act_mainWindow_removeNode
        )
        {
            return Ex_fileLoader_nodeRemoved
            <
                Action_mainWindow_removeNode
            >
            (
                act_mainWindow_removeNode
            );
        }

        // fileLoader_nodeSelected -------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_nodeSelected {};

        template
        <
            typename Action_mainWindow_selectNode
        >
        struct Ex_fileLoader_nodeSelected
        {
            typedef void result_type;

            Action_mainWindow_selectNode act_mainWindow_selectNode;

            Ex_fileLoader_nodeSelected
            (
                const Action_mainWindow_selectNode &act_mainWindow_selectNode
            ) :
                act_mainWindow_selectNode(act_mainWindow_selectNode)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &openNode_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);
                CREATE_ARG(openNode, openNode);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.selectNode
                EXECUTE_ACTION
                (
                    mainWindow, selectNode,
                    PASS_ARG(mainWindow, selectNode, nodePath, nodePath),
                    PASS_ARG(mainWindow, selectNode, openNode, openNode)
                );

            }
        };

        template
<
            typename Action_mainWindow_selectNode
        >
        inline static Ex_fileLoader_nodeSelected
        <
            Action_mainWindow_selectNode
        >
        ex_fileLoader_nodeSelected
        (
            const Action_mainWindow_selectNode &act_mainWindow_selectNode
        )
        {
            return Ex_fileLoader_nodeSelected
            <
                Action_mainWindow_selectNode
            >
            (
                act_mainWindow_selectNode
            );
        }

        // fileLoader_actionListFound ----------------------------------------------------------------------------------------------
        struct Tag_fileLoader_actionListFound {};

        template
        <
            typename Action_mainWindow_showActions
        >
        struct Ex_fileLoader_actionListFound
        {
            typedef void result_type;

            Action_mainWindow_showActions act_mainWindow_showActions;

            Ex_fileLoader_actionListFound
            (
                const Action_mainWindow_showActions &act_mainWindow_showActions
            ) :
                act_mainWindow_showActions(act_mainWindow_showActions)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &actionList_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(actionList, actionList);
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.showActions
                EXECUTE_ACTION
                (
                    mainWindow, showActions,
                    PASS_ARG(mainWindow, showActions, nodePath, nodePath),
                    PASS_ARG(mainWindow, showActions, actionList, actionList)
                );

            }
        };

        template
<
            typename Action_mainWindow_showActions
        >
        inline static Ex_fileLoader_actionListFound
        <
            Action_mainWindow_showActions
        >
        ex_fileLoader_actionListFound
        (
            const Action_mainWindow_showActions &act_mainWindow_showActions
        )
        {
            return Ex_fileLoader_actionListFound
            <
                Action_mainWindow_showActions
            >
            (
                act_mainWindow_showActions
            );
        }

        // fileLoader_nodeRenamed --------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_nodeRenamed {};

        template
        <
            typename Action_mainWindow_renameNode
        >
        struct Ex_fileLoader_nodeRenamed
        {
            typedef void result_type;

            Action_mainWindow_renameNode act_mainWindow_renameNode;

            Ex_fileLoader_nodeRenamed
            (
                const Action_mainWindow_renameNode &act_mainWindow_renameNode
            ) :
                act_mainWindow_renameNode(act_mainWindow_renameNode)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &nodeId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodeId, nodeId);
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.renameNode
                EXECUTE_ACTION
                (
                    mainWindow, renameNode,
                    PASS_ARG(mainWindow, renameNode, nodePath, nodePath),
                    PASS_ARG(mainWindow, renameNode, nodeId, nodeId)
                );

            }
        };

        template
<
            typename Action_mainWindow_renameNode
        >
        inline static Ex_fileLoader_nodeRenamed
        <
            Action_mainWindow_renameNode
        >
        ex_fileLoader_nodeRenamed
        (
            const Action_mainWindow_renameNode &act_mainWindow_renameNode
        )
        {
            return Ex_fileLoader_nodeRenamed
            <
                Action_mainWindow_renameNode
            >
            (
                act_mainWindow_renameNode
            );
        }

        // fileLoader_flowNodeFound ------------------------------------------------------------------------------------------------
        struct Tag_fileLoader_flowNodeFound {};

        template
        <
            typename Action_mainWindow_addFlowNode
        >
        struct Ex_fileLoader_flowNodeFound
        {
            typedef void result_type;

            Action_mainWindow_addFlowNode act_mainWindow_addFlowNode;

            Ex_fileLoader_flowNodeFound
            (
                const Action_mainWindow_addFlowNode &act_mainWindow_addFlowNode
            ) :
                act_mainWindow_addFlowNode(act_mainWindow_addFlowNode)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &nodePath_in,
                const InArg1 &value_in,
                const InArg2 &isExpandable_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(isExpandable, isExpandable);
                CREATE_ARG(nodePath, nodePath);
                CREATE_ARG(value, value);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.addFlowNode
                EXECUTE_ACTION
                (
                    mainWindow, addFlowNode,
                    PASS_ARG(mainWindow, addFlowNode, nodePath, nodePath),
                    PASS_ARG(mainWindow, addFlowNode, value, value),
                    PASS_ARG(mainWindow, addFlowNode, isExpandable, isExpandable)
                );

            }
        };

        template
<
            typename Action_mainWindow_addFlowNode
        >
        inline static Ex_fileLoader_flowNodeFound
        <
            Action_mainWindow_addFlowNode
        >
        ex_fileLoader_flowNodeFound
        (
            const Action_mainWindow_addFlowNode &act_mainWindow_addFlowNode
        )
        {
            return Ex_fileLoader_flowNodeFound
            <
                Action_mainWindow_addFlowNode
            >
            (
                act_mainWindow_addFlowNode
            );
        }

        // fileLoader_noMoreFlowNodes ----------------------------------------------------------------------------------------------
        struct Tag_fileLoader_noMoreFlowNodes {};

        template
        <
            typename Action_mainWindow_noMoreFlowNodes
        >
        struct Ex_fileLoader_noMoreFlowNodes
        {
            typedef void result_type;

            Action_mainWindow_noMoreFlowNodes act_mainWindow_noMoreFlowNodes;

            Ex_fileLoader_noMoreFlowNodes
            (
                const Action_mainWindow_noMoreFlowNodes &act_mainWindow_noMoreFlowNodes
            ) :
                act_mainWindow_noMoreFlowNodes(act_mainWindow_noMoreFlowNodes)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.noMoreFlowNodes
                EXECUTE_ACTION
                (
                    mainWindow, noMoreFlowNodes,
                );

            }
        };

        template
<
            typename Action_mainWindow_noMoreFlowNodes
        >
        inline static Ex_fileLoader_noMoreFlowNodes
        <
            Action_mainWindow_noMoreFlowNodes
        >
        ex_fileLoader_noMoreFlowNodes
        (
            const Action_mainWindow_noMoreFlowNodes &act_mainWindow_noMoreFlowNodes
        )
        {
            return Ex_fileLoader_noMoreFlowNodes
            <
                Action_mainWindow_noMoreFlowNodes
            >
            (
                act_mainWindow_noMoreFlowNodes
            );
        }

        // fileLoader_removeChildren -----------------------------------------------------------------------------------------------
        struct Tag_fileLoader_removeChildren {};

        template
        <
            typename Action_mainWindow_removeChildren
        >
        struct Ex_fileLoader_removeChildren
        {
            typedef void result_type;

            Action_mainWindow_removeChildren act_mainWindow_removeChildren;

            Ex_fileLoader_removeChildren
            (
                const Action_mainWindow_removeChildren &act_mainWindow_removeChildren
            ) :
                act_mainWindow_removeChildren(act_mainWindow_removeChildren)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &nodePath_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(nodePath, nodePath);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.removeChildren
                EXECUTE_ACTION
                (
                    mainWindow, removeChildren,
                    PASS_ARG(mainWindow, removeChildren, nodePath, nodePath)
                );

            }
        };

        template
<
            typename Action_mainWindow_removeChildren
        >
        inline static Ex_fileLoader_removeChildren
        <
            Action_mainWindow_removeChildren
        >
        ex_fileLoader_removeChildren
        (
            const Action_mainWindow_removeChildren &act_mainWindow_removeChildren
        )
        {
            return Ex_fileLoader_removeChildren
            <
                Action_mainWindow_removeChildren
            >
            (
                act_mainWindow_removeChildren
            );
        }

        // fileLoader_saveDesignTreeState ------------------------------------------------------------------------------------------
        struct Tag_fileLoader_saveDesignTreeState {};

        template
        <
            typename Action_mainWindow_saveDesignTreeState
        >
        struct Ex_fileLoader_saveDesignTreeState
        {
            typedef void result_type;

            Action_mainWindow_saveDesignTreeState act_mainWindow_saveDesignTreeState;

            Ex_fileLoader_saveDesignTreeState
            (
                const Action_mainWindow_saveDesignTreeState &act_mainWindow_saveDesignTreeState
            ) :
                act_mainWindow_saveDesignTreeState(act_mainWindow_saveDesignTreeState)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.saveDesignTreeState
                EXECUTE_ACTION
                (
                    mainWindow, saveDesignTreeState,
                );

            }
        };

        template
<
            typename Action_mainWindow_saveDesignTreeState
        >
        inline static Ex_fileLoader_saveDesignTreeState
        <
            Action_mainWindow_saveDesignTreeState
        >
        ex_fileLoader_saveDesignTreeState
        (
            const Action_mainWindow_saveDesignTreeState &act_mainWindow_saveDesignTreeState
        )
        {
            return Ex_fileLoader_saveDesignTreeState
            <
                Action_mainWindow_saveDesignTreeState
            >
            (
                act_mainWindow_saveDesignTreeState
            );
        }

        // fileLoader_restoreDesignTreeState ---------------------------------------------------------------------------------------
        struct Tag_fileLoader_restoreDesignTreeState {};

        template
        <
            typename Action_mainWindow_restoreDesignTreeState
        >
        struct Ex_fileLoader_restoreDesignTreeState
        {
            typedef void result_type;

            Action_mainWindow_restoreDesignTreeState act_mainWindow_restoreDesignTreeState;

            Ex_fileLoader_restoreDesignTreeState
            (
                const Action_mainWindow_restoreDesignTreeState &act_mainWindow_restoreDesignTreeState
            ) :
                act_mainWindow_restoreDesignTreeState(act_mainWindow_restoreDesignTreeState)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // mainWindow.actions.restoreDesignTreeState
                EXECUTE_ACTION
                (
                    mainWindow, restoreDesignTreeState,
                );

            }
        };

        template
<
            typename Action_mainWindow_restoreDesignTreeState
        >
        inline static Ex_fileLoader_restoreDesignTreeState
        <
            Action_mainWindow_restoreDesignTreeState
        >
        ex_fileLoader_restoreDesignTreeState
        (
            const Action_mainWindow_restoreDesignTreeState &act_mainWindow_restoreDesignTreeState
        )
        {
            return Ex_fileLoader_restoreDesignTreeState
            <
                Action_mainWindow_restoreDesignTreeState
            >
            (
                act_mainWindow_restoreDesignTreeState
            );
        }

        // ConnInstances -----------------------------------------------------------------------------------------------------------
        struct ConnInstances
        {
            typename Connectors::Logger &logger;
            typename Connectors::MainWindow &mainWindow;
            typename Connectors::FileLoader &fileLoader;

            ConnInstances(const chila::connectionTools::lib::codegen::ConnectorMap &cMap) :
                logger(cMap.get<typename Connectors::Logger>("logger")),
                mainWindow(cMap.get<typename Connectors::MainWindow>("mainWindow")),
                fileLoader(cMap.get<typename Connectors::FileLoader>("fileLoader"))
            {}
        };

        // logger ------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_logger(ConnInstances &cInstances, const Providers &providers)
        {
        }

        // mainWindow --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_mainWindow(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.mainWindow.events.launcher_started
                = ex_mainWindow_launcher_started
            (
                providers.mainWindowNameProv
                ,
                actionExecuter<Tag_mainWindow_launcher_started, 0>(cInstances.logger.actions.moduleStarted),
                actionExecuter<Tag_mainWindow_launcher_started, 1>(cInstances.mainWindow.actions.waitEvent)
            );
            cInstances.mainWindow.events.launcher_finished
                = ex_mainWindow_launcher_finished
            (
                providers.mainWindowNameProv
                ,
                actionExecuter<Tag_mainWindow_launcher_finished, 0>(cInstances.logger.actions.moduleFinished)
            );
            cInstances.mainWindow.events.actionRequest
                = ex_mainWindow_actionRequest
            (
                actionExecuter<Tag_mainWindow_actionRequest, 0>(cInstances.fileLoader.actions.performAction),
                actionExecuter<Tag_mainWindow_actionRequest, 1>(cInstances.mainWindow.actions.waitEvent)
            );
            cInstances.mainWindow.events.undoRequest
                = ex_mainWindow_undoRequest
            (
                actionExecuter<Tag_mainWindow_undoRequest, 0>(cInstances.fileLoader.actions.undo)
            );
            cInstances.mainWindow.events.redoRequest
                = ex_mainWindow_redoRequest
            (
                actionExecuter<Tag_mainWindow_redoRequest, 0>(cInstances.fileLoader.actions.redo)
            );
            cInstances.mainWindow.events.saveRequest
                = ex_mainWindow_saveRequest
            (
                actionExecuter<Tag_mainWindow_saveRequest, 0>(cInstances.fileLoader.actions.save),
                actionExecuter<Tag_mainWindow_saveRequest, 1>(cInstances.mainWindow.actions.waitEvent)
            );
            cInstances.mainWindow.events.actionListRequired
                = ex_mainWindow_actionListRequired
            (
                actionExecuter<Tag_mainWindow_actionListRequired, 0>(cInstances.fileLoader.actions.giveActionList),
                actionExecuter<Tag_mainWindow_actionListRequired, 1>(cInstances.mainWindow.actions.waitEvent)
            );
            cInstances.mainWindow.events.flowNodesRequired
                = ex_mainWindow_flowNodesRequired
            (
                actionExecuter<Tag_mainWindow_flowNodesRequired, 0>(cInstances.fileLoader.actions.requestFlowNodes)
            );
            cInstances.mainWindow.events.flowNodeSelected
                = ex_mainWindow_flowNodeSelected
            (
                actionExecuter<Tag_mainWindow_flowNodeSelected, 0>(cInstances.fileLoader.actions.showFNodeInfo)
            );
            cInstances.mainWindow.events.checkNodes
                = ex_mainWindow_checkNodes
            (
                actionExecuter<Tag_mainWindow_checkNodes, 0>(cInstances.fileLoader.actions.checkNodes)
            );
            cInstances.mainWindow.events.expandFlowNode
                = ex_mainWindow_expandFlowNode
            (
                actionExecuter<Tag_mainWindow_expandFlowNode, 0>(cInstances.fileLoader.actions.expandFlowNode)
            );
            cInstances.mainWindow.events.moveUpRequest
                = ex_mainWindow_moveUpRequest
            (
                actionExecuter<Tag_mainWindow_moveUpRequest, 0>(cInstances.fileLoader.actions.moveUp)
            );
            cInstances.mainWindow.events.moveDownRequest
                = ex_mainWindow_moveDownRequest
            (
                actionExecuter<Tag_mainWindow_moveDownRequest, 0>(cInstances.fileLoader.actions.moveDown)
            );
        }

        // fileLoader --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_fileLoader(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.fileLoader.events.launcher_started
                = ex_fileLoader_launcher_started
            (
                providers.fileLoaderNameProv
                ,
                actionExecuter<Tag_fileLoader_launcher_started, 0>(cInstances.logger.actions.moduleStarted)
            );
            cInstances.fileLoader.events.launcher_finished
                = ex_fileLoader_launcher_finished
            (
                providers.fileLoaderNameProv
                ,
                actionExecuter<Tag_fileLoader_launcher_finished, 0>(cInstances.logger.actions.moduleFinished)
            );
            cInstances.fileLoader.events.connectorLoaded
                = ex_fileLoader_connectorLoaded
            (
                actionExecuter<Tag_fileLoader_connectorLoaded, 0>(cInstances.logger.actions.connectorLoaded)
            );
            cInstances.fileLoader.events.cPerformerLoaded
                = ex_fileLoader_cPerformerLoaded
            (
                actionExecuter<Tag_fileLoader_cPerformerLoaded, 0>(cInstances.logger.actions.cPerformerLoaded)
            );
            cInstances.fileLoader.events.nodeFound
                = ex_fileLoader_nodeFound
            (
                actionExecuter<Tag_fileLoader_nodeFound, 0>(cInstances.mainWindow.actions.addNode)
            );
            cInstances.fileLoader.events.valueFound
                = ex_fileLoader_valueFound
            (
                actionExecuter<Tag_fileLoader_valueFound, 0>(cInstances.mainWindow.actions.setNodeValue)
            );
            cInstances.fileLoader.events.outputText
                = ex_fileLoader_outputText
            (
                actionExecuter<Tag_fileLoader_outputText, 0>(cInstances.mainWindow.actions.addOutputText)
            );
            cInstances.fileLoader.events.clearOutput
                = ex_fileLoader_clearOutput
            (
                actionExecuter<Tag_fileLoader_clearOutput, 0>(cInstances.mainWindow.actions.clearOutput)
            );
            cInstances.fileLoader.events.actionNotPerformed
                = ex_fileLoader_actionNotPerformed
            (
                actionExecuter<Tag_fileLoader_actionNotPerformed, 0>(cInstances.mainWindow.actions.actionNotPerformed)
            );
            cInstances.fileLoader.events.nodeRemoved
                = ex_fileLoader_nodeRemoved
            (
                actionExecuter<Tag_fileLoader_nodeRemoved, 0>(cInstances.mainWindow.actions.removeNode)
            );
            cInstances.fileLoader.events.nodeSelected
                = ex_fileLoader_nodeSelected
            (
                actionExecuter<Tag_fileLoader_nodeSelected, 0>(cInstances.mainWindow.actions.selectNode)
            );
            cInstances.fileLoader.events.actionListFound
                = ex_fileLoader_actionListFound
            (
                actionExecuter<Tag_fileLoader_actionListFound, 0>(cInstances.mainWindow.actions.showActions)
            );
            cInstances.fileLoader.events.nodeRenamed
                = ex_fileLoader_nodeRenamed
            (
                actionExecuter<Tag_fileLoader_nodeRenamed, 0>(cInstances.mainWindow.actions.renameNode)
            );
            cInstances.fileLoader.events.flowNodeFound
                = ex_fileLoader_flowNodeFound
            (
                actionExecuter<Tag_fileLoader_flowNodeFound, 0>(cInstances.mainWindow.actions.addFlowNode)
            );
            cInstances.fileLoader.events.noMoreFlowNodes
                = ex_fileLoader_noMoreFlowNodes
            (
                actionExecuter<Tag_fileLoader_noMoreFlowNodes, 0>(cInstances.mainWindow.actions.noMoreFlowNodes)
            );
            cInstances.fileLoader.events.removeChildren
                = ex_fileLoader_removeChildren
            (
                actionExecuter<Tag_fileLoader_removeChildren, 0>(cInstances.mainWindow.actions.removeChildren)
            );
            cInstances.fileLoader.events.saveDesignTreeState
                = ex_fileLoader_saveDesignTreeState
            (
                actionExecuter<Tag_fileLoader_saveDesignTreeState, 0>(cInstances.mainWindow.actions.saveDesignTreeState)
            );
            cInstances.fileLoader.events.restoreDesignTreeState
                = ex_fileLoader_restoreDesignTreeState
            (
                actionExecuter<Tag_fileLoader_restoreDesignTreeState, 0>(cInstances.mainWindow.actions.restoreDesignTreeState)
            );
        }

        template <typename Args>
        static void connect(const Args &args)
        {
            ConnInstances cInstances(args.cMap);

            connect_logger(cInstances, args.providers);
            connect_mainWindow(cInstances, args.providers);
            connect_fileLoader(cInstances, args.providers);
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
