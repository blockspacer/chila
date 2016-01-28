/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS_DEF_SIGNAL(r, data, i, elem)     BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(signal_, elem)
#define CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS_CALL_METHOD(r, method, i, elem)  BOOST_PP_CAT(signal_, elem).method();

#define CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS(Name, connections) \
    struct Name \
    { \
        sigc::connection BOOST_PP_SEQ_FOR_EACH_I(CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS_DEF_SIGNAL,, connections); \
        \
        void block() \
        { \
            BOOST_PP_SEQ_FOR_EACH_I(CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS_CALL_METHOD, block, connections) \
        } \
        void unblock() \
        { \
            BOOST_PP_SEQ_FOR_EACH_I(CHILA_CODEX_BASE_LIB__DEF_WIDGET_CONNS_CALL_METHOD, unblock, connections) \
        } \
        struct Blocker \
        { \
            Name &slots; \
            \
            Blocker(Name &slots) : slots(slots) { slots.block(); } \
            ~Blocker() { slots.unblock(); } \
        }; \
        Blocker blocker() { return Blocker(*this); } \
    }
