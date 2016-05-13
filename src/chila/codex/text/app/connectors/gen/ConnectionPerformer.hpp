// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTIONPERFORMER_HPP

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
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ \
    (fileId) \
    (fileName) \
    (notebook_tabName) \
    (notebook_tabWidget) \
    (notebook_tabTooltip) \
    (textBuffer) \
    (tagId) \
    (errorMsg) \
    (tags) \
    (tagsToApply) \
    (parserId) \
    (findReplace_findText) \
    (findReplace_replaceText) \
    (findReplace_checks) \
    (action_path) \
    (action_pathDataList) \
    (action_data)

// ----------------------------- ConnectorAliases utility macros ----------------------------------
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_SEQ \
    (Application)(MainWindow)(TextEditor)(TextHighlighter)(FileOpener) \
    (FindReplace)(FileChooser)(BaseActionExecuter)(TextActionExecuter)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_Application \
    ((notebook:tabName)(notebook_tabName)) \
    ((notebook:tabWidget)(notebook_tabWidget))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_MainWindow \
    ((notebook:tabName)(notebook_tabName)) \
    ((notebook:tabWidget)(notebook_tabWidget)) \
    ((notebook:tabTooltip)(notebook_tabTooltip)) \
    ((notebook:tabId)(fileId)) \
    ((actionPath)(action_path)) \
    ((actionData)(action_data)) \
    ((actionPathDataList)(action_pathDataList))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_TextEditor \
    ((fileName)(fileName)) \
    ((notebook:tabName)(notebook_tabName)) \
    ((notebook:tabWidget)(notebook_tabWidget)) \
    ((fileId)(fileId)) \
    ((textBuffer)(textBuffer)) \
    ((errorMsg)(errorMsg)) \
    ((tags)(tags)) \
    ((parserId)(parserId)) \
    ((tagsToApply)(tagsToApply)) \
    ((notebook:tabTooltip)(notebook_tabTooltip)) \
    ((findReplace:findText)(findReplace_findText)) \
    ((findReplace:replaceText)(findReplace_replaceText)) \
    ((findReplace:checks)(findReplace_checks)) \
    ((action:path)(action_path)) \
    ((action:data)(action_data)) \
    ((action:pathDataList)(action_pathDataList))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_TextHighlighter \
    ((fileId)(fileId)) \
    ((tags)(tags)) \
    ((errorMsg)(errorMsg)) \
    ((textBuffer)(textBuffer)) \
    ((parserId)(parserId)) \
    ((tagsToApply)(tagsToApply))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FileOpener \
    ((fileName)(fileName)) \
    ((fileId)(fileId)) \
    ((textBuffer)(textBuffer)) \
    ((errorMsg)(errorMsg)) \
    ((fileType)(parserId))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FindReplace \
    ((findText)(findReplace_findText)) \
    ((replaceText)(findReplace_replaceText)) \
    ((checks)(findReplace_checks)) \
    ((errorMsg)(errorMsg))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_FileChooser \
    ((fileName)(fileName))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_BaseActionExecuter \
    ((actionPath)(action_path))

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_ALIAS_AALINK_SEQ_TextActionExecuter \
    ((actionPath)(action_path))


// ----------------------------- ArgumentProvider utility macros ---------------------------------------
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__APCREATORS_SEQ

// ----------------------------- Connector instances utility macros ---------------------------------------
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_SEQ \
    ((BaseActionExecuter)(base_actionExecuter)) \
    ((MainWindow)(base_mainWindow)) \
    ((FileChooser)(base_fileChooser_open)) \
    ((FileChooser)(base_fileChooser_saveAs)) \
    ((TextActionExecuter)(text_actionExecuter)) \
    ((FindReplace)(text_findReplace)) \
    ((TextEditor)(text_textEditor)) \
    ((TextHighlighter)(text_textHighlighter)) \
    ((FileOpener)(text_fileOpener))


#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_actionExecuter BaseActionExecuter
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_mainWindow MainWindow
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_fileChooser_open FileChooser
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_base_fileChooser_saveAs FileChooser
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_text_actionExecuter TextActionExecuter
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_text_findReplace FindReplace
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_text_textEditor TextEditor
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_text_textHighlighter TextHighlighter
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONN_INSTANCE_ALIAS_OF_text_fileOpener FileOpener

// -------------------------------------- Namespace start ----------------------------------------------
#include <chila/lib/misc/macrosExp.hpp>

CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,codex,text,app,connectors,gen))
{

    template <typename ArgTypes, typename Connectors>
    struct ConnectionPerformer
    {
        static chila::lib::misc::Path path() { return "chila.codex.text.app.connectors.gen.ConnectionPerformer"; }

        // ArgAliases
        struct ArgAliases
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_ARG_ALIASES(CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__ARG_ALIAS_SEQ)
        };

        // base_actionExecuter_file_new --------------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_new {};

        template
        <
            typename Action_text_textEditor_newEditor
        >
        struct Ex_base_actionExecuter_file_new
        {
            typedef void result_type;

            const Action_text_textEditor_newEditor &act_text_textEditor_newEditor;

            Ex_base_actionExecuter_file_new
            (
                const Action_text_textEditor_newEditor &act_text_textEditor_newEditor
            ) :
                act_text_textEditor_newEditor(act_text_textEditor_newEditor)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.newEditor
                EXECUTE_ACTION
                (
                    text_textEditor, newEditor,
                );

            }
        };

        template
<
            typename Action_text_textEditor_newEditor
        >
        inline static Ex_base_actionExecuter_file_new
        <
            Action_text_textEditor_newEditor
        >
        ex_base_actionExecuter_file_new
        (
            const Action_text_textEditor_newEditor &act_text_textEditor_newEditor
        )
        {
            return Ex_base_actionExecuter_file_new
            <
                Action_text_textEditor_newEditor
            >
            (
                act_text_textEditor_newEditor
            );
        }

        // base_actionExecuter_file_save -------------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_save {};

        template
        <
            typename Action_text_textEditor_saveEditorContents_current
        >
        struct Ex_base_actionExecuter_file_save
        {
            typedef void result_type;

            const Action_text_textEditor_saveEditorContents_current &act_text_textEditor_saveEditorContents_current;

            Ex_base_actionExecuter_file_save
            (
                const Action_text_textEditor_saveEditorContents_current &act_text_textEditor_saveEditorContents_current
            ) :
                act_text_textEditor_saveEditorContents_current(act_text_textEditor_saveEditorContents_current)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.saveEditorContents.current
                EXECUTE_ACTION
                (
                    text_textEditor, saveEditorContents_current,
                );

            }
        };

        template
<
            typename Action_text_textEditor_saveEditorContents_current
        >
        inline static Ex_base_actionExecuter_file_save
        <
            Action_text_textEditor_saveEditorContents_current
        >
        ex_base_actionExecuter_file_save
        (
            const Action_text_textEditor_saveEditorContents_current &act_text_textEditor_saveEditorContents_current
        )
        {
            return Ex_base_actionExecuter_file_save
            <
                Action_text_textEditor_saveEditorContents_current
            >
            (
                act_text_textEditor_saveEditorContents_current
            );
        }

        // base_actionExecuter_file_saveAll ----------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_saveAll {};

        template
        <
            typename Action_text_textEditor_saveAll
        >
        struct Ex_base_actionExecuter_file_saveAll
        {
            typedef void result_type;

            const Action_text_textEditor_saveAll &act_text_textEditor_saveAll;

            Ex_base_actionExecuter_file_saveAll
            (
                const Action_text_textEditor_saveAll &act_text_textEditor_saveAll
            ) :
                act_text_textEditor_saveAll(act_text_textEditor_saveAll)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.saveAll
                EXECUTE_ACTION
                (
                    text_textEditor, saveAll,
                );

            }
        };

        template
<
            typename Action_text_textEditor_saveAll
        >
        inline static Ex_base_actionExecuter_file_saveAll
        <
            Action_text_textEditor_saveAll
        >
        ex_base_actionExecuter_file_saveAll
        (
            const Action_text_textEditor_saveAll &act_text_textEditor_saveAll
        )
        {
            return Ex_base_actionExecuter_file_saveAll
            <
                Action_text_textEditor_saveAll
            >
            (
                act_text_textEditor_saveAll
            );
        }

        // base_actionExecuter_file_close ------------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_close {};

        template
        <
            typename Action_text_textEditor_closingSelectedEditor
        >
        struct Ex_base_actionExecuter_file_close
        {
            typedef void result_type;

            const Action_text_textEditor_closingSelectedEditor &act_text_textEditor_closingSelectedEditor;

            Ex_base_actionExecuter_file_close
            (
                const Action_text_textEditor_closingSelectedEditor &act_text_textEditor_closingSelectedEditor
            ) :
                act_text_textEditor_closingSelectedEditor(act_text_textEditor_closingSelectedEditor)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.closingSelectedEditor
                EXECUTE_ACTION
                (
                    text_textEditor, closingSelectedEditor,
                );

            }
        };

        template
