/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <boost/preprocessor.hpp>


#define CHILA_LIB_MISC__NSP_FOR(r, data, i, nspName) \
        BOOST_PP_EXPR_IF(i, {) namespace nspName

#define CHILA_LIB_MISC__DEF_NAMESPACE(deep, nspTuple) \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__NSP_FOR,, BOOST_PP_TUPLE_TO_SEQ(deep, nspTuple))

#define CHILA_LIB_MISC__DEF_NAMESPACE_SEQ(NSP_SEQ) \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__NSP_FOR,, NSP_SEQ)

#define CHILA_LIB_MISC__DEF_NAMESPACE_VAR(...) \
        CHILA_LIB_MISC__DEF_NAMESPACE_SEQ(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define CHILA_LIB_MISC__DEC_NAMESPACE_VAR(...) \
        CHILA_LIB_MISC__DEF_NAMESPACE_VAR(__VA_ARGS__) { BOOST_PP_REPEAT(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), CHILA_LIB_MISC__TEXTREP, })

#define CHILA_LIB_MISC__DEF_EXCEPTION(Name, whatTxt) \
    struct Name: public chila::lib::misc::Exception  \
    {                         \
        Name() {}             \
        const char *what() const throw() { return whatTxt; } \
        virtual std::string message() const { return what(); } \
        ~Name() throw() {}    \
    }

#define CHILA_LIB_MISC__DEF_EXCEPTION_WB(Name, whatTxt, Base) \
    struct Name: public Base  \
    {                     \
        Name() {}         \
        const char *what() const throw() { return whatTxt; } \
        ~Name() throw() {} \
    }

#define CHILA_LIB_MISC__SHOW(maxSize, x) std::cout << "<" << chila::lib::misc::cCharInserter<maxSize>(__FILE__) << ":" << __LINE__ << ">: [" << x << "]" << std::endl

#define CHILA_LIB_MISC__SHOW_SYNC(maxSize, x) \
    chila::lib::misc::lockCOutMutexWhile([&] { CHILA_LIB_MISC__SHOW(maxSize, x); });

#define CHILA_LIB_MISC__FWDEC_SPTR(Type) \
    typedef std::shared_ptr<Type> Type##SPtr; \
    typedef std::shared_ptr<const Type> Type##SCPtr; \
    typedef boost::weak_ptr<Type> Type##WPtr; \
    typedef boost::weak_ptr<const Type> Type##WCPtr; \
    typedef std::unique_ptr<Type> Type##UPtr; \
    typedef std::unique_ptr<const Type> Type##UCPtr; \
    typedef chila::lib::misc::SmartSUPtr<Type> Type##SUPtr; \
    typedef chila::lib::misc::SmartSUPtr<const Type> Type##SUCPtr

//#define CHILA_LIB_MISC__FWDEC_APTR(Type) \
//    typedef std::auto_ptr<Type> Type##APtr; \
//    typedef std::auto_ptr<const Type> Type##ACPtr;

#define CHILA_LIB_MISC__FWDEC_TYPE(Type) \
    class Type; \
    CHILA_LIB_MISC__FWDEC_SPTR(Type)

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR(Name) \
    struct Name: public std::runtime_error, public boost::exception  \
    { \
        Name(const std::string &msg) : std::runtime_error(msg) {} \
        ~Name() throw() {} \
    }

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR_WT(Name, errMsg) \
    struct Name: public std::runtime_error, public boost::exception  \
    { \
        Name(const std::string &msg = "") : std::runtime_error(std::string(errMsg) + (msg.empty() ? "" : ": " + msg)) {} \
        ~Name() throw() {} \
    }

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR_FROM_BASE(Base, Name, errMsg) \
    struct Name: public Base  \
    { \
        Name(const std::string &msg = "") : Base(std::string(errMsg) + (msg.empty() ? "" : ": " + msg)) {} \
        ~Name() throw() {} \
    }

#define CHILA_LIB_MISC__CHECK_CALL(exp) \
    ::chila::lib::misc::checkCall((exp), "error calling \"" #exp "\"", __FILE__, __LINE__)

#define CHILA_LIB_MISC__CHECK_CALL_EV(exp, ev) \
    ::chila::lib::misc::checkCall((exp), ev, "error calling \"" #exp "\"", __FILE__, __LINE__)

#define CHILA_LIB_MISC__CHECK_CALL_ERRNO(exp) \
    ::chila::lib::misc::checkCallErrno((exp), "error calling \"" #exp "\"", __FILE__, __LINE__)


#define CHILA_LIB_MISC__PARAM_TYPE(Type) boost::call_traits<Type>::param_type

#define CHILA_LIB_MISC__DYNAMIC_CAST_VAR(Type, var, object) Type *var = dynamic_cast<Type*>(object)

#define CHILA_LIB_MISC__ASSERT(exp) ((exp) ? static_cast<void>(0) : \
    BOOST_THROW_EXCEPTION(chila::lib::misc::AssertionFailed(BOOST_PP_STRINGIZE(exp))));

#define CHILA_LIB_MISC__APP_ASSERT(exp, msg) if (!(exp)) \
    { \
        std::stringstream str; \
        str << msg; \
        BOOST_THROW_EXCEPTION(chila::lib::misc::ApplicationError(str.str())); \
    }

#define CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR_TEXT(z, n, data) }

#define CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(...) \
    BOOST_PP_REPEAT(BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR_TEXT,)

#define CHILA_LIB_MISC__STRINGSTREAM(exp) static_cast<std::stringstream&>(std::stringstream() << exp).str()

#define CHILA_LIB_MISC__DEF_OP_LESS_THAN(Derived, Base) \
    bool operator<(const Base &rhs) const \
    { \
        return *this < *boost::polymorphic_downcast<const Derived*>(&rhs); \
    }

// CHILA_LIB_MISC__NAMED_TUPLE ----------------------------------------------------------------------------------------------------------------------

#define _CHILA_LIB_MISC__NTUPLE_FTYPE(elem) BOOST_PP_SEQ_ELEM(0, elem)
#define _CHILA_LIB_MISC__NTUPLE_FNAME(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define _CHILA_LIB_MISC__NTUPLE_TOFINISH(size, r) BOOST_PP_SUB(size, BOOST_PP_SUB(r, 1))

#define _CHILA_LIB_MISC__NTUPLE_COMP_LESS(r, size, elem) \
    _CHILA_LIB_MISC__NTUPLE_FNAME(elem) < rhs._CHILA_LIB_MISC__NTUPLE_FNAME(elem) || ( \
    BOOST_PP_IF(_CHILA_LIB_MISC__NTUPLE_TOFINISH(size, r), \
        _CHILA_LIB_MISC__NTUPLE_FNAME(elem) == rhs._CHILA_LIB_MISC__NTUPLE_FNAME(elem) &&, false)

#define _CHILA_LIB_MISC__NTUPLE_COMP_EQ(r, size, elem) \
    _CHILA_LIB_MISC__NTUPLE_FNAME(elem) == rhs._CHILA_LIB_MISC__NTUPLE_FNAME(elem) &&

#define _CHILA_LIB_MISC__NTUPLE_FIELD(r, data, elem) \
    _CHILA_LIB_MISC__NTUPLE_FTYPE(elem) _CHILA_LIB_MISC__NTUPLE_FNAME(elem);

#define _CHILA_LIB_MISC__NTUPLE_ARG(r, data, elem) \
    BOOST_PP_COMMA_IF(BOOST_PP_SUB(r, 2)) \
    _CHILA_LIB_MISC__NTUPLE_FTYPE(elem) _CHILA_LIB_MISC__NTUPLE_FNAME(elem)

#define _CHILA_LIB_MISC__NTUPLE_INIT_ARG(r, data, elem) \
    BOOST_PP_COMMA_IF(BOOST_PP_SUB(r, 2)) \
    _CHILA_LIB_MISC__NTUPLE_FNAME(elem)(_CHILA_LIB_MISC__NTUPLE_FNAME(elem))

#define _CHILA_LIB_MISC__NTUPLE_PUT_RPAREN(z, n, data) )

#define CHILA_LIB_MISC__NAMED_TUPLE_BODY(Name, fields) \
        BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_MISC__NTUPLE_FIELD,,fields) \
        \
        Name() = default; \
        Name(Name &&rhs) = default; \
        Name(const Name &rhs) = default; \
        Name &operator=(const Name &name) = default; \
        Name &operator=(Name &&name) = default; \
        Name(BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_MISC__NTUPLE_ARG,,fields)) : \
            BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_MISC__NTUPLE_INIT_ARG,,fields)

#define CHILA_LIB_MISC__NAMED_TUPLE_COMP(Name, fields) \
        bool operator<(const Name &rhs) const \
        { \
            return BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_MISC__NTUPLE_COMP_LESS, BOOST_PP_SEQ_SIZE(fields) ,fields) \
            BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(fields), _CHILA_LIB_MISC__NTUPLE_PUT_RPAREN,); \
        } \
        bool operator==(const Name &rhs) const \
        { \
            return BOOST_PP_SEQ_FOR_EACH(_CHILA_LIB_MISC__NTUPLE_COMP_EQ,,fields) true; \
        }

