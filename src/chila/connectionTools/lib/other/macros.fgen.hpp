#include <chila/lib/misc/macrosExp.hpp>

//../../../../src/chila/connectionTools/lib/other/macros.fgen.py
#ifndef MY_NSP_START\

    #define MY_NSP_START \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(chila,connectionTools,lib,other)

    #define MY_NSP_END \
        CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(chila,connectionTools,lib,other)

    #define my_assert \
        CHILA_LIB_MISC__ASSERT

    #define ipss \
        CHILA_LIB_MISC__IPSS

    #define ipss_end \
        CHILA_LIB_MISC__IPSS_END

    #define LAUNCHER_ADD_TO_EVENT(Name, name) \
        void addTo##Name##Event(const Function &action) override \
        { \
            if (connector.events.launcher_##name) \
                connector.events.launcher_##name.passFunAndSet(chila::connectionTools::lib::other::funExecSequence(action)); \
            else \
                connector.events.launcher_##name = action; \
        } \
        

    #define LAUNCHER_ADD_TO_EVENT_VIRTUAL(Name, name) \
        virtual void addTo##Name##Event(const Function &action) = 0;

#else 

    #undef MY_NSP_START
    #undef MY_NSP_END
    #undef my_assert
    #undef ipss
    #undef ipss_end
    #undef LAUNCHER_ADD_TO_EVENT
    #undef LAUNCHER_ADD_TO_EVENT_VIRTUAL

#endif