<
            typename Action_text_textEditor_closingSelectedEditor
        >
        inline static Ex_base_actionExecuter_file_close
        <
            Action_text_textEditor_closingSelectedEditor
        >
        ex_base_actionExecuter_file_close
        (
            const Action_text_textEditor_closingSelectedEditor &act_text_textEditor_closingSelectedEditor
        )
        {
            return Ex_base_actionExecuter_file_close
            <
                Action_text_textEditor_closingSelectedEditor
            >
            (
                act_text_textEditor_closingSelectedEditor
            );
        }

        // base_actionExecuter_file_open -------------------------------------------------------------------------------------------
        struct Tag_base_actionExecuter_file_open {};

        template
        <
            typename Action_text_textEditor_newEditor
        >
        struct Ex_base_actionExecuter_file_open
        {
            typedef void result_type;

            const Action_text_textEditor_newEditor &act_text_textEditor_newEditor;

            Ex_base_actionExecuter_file_open
            (
                const Action_text_textEditor_newEditor &act_text_textEditor_newEditor
            ) :
                act_text_textEditor_newEditor(act_text_textEditor_newEditor)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.newEditor
                EXECUTE_ACTION
                (
                    text_textEditor, newEditor,
                );

            }
        };

        template
<
            typename Action_text_textEditor_newEditor
        >
        inline static Ex_base_actionExecuter_file_open
        <
            Action_text_textEditor_newEditor
        >
        ex_base_actionExecuter_file_open
        (
            const Action_text_textEditor_newEditor &act_text_textEditor_newEditor
        )
        {
            return Ex_base_actionExecuter_file_open
            <
                Action_text_textEditor_newEditor
            >
            (
                act_text_textEditor_newEditor
            );
        }

        // base_mainWindow_notebook_closingTab -------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_notebook_closingTab {};

        template
        <
            typename Action_text_textEditor_closingEditor
        >
        struct Ex_base_mainWindow_notebook_closingTab
        {
            typedef void result_type;

            const Action_text_textEditor_closingEditor &act_text_textEditor_closingEditor;

            Ex_base_mainWindow_notebook_closingTab
            (
                const Action_text_textEditor_closingEditor &act_text_textEditor_closingEditor
            ) :
                act_text_textEditor_closingEditor(act_text_textEditor_closingEditor)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &notebook_tabId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(notebook_tabId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.closingEditor
                EXECUTE_ACTION
                (
                    text_textEditor, closingEditor,
                    PASS_ARG(text_textEditor, closingEditor, fileId, fileId)
                );

            }
        };

        template
<
            typename Action_text_textEditor_closingEditor
        >
        inline static Ex_base_mainWindow_notebook_closingTab
        <
            Action_text_textEditor_closingEditor
        >
        ex_base_mainWindow_notebook_closingTab
        (
            const Action_text_textEditor_closingEditor &act_text_textEditor_closingEditor
        )
        {
            return Ex_base_mainWindow_notebook_closingTab
            <
                Action_text_textEditor_closingEditor
            >
            (
                act_text_textEditor_closingEditor
            );
        }

        // base_mainWindow_notebook_tabSelected ------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_notebook_tabSelected {};

        template
        <
            typename Action_text_fileOpener_fileSelected,
            typename Action_text_textEditor_fileSelected
        >
        struct Ex_base_mainWindow_notebook_tabSelected
        {
            typedef void result_type;

            const Action_text_fileOpener_fileSelected &act_text_fileOpener_fileSelected;
            const Action_text_textEditor_fileSelected &act_text_textEditor_fileSelected;

            Ex_base_mainWindow_notebook_tabSelected
            (
                const Action_text_fileOpener_fileSelected &act_text_fileOpener_fileSelected,
                const Action_text_textEditor_fileSelected &act_text_textEditor_fileSelected
            ) :
                act_text_fileOpener_fileSelected(act_text_fileOpener_fileSelected),
                act_text_textEditor_fileSelected(act_text_textEditor_fileSelected)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &notebook_tabId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(notebook_tabId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_fileOpener.actions.fileSelected
                EXECUTE_ACTION
                (
                    text_fileOpener, fileSelected,
                    PASS_ARG(text_fileOpener, fileSelected, fileId, fileId)
                );

                // text_textEditor.actions.fileSelected
                EXECUTE_ACTION
                (
                    text_textEditor, fileSelected,
                    PASS_ARG(text_textEditor, fileSelected, fileId, fileId)
                );

            }
        };

        template
<
            typename Action_text_fileOpener_fileSelected,
            typename Action_text_textEditor_fileSelected
        >
        inline static Ex_base_mainWindow_notebook_tabSelected
        <
            Action_text_fileOpener_fileSelected,
            Action_text_textEditor_fileSelected
        >
        ex_base_mainWindow_notebook_tabSelected
        (
            const Action_text_fileOpener_fileSelected &act_text_fileOpener_fileSelected,
            const Action_text_textEditor_fileSelected &act_text_textEditor_fileSelected
        )
        {
            return Ex_base_mainWindow_notebook_tabSelected
            <
                Action_text_fileOpener_fileSelected,
                Action_text_textEditor_fileSelected
            >
            (
                act_text_fileOpener_fileSelected,
                act_text_textEditor_fileSelected
            );
        }

        // base_mainWindow_actionExecuted ------------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_actionExecuted {};

        template
        <
            typename Action_text_actionExecuter_execute
        >
        struct Ex_base_mainWindow_actionExecuted
        {
            typedef void result_type;

            const Action_text_actionExecuter_execute &act_text_actionExecuter_execute;

            Ex_base_mainWindow_actionExecuted
            (
                const Action_text_actionExecuter_execute &act_text_actionExecuter_execute
            ) :
                act_text_actionExecuter_execute(act_text_actionExecuter_execute)
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
                CREATE_ARG(actionPath, action_path);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_actionExecuter.actions.execute
                EXECUTE_ACTION
                (
                    text_actionExecuter, execute,
                    PASS_ARG(text_actionExecuter, execute, actionPath, action_path)
                );

            }
        };

        template
<
            typename Action_text_actionExecuter_execute
        >
        inline static Ex_base_mainWindow_actionExecuted
        <
            Action_text_actionExecuter_execute
        >
        ex_base_mainWindow_actionExecuted
        (
            const Action_text_actionExecuter_execute &act_text_actionExecuter_execute
        )
        {
            return Ex_base_mainWindow_actionExecuted
            <
                Action_text_actionExecuter_execute
            >
            (
                act_text_actionExecuter_execute
            );
        }

        // base_mainWindow_notebook_tabAdded ---------------------------------------------------------------------------------------
        struct Tag_base_mainWindow_notebook_tabAdded {};

        template
        <
            typename Action_text_textEditor_tabAdded
        >
        struct Ex_base_mainWindow_notebook_tabAdded
        {
            typedef void result_type;

            const Action_text_textEditor_tabAdded &act_text_textEditor_tabAdded;

            Ex_base_mainWindow_notebook_tabAdded
            (
                const Action_text_textEditor_tabAdded &act_text_textEditor_tabAdded
            ) :
                act_text_textEditor_tabAdded(act_text_textEditor_tabAdded)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &notebook_tabId_in,
                const InArg1 &notebook_tabWidget_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(notebook_tabId, fileId);
                CREATE_ARG(notebook_tabWidget, notebook_tabWidget);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.tabAdded
                EXECUTE_ACTION
                (
                    text_textEditor, tabAdded,
                    PASS_ARG(text_textEditor, tabAdded, fileId, fileId),
                    PASS_ARG(text_textEditor, tabAdded, notebook_tabWidget, notebook_tabWidget)
                );

            }
        };

        template
<
            typename Action_text_textEditor_tabAdded
        >
        inline static Ex_base_mainWindow_notebook_tabAdded
        <
            Action_text_textEditor_tabAdded
        >
        ex_base_mainWindow_notebook_tabAdded
        (
            const Action_text_textEditor_tabAdded &act_text_textEditor_tabAdded
        )
        {
            return Ex_base_mainWindow_notebook_tabAdded
            <
                Action_text_textEditor_tabAdded
            >
            (
                act_text_textEditor_tabAdded
            );
        }

        // base_fileChooser_open_fileChosen ----------------------------------------------------------------------------------------
        struct Tag_base_fileChooser_open_fileChosen {};

        template
        <
            typename Action_text_fileOpener_openFile
        >
        struct Ex_base_fileChooser_open_fileChosen
        {
            typedef void result_type;

            const Action_text_fileOpener_openFile &act_text_fileOpener_openFile;

            Ex_base_fileChooser_open_fileChosen
            (
                const Action_text_fileOpener_openFile &act_text_fileOpener_openFile
            ) :
                act_text_fileOpener_openFile(act_text_fileOpener_openFile)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileName_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileName, fileName);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_fileOpener.actions.openFile
                EXECUTE_ACTION
                (
                    text_fileOpener, openFile,
                    PASS_ARG(text_fileOpener, openFile, fileName, fileName)
                );

            }
        };

        template
