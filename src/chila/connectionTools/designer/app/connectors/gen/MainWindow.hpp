/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__MAINWINDOW_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__MAINWINDOW_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/call_traits.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <string>

#include <boost/mpl/set.hpp>
#include <chila/connectionTools/lib/codegen/ActionImplExecuter.hpp>
#include <chila/connectionTools/lib/codegen/FunctionSigCreator.hpp>
#include <chila/connectionTools/lib/codegen/EventExecuter.hpp>
#include <chila/connectionTools/lib/codegen/Connector.hpp>
#include <chila/connectionTools/lib/other/macrosExp.hpp>
#include <chila/connectionTools/lib/codegen/macrosDef.hpp>
#include <chila/lib/misc/macrosExp.hpp>

#define MY_BIND_ACTION(name) \
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__BIND_ACTION(Target, target, name)
#define DEF_CONNECTOR_ARGUMENT CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENT
#define DEF_CONNECTOR_FUNCTION CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTION
#define DEF_ARG_ALIAS CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS
#define DEF_ARG_ALIAS_LINK CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIAS_LINK

// Arguments defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ARGS_MainWindow \
    (moduleName) \
    (nodePath) \
    (nodeId) \
    (value) \
    (action) \
    (actionList) \
    (errorText) \
    (outputText) \
    (openNode) \
    (isExpandable) \
    (textProperties)

// Event defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_MainWindow \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (actionRequest) \
    (undoRequest) \
    (redoRequest) \
    (saveRequest) \
    (moveUpRequest) \
    (moveDownRequest) \
    (actionListRequired) \
    (flowNodesRequired) \
    (flowNodeSelected) \
    (checkNodes) \
    (expandFlowNode)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_starting \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_started \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_deactivating \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_deactivated \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_finishing \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_finished \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_actionRequest \
    (nodePath)(action)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_undoRequest \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_redoRequest \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_saveRequest \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_moveUpRequest \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_moveDownRequest \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_actionListRequired \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_flowNodesRequired \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_flowNodeSelected \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_checkNodes \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_expandFlowNode \
    (nodePath)

// Action defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_MainWindow \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (waitEvent) \
    (addNode) \
    (setNodeValue) \
    (addOutputText) \
    (clearOutput) \
    (actionNotPerformed) \
    (removeNode) \
    (removeChildren) \
    (selectNode) \
    (showActions) \
    (renameNode) \
    (addFlowNode) \
    (noMoreFlowNodes) \
    (saveDesignTreeState) \
    (restoreDesignTreeState)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_start \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_deactivate \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_finish \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_waitEvent \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_addNode \
    (nodePath)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_setNodeValue \
    (nodePath)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_addOutputText \
    (textProperties)(outputText)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_clearOutput \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_actionNotPerformed \
    (errorText)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_removeNode \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_removeChildren \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_selectNode \
    (nodePath)(openNode)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_showActions \
    (nodePath)(actionList)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_renameNode \
    (nodePath)(nodeId)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_addFlowNode \
    (nodePath)(value)(isExpandable)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_noMoreFlowNodes \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_saveDesignTreeState \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_restoreDesignTreeState \


// Actions' called events
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_start \
    (launcher_started)(flowNodesRequired)(actionListRequired)(saveRequest)(flowNodeSelected)(checkNodes)(expandFlowNode)(moveUpRequest)(moveDownRequest)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_deactivate \
    (launcher_deactivated)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_finish \
    (launcher_finished)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_waitEvent \
    (actionListRequired)(actionRequest)(saveRequest)(undoRequest)(redoRequest)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_addNode \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_setNodeValue \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_addOutputText \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_clearOutput \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_actionNotPerformed \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_removeNode \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_removeChildren \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_selectNode \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_showActions \
    (actionRequest)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_renameNode \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_addFlowNode \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_noMoreFlowNodes \
    (flowNodeSelected)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_saveDesignTreeState \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_restoreDesignTreeState \



CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,designer,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct MainWindow final: public chila::connectionTools::lib::codegen::ConnectorImpl<MainWindow<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.designer.app.connectors.gen.MainWindow"; }

        typedef MainWindow Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, MainWindow)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, MainWindow)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, MainWindow)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, MainWindow)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, MainWindow)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, MainWindow) {}
        } actions;


        MainWindow() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(waitEvent);
            MY_BIND_ACTION(addNode);
            MY_BIND_ACTION(setNodeValue);
            MY_BIND_ACTION(addOutputText);
            MY_BIND_ACTION(clearOutput);
            MY_BIND_ACTION(actionNotPerformed);
            MY_BIND_ACTION(removeNode);
            MY_BIND_ACTION(removeChildren);
            MY_BIND_ACTION(selectNode);
            MY_BIND_ACTION(showActions);
            MY_BIND_ACTION(renameNode);
            MY_BIND_ACTION(addFlowNode);
            MY_BIND_ACTION(noMoreFlowNodes);
            MY_BIND_ACTION(saveDesignTreeState);
            MY_BIND_ACTION(restoreDesignTreeState);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
