/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <boost/preprocessor.hpp>


#define CHILA_LIB_MISC__NSP_FOR(r, data, i, nspName) \
        BOOST_PP_EXPR_IF(i, {) namespace nspName

#define CHILA_LIB_MISC__DEF_NAMESPACE(deep, nspTuple) \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__NSP_FOR,, BOOST_PP_TUPLE_TO_SEQ(deep, nspTuple))

#define CHILA_LIB_MISC__DEF_NAMESPACE_VAR(...) \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__NSP_FOR,, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define CHILA_LIB_MISC__DEF_EXCEPTION(Name, whatTxt) \
    struct Name: public chila::lib::misc::Exception                    \
    {                                                                   \
        Name() {}                                                       \
        const char *what() const throw() { return whatTxt; }            \
        virtual std::string message() const { return what(); }          \
        ~Name() throw() {}                                              \
    }

#define CHILA_LIB_MISC__DEF_EXCEPTION_WB(Name, whatTxt, Base) \
    struct Name: public Base                                       \
    {                                                               \
        Name() {}                                                   \
        const char *what() const throw() { return whatTxt; }        \
        ~Name() throw() {}                                          \
    }

#define CHILA_LIB_MISC__SHOW(x) std::cout << "<" << __FILE__ << ":" << __LINE__ << ">: [" << x << "]" << std::endl

#define CHILA_LIB_MISC__FWDEC_SPTR(Type)                            \
    typedef boost::shared_ptr<Type> Type##SPtr;            \
    typedef boost::shared_ptr<const Type> Type##SCPtr;     \
    typedef boost::weak_ptr<Type> Type##WPtr;              \
    typedef boost::weak_ptr<const Type> Type##WCPtr;        \
    typedef std::unique_ptr<Type> Type##UPtr;         \
    typedef std::unique_ptr<const Type> Type##UCPtr

#define CHILA_LIB_MISC__FWDEC_APTR(Type)                                \
    typedef std::auto_ptr<Type> Type##APtr;             \
    typedef std::auto_ptr<const Type> Type##ACPtr;

#define CHILA_LIB_MISC__FWDEC_TYPE(Type)                            \
    class Type;                                     \
    CHILA_LIB_MISC__FWDEC_SPTR(Type)

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR(Name) \
    struct Name: public std::runtime_error, public boost::exception     \
    {                                           \
        Name(const std::string &msg) : std::runtime_error(msg) {}   \
        ~Name() throw() {}                      \
    }

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(Name, errMsg) \
    struct Name: public std::runtime_error, public boost::exception     \
    {                                           \
        Name(const std::string &msg = "") : std::runtime_error(std::string(errMsg) + (msg.empty() ? "" : ": " + msg)) {}   \
        ~Name() throw() {}                      \
    }

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE(Base, Name, errMsg) \
    struct Name: public Base     \
    {                                           \
        Name(const std::string &msg = "") : Base(std::string(errMsg) + (msg.empty() ? "" : ": " + msg)) {}   \
        ~Name() throw() {}                      \
    }

#define CHILA_LIB_MISC__CHECK_CALL(exp) \
    ::chila::lib::misc::checkCall((exp), "error calling \"" #exp "\"", __FILE__, __LINE__)

#define CHILA_LIB_MISC__CHECK_CALL_EV(exp, ev) \
    ::chila::lib::misc::checkCall((exp), ev, "error calling \"" #exp "\"", __FILE__, __LINE__)

#define CHILA_LIB_MISC__PARAM_TYPE(Type) boost::call_traits<Type>::param_type

#define CHILA_LIB_MISC__DYNAMIC_CAST_VAR(Type, var, object) Type *var = dynamic_cast<Type*>(object)

#define CHILA_LIB_MISC__ASSERT(exp) if (!(exp)) \
    BOOST_THROW_EXCEPTION(chila::lib::misc::AssertionFailed(#exp));

#define CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR_TEXT(z, n, data) }

#define CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(...) \
    BOOST_PP_REPEAT(BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR_TEXT,)