<
            typename Action_text_fileOpener_openFile
        >
        inline static Ex_base_fileChooser_open_fileChosen
        <
            Action_text_fileOpener_openFile
        >
        ex_base_fileChooser_open_fileChosen
        (
            const Action_text_fileOpener_openFile &act_text_fileOpener_openFile
        )
        {
            return Ex_base_fileChooser_open_fileChosen
            <
                Action_text_fileOpener_openFile
            >
            (
                act_text_fileOpener_openFile
            );
        }

        // base_fileChooser_saveAs_fileChosen --------------------------------------------------------------------------------------
        struct Tag_base_fileChooser_saveAs_fileChosen {};

        template
        <
            typename Action_text_textEditor_saveEditorContents_as
        >
        struct Ex_base_fileChooser_saveAs_fileChosen
        {
            typedef void result_type;

            const Action_text_textEditor_saveEditorContents_as &act_text_textEditor_saveEditorContents_as;

            Ex_base_fileChooser_saveAs_fileChosen
            (
                const Action_text_textEditor_saveEditorContents_as &act_text_textEditor_saveEditorContents_as
            ) :
                act_text_textEditor_saveEditorContents_as(act_text_textEditor_saveEditorContents_as)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileName_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileName, fileName);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.saveEditorContents.as
                EXECUTE_ACTION
                (
                    text_textEditor, saveEditorContents_as,
                    PASS_ARG(text_textEditor, saveEditorContents_as, fileName, fileName)
                );

            }
        };

        template
<
            typename Action_text_textEditor_saveEditorContents_as
        >
        inline static Ex_base_fileChooser_saveAs_fileChosen
        <
            Action_text_textEditor_saveEditorContents_as
        >
        ex_base_fileChooser_saveAs_fileChosen
        (
            const Action_text_textEditor_saveEditorContents_as &act_text_textEditor_saveEditorContents_as
        )
        {
            return Ex_base_fileChooser_saveAs_fileChosen
            <
                Action_text_textEditor_saveEditorContents_as
            >
            (
                act_text_textEditor_saveEditorContents_as
            );
        }

        // text_actionExecuter_edit_undo -------------------------------------------------------------------------------------------
        struct Tag_text_actionExecuter_edit_undo {};

        template
        <
            typename Action_text_textEditor_undo
        >
        struct Ex_text_actionExecuter_edit_undo
        {
            typedef void result_type;

            const Action_text_textEditor_undo &act_text_textEditor_undo;

            Ex_text_actionExecuter_edit_undo
            (
                const Action_text_textEditor_undo &act_text_textEditor_undo
            ) :
                act_text_textEditor_undo(act_text_textEditor_undo)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.undo
                EXECUTE_ACTION
                (
                    text_textEditor, undo,
                );

            }
        };

        template
<
            typename Action_text_textEditor_undo
        >
        inline static Ex_text_actionExecuter_edit_undo
        <
            Action_text_textEditor_undo
        >
        ex_text_actionExecuter_edit_undo
        (
            const Action_text_textEditor_undo &act_text_textEditor_undo
        )
        {
            return Ex_text_actionExecuter_edit_undo
            <
                Action_text_textEditor_undo
            >
            (
                act_text_textEditor_undo
            );
        }

        // text_actionExecuter_edit_redo -------------------------------------------------------------------------------------------
        struct Tag_text_actionExecuter_edit_redo {};

        template
        <
            typename Action_text_textEditor_redo
        >
        struct Ex_text_actionExecuter_edit_redo
        {
            typedef void result_type;

            const Action_text_textEditor_redo &act_text_textEditor_redo;

            Ex_text_actionExecuter_edit_redo
            (
                const Action_text_textEditor_redo &act_text_textEditor_redo
            ) :
                act_text_textEditor_redo(act_text_textEditor_redo)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.redo
                EXECUTE_ACTION
                (
                    text_textEditor, redo,
                );

            }
        };

        template
<
            typename Action_text_textEditor_redo
        >
        inline static Ex_text_actionExecuter_edit_redo
        <
            Action_text_textEditor_redo
        >
        ex_text_actionExecuter_edit_redo
        (
            const Action_text_textEditor_redo &act_text_textEditor_redo
        )
        {
            return Ex_text_actionExecuter_edit_redo
            <
                Action_text_textEditor_redo
            >
            (
                act_text_textEditor_redo
            );
        }

        // text_actionExecuter_edit_findReplace ------------------------------------------------------------------------------------
        struct Tag_text_actionExecuter_edit_findReplace {};

        template
        <
            typename Action_text_textEditor_findReplace_start
        >
        struct Ex_text_actionExecuter_edit_findReplace
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_start &act_text_textEditor_findReplace_start;

            Ex_text_actionExecuter_edit_findReplace
            (
                const Action_text_textEditor_findReplace_start &act_text_textEditor_findReplace_start
            ) :
                act_text_textEditor_findReplace_start(act_text_textEditor_findReplace_start)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.start
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_start,
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_start
        >
        inline static Ex_text_actionExecuter_edit_findReplace
        <
            Action_text_textEditor_findReplace_start
        >
        ex_text_actionExecuter_edit_findReplace
        (
            const Action_text_textEditor_findReplace_start &act_text_textEditor_findReplace_start
        )
        {
            return Ex_text_actionExecuter_edit_findReplace
            <
                Action_text_textEditor_findReplace_start
            >
            (
                act_text_textEditor_findReplace_start
            );
        }

        // text_findReplace_findPrevious -------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_findPrevious {};

        template
        <
            typename Action_text_textEditor_findReplace_findPrevious,
            typename Action_base_mainWindow_setPresent
        >
        struct Ex_text_findReplace_findPrevious
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_findPrevious &act_text_textEditor_findReplace_findPrevious;
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent;

            Ex_text_findReplace_findPrevious
            (
                const Action_text_textEditor_findReplace_findPrevious &act_text_textEditor_findReplace_findPrevious,
                const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
            ) :
                act_text_textEditor_findReplace_findPrevious(act_text_textEditor_findReplace_findPrevious),
                act_base_mainWindow_setPresent(act_base_mainWindow_setPresent)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.findPrevious
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_findPrevious,
                );

                // base_mainWindow.actions.setPresent
                EXECUTE_ACTION
                (
                    base_mainWindow, setPresent,
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_findPrevious,
            typename Action_base_mainWindow_setPresent
        >
        inline static Ex_text_findReplace_findPrevious
        <
            Action_text_textEditor_findReplace_findPrevious,
            Action_base_mainWindow_setPresent
        >
        ex_text_findReplace_findPrevious
        (
            const Action_text_textEditor_findReplace_findPrevious &act_text_textEditor_findReplace_findPrevious,
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
        )
        {
            return Ex_text_findReplace_findPrevious
            <
                Action_text_textEditor_findReplace_findPrevious,
                Action_base_mainWindow_setPresent
            >
            (
                act_text_textEditor_findReplace_findPrevious,
                act_base_mainWindow_setPresent
            );
        }

        // text_findReplace_findNext -----------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_findNext {};

        template
        <
            typename Action_text_textEditor_findReplace_findNext,
            typename Action_base_mainWindow_setPresent
        >
        struct Ex_text_findReplace_findNext
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_findNext &act_text_textEditor_findReplace_findNext;
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent;

            Ex_text_findReplace_findNext
            (
                const Action_text_textEditor_findReplace_findNext &act_text_textEditor_findReplace_findNext,
                const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
            ) :
                act_text_textEditor_findReplace_findNext(act_text_textEditor_findReplace_findNext),
                act_base_mainWindow_setPresent(act_base_mainWindow_setPresent)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.findNext
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_findNext,
                );

                // base_mainWindow.actions.setPresent
                EXECUTE_ACTION
                (
                    base_mainWindow, setPresent,
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_findNext,
            typename Action_base_mainWindow_setPresent
        >
        inline static Ex_text_findReplace_findNext
        <
            Action_text_textEditor_findReplace_findNext,
            Action_base_mainWindow_setPresent
        >
        ex_text_findReplace_findNext
        (
            const Action_text_textEditor_findReplace_findNext &act_text_textEditor_findReplace_findNext,
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
        )
        {
            return Ex_text_findReplace_findNext
            <
                Action_text_textEditor_findReplace_findNext,
                Action_base_mainWindow_setPresent
            >
            (
                act_text_textEditor_findReplace_findNext,
                act_base_mainWindow_setPresent
            );
        }

        // text_findReplace_replace ------------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_replace {};

        template
        <
            typename Action_text_textEditor_findReplace_replace,
            typename Action_base_mainWindow_setPresent
        >
        struct Ex_text_findReplace_replace
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_replace &act_text_textEditor_findReplace_replace;
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent;

            Ex_text_findReplace_replace
            (
                const Action_text_textEditor_findReplace_replace &act_text_textEditor_findReplace_replace,
                const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
            ) :
                act_text_textEditor_findReplace_replace(act_text_textEditor_findReplace_replace),
                act_base_mainWindow_setPresent(act_base_mainWindow_setPresent)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &replaceText_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(replaceText, findReplace_replaceText);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.replace
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_replace,
                    PASS_ARG(text_textEditor, findReplace_replace, findReplace_replaceText, findReplace_replaceText)
                );

                // base_mainWindow.actions.setPresent
                EXECUTE_ACTION
                (
                    base_mainWindow, setPresent,
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_replace,
            typename Action_base_mainWindow_setPresent
        >
        inline static Ex_text_findReplace_replace
        <
            Action_text_textEditor_findReplace_replace,
            Action_base_mainWindow_setPresent
        >
        ex_text_findReplace_replace
        (
            const Action_text_textEditor_findReplace_replace &act_text_textEditor_findReplace_replace,
            const Action_base_mainWindow_setPresent &act_base_mainWindow_setPresent
        )
        {
            return Ex_text_findReplace_replace
            <
                Action_text_textEditor_findReplace_replace,
                Action_base_mainWindow_setPresent
            >
            (
                act_text_textEditor_findReplace_replace,
                act_base_mainWindow_setPresent
            );
        }

        // text_findReplace_replaceAll ---------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_replaceAll {};

        template
        <
            typename Action_text_textEditor_findReplace_replaceAll
        >
        struct Ex_text_findReplace_replaceAll
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_replaceAll &act_text_textEditor_findReplace_replaceAll;

            Ex_text_findReplace_replaceAll
            (
                const Action_text_textEditor_findReplace_replaceAll &act_text_textEditor_findReplace_replaceAll
            ) :
                act_text_textEditor_findReplace_replaceAll(act_text_textEditor_findReplace_replaceAll)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &replaceText_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(replaceText, findReplace_replaceText);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.replaceAll
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_replaceAll,
                    PASS_ARG(text_textEditor, findReplace_replaceAll, findReplace_replaceText, findReplace_replaceText)
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_replaceAll
        >
        inline static Ex_text_findReplace_replaceAll
        <
            Action_text_textEditor_findReplace_replaceAll
        >
        ex_text_findReplace_replaceAll
        (
            const Action_text_textEditor_findReplace_replaceAll &act_text_textEditor_findReplace_replaceAll
        )
        {
            return Ex_text_findReplace_replaceAll
            <
                Action_text_textEditor_findReplace_replaceAll
            >
            (
                act_text_textEditor_findReplace_replaceAll
            );
        }

        // text_findReplace_closed -------------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_closed {};

        template
        <
            typename Action_text_textEditor_findReplace_restoreFind
        >
        struct Ex_text_findReplace_closed
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_restoreFind &act_text_textEditor_findReplace_restoreFind;

            Ex_text_findReplace_closed
            (
                const Action_text_textEditor_findReplace_restoreFind &act_text_textEditor_findReplace_restoreFind
            ) :
                act_text_textEditor_findReplace_restoreFind(act_text_textEditor_findReplace_restoreFind)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.restoreFind
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_restoreFind,
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_restoreFind
        >
        inline static Ex_text_findReplace_closed
        <
            Action_text_textEditor_findReplace_restoreFind
        >
        ex_text_findReplace_closed
        (
            const Action_text_textEditor_findReplace_restoreFind &act_text_textEditor_findReplace_restoreFind
        )
        {
            return Ex_text_findReplace_closed
            <
                Action_text_textEditor_findReplace_restoreFind
            >
            (
                act_text_textEditor_findReplace_restoreFind
            );
        }

        // text_findReplace_stateChanged -------------------------------------------------------------------------------------------
        struct Tag_text_findReplace_stateChanged {};

        template
        <
            typename Action_text_textEditor_findReplace_stateChanged
        >
        struct Ex_text_findReplace_stateChanged
        {
            typedef void result_type;

            const Action_text_textEditor_findReplace_stateChanged &act_text_textEditor_findReplace_stateChanged;

            Ex_text_findReplace_stateChanged
            (
                const Action_text_textEditor_findReplace_stateChanged &act_text_textEditor_findReplace_stateChanged
            ) :
                act_text_textEditor_findReplace_stateChanged(act_text_textEditor_findReplace_stateChanged)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &findText_in,
                const InArg1 &checks_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(checks, findReplace_checks);
                CREATE_ARG(findText, findReplace_findText);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.findReplace.stateChanged
                EXECUTE_ACTION
                (
                    text_textEditor, findReplace_stateChanged,
                    PASS_ARG(text_textEditor, findReplace_stateChanged, findReplace_findText, findReplace_findText),
                    PASS_ARG(text_textEditor, findReplace_stateChanged, findReplace_checks, findReplace_checks)
                );

            }
        };

        template
