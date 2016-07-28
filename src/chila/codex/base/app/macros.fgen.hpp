#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/codex/base/app/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,codex,base,app)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,codex,base,app)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define app_assert \
        CHILA_LIB_MISC__APP_ASSERT

    #define add_default_anyprinter(Type) \
        CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER(valueStreamer, Type)

    #define add_default_anyprinter_sptr(Type) \
        CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR(valueStreamer, Type)

    #define add_default_anyprinter_sptr_get(Type) \
        CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR_GET(valueStreamer, Type)

    #define ADD_DFF_AND_POST(provsOwner) \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:application", "action",  \
                    provsOwner.base_application->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:application", "event",  \
                    provsOwner.base_application->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_application->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_application->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_application->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:application", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_application->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_application->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_application->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:application", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_application->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_application->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_application->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:application", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:mainWindow", "action",  \
                    provsOwner.base_mainWindow->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:mainWindow", "event",  \
                    provsOwner.base_mainWindow->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_mainWindow->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_mainWindow->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_mainWindow->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:mainWindow", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_mainWindow->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_mainWindow->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_mainWindow->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:mainWindow", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_mainWindow->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_mainWindow->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_mainWindow->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:mainWindow", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:fileChooser:open", "action",  \
                    provsOwner.base_fileChooser_open->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:fileChooser:open", "event",  \
                    provsOwner.base_fileChooser_open->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_fileChooser_open->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_open->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_open->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:open", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_fileChooser_open->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_open->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_open->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:open", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_fileChooser_open->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_open->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_open->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:open", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:fileChooser:saveAs", "action",  \
                    provsOwner.base_fileChooser_saveAs->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:fileChooser:saveAs", "event",  \
                    provsOwner.base_fileChooser_saveAs->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:saveAs", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:saveAs", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_fileChooser_saveAs->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:fileChooser:saveAs", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:actionExecuter", "action",  \
                    provsOwner.base_actionExecuter->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:actionExecuter", "event",  \
                    provsOwner.base_actionExecuter->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_actionExecuter->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_actionExecuter->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_actionExecuter->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:actionExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_actionExecuter->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_actionExecuter->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_actionExecuter->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:actionExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_actionExecuter->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_actionExecuter->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_actionExecuter->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:actionExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:netServer", "action",  \
                    provsOwner.base_appCommand_netServer->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:netServer", "event",  \
                    provsOwner.base_appCommand_netServer->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_appCommand_netServer->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_netServer->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_netServer->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:netServer", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_netServer->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_netServer->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_netServer->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:netServer", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_netServer->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_netServer->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_netServer->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:netServer", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:funDynExecuter", "action",  \
                    provsOwner.base_appCommand_funDynExecuter->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:funDynExecuter", "event",  \
                    provsOwner.base_appCommand_funDynExecuter->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynExecuter->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynExecuter", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:funDynXMLParser", "action",  \
                    provsOwner.base_appCommand_funDynXMLParser->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:funDynXMLParser", "event",  \
                    provsOwner.base_appCommand_funDynXMLParser->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynXMLParser", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynXMLParser", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_funDynXMLParser->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:funDynXMLParser", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            if (debugLogFile)  \
            {  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:msgCreator", "action",  \
                    provsOwner.base_appCommand_msgCreator->connector.actions.list(), showArguments);  \
                chila::connectionTools::lib::other::addDebugFileFunToFunctions(  \
                    *debugLogFile, anyPrinter, "base:appCommand:msgCreator", "event",  \
                    provsOwner.base_appCommand_msgCreator->connector.events.list(), showArguments);  \
            }  \
            provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_start.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_start.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_start)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:msgCreator", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_deactivate.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_deactivate.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_deactivate)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:msgCreator", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \
            provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_finish.passFunAndSet(chila::lib::misc::SetPostFun(ioService));  \
            if (debugLogFile)  \
            {  \
                provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_finish.passFunAndSet  \
                (  \
                    chila::connectionTools::lib::other::DebugFileFunPFS<decltype(provsOwner.base_appCommand_msgCreator->connector.action##s.launcher_finish)>  \
                    (  \
                        *debugLogFile, anyPrinter, "base:appCommand:msgCreator", "action", showArguments, "posted in 'events'"  \
                    )  \
                );  \
            }  \


    #define create_module_wa(name, ...) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_WA(CPModTypes, CHILA_CODEX_BASE_APP_CONNECTORS_GEN, name, __VA_ARGS__)

    #define create_module_na(name) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__CREATE_MODULE_NA(CPModTypes, CHILA_CODEX_BASE_APP_CONNECTORS_GEN, name)

    #define set_dff_post_functions(object, type, queueName, functions) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__SET_DFF_POST_FUNCTIONS(providers, object, type, queueName, valueStreamer, functions)

    #define postfun_and_dff(module, funType, fun) \
        CHILA_CONNECTIONTOOLS_LIB_OTHER__POSTFUN_AND_DFF(providers, module, funType,                                                             fun, debugLogFile, ioService, valueStreamer, showArguments)

    #define add_to_event(module, event) \
        cclOther::addToConnFunction(module->connector.events.event,

#else

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef app_assert
    #undef add_default_anyprinter
    #undef add_default_anyprinter_sptr
    #undef add_default_anyprinter_sptr_get
    #undef ADD_DFF_AND_POST
    #undef create_module_wa
    #undef create_module_na
    #undef set_dff_post_functions
    #undef postfun_and_dff
    #undef add_to_event

#endif

