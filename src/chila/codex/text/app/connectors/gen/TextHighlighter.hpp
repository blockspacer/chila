// ******************************************************************
// *                 This is auto-generated code                    *
// *                    - DO NOT MODIFY -                           *
// ******************************************************************

#ifndef CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__TEXTHIGHLIGHTER_HPP
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__TEXTHIGHLIGHTER_HPP

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
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ARGS_TextHighlighter \
    (fileId) \
    (parserId) \
    (textBuffer) \
    (tags) \
    (errorMsg) \
    (tagsToApply)

// Event defines
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENTS_TextHighlighter \
    (launcher_starting) \
    (launcher_started) \
    (launcher_deactivating) \
    (launcher_deactivated) \
    (launcher_finishing) \
    (launcher_finished) \
    (fatalError) \
    (applyTags)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_starting \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_started \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_deactivating \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_deactivated \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_finishing \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_launcher_finished \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_fatalError \
    (errorMsg)
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_EVENT_ARGS_TextHighlighter_applyTags \
    (fileId)(tags)(tagsToApply)

// Action defines
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTIONS_TextHighlighter \
    (launcher_start) \
    (launcher_deactivate) \
    (launcher_finish) \
    (parseText)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextHighlighter_launcher_start \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextHighlighter_launcher_deactivate \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextHighlighter_launcher_finish \

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_ARGS_TextHighlighter_parseText \
    (fileId)(parserId)(textBuffer)

// Actions' called events
#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextHighlighter_launcher_start \
    (launcher_started)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextHighlighter_launcher_deactivate \
    (launcher_deactivated)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextHighlighter_launcher_finish \
    (launcher_finished)

#define CHILA_CODEX_TEXT_APP_CONNECTORS_GEN__CONNECTOR_ACTION_EVCALLED_TextHighlighter_parseText \
    (applyTags)(fatalError)


CHILA_LIB_MISC__DEF_NAMESPACE(6, (chila,codex,text,app,connectors,gen))
{
    /** This class serves as a event and action connector for the connector.
      * Connectors should hold an instance of this class and connect their actions
      * in the constructor.
      */
    template <typename _ArgTypes>
    struct TextHighlighter final: public chila::connectionTools::lib::codegen::ConnectorImpl<TextHighlighter<_ArgTypes>>
    {
        static chila::lib::misc::Path path() { return "chila.codex.text.app.connectors.gen.TextHighlighter"; }

        typedef TextHighlighter Connector;
        typedef _ArgTypes ArgTypes;

        // Arguments
        CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_ARGUMENTS( \
            CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, TextHighlighter)

        // Events
        struct Events
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, EVENT, TextHighlighter)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, EVENT, TextHighlighter)
        } events;

        // Actions
        struct Actions
        {
            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUNCTIONS(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, ACTION, TextHighlighter)

            CHILA_CONNECTIONTOOLS_LIB_CODEGEN__DEF_CONNECTOR_FUN_FUSIONSEQ(
                CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, ACTION, TextHighlighter)

            Actions(Connector &connector) :
                CHILA_CONNECTIONTOOLS_LIB_CODEGEN__ACTIONS_INIT(
                    CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, TextHighlighter) {}
        } actions;


        TextHighlighter() : actions(*this) {}

        // Binds the actions to 'target'
        template <typename Target>
        void bindActions(Target &target)
        {
            MY_BIND_ACTION(launcher_start);
            MY_BIND_ACTION(launcher_deactivate);
            MY_BIND_ACTION(launcher_finish);
            MY_BIND_ACTION(parseText);
        }
    };
}}}}}}


#undef MY_BIND_ACTION
#undef DEF_CONNECTOR_ARGUMENT
#undef DEF_CONNECTOR_FUNCTION
#undef DEF_ARG_ALIAS
#undef DEF_ARG_ALIAS_LINK

#endif