<
            typename Action_text_textEditor_findReplace_stateChanged
        >
        inline static Ex_text_findReplace_stateChanged
        <
            Action_text_textEditor_findReplace_stateChanged
        >
        ex_text_findReplace_stateChanged
        (
            const Action_text_textEditor_findReplace_stateChanged &act_text_textEditor_findReplace_stateChanged
        )
        {
            return Ex_text_findReplace_stateChanged
            <
                Action_text_textEditor_findReplace_stateChanged
            >
            (
                act_text_textEditor_findReplace_stateChanged
            );
        }

        // text_textEditor_newTBTabRequested ---------------------------------------------------------------------------------------
        struct Tag_text_textEditor_newTBTabRequested {};

        template
        <
            typename Action_base_mainWindow_notebook_openNewTab
        >
        struct Ex_text_textEditor_newTBTabRequested
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_openNewTab &act_base_mainWindow_notebook_openNewTab;

            Ex_text_textEditor_newTBTabRequested
            (
                const Action_base_mainWindow_notebook_openNewTab &act_base_mainWindow_notebook_openNewTab
            ) :
                act_base_mainWindow_notebook_openNewTab(act_base_mainWindow_notebook_openNewTab)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2,
                typename InArg3
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &notebook_tabName_in,
                const InArg2 &notebook_tabTooltip_in,
                const InArg3 &notebook_tabWidget_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(notebook_tabName, notebook_tabName);
                CREATE_ARG(notebook_tabTooltip, notebook_tabTooltip);
                CREATE_ARG(notebook_tabWidget, notebook_tabWidget);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.openNewTab
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_openNewTab,
                    PASS_ARG(base_mainWindow, notebook_openNewTab, notebook_tabId, fileId),
                    PASS_ARG(base_mainWindow, notebook_openNewTab, notebook_tabName, notebook_tabName),
                    PASS_ARG(base_mainWindow, notebook_openNewTab, notebook_tabTooltip, notebook_tabTooltip),
                    PASS_ARG(base_mainWindow, notebook_openNewTab, notebook_tabWidget, notebook_tabWidget)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_openNewTab
        >
        inline static Ex_text_textEditor_newTBTabRequested
        <
            Action_base_mainWindow_notebook_openNewTab
        >
        ex_text_textEditor_newTBTabRequested
        (
            const Action_base_mainWindow_notebook_openNewTab &act_base_mainWindow_notebook_openNewTab
        )
        {
            return Ex_text_textEditor_newTBTabRequested
            <
                Action_base_mainWindow_notebook_openNewTab
            >
            (
                act_base_mainWindow_notebook_openNewTab
            );
        }

        // text_textEditor_parseText -----------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_parseText {};

        template
        <
            typename Action_text_textHighlighter_parseText
        >
        struct Ex_text_textEditor_parseText
        {
            typedef void result_type;

            const Action_text_textHighlighter_parseText &act_text_textHighlighter_parseText;

            Ex_text_textEditor_parseText
            (
                const Action_text_textHighlighter_parseText &act_text_textHighlighter_parseText
            ) :
                act_text_textHighlighter_parseText(act_text_textHighlighter_parseText)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &parserId_in,
                const InArg2 &textBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(parserId, parserId);
                CREATE_ARG(textBuffer, textBuffer);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textHighlighter.actions.parseText
                EXECUTE_ACTION
                (
                    text_textHighlighter, parseText,
                    PASS_ARG(text_textHighlighter, parseText, fileId, fileId),
                    PASS_ARG(text_textHighlighter, parseText, parserId, parserId),
                    PASS_ARG(text_textHighlighter, parseText, textBuffer, textBuffer)
                );

            }
        };

        template
<
            typename Action_text_textHighlighter_parseText
        >
        inline static Ex_text_textEditor_parseText
        <
            Action_text_textHighlighter_parseText
        >
        ex_text_textEditor_parseText
        (
            const Action_text_textHighlighter_parseText &act_text_textHighlighter_parseText
        )
        {
            return Ex_text_textEditor_parseText
            <
                Action_text_textHighlighter_parseText
            >
            (
                act_text_textHighlighter_parseText
            );
        }

        // text_textEditor_saveEditorContents_current ------------------------------------------------------------------------------
        struct Tag_text_textEditor_saveEditorContents_current {};

        template
        <
            typename Action_text_fileOpener_saveFile_current
        >
        struct Ex_text_textEditor_saveEditorContents_current
        {
            typedef void result_type;

            const Action_text_fileOpener_saveFile_current &act_text_fileOpener_saveFile_current;

            Ex_text_textEditor_saveEditorContents_current
            (
                const Action_text_fileOpener_saveFile_current &act_text_fileOpener_saveFile_current
            ) :
                act_text_fileOpener_saveFile_current(act_text_fileOpener_saveFile_current)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &textBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(textBuffer, textBuffer);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_fileOpener.actions.saveFile.current
                EXECUTE_ACTION
                (
                    text_fileOpener, saveFile_current,
                    PASS_ARG(text_fileOpener, saveFile_current, fileId, fileId),
                    PASS_ARG(text_fileOpener, saveFile_current, textBuffer, textBuffer)
                );

            }
        };

        template
