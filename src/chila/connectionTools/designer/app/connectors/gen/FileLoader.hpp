// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__FILELOADER_HPP
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__FILELOADER_HPP

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef FUSION_MAX_VECTOR_SIZE
#undef BOOST_MPL_LIMIT_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#include <boost/call_traits.hpp>
#include <boost/function.hpp>
#include <chila/lib/misc/MemFnExecuter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <string>

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
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ARGS_FileLoader \
    (moduleName) \
    (filePath) \
    (nodePath) \
    (nodeId) \
    (value) \
    (cToolsPath) \
    (action) \
    (actionList) \
    (outputText) \
    (errorText) \
    (openNode) \
    (isExpandable) \
    (textProperties)

// Event defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_FileLoader \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (nodeFound) \
    (noMoreFlowNodes) \
    (valueFound) \
    (connectorLoaded) \
    (cPerformerLoaded) \
    (outputText) \
    (clearOutput) \
    (actionNotPerformed) \
    (nodeRemoved) \
    (nodeSelected) \
    (removeChildren) \
    (actionListFound) \
    (nodeRenamed) \
    (flowNodeFound) \
    (flowNodeNotFound) \
    (saveDesignTreeState) \
    (restoreDesignTreeState)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_starting \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_started \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_deactivating \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_deactivated \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_finishing \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_launcher_finished \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_nodeFound \
    (nodePath)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_noMoreFlowNodes \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_valueFound \
    (nodePath)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_connectorLoaded \
    (cToolsPath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_cPerformerLoaded \
    (cToolsPath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_outputText \
    (textProperties)(outputText)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_clearOutput \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_actionNotPerformed \
    (errorText)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_nodeRemoved \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_nodeSelected \
    (nodePath)(openNode)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_removeChildren \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_actionListFound \
    (nodePath)(actionList)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_nodeRenamed \
    (nodePath)(nodeId)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_flowNodeFound \
    (nodePath)(value)(isExpandable)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_flowNodeNotFound \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_saveDesignTreeState \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_FileLoader_restoreDesignTreeState \


// Action defines
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_FileLoader \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (loadCPerformer) \
    (loadConnector) \
    (performAction) \
    (undo) \
    (redo) \
    (save) \
    (moveUp) \
    (moveDown) \
    (giveActionList) \
    (refreshTree) \
    (requestFlowNodes) \
    (showFNodeInfo) \
    (checkNodes) \
    (expandFlowNode)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_launcher_start \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_launcher_deactivate \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_launcher_finish \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_loadCPerformer \
    (filePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_loadConnector \
    (filePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_performAction \
    (nodePath)(action)(value)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_undo \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_redo \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_save \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_moveUp \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_moveDown \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_giveActionList \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_refreshTree \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_requestFlowNodes \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_showFNodeInfo \
    (nodePath)
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_checkNodes \

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_FileLoader_expandFlowNode \
    (nodePath)

// Actions' called events
#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_launcher_start \
    (launcher_started)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_launcher_deactivate \
    (launcher_deactivated)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_launcher_finish \
    (launcher_finished)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_loadCPerformer \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_loadConnector \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_performAction \
    (saveDesignTreeState)(restoreDesignTreeState)(clearOutput)(outputText)(nodeFound)(nodeSelected)(nodeRemoved)(removeChildren)(actionNotPerformed)(valueFound)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_undo \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_redo \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_save \


#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_moveUp \
    (saveDesignTreeState)(restoreDesignTreeState)(nodeFound)(nodeRemoved)(removeChildren)(valueFound)(nodeSelected)(clearOutput)(outputText)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_moveDown \
    (saveDesignTreeState)(restoreDesignTreeState)(nodeFound)(nodeRemoved)(removeChildren)(valueFound)(nodeSelected)(clearOutput)(outputText)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_giveActionList \
    (actionListFound)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_refreshTree \
    (nodeFound)(valueFound)(clearOutput)(outputText)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_requestFlowNodes \
    (flowNodeFound)(noMoreFlowNodes)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_showFNodeInfo \
    (clearOutput)(outputText)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_checkNodes \
    (clearOutput)(outputText)

#define CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_FileLoader_expandFlowNode \



CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,connectionTools,designer,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct FileLoader final: public chila::connectionTools::lib::codegen::ConnectorImpl<FileLoader<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.connectionTools.designer.app.connectors.gen.FileLoader"; }

        typedef FileLoader Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, FileLoader)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, FileLoader)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, EVENT, FileLoader)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, FileLoader)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, ACTION, FileLoader)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CONNECTIONTOOLS_DESIGNER_APP_CONNECTORS_GEN, FileLoader) {}
        } actions;


        FileLoader() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(loadCPerformer);
            MY_BIND_ACTION(loadConnector);
            MY_BIND_ACTION(performAction);
            MY_BIND_ACTION(undo);
            MY_BIND_ACTION(redo);
            MY_BIND_ACTION(save);
            MY_BIND_ACTION(moveUp);
            MY_BIND_ACTION(moveDown);
            MY_BIND_ACTION(giveActionList);
            MY_BIND_ACTION(refreshTree);
            MY_BIND_ACTION(requestFlowNodes);
            MY_BIND_ACTION(showFNodeInfo);
            MY_BIND_ACTION(checkNodes);
            MY_BIND_ACTION(expandFlowNode);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