#define CHILA_LIB_MISC__NAMED_TUPLE(Name, hasComp, fields) \
        struct Name \
        { \
            CHILA_LIB_MISC__NAMED_TUPLE_BODY(Name, fields) {} \
            \
            BOOST_PP_IF(hasComp, CHILA_LIB_MISC__NAMED_TUPLE_COMP(Name, fields),) \
        }

#define CHILA_LIB_MISC__ADD_CONST_IF(Type, addConst) \
    chila::lib::misc::AddConstIf<Type, addConst>::type

#define CHILA_LIB_MISC__ADD_CONST_IF_TN(Type, addConst) \
    typename chila::lib::misc::AddConstIf<Type, addConst>::type

#define CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER(anyPrinter, Type) \
        chila::lib::misc::addFunWR<Type>(anyPrinter, [](std::ostream &out, const Type &val) \
        { \
            out << val; \
        });

#define CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR(anyPrinter, Type) \
        chila::lib::misc::addFunWR<std::shared_ptr<Type>>(anyPrinter, [](std::ostream &out, const std::shared_ptr<Type> &val) \
        { \
            out << *val; \
        });

#define CHILA_LIB_MISC__ADD_DEFAULT_ANYPRINTER_SPTR_GET(anyPrinter, Type) \
        chila::lib::misc::addFunWR<std::shared_ptr<Type>>(anyPrinter, [](std::ostream &out, const std::shared_ptr<Type> &val) \
        { \
            out << val.get(); \
        });