<
            typename Action_text_fileOpener_saveFile_current
        >
        inline static Ex_text_textEditor_saveEditorContents_current
        <
            Action_text_fileOpener_saveFile_current
        >
        ex_text_textEditor_saveEditorContents_current
        (
            const Action_text_fileOpener_saveFile_current &act_text_fileOpener_saveFile_current
        )
        {
            return Ex_text_textEditor_saveEditorContents_current
            <
                Action_text_fileOpener_saveFile_current
            >
            (
                act_text_fileOpener_saveFile_current
            );
        }

        // text_textEditor_saveEditorContents_as -----------------------------------------------------------------------------------
        struct Tag_text_textEditor_saveEditorContents_as {};

        template
        <
            typename Action_text_fileOpener_saveFile_as
        >
        struct Ex_text_textEditor_saveEditorContents_as
        {
            typedef void result_type;

            const Action_text_fileOpener_saveFile_as &act_text_fileOpener_saveFile_as;

            Ex_text_textEditor_saveEditorContents_as
            (
                const Action_text_fileOpener_saveFile_as &act_text_fileOpener_saveFile_as
            ) :
                act_text_fileOpener_saveFile_as(act_text_fileOpener_saveFile_as)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &fileName_in,
                const InArg2 &textBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(fileName, fileName);
                CREATE_ARG(textBuffer, textBuffer);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_fileOpener.actions.saveFile.as
                EXECUTE_ACTION
                (
                    text_fileOpener, saveFile_as,
                    PASS_ARG(text_fileOpener, saveFile_as, fileId, fileId),
                    PASS_ARG(text_fileOpener, saveFile_as, fileName, fileName),
                    PASS_ARG(text_fileOpener, saveFile_as, textBuffer, textBuffer)
                );

            }
        };

        template
<
            typename Action_text_fileOpener_saveFile_as
        >
        inline static Ex_text_textEditor_saveEditorContents_as
        <
            Action_text_fileOpener_saveFile_as
        >
        ex_text_textEditor_saveEditorContents_as
        (
            const Action_text_fileOpener_saveFile_as &act_text_fileOpener_saveFile_as
        )
        {
            return Ex_text_textEditor_saveEditorContents_as
            <
                Action_text_fileOpener_saveFile_as
            >
            (
                act_text_fileOpener_saveFile_as
            );
        }

        // text_textEditor_contentsModified ----------------------------------------------------------------------------------------
        struct Tag_text_textEditor_contentsModified {};

        template
        <
            typename Action_base_mainWindow_notebook_tabContentsModified
        >
        struct Ex_text_textEditor_contentsModified
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_tabContentsModified &act_base_mainWindow_notebook_tabContentsModified;

            Ex_text_textEditor_contentsModified
            (
                const Action_base_mainWindow_notebook_tabContentsModified &act_base_mainWindow_notebook_tabContentsModified
            ) :
                act_base_mainWindow_notebook_tabContentsModified(act_base_mainWindow_notebook_tabContentsModified)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.tabContentsModified
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_tabContentsModified,
                    PASS_ARG(base_mainWindow, notebook_tabContentsModified, notebook_tabId, fileId)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_tabContentsModified
        >
        inline static Ex_text_textEditor_contentsModified
        <
            Action_base_mainWindow_notebook_tabContentsModified
        >
        ex_text_textEditor_contentsModified
        (
            const Action_base_mainWindow_notebook_tabContentsModified &act_base_mainWindow_notebook_tabContentsModified
        )
        {
            return Ex_text_textEditor_contentsModified
            <
                Action_base_mainWindow_notebook_tabContentsModified
            >
            (
                act_base_mainWindow_notebook_tabContentsModified
            );
        }

        // text_textEditor_contentsAreOriginal -------------------------------------------------------------------------------------
        struct Tag_text_textEditor_contentsAreOriginal {};

        template
        <
            typename Action_base_mainWindow_notebook_tabContentsAreOriginal
        >
        struct Ex_text_textEditor_contentsAreOriginal
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_tabContentsAreOriginal &act_base_mainWindow_notebook_tabContentsAreOriginal;

            Ex_text_textEditor_contentsAreOriginal
            (
                const Action_base_mainWindow_notebook_tabContentsAreOriginal &act_base_mainWindow_notebook_tabContentsAreOriginal
            ) :
                act_base_mainWindow_notebook_tabContentsAreOriginal(act_base_mainWindow_notebook_tabContentsAreOriginal)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.tabContentsAreOriginal
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_tabContentsAreOriginal,
                    PASS_ARG(base_mainWindow, notebook_tabContentsAreOriginal, notebook_tabId, fileId)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_tabContentsAreOriginal
        >
        inline static Ex_text_textEditor_contentsAreOriginal
        <
            Action_base_mainWindow_notebook_tabContentsAreOriginal
        >
        ex_text_textEditor_contentsAreOriginal
        (
            const Action_base_mainWindow_notebook_tabContentsAreOriginal &act_base_mainWindow_notebook_tabContentsAreOriginal
        )
        {
            return Ex_text_textEditor_contentsAreOriginal
            <
                Action_base_mainWindow_notebook_tabContentsAreOriginal
            >
            (
                act_base_mainWindow_notebook_tabContentsAreOriginal
            );
        }

        // text_textEditor_tabDataChanged ------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_tabDataChanged {};

        template
        <
            typename Action_base_mainWindow_notebook_tabDataChanged
        >
        struct Ex_text_textEditor_tabDataChanged
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_tabDataChanged &act_base_mainWindow_notebook_tabDataChanged;

            Ex_text_textEditor_tabDataChanged
            (
                const Action_base_mainWindow_notebook_tabDataChanged &act_base_mainWindow_notebook_tabDataChanged
            ) :
                act_base_mainWindow_notebook_tabDataChanged(act_base_mainWindow_notebook_tabDataChanged)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &notebook_tabName_in,
                const InArg2 &notebook_tabTooltip_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(notebook_tabName, notebook_tabName);
                CREATE_ARG(notebook_tabTooltip, notebook_tabTooltip);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.tabDataChanged
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_tabDataChanged,
                    PASS_ARG(base_mainWindow, notebook_tabDataChanged, notebook_tabId, fileId),
                    PASS_ARG(base_mainWindow, notebook_tabDataChanged, notebook_tabName, notebook_tabName),
                    PASS_ARG(base_mainWindow, notebook_tabDataChanged, notebook_tabTooltip, notebook_tabTooltip)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_tabDataChanged
        >
        inline static Ex_text_textEditor_tabDataChanged
        <
            Action_base_mainWindow_notebook_tabDataChanged
        >
        ex_text_textEditor_tabDataChanged
        (
            const Action_base_mainWindow_notebook_tabDataChanged &act_base_mainWindow_notebook_tabDataChanged
        )
        {
            return Ex_text_textEditor_tabDataChanged
            <
                Action_base_mainWindow_notebook_tabDataChanged
            >
            (
                act_base_mainWindow_notebook_tabDataChanged
            );
        }

        // text_textEditor_editorClosed --------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_editorClosed {};

        template
        <
            typename Action_text_fileOpener_fileClosed,
            typename Action_base_mainWindow_notebook_closeTab
        >
        struct Ex_text_textEditor_editorClosed
        {
            typedef void result_type;

            const Action_text_fileOpener_fileClosed &act_text_fileOpener_fileClosed;
            const Action_base_mainWindow_notebook_closeTab &act_base_mainWindow_notebook_closeTab;

            Ex_text_textEditor_editorClosed
            (
                const Action_text_fileOpener_fileClosed &act_text_fileOpener_fileClosed,
                const Action_base_mainWindow_notebook_closeTab &act_base_mainWindow_notebook_closeTab
            ) :
                act_text_fileOpener_fileClosed(act_text_fileOpener_fileClosed),
                act_base_mainWindow_notebook_closeTab(act_base_mainWindow_notebook_closeTab)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_fileOpener.actions.fileClosed
                EXECUTE_ACTION
                (
                    text_fileOpener, fileClosed,
                    PASS_ARG(text_fileOpener, fileClosed, fileId, fileId)
                );

                // base_mainWindow.actions.notebook.closeTab
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_closeTab,
                    PASS_ARG(base_mainWindow, notebook_closeTab, notebook_tabId, fileId)
                );

            }
        };

        template
<
            typename Action_text_fileOpener_fileClosed,
            typename Action_base_mainWindow_notebook_closeTab
        >
        inline static Ex_text_textEditor_editorClosed
        <
            Action_text_fileOpener_fileClosed,
            Action_base_mainWindow_notebook_closeTab
        >
        ex_text_textEditor_editorClosed
        (
            const Action_text_fileOpener_fileClosed &act_text_fileOpener_fileClosed,
            const Action_base_mainWindow_notebook_closeTab &act_base_mainWindow_notebook_closeTab
        )
        {
            return Ex_text_textEditor_editorClosed
            <
                Action_text_fileOpener_fileClosed,
                Action_base_mainWindow_notebook_closeTab
            >
            (
                act_text_fileOpener_fileClosed,
                act_base_mainWindow_notebook_closeTab
            );
        }

        // text_textEditor_findReplace_setFindText ---------------------------------------------------------------------------------
        struct Tag_text_textEditor_findReplace_setFindText {};

        template
        <
            typename Action_text_findReplace_setTexts
        >
        struct Ex_text_textEditor_findReplace_setFindText
        {
            typedef void result_type;

            const Action_text_findReplace_setTexts &act_text_findReplace_setTexts;

            Ex_text_textEditor_findReplace_setFindText
            (
                const Action_text_findReplace_setTexts &act_text_findReplace_setTexts
            ) :
                act_text_findReplace_setTexts(act_text_findReplace_setTexts)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &findReplace_findText_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(findReplace_findText, findReplace_findText);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_findReplace.actions.setTexts
                EXECUTE_ACTION
                (
                    text_findReplace, setTexts,
                    PASS_ARG(text_findReplace, setTexts, findText, findReplace_findText)
                );

            }
        };

        template
