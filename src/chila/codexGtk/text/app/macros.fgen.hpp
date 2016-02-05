#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codexGtk/text/app/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codexGtk,text,app)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codexGtk,text,app)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define create_module_wa(name, ...) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_WA(CPModTypes, CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, name, __VA_ARGS__)

    #define create_module_na(name) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_NA(CPModTypes, CHILA_CODEX_TEXT_APP_CONNECTORS_GEN, name)

    #define add_default_anyprinter_sptr_get(Type) \
        CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR_GET(valueStreamer, Type)

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define set_post_function(object, type, function, queue, queueName) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_POST_FUNCTION(providers, object, type, function, queue, queueName, valueStreamer)

    #define set_dff_post_functions(object, type, queueName, functions) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS(providers, object, type, queueName, valueStreamer, functions)

    #define ADD_DFF_AND_POST(provsOwner) \
            if (debugLogFile) \
            { \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:textEditor", "action", \
                    provsOwner.text_textEditor->connector.actions.list(), showArguments); \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:textEditor", "event", \
                    provsOwner.text_textEditor->connector.events.list(), showArguments); \
            } \
            provsOwner.text_textEditor->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textEditor->connector.action##s.launcher_start.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textEditor->connector.action##s.launcher_start)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textEditor", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_textEditor->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textEditor->connector.action##s.launcher_deactivate.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textEditor->connector.action##s.launcher_deactivate)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textEditor", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_textEditor->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textEditor->connector.action##s.launcher_finish.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textEditor->connector.action##s.launcher_finish)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textEditor", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            if (debugLogFile) \
            { \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:textHighlighter", "action", \
                    provsOwner.text_textHighlighter->connector.actions.list(), showArguments); \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:textHighlighter", "event", \
                    provsOwner.text_textHighlighter->connector.events.list(), showArguments); \
            } \
            provsOwner.text_textHighlighter->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textHighlighter->connector.action##s.launcher_start.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textHighlighter->connector.action##s.launcher_start)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textHighlighter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_textHighlighter->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textHighlighter->connector.action##s.launcher_deactivate.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textHighlighter->connector.action##s.launcher_deactivate)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textHighlighter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_textHighlighter->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_textHighlighter->connector.action##s.launcher_finish.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_textHighlighter->connector.action##s.launcher_finish)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:textHighlighter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            if (debugLogFile) \
            { \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:findReplace", "action", \
                    provsOwner.text_findReplace->connector.actions.list(), showArguments); \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:findReplace", "event", \
                    provsOwner.text_findReplace->connector.events.list(), showArguments); \
            } \
            provsOwner.text_findReplace->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_findReplace->connector.action##s.launcher_start.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_findReplace->connector.action##s.launcher_start)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:findReplace", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_findReplace->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_findReplace->connector.action##s.launcher_deactivate.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_findReplace->connector.action##s.launcher_deactivate)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:findReplace", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_findReplace->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_findReplace->connector.action##s.launcher_finish.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_findReplace->connector.action##s.launcher_finish)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:findReplace", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            if (debugLogFile) \
            { \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:actionExecuter", "action", \
                    provsOwner.text_actionExecuter->connector.actions.list(), showArguments); \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:actionExecuter", "event", \
                    provsOwner.text_actionExecuter->connector.events.list(), showArguments); \
            } \
            provsOwner.text_actionExecuter->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_actionExecuter->connector.action##s.launcher_start.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_actionExecuter->connector.action##s.launcher_start)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:actionExecuter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_actionExecuter->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_actionExecuter->connector.action##s.launcher_deactivate.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_actionExecuter->connector.action##s.launcher_deactivate)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:actionExecuter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_actionExecuter->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_actionExecuter->connector.action##s.launcher_finish.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_actionExecuter->connector.action##s.launcher_finish)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:actionExecuter", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            if (debugLogFile) \
            { \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:fileOpener", "action", \
                    provsOwner.text_fileOpener->connector.actions.list(), showArguments); \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions( \
                    *debugLogFile, valueStreamer, "text:fileOpener", "event", \
                    provsOwner.text_fileOpener->connector.events.list(), showArguments); \
            } \
            provsOwner.text_fileOpener->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_fileOpener->connector.action##s.launcher_start.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_fileOpener->connector.action##s.launcher_start)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:fileOpener", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_fileOpener->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_fileOpener->connector.action##s.launcher_deactivate.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_fileOpener->connector.action##s.launcher_deactivate)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:fileOpener", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \
            provsOwner.text_fileOpener->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService)); \
            if (debugLogFile) \
            { \
                provsOwner.text_fileOpener->connector.action##s.launcher_finish.passFunAndSet \
                ( \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.text_fileOpener->connector.action##s.launcher_finish)> \
                    ( \
                        *debugLogFile, valueStreamer, "text:fileOpener", "action", showArguments, "posted in 'events'" \
                    ) \
                ); \
            } \


#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef app_assert
    #undef create_module_wa
    #undef create_module_na
    #undef add_default_anyprinter_sptr_get
    #undef app_assert
    #undef set_post_function
    #undef set_dff_post_functions
    #undef ADD_DFF_AND_POST

#endif