#define CHILA_LIB_MISC__ET_VALUE(elem) BOOST_PP_SEQ_ELEM(0, elem)
#define CHILA_LIB_MISC__ET_NAME(elem) BOOST_PP_SEQ_ELEM(1, elem)

#define CHILA_LIB_MISC__DEF_ENUM_TYPE_VAL(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) CHILA_LIB_MISC__ET_VALUE(elem)

#define CHILA_LIB_MISC__DEF_ENUM_TYPE_CASE(r, Name, i, elem) \
    case Name::CHILA_LIB_MISC__ET_VALUE(elem): return CHILA_LIB_MISC__ET_NAME(elem);

#define CHILA_LIB_MISC__DEF_ENUM_TYPE_IF(r, Name, i, elem) \
    BOOST_PP_IF(i, else, ) if (name == CHILA_LIB_MISC__ET_NAME(elem)) return Name::CHILA_LIB_MISC__ET_VALUE(elem);


#define CHILA_LIB_MISC__DEF_ENUM_TEMPLATES \
    template <typename Type> \
    inline Type getValue(const std::string &name); \
    \
    template <typename Type> \
    constexpr unsigned getSize()

#define CHILA_LIB_MISC__DEF_ENUM_TYPE(NName, valueNameList) \
    enum class NName \
    { \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__DEF_ENUM_TYPE_VAL,, valueNameList) \
    }; \
    \
    inline std::string getName(NName val) \
    { \
        switch (val) \
        { \
            BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__DEF_ENUM_TYPE_CASE, NName, valueNameList) \
            default: BOOST_THROW_EXCEPTION(chila::lib::misc::InvalidArgument()); \
        } \
    } \
    \
    template <> \
    inline NName getValue<NName>(const std::string &name) \
    { \
        BOOST_PP_SEQ_FOR_EACH_I(CHILA_LIB_MISC__DEF_ENUM_TYPE_IF, NName, valueNameList) \
        else BOOST_THROW_EXCEPTION(chila::lib::misc::InvalidArgument()); \
    } \
    template <> \
    constexpr unsigned getSize<NName>() { return BOOST_PP_SEQ_SIZE(valueNameList); }