<
            typename Action_text_findReplace_setTexts
        >
        inline static Ex_text_textEditor_findReplace_setFindText
        <
            Action_text_findReplace_setTexts
        >
        ex_text_textEditor_findReplace_setFindText
        (
            const Action_text_findReplace_setTexts &act_text_findReplace_setTexts
        )
        {
            return Ex_text_textEditor_findReplace_setFindText
            <
                Action_text_findReplace_setTexts
            >
            (
                act_text_findReplace_setTexts
            );
        }

        // text_textEditor_registerAction ------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_registerAction {};

        template
        <
            typename Action_base_mainWindow_addAction
        >
        struct Ex_text_textEditor_registerAction
        {
            typedef void result_type;

            const Action_base_mainWindow_addAction &act_base_mainWindow_addAction;

            Ex_text_textEditor_registerAction
            (
                const Action_base_mainWindow_addAction &act_base_mainWindow_addAction
            ) :
                act_base_mainWindow_addAction(act_base_mainWindow_addAction)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &action_pathDataList_in,
                const InArg1 &action_data_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(action_data, action_data);
                CREATE_ARG(action_pathDataList, action_pathDataList);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.addAction
                EXECUTE_ACTION
                (
                    base_mainWindow, addAction,
                    PASS_ARG(base_mainWindow, addAction, actionPathDataList, action_pathDataList),
                    PASS_ARG(base_mainWindow, addAction, actionData, action_data)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_addAction
        >
        inline static Ex_text_textEditor_registerAction
        <
            Action_base_mainWindow_addAction
        >
        ex_text_textEditor_registerAction
        (
            const Action_base_mainWindow_addAction &act_base_mainWindow_addAction
        )
        {
            return Ex_text_textEditor_registerAction
            <
                Action_base_mainWindow_addAction
            >
            (
                act_base_mainWindow_addAction
            );
        }

        // text_textEditor_clearActions --------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_clearActions {};

        template
        <
            typename Action_base_mainWindow_clearActions
        >
        struct Ex_text_textEditor_clearActions
        {
            typedef void result_type;

            const Action_base_mainWindow_clearActions &act_base_mainWindow_clearActions;

            Ex_text_textEditor_clearActions
            (
                const Action_base_mainWindow_clearActions &act_base_mainWindow_clearActions
            ) :
                act_base_mainWindow_clearActions(act_base_mainWindow_clearActions)
            {}

            void operator()
            (
            ) const
            {
                // Arguments -----------------------------------------------------------------

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.clearActions
                EXECUTE_ACTION
                (
                    base_mainWindow, clearActions,
                );

            }
        };

        template
<
            typename Action_base_mainWindow_clearActions
        >
        inline static Ex_text_textEditor_clearActions
        <
            Action_base_mainWindow_clearActions
        >
        ex_text_textEditor_clearActions
        (
            const Action_base_mainWindow_clearActions &act_base_mainWindow_clearActions
        )
        {
            return Ex_text_textEditor_clearActions
            <
                Action_base_mainWindow_clearActions
            >
            (
                act_base_mainWindow_clearActions
            );
        }

        // text_textEditor_addSeparator --------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_addSeparator {};

        template
        <
            typename Action_base_mainWindow_addSeparator
        >
        struct Ex_text_textEditor_addSeparator
        {
            typedef void result_type;

            const Action_base_mainWindow_addSeparator &act_base_mainWindow_addSeparator;

            Ex_text_textEditor_addSeparator
            (
                const Action_base_mainWindow_addSeparator &act_base_mainWindow_addSeparator
            ) :
                act_base_mainWindow_addSeparator(act_base_mainWindow_addSeparator)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &action_pathDataList_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(action_pathDataList, action_pathDataList);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.addSeparator
                EXECUTE_ACTION
                (
                    base_mainWindow, addSeparator,
                    PASS_ARG(base_mainWindow, addSeparator, actionPathDataList, action_pathDataList)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_addSeparator
        >
        inline static Ex_text_textEditor_addSeparator
        <
            Action_base_mainWindow_addSeparator
        >
        ex_text_textEditor_addSeparator
        (
            const Action_base_mainWindow_addSeparator &act_base_mainWindow_addSeparator
        )
        {
            return Ex_text_textEditor_addSeparator
            <
                Action_base_mainWindow_addSeparator
            >
            (
                act_base_mainWindow_addSeparator
            );
        }

        // text_textEditor_selectFile ----------------------------------------------------------------------------------------------
        struct Tag_text_textEditor_selectFile {};

        template
        <
            typename Action_base_mainWindow_notebook_selectTab
        >
        struct Ex_text_textEditor_selectFile
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab;

            Ex_text_textEditor_selectFile
            (
                const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab
            ) :
                act_base_mainWindow_notebook_selectTab(act_base_mainWindow_notebook_selectTab)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.selectTab
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_selectTab,
                    PASS_ARG(base_mainWindow, notebook_selectTab, notebook_tabId, fileId)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_selectTab
        >
        inline static Ex_text_textEditor_selectFile
        <
            Action_base_mainWindow_notebook_selectTab
        >
        ex_text_textEditor_selectFile
        (
            const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab
        )
        {
            return Ex_text_textEditor_selectFile
            <
                Action_base_mainWindow_notebook_selectTab
            >
            (
                act_base_mainWindow_notebook_selectTab
            );
        }

        // text_textHighlighter_applyTags ------------------------------------------------------------------------------------------
        struct Tag_text_textHighlighter_applyTags {};

        template
        <
            typename Action_text_textEditor_applyTags
        >
        struct Ex_text_textHighlighter_applyTags
        {
            typedef void result_type;

            const Action_text_textEditor_applyTags &act_text_textEditor_applyTags;

            Ex_text_textHighlighter_applyTags
            (
                const Action_text_textEditor_applyTags &act_text_textEditor_applyTags
            ) :
                act_text_textEditor_applyTags(act_text_textEditor_applyTags)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &tags_in,
                const InArg2 &tagsToApply_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(tags, tags);
                CREATE_ARG(tagsToApply, tagsToApply);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.applyTags
                EXECUTE_ACTION
                (
                    text_textEditor, applyTags,
                    PASS_ARG(text_textEditor, applyTags, fileId, fileId),
                    PASS_ARG(text_textEditor, applyTags, tags, tags),
                    PASS_ARG(text_textEditor, applyTags, tagsToApply, tagsToApply)
                );

            }
        };

        template
<
            typename Action_text_textEditor_applyTags
        >
        inline static Ex_text_textHighlighter_applyTags
        <
            Action_text_textEditor_applyTags
        >
        ex_text_textHighlighter_applyTags
        (
            const Action_text_textEditor_applyTags &act_text_textEditor_applyTags
        )
        {
            return Ex_text_textHighlighter_applyTags
            <
                Action_text_textEditor_applyTags
            >
            (
                act_text_textEditor_applyTags
            );
        }

        // text_fileOpener_openingNewFile ------------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_openingNewFile {};

        template
        <
            typename Action_text_textEditor_openEditor
        >
        struct Ex_text_fileOpener_openingNewFile
        {
            typedef void result_type;

            const Action_text_textEditor_openEditor &act_text_textEditor_openEditor;

            Ex_text_fileOpener_openingNewFile
            (
                const Action_text_textEditor_openEditor &act_text_textEditor_openEditor
            ) :
                act_text_textEditor_openEditor(act_text_textEditor_openEditor)
            {}

            template
            <
                typename InArg0,
                typename InArg1,
                typename InArg2
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &fileName_in,
                const InArg2 &fileType_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(fileName, fileName);
                CREATE_ARG(fileType, parserId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.openEditor
                EXECUTE_ACTION
                (
                    text_textEditor, openEditor,
                    PASS_ARG(text_textEditor, openEditor, fileId, fileId),
                    PASS_ARG(text_textEditor, openEditor, fileName, fileName),
                    PASS_ARG(text_textEditor, openEditor, parserId, parserId)
                );

            }
        };

        template
<
            typename Action_text_textEditor_openEditor
        >
        inline static Ex_text_fileOpener_openingNewFile
        <
            Action_text_textEditor_openEditor
        >
        ex_text_fileOpener_openingNewFile
        (
            const Action_text_textEditor_openEditor &act_text_textEditor_openEditor
        )
        {
            return Ex_text_fileOpener_openingNewFile
            <
                Action_text_textEditor_openEditor
            >
            (
                act_text_textEditor_openEditor
            );
        }

        // text_fileOpener_textFound -----------------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_textFound {};

        template
        <
            typename Action_text_textEditor_addText
        >
        struct Ex_text_fileOpener_textFound
        {
            typedef void result_type;

            const Action_text_textEditor_addText &act_text_textEditor_addText;

            Ex_text_fileOpener_textFound
            (
                const Action_text_textEditor_addText &act_text_textEditor_addText
            ) :
                act_text_textEditor_addText(act_text_textEditor_addText)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &textBuffer_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(textBuffer, textBuffer);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.addText
                EXECUTE_ACTION
                (
                    text_textEditor, addText,
                    PASS_ARG(text_textEditor, addText, fileId, fileId),
                    PASS_ARG(text_textEditor, addText, textBuffer, textBuffer)
                );

            }
        };

        template
<
            typename Action_text_textEditor_addText
        >
        inline static Ex_text_fileOpener_textFound
        <
            Action_text_textEditor_addText
        >
        ex_text_fileOpener_textFound
        (
            const Action_text_textEditor_addText &act_text_textEditor_addText
        )
        {
            return Ex_text_fileOpener_textFound
            <
                Action_text_textEditor_addText
            >
            (
                act_text_textEditor_addText
            );
        }

        // text_fileOpener_fileAlreadyOpened ---------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_fileAlreadyOpened {};

        template
        <
            typename Action_base_mainWindow_notebook_selectTab
        >
        struct Ex_text_fileOpener_fileAlreadyOpened
        {
            typedef void result_type;

            const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab;

            Ex_text_fileOpener_fileAlreadyOpened
            (
                const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab
            ) :
                act_base_mainWindow_notebook_selectTab(act_base_mainWindow_notebook_selectTab)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_mainWindow.actions.notebook.selectTab
                EXECUTE_ACTION
                (
                    base_mainWindow, notebook_selectTab,
                    PASS_ARG(base_mainWindow, notebook_selectTab, notebook_tabId, fileId)
                );

            }
        };

        template
<
            typename Action_base_mainWindow_notebook_selectTab
        >
        inline static Ex_text_fileOpener_fileAlreadyOpened
        <
            Action_base_mainWindow_notebook_selectTab
        >
        ex_text_fileOpener_fileAlreadyOpened
        (
            const Action_base_mainWindow_notebook_selectTab &act_base_mainWindow_notebook_selectTab
        )
        {
            return Ex_text_fileOpener_fileAlreadyOpened
            <
                Action_base_mainWindow_notebook_selectTab
            >
            (
                act_base_mainWindow_notebook_selectTab
            );
        }

        // text_fileOpener_fileSaved -----------------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_fileSaved {};

        template
        <
            typename Action_text_textEditor_editorTypeChanged,
            typename Action_text_textEditor_savingDone
        >
        struct Ex_text_fileOpener_fileSaved
        {
            typedef void result_type;

            const Action_text_textEditor_editorTypeChanged &act_text_textEditor_editorTypeChanged;
            const Action_text_textEditor_savingDone &act_text_textEditor_savingDone;

            Ex_text_fileOpener_fileSaved
            (
                const Action_text_textEditor_editorTypeChanged &act_text_textEditor_editorTypeChanged,
                const Action_text_textEditor_savingDone &act_text_textEditor_savingDone
            ) :
                act_text_textEditor_editorTypeChanged(act_text_textEditor_editorTypeChanged),
                act_text_textEditor_savingDone(act_text_textEditor_savingDone)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &fileType_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);
                CREATE_ARG(fileType, parserId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.editorTypeChanged
                EXECUTE_ACTION
                (
                    text_textEditor, editorTypeChanged,
                    PASS_ARG(text_textEditor, editorTypeChanged, fileId, fileId),
                    PASS_ARG(text_textEditor, editorTypeChanged, parserId, parserId)
                );

                // text_textEditor.actions.savingDone
                EXECUTE_ACTION
                (
                    text_textEditor, savingDone,
                    PASS_ARG(text_textEditor, savingDone, fileId, fileId)
                );

            }
        };

        template
