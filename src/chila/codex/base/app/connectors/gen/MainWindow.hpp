// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CODEX_BASE_APP_CONNECTORS_GEN__MAINWINDOW_HPP
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__MAINWINDOW_HPP

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
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ARGS_MainWindow \
    (notebook_tabId) \
    (notebook_tabName) \
    (notebook_tabTooltip) \
    (notebook_tabWidget) \
    (actionPath) \
    (actionData) \
    (actionPathDataList) \
    (errorMsg)

// Event defines
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_MainWindow \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (exitActionActivated) \
    (projectButtonPressed) \
    (fatalError) \
    (actionExecuted) \
    (notebook_closingTab) \
    (notebook_tabSelected) \
    (notebook_tabAdded)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_starting \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_started \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_deactivating \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_deactivated \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_finishing \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_launcher_finished \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_exitActionActivated \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_projectButtonPressed \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_fatalError \
    (errorMsg)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_actionExecuted \
    (actionPath)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_notebook_closingTab \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_notebook_tabSelected \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_MainWindow_notebook_tabAdded \
    (notebook_tabId)(notebook_tabWidget)

// Action defines
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_MainWindow \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (notebook_openNewTab) \
    (notebook_selectTab) \
    (notebook_tabContentsModified) \
    (notebook_tabContentsAreOriginal) \
    (notebook_tabDataChanged) \
    (notebook_closeTab) \
    (setPresent) \
    (addAction) \
    (addSeparator) \
    (clearActions)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_start \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_deactivate \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_launcher_finish \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_openNewTab \
    (notebook_tabId)(notebook_tabName)(notebook_tabTooltip)(notebook_tabWidget)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_selectTab \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_tabContentsModified \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_tabContentsAreOriginal \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_tabDataChanged \
    (notebook_tabId)(notebook_tabName)(notebook_tabTooltip)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_notebook_closeTab \
    (notebook_tabId)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_setPresent \

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_addAction \
    (actionPathDataList)(actionData)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_addSeparator \
    (actionPathDataList)
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_MainWindow_clearActions \


// Actions' called events
#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_start \
    (launcher_started)(exitActionActivated)(projectButtonPressed)(actionExecuted)(notebook_tabSelected)(fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_deactivate \
    (launcher_deactivated)(fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_launcher_finish \
    (launcher_finished)(fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_openNewTab \
    (notebook_closingTab)(notebook_tabSelected)(notebook_tabAdded)(fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_selectTab \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_tabContentsModified \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_tabContentsAreOriginal \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_tabDataChanged \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_notebook_closeTab \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_setPresent \
    (fatalError)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_addAction \
    (fatalError)(actionExecuted)

#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_addSeparator \


#define CHILA_CODEX_BASE_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_MainWindow_clearActions \
    (fatalError)


CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,codex,base,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct MainWindow final: public chila::connectionTools::lib::codegen::ConnectorImpl<MainWindow<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.codex.base.app.connectors.gen.MainWindow"; }

        typedef MainWindow Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CODEX_BASE_APP_CONNECTORS_GEN, MainWindow)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_BASE_APP_CONNECTORS_GEN, EVENT, MainWindow)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_BASE_APP_CONNECTORS_GEN, EVENT, MainWindow)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_BASE_APP_CONNECTORS_GEN, ACTION, MainWindow)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_BASE_APP_CONNECTORS_GEN, ACTION, MainWindow)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CODEX_BASE_APP_CONNECTORS_GEN, MainWindow) {}
        } actions;


        MainWindow() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(notebook_openNewTab);
            MY_BIND_ACTION(notebook_selectTab);
            MY_BIND_ACTION(notebook_tabContentsModified);
            MY_BIND_ACTION(notebook_tabContentsAreOriginal);
            MY_BIND_ACTION(notebook_tabDataChanged);
            MY_BIND_ACTION(notebook_closeTab);
            MY_BIND_ACTION(setPresent);
            MY_BIND_ACTION(addAction);
            MY_BIND_ACTION(addSeparator);
            MY_BIND_ACTION(clearActions);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