#define CHILA_LIB_MISC__CATCHTHROW_APPERROR(Exception, msg, exp) \
    chila::lib::misc::catchThrowAppError<Exception>(msg, [&]()->decltype(exp){ return exp; })

#define CHILA_LIB_MISC__CATCHTHROW_APPERROR_REF(Exception, msg, exp) \
    chila::lib::misc::catchThrowAppError<Exception>(msg, [&]()->decltype(exp)&{ return exp; })

#define CHILA_LIB_MISC__ENABLE_SIGC_RETURN_FROM_LAMBDA \
    namespace sigc \
    { \
        template <typename Functor> \
        struct functor_trait<Functor, false> \
        { \
            typedef decltype (::sigc::mem_fun (std::declval<Functor&> (), \
                        &Functor::operator())) _intermediate; \
            \
            typedef typename _intermediate::result_type result_type; \
            typedef Functor functor_type; \
        }; \
    }

#define CHILA_LIB_MISC__TEXTREP(z, n, text) text

#define CHILA_LIB_MISC__REMOVE_PAREN(exp) BOOST_PP_SEQ_ENUM(BOOST_PP_VARIADIC_TO_SEQ(exp))

#define CHILA_LIB_MISC__CATCH_EXCEPTIONS_MAIN_ELEM(r, detailFun, Exception) \
    catch (const Exception &ex) \
    { \
        std::cerr << "Error: " << ex.what() << "." << std::endl; \
        detailFun(ex); \
        exit(EXIT_FAILURE); \
    }

#define CHILA_LIB_MISC__CATCH_EXCEPTIONS_MAIN(exSeq, detailFun) \
    BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_MISC__CATCH_EXCEPTIONS_MAIN_ELEM, detailFun, exSeq)

#define CHILA_LIB_MISC__DEC_ERROR_INFO_TYPE(Name, Type) \
    using Name = boost::error_info<struct BOOST_PP_CAT(tag_, Name), Type>; \

#define CHILA_LIB_MISC__DEC_ERROR_INFO_TYPE_ELEM(r, data, elem) \
    CHILA_LIB_MISC__DEC_ERROR_INFO_TYPE \
    ( \
        BOOST_PP_SEQ_ELEM(0, elem), \
        BOOST_PP_SEQ_ELEM(1, elem) \
    )

#define CHILA_LIB_MISC__DEC_ERROR_INFO_STRUCT_EX_DET(r, data, elem) \
    chila::lib::misc::printExDetail<BOOST_PP_SEQ_ELEM(0, elem)>(ex, BOOST_PP_SEQ_ELEM(2, elem));

#define CHILA_LIB_MISC__DEC_ERROR_INFO_STRUCT(dataSeq) \
    struct ExceptionInfo \
    { \
        BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_MISC__DEC_ERROR_INFO_TYPE_ELEM,, dataSeq) \
        template <typename ExType> \
        static void printExDetail(const ExType &ex) \
        { \
            BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_MISC__DEC_ERROR_INFO_STRUCT_EX_DET,, dataSeq) \
        } \
    };

#define CHILA_LIB_MISC__DEF_EX_DETAIL_FUN__ELEM(r, data, Name) \
    Name::printExDetail(ex);

#define CHILA_LIB_MISC__DEF_EX_DETAIL_FUN(name, exInfoSeq) \
    void name(const boost::exception &ex) \
    { \
        BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_MISC__DEF_EX_DETAIL_FUN__ELEM,, exInfoSeq) \
    }