<
            typename Action_text_textEditor_editorTypeChanged,
            typename Action_text_textEditor_savingDone
        >
        inline static Ex_text_fileOpener_fileSaved
        <
            Action_text_textEditor_editorTypeChanged,
            Action_text_textEditor_savingDone
        >
        ex_text_fileOpener_fileSaved
        (
            const Action_text_textEditor_editorTypeChanged &act_text_textEditor_editorTypeChanged,
            const Action_text_textEditor_savingDone &act_text_textEditor_savingDone
        )
        {
            return Ex_text_fileOpener_fileSaved
            <
                Action_text_textEditor_editorTypeChanged,
                Action_text_textEditor_savingDone
            >
            (
                act_text_textEditor_editorTypeChanged,
                act_text_textEditor_savingDone
            );
        }

        // text_fileOpener_fileOpened ----------------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_fileOpened {};

        template
        <
            typename Action_text_textEditor_openingDone
        >
        struct Ex_text_fileOpener_fileOpened
        {
            typedef void result_type;

            const Action_text_textEditor_openingDone &act_text_textEditor_openingDone;

            Ex_text_fileOpener_fileOpened
            (
                const Action_text_textEditor_openingDone &act_text_textEditor_openingDone
            ) :
                act_text_textEditor_openingDone(act_text_textEditor_openingDone)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileId, fileId);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // text_textEditor.actions.openingDone
                EXECUTE_ACTION
                (
                    text_textEditor, openingDone,
                    PASS_ARG(text_textEditor, openingDone, fileId, fileId)
                );

            }
        };

        template
<
            typename Action_text_textEditor_openingDone
        >
        inline static Ex_text_fileOpener_fileOpened
        <
            Action_text_textEditor_openingDone
        >
        ex_text_fileOpener_fileOpened
        (
            const Action_text_textEditor_openingDone &act_text_textEditor_openingDone
        )
        {
            return Ex_text_fileOpener_fileOpened
            <
                Action_text_textEditor_openingDone
            >
            (
                act_text_textEditor_openingDone
            );
        }

        // text_fileOpener_fileSelected --------------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_fileSelected {};

        template
        <
            typename Action_base_fileChooser_saveAs_setFileName
        >
        struct Ex_text_fileOpener_fileSelected
        {
            typedef void result_type;

            const Action_base_fileChooser_saveAs_setFileName &act_base_fileChooser_saveAs_setFileName;

            Ex_text_fileOpener_fileSelected
            (
                const Action_base_fileChooser_saveAs_setFileName &act_base_fileChooser_saveAs_setFileName
            ) :
                act_base_fileChooser_saveAs_setFileName(act_base_fileChooser_saveAs_setFileName)
            {}

            template
            <
                typename InArg0,
                typename InArg1
            >
            void operator()
            (
                const InArg0 &fileId_in,
                const InArg1 &fileName_in
            ) const
            {
                // Arguments -----------------------------------------------------------------
                CREATE_ARG(fileName, fileName);

                // Providers -----------------------------------------------------------------
                // Actions -------------------------------------------------------------------
                // base_fileChooser_saveAs.actions.setFileName
                EXECUTE_ACTION
                (
                    base_fileChooser_saveAs, setFileName,
                    PASS_ARG(base_fileChooser_saveAs, setFileName, fileName, fileName)
                );

            }
        };

        template
