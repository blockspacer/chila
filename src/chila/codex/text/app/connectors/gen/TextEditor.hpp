// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__TEXTEDITOR_HPP
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__TEXTEDITOR_HPP

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
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ARGS_TextEditor \
    (fileName) \
    (notebook_tabName) \
    (notebook_tabTooltip) \
    (notebook_tabWidget) \
    (errorMsg) \
    (fileId) \
    (textBuffer) \
    (tags) \
    (parserId) \
    (tagsToApply) \
    (findReplace_findText) \
    (findReplace_replaceText) \
    (findReplace_checks) \
    (action_path) \
    (action_pathDataList) \
    (action_data)

// Event defines
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_TextEditor \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (newTBTabRequested) \
    (parseText) \
    (fatalError) \
    (saveEditorContents_current) \
    (saveEditorContents_as) \
    (contentsModified) \
    (contentsAreOriginal) \
    (fileSelected) \
    (tabDataChanged) \
    (editorClosed) \
    (findReplace_setFindText) \
    (registerAction) \
    (clearActions) \
    (addSeparator) \
    (selectFile)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_starting \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_started \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_deactivating \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_deactivated \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_finishing \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_launcher_finished \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_newTBTabRequested \
    (fileId)(notebook_tabName)(notebook_tabTooltip)(notebook_tabWidget)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_parseText \
    (fileId)(parserId)(textBuffer)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_fatalError \
    (errorMsg)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_saveEditorContents_current \
    (fileId)(textBuffer)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_saveEditorContents_as \
    (fileId)(fileName)(textBuffer)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_contentsModified \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_contentsAreOriginal \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_fileSelected \
    (fileId)(fileName)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_tabDataChanged \
    (fileId)(notebook_tabName)(notebook_tabTooltip)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_editorClosed \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_findReplace_setFindText \
    (findReplace_findText)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_registerAction \
    (action_pathDataList)(action_data)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_clearActions \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_addSeparator \
    (action_pathDataList)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextEditor_selectFile \
    (fileId)

// Action defines
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_TextEditor \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (newEditor) \
    (openEditor) \
    (addText) \
    (applyTags) \
    (saveEditorContents_current) \
    (saveEditorContents_as) \
    (openingDone) \
    (savingDone) \
    (undo) \
    (redo) \
    (fileSelected) \
    (editorTypeChanged) \
    (closingEditor) \
    (closingSelectedEditor) \
    (findReplace_start) \
    (findReplace_findPrevious) \
    (findReplace_findNext) \
    (findReplace_replace) \
    (findReplace_replaceAll) \
    (findReplace_restoreFind) \
    (findReplace_stateChanged) \
    (saveAll) \
    (tabAdded)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_launcher_start \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_launcher_deactivate \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_launcher_finish \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_newEditor \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_openEditor \
    (fileId)(fileName)(parserId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_addText \
    (fileId)(textBuffer)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_applyTags \
    (fileId)(tags)(tagsToApply)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_saveEditorContents_current \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_saveEditorContents_as \
    (fileName)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_openingDone \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_savingDone \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_undo \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_redo \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_fileSelected \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_editorTypeChanged \
    (fileId)(parserId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_closingEditor \
    (fileId)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_closingSelectedEditor \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_start \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_findPrevious \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_findNext \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_replace \
    (findReplace_replaceText)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_replaceAll \
    (findReplace_replaceText)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_restoreFind \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_findReplace_stateChanged \
    (findReplace_findText)(findReplace_checks)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_saveAll \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextEditor_tabAdded \
    (fileId)(notebook_tabWidget)

// Actions' called events
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_launcher_start \
    (launcher_started)(registerAction)(addSeparator)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_launcher_deactivate \
    (launcher_deactivated)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_launcher_finish \
    (launcher_finished)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_newEditor \
    (newTBTabRequested)(fatalError)(parseText)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_openEditor \
    (newTBTabRequested)(parseText)(fatalError)(contentsModified)(contentsAreOriginal)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_addText \
    (fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_applyTags \
    (fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_saveEditorContents_current \
    (saveEditorContents_current)(fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_saveEditorContents_as \
    (saveEditorContents_as)(tabDataChanged)(fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_openingDone \
    (contentsAreOriginal)(parseText)(fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_savingDone \
    (fatalError)(editorClosed)(contentsAreOriginal)(saveEditorContents_current)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_undo \
    (fatalError)(parseText)(contentsModified)(contentsAreOriginal)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_redo \
    (fatalError)(parseText)(contentsModified)(contentsAreOriginal)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_fileSelected \


#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_editorTypeChanged \
    (parseText)(fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_closingEditor \
    (fatalError)(saveEditorContents_current)(editorClosed)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_closingSelectedEditor \
    (fatalError)(saveEditorContents_current)(editorClosed)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_start \
    (fatalError)(findReplace_setFindText)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_findPrevious \
    (fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_findNext \
    (fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_replace \
    (fatalError)(contentsModified)(contentsAreOriginal)(parseText)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_replaceAll \
    (fatalError)(contentsModified)(contentsAreOriginal)(parseText)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_restoreFind \
    (fatalError)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_findReplace_stateChanged \


#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_saveAll \
    (fatalError)(saveEditorContents_current)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextEditor_tabAdded \
    (fatalError)(selectFile)(contentsModified)(contentsAreOriginal)


CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,codex,text,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct TextEditor final: public chila::connectionTools::lib::codegen::ConnectorImpl<TextEditor<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.codex.text.app.connectors.gen.TextEditor"; }

        typedef TextEditor Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, TextEditor)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, EVENT, TextEditor)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, EVENT, TextEditor)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, ACTION, TextEditor)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, ACTION, TextEditor)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, TextEditor) {}
        } actions;


        TextEditor() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(newEditor);
            MY_BIND_ACTION(openEditor);
            MY_BIND_ACTION(addText);
            MY_BIND_ACTION(applyTags);
            MY_BIND_ACTION(saveEditorContents_current);
            MY_BIND_ACTION(saveEditorContents_as);
            MY_BIND_ACTION(openingDone);
            MY_BIND_ACTION(savingDone);
            MY_BIND_ACTION(undo);
            MY_BIND_ACTION(redo);
            MY_BIND_ACTION(fileSelected);
            MY_BIND_ACTION(editorTypeChanged);
            MY_BIND_ACTION(closingEditor);
            MY_BIND_ACTION(closingSelectedEditor);
            MY_BIND_ACTION(findReplace_start);
            MY_BIND_ACTION(findReplace_findPrevious);
            MY_BIND_ACTION(findReplace_findNext);
            MY_BIND_ACTION(findReplace_replace);
            MY_BIND_ACTION(findReplace_replaceAll);
            MY_BIND_ACTION(findReplace_restoreFind);
            MY_BIND_ACTION(findReplace_stateChanged);
            MY_BIND_ACTION(saveAll);
            MY_BIND_ACTION(tabAdded);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