<
            typename Action_base_fileChooser_saveAs_setFileName
        >
        inline static Ex_text_fileOpener_fileSelected
        <
            Action_base_fileChooser_saveAs_setFileName
        >
        ex_text_fileOpener_fileSelected
        (
            const Action_base_fileChooser_saveAs_setFileName &act_base_fileChooser_saveAs_setFileName
        )
        {
            return Ex_text_fileOpener_fileSelected
            <
                Action_base_fileChooser_saveAs_setFileName
            >
            (
                act_base_fileChooser_saveAs_setFileName
            );
        }

        // text_fileOpener_savingUnnamedFile ---------------------------------------------------------------------------------------
        struct Tag_text_fileOpener_savingUnnamedFile {};

        template
        <
            typename Action_base_fileChooser_saveAs_open
        >
        struct Ex_text_fileOpener_savingUnnamedFile
        {
            typedef void result_type;

            const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open;

            Ex_text_fileOpener_savingUnnamedFile
            (
                const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open
            ) :
                act_base_fileChooser_saveAs_open(act_base_fileChooser_saveAs_open)
            {}

            template
            <
                typename InArg0
            >
            void operator()
            (
                const InArg0 &fileId_in
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
        inline static Ex_text_fileOpener_savingUnnamedFile
        <
            Action_base_fileChooser_saveAs_open
        >
        ex_text_fileOpener_savingUnnamedFile
        (
            const Action_base_fileChooser_saveAs_open &act_base_fileChooser_saveAs_open
        )
        {
            return Ex_text_fileOpener_savingUnnamedFile
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
            typename Connectors::BaseActionExecuter &base_actionExecuter;
            typename Connectors::MainWindow &base_mainWindow;
            typename Connectors::FileChooser &base_fileChooser_open;
            typename Connectors::FileChooser &base_fileChooser_saveAs;
            typename Connectors::TextActionExecuter &text_actionExecuter;
            typename Connectors::FindReplace &text_findReplace;
            typename Connectors::TextEditor &text_textEditor;
            typename Connectors::TextHighlighter &text_textHighlighter;
            typename Connectors::FileOpener &text_fileOpener;

            ConnInstances(const chila::connectionTools::lib::codegen::ConnectorMap &cMap) :
                base_actionExecuter(cMap.get<typename Connectors::BaseActionExecuter>("base.actionExecuter")),
                base_mainWindow(cMap.get<typename Connectors::MainWindow>("base.mainWindow")),
                base_fileChooser_open(cMap.get<typename Connectors::FileChooser>("base.fileChooser.open")),
                base_fileChooser_saveAs(cMap.get<typename Connectors::FileChooser>("base.fileChooser.saveAs")),
                text_actionExecuter(cMap.get<typename Connectors::TextActionExecuter>("text.actionExecuter")),
                text_findReplace(cMap.get<typename Connectors::FindReplace>("text.findReplace")),
                text_textEditor(cMap.get<typename Connectors::TextEditor>("text.textEditor")),
                text_textHighlighter(cMap.get<typename Connectors::TextHighlighter>("text.textHighlighter")),
                text_fileOpener(cMap.get<typename Connectors::FileOpener>("text.fileOpener"))
            {}
        };

        // base_actionExecuter ----------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_actionExecuter(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_actionExecuter.events.file_new.addFun(ex_base_actionExecuter_file_new
            (
                cInstances.text_textEditor.actions.newEditor
            ));
            cInstances.base_actionExecuter.events.file_save.addFun(ex_base_actionExecuter_file_save
            (
                cInstances.text_textEditor.actions.saveEditorContents_current
            ));
            cInstances.base_actionExecuter.events.file_saveAll.addFun(ex_base_actionExecuter_file_saveAll
            (
                cInstances.text_textEditor.actions.saveAll
            ));
            cInstances.base_actionExecuter.events.file_close.addFun(ex_base_actionExecuter_file_close
            (
                cInstances.text_textEditor.actions.closingSelectedEditor
            ));
            cInstances.base_actionExecuter.events.file_open.addFun(ex_base_actionExecuter_file_open
            (
                cInstances.text_textEditor.actions.newEditor
            ));
        }

        // base_mainWindow --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_mainWindow(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_mainWindow.events.notebook_closingTab.addFun(ex_base_mainWindow_notebook_closingTab
            (
                cInstances.text_textEditor.actions.closingEditor
            ));
            cInstances.base_mainWindow.events.notebook_tabSelected.addFun(ex_base_mainWindow_notebook_tabSelected
            (
                cInstances.text_fileOpener.actions.fileSelected,
                cInstances.text_textEditor.actions.fileSelected
            ));
            cInstances.base_mainWindow.events.actionExecuted.addFun(ex_base_mainWindow_actionExecuted
            (
                cInstances.text_actionExecuter.actions.execute
            ));
            cInstances.base_mainWindow.events.notebook_tabAdded.addFun(ex_base_mainWindow_notebook_tabAdded
            (
                cInstances.text_textEditor.actions.tabAdded
            ));
        }

        // base_fileChooser_open --------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_fileChooser_open(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_fileChooser_open.events.fileChosen.addFun(ex_base_fileChooser_open_fileChosen
            (
                cInstances.text_fileOpener.actions.openFile
            ));
        }

        // base_fileChooser_saveAs ------------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_base_fileChooser_saveAs(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.base_fileChooser_saveAs.events.fileChosen.addFun(ex_base_fileChooser_saveAs_fileChosen
            (
                cInstances.text_textEditor.actions.saveEditorContents_as
            ));
        }

        // text_actionExecuter ----------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_text_actionExecuter(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.text_actionExecuter.events.edit_undo.addFun(ex_text_actionExecuter_edit_undo
            (
                cInstances.text_textEditor.actions.undo
            ));
            cInstances.text_actionExecuter.events.edit_redo.addFun(ex_text_actionExecuter_edit_redo
            (
                cInstances.text_textEditor.actions.redo
            ));
            cInstances.text_actionExecuter.events.edit_findReplace.addFun(ex_text_actionExecuter_edit_findReplace
            (
                cInstances.text_textEditor.actions.findReplace_start
            ));
        }

        // text_findReplace -------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_text_findReplace(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.text_findReplace.events.findPrevious.addFun(ex_text_findReplace_findPrevious
            (
                cInstances.text_textEditor.actions.findReplace_findPrevious,
                cInstances.base_mainWindow.actions.setPresent
            ));
            cInstances.text_findReplace.events.findNext.addFun(ex_text_findReplace_findNext
            (
                cInstances.text_textEditor.actions.findReplace_findNext,
                cInstances.base_mainWindow.actions.setPresent
            ));
            cInstances.text_findReplace.events.replace.addFun(ex_text_findReplace_replace
            (
                cInstances.text_textEditor.actions.findReplace_replace,
                cInstances.base_mainWindow.actions.setPresent
            ));
            cInstances.text_findReplace.events.replaceAll.addFun(ex_text_findReplace_replaceAll
            (
                cInstances.text_textEditor.actions.findReplace_replaceAll
            ));
            cInstances.text_findReplace.events.closed.addFun(ex_text_findReplace_closed
            (
                cInstances.text_textEditor.actions.findReplace_restoreFind
            ));
            cInstances.text_findReplace.events.stateChanged.addFun(ex_text_findReplace_stateChanged
            (
                cInstances.text_textEditor.actions.findReplace_stateChanged
            ));
        }

        // text_textEditor --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_text_textEditor(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.text_textEditor.events.newTBTabRequested.addFun(ex_text_textEditor_newTBTabRequested
            (
                cInstances.base_mainWindow.actions.notebook_openNewTab
            ));
            cInstances.text_textEditor.events.parseText.addFun(ex_text_textEditor_parseText
            (
                cInstances.text_textHighlighter.actions.parseText
            ));
            cInstances.text_textEditor.events.saveEditorContents_current.addFun(ex_text_textEditor_saveEditorContents_current
            (
                cInstances.text_fileOpener.actions.saveFile_current
            ));
            cInstances.text_textEditor.events.saveEditorContents_as.addFun(ex_text_textEditor_saveEditorContents_as
            (
                cInstances.text_fileOpener.actions.saveFile_as
            ));
            cInstances.text_textEditor.events.contentsModified.addFun(ex_text_textEditor_contentsModified
            (
                cInstances.base_mainWindow.actions.notebook_tabContentsModified
            ));
            cInstances.text_textEditor.events.contentsAreOriginal.addFun(ex_text_textEditor_contentsAreOriginal
            (
                cInstances.base_mainWindow.actions.notebook_tabContentsAreOriginal
            ));
            cInstances.text_textEditor.events.tabDataChanged.addFun(ex_text_textEditor_tabDataChanged
            (
                cInstances.base_mainWindow.actions.notebook_tabDataChanged
            ));
            cInstances.text_textEditor.events.editorClosed.addFun(ex_text_textEditor_editorClosed
            (
                cInstances.text_fileOpener.actions.fileClosed,
                cInstances.base_mainWindow.actions.notebook_closeTab
            ));
            cInstances.text_textEditor.events.findReplace_setFindText.addFun(ex_text_textEditor_findReplace_setFindText
            (
                cInstances.text_findReplace.actions.setTexts
            ));
            cInstances.text_textEditor.events.registerAction.addFun(ex_text_textEditor_registerAction
            (
                cInstances.base_mainWindow.actions.addAction
            ));
            cInstances.text_textEditor.events.clearActions.addFun(ex_text_textEditor_clearActions
            (
                cInstances.base_mainWindow.actions.clearActions
            ));
            cInstances.text_textEditor.events.addSeparator.addFun(ex_text_textEditor_addSeparator
            (
                cInstances.base_mainWindow.actions.addSeparator
            ));
            cInstances.text_textEditor.events.selectFile.addFun(ex_text_textEditor_selectFile
            (
                cInstances.base_mainWindow.actions.notebook_selectTab
            ));
        }

        // text_textHighlighter ---------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_text_textHighlighter(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.text_textHighlighter.events.applyTags.addFun(ex_text_textHighlighter_applyTags
            (
                cInstances.text_textEditor.actions.applyTags
            ));
        }

        // text_fileOpener --------------------------------------------------------------------------------------------------------------
        template <typename Providers>
        static void connect_text_fileOpener(ConnInstances &cInstances, const Providers &providers)
        {
            cInstances.text_fileOpener.events.openingNewFile.addFun(ex_text_fileOpener_openingNewFile
            (
                cInstances.text_textEditor.actions.openEditor
            ));
            cInstances.text_fileOpener.events.textFound.addFun(ex_text_fileOpener_textFound
            (
                cInstances.text_textEditor.actions.addText
            ));
            cInstances.text_fileOpener.events.fileAlreadyOpened.addFun(ex_text_fileOpener_fileAlreadyOpened
            (
                cInstances.base_mainWindow.actions.notebook_selectTab
            ));
            cInstances.text_fileOpener.events.fileSaved.addFun(ex_text_fileOpener_fileSaved
            (
                cInstances.text_textEditor.actions.editorTypeChanged,
                cInstances.text_textEditor.actions.savingDone
            ));
            cInstances.text_fileOpener.events.fileOpened.addFun(ex_text_fileOpener_fileOpened
            (
                cInstances.text_textEditor.actions.openingDone
            ));
            cInstances.text_fileOpener.events.fileSelected.addFun(ex_text_fileOpener_fileSelected
            (
                cInstances.base_fileChooser_saveAs.actions.setFileName
            ));
            cInstances.text_fileOpener.events.savingUnnamedFile.addFun(ex_text_fileOpener_savingUnnamedFile
            (
                cInstances.base_fileChooser_saveAs.actions.open
            ));
        }

        template <typename Args>
        static void connect(const Args &args)
        {
            ConnInstances cInstances(args.cMap);

            connect_base_actionExecuter(cInstances, args.providers);
            connect_base_mainWindow(cInstances, args.providers);
            connect_base_fileChooser_open(cInstances, args.providers);
            connect_base_fileChooser_saveAs(cInstances, args.providers);
            connect_text_actionExecuter(cInstances, args.providers);
            connect_text_findReplace(cInstances, args.providers);
            connect_text_textEditor(cInstances, args.providers);
            connect_text_textHighlighter(cInstances, args.providers);
            connect_text_fileOpener(cInstances, args.providers);
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
