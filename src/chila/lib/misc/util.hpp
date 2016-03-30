/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__UTIL_HPP
#define CHILA_LIB_MISC__UTIL_HPP

#include "fwd.hpp"
#include <boost/any.hpp>
#include <string>
#include <boost/program_options.hpp>
#include <memory>
#include <map>
#include <boost/range.hpp>
#include "exceptions.hpp"
#include <boost/call_traits.hpp>
#include <boost/thread/mutex.hpp>
#include "SinkInserter.hpp"
#include <errno.h>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/tokenizer.hpp>
#include <boost/function_types/result_type.hpp>

#include "macros.fgen.hpp"

namespace boost
{
    template <typename T>
    struct call_traits<std::unique_ptr<T>>
    {
        public:
           typedef std::unique_ptr<T> value_type;
           typedef value_type& reference;
           typedef const value_type& const_reference;
           typedef reference param_type; // TODO Check this out. Doesn't seem right.
    };

    template <typename T>
    struct call_traits<chila::lib::misc::SmartSUPtr<T>>
    {
        public:
           typedef chila::lib::misc::SmartSUPtr<T> value_type;
           typedef value_type& reference;
           typedef const value_type& const_reference;
           typedef reference param_type; // TODO Check this out. Doesn't seem right.
    };
}

MY_NSP_START
{
    extern boost::mutex coutMutex, cerrMutex;

    template <typename Fun>
    typename boost::function_types::result_type<Fun>::type
        executeVoidBoolFun(const Fun &fun, int a = 0)
    {
        return fun();
    }

    template <typename Fun>
    bool executeVoidBoolFun(const Fun &fun, long a = 0)
    {
        fun();
        return true;
    }

    template <typename T>
    inline std::shared_ptr<T> removeConst(const std::shared_ptr<const T> &value)
    {
        return std::const_pointer_cast<T>(value);
    }

    template <typename T>
    inline T &removeConst(const T &value)
    {
        return const_cast<T&>(value);
    }

    template <typename T>
    inline T *removeConst(const T *value)
    {
        return const_cast<T*>(value);
    }

    void throwSystemError(int errVal, const char *msg, const char *file, int line);

    template <typename RetVal>
    inline RetVal checkCall(RetVal exp, RetVal errorVal, const char *message, const char *file, int line)
    {
        if (exp == errorVal)
            throwSystemError(errno, message, file, line);
        else
            return exp;
    }

    inline int checkCall(int exp, const char *message, const char *file, int line)
    {
        if (exp == -1)
        {
            throwSystemError(errno, message, file, line); return 0;
        }
        else return exp;
    }

    inline void checkCallErrno(int exp, const char *message, const char *file, int line)
    {
        if (exp)
        {
            throwSystemError(exp, message, file, line);
        }
    }

    template <typename Target, typename Base>
    inline std::shared_ptr<Target> polymorphic_pointer_downcast(const std::shared_ptr<Base> &ptr)
    {
        assert(dynamic_cast<Target*>(ptr.get()) == ptr.get());
        return std::static_pointer_cast<Target>(ptr);
    }

    template <typename Fun>
    inline void lockMutexWhile(boost::mutex &mutex, const Fun &fun)
    {
        boost::mutex::scoped_lock lock(mutex);
        fun();
    }

    template <typename Fun>
    inline void lockCOutMutexWhile(const Fun &fun)
    {
        lockMutexWhile(coutMutex, fun);
    }

    template <typename Fun>
    inline void lockCErrMutexWhile(const Fun &fun)
    {
        lockMutexWhile(coutMutex, fun);
    }

    template <typename Type, bool cond>
    struct AddConstIf { using type = Type; };

    template <typename Type>
    struct AddConstIf<Type, true> { using type = const Type; };

    template <typename Type>
    inline Type *checkNotNull(Type *data)
    {
        my_assert(data);
        return data;
    }

    template <typename Type>
    inline Type &deref(Type *data)
    {
        my_assert(data);
        return *data;
    }

    template <typename Type>
    struct Quoted final: public chila::lib::misc::SinkInserter<Quoted<Type>>
    {
        const Type &data;
        Quoted(const Type &data) : data(data) {}

        template <typename Sink>
        void write(Sink &sink) const
        {
            sink << "\"" << data << "\"";
        }
    };

    template <typename Type>
    inline Quoted<Type> quoted(const Type &data) { return Quoted<Type>(data); }


    template <typename Type>
    struct XMLEscape final: public chila::lib::misc::SinkInserter<XMLEscape<Type>>
    {
        const Type &data;
        XMLEscape(const Type &data) : data(data) {}

        template <typename Sink>
        void write(Sink &sink) const
        {
            sink << data;
//            for (auto &c : data)
//            {
//                switch (c)
//                {
//                    case '\"':  sink << "&quot;";   break;
//                    case '&':   sink << "&amp;";    break;
//                    case '<':   sink << "&lt;";     break;
//                    case '>':   sink << "&gt;";     break;
//                    default: sink.put(c);           break;
//                }
//            }
        }
    };

    template <typename Type>
    inline XMLEscape<Type> xmlEscape(const Type &data) { return XMLEscape<Type>(data); }

    template <unsigned maxSize>
    struct CCharInserter final: public chila::lib::misc::SinkInserter<CCharInserter<maxSize>>
    {
        const char *value;

        static_assert(maxSize >= 3, "invalid 'maxSize'");

        CCharInserter(const char *value) : value(value) {}

        template <typename Sink>
        void write(Sink &sink) const
        {
            auto size = ::strlen(value);
            auto newMSize = maxSize - 3;

            if (size > newMSize)
            {
                sink << "..." << (value + (size - newMSize));
            }
            else
            {
                sink << value;
            }
        }
    };

    template <unsigned maxSize>
    inline CCharInserter<maxSize> cCharInserter(const char *value) { return CCharInserter<maxSize>(value); }

    inline const char *boolToText(bool value)
    {
        return value ? "true" : "false";
    }

    inline bool textToBool(const char *text)
    {
        if (::strcmp(text, "true") == 0)
            return true;
        else if (::strcmp(text, "false") == 0)
            return false;
        else
        {
            BOOST_THROW_EXCEPTION(std::invalid_argument("test"));
        }
    }

    inline bool textToBool(const std::string &text)
    {
        return textToBool(text.c_str());
    }

    template <typename T>
    inline auto moveOrPass(T& t) noexcept -> typename boost::disable_if<boost::is_reference<T>, decltype(rvalue_cast(t))>::type
    {
        return rvalue_cast(t);
    }

    template <typename T>
    inline auto moveOrPass(T t) noexcept -> typename boost::enable_if<boost::is_reference<T>, T&>::type
    {
        return t;
    }

    struct NullDeleter
    {
        void operator()(void const *) const {}
    };

    template <typename Type>
    Type getProgramOption(boost::program_options::variables_map &vm, const std::string &name)
    {
        if (vm.count(name))
        {
            return vm[name].as<Type>();
        }
        else
        {
            BOOST_THROW_EXCEPTION(ApplicationError("error: '" + name + "' argument is missing."));
        }
    }

    template <typename Type>
    Type getProgramOption(boost::program_options::variables_map &vm, const std::string &name, const Type &defVal)
    {
        if (vm.count(name))
        {
            return vm[name].as<Type>();
        }
        else
        {
            return defVal;
        }
    }

    template <typename Type>
    void showErrorInfo(std::ostream &out, const std::exception &ex, const std::string &name, bool extended = false)
    {
        if (auto *value = boost::get_error_info<Type>(ex))
            out << "- " << name << ": " << (extended ? "\n" : "[") << *value << (extended ? "" : "]\n") << std::flush;
    }

    template <typename Range, typename Fun>
    void find(Range toFind, Fun &fun)
    {
        auto begin = boost::begin(toFind);
        auto end = boost::end(toFind);

        for (auto it = begin; it != end && fun(it); ++it);
    }

    boost::filesystem::path getRelativePath(const boost::filesystem::path &dir,
            const boost::filesystem::path &path);

    template <typename Fun>
    struct AtExit
    {
        Fun fun;
        bool active;

        AtExit(Fun fun) : fun(rvalue_cast(fun)), active(true) {}
        ~AtExit() { if (active) fun(); }
    };

    template <typename Fun>
    inline AtExit<Fun> atExit(Fun fun)
    {
        return AtExit<Fun>(rvalue_cast(fun));
    }

    std::string replace(const std::string &text, const std::string &rep, const std::string &with);

    template <typename Exception, typename Fun, typename CatchFun>
    auto catchEx(const Fun &fun, const CatchFun &catchFun) -> decltype(fun()) try
    {
        return fun();
    }
    catch (Exception &ex)
    {
        catchFun(ex);
        throw;
    }

    template <typename FromType, typename ToType, typename Exception>
    [[ noreturn ]] void rethrowBadCast(const Exception &ex)
    {
        throw boost::enable_error_info(ex) << chila::lib::misc::ExceptionInfo::TypeFrom(boost::typeindex::type_id<FromType>())
                                           << chila::lib::misc::ExceptionInfo::TypeTo(boost::typeindex::type_id<ToType>());
    }

    template <typename FromType, typename ToType, typename Fun>
    auto catchThrowBadCast(const Fun &fun) -> decltype(fun()) try
    {
        return fun();
    }
    catch (const std::bad_cast &ex)
    {
        rethrowBadCast<FromType, ToType>(ex);
    }

    template <typename Exception, typename Fun>
    auto catchThrowAppError(const char *text, const Fun &fun) -> decltype(fun()) try
    {
        return fun();
    }
    catch (Exception &ex)
    {
        BOOST_THROW_EXCEPTION(ApplicationError(text));
    }

    template <typename ToType, typename FromType>
    ToType &dynamicCast(FromType &from) try
    {
        return chila::lib::misc::catchThrowBadCast<FromType&, ToType&>([&]() -> ToType&
        {
            return dynamic_cast<ToType&>(from);
        });
    }
    catch (const boost::exception &ex)
    {
        ex << chila::lib::misc::ExceptionInfo::ActualType(boost::typeindex::type_id_runtime(from));
        throw;
    }

    template <typename ToType, typename FromType>
    const ToType &dynamicCast(const FromType &from) try
    {
        return chila::lib::misc::catchThrowBadCast<const FromType&, const ToType&>([&]() -> const ToType&
        {
            return dynamic_cast<const ToType&>(from);
        });
    }
    catch (const boost::exception &ex)
    {
        ex << chila::lib::misc::ExceptionInfo::ActualType(boost::typeindex::type_id_runtime(from));
        throw;
    }

    constexpr unsigned MAX_UINT = std::numeric_limits<unsigned>::max();

    template <typename Range, typename NotChild>
    boost::iterator_range<typename Range::iterator> getChildren(const Range &range, const NotChild &notChild)
    {
        return boost::make_iterator_range(boost::begin(range), boost::find_if(range, notChild));
    }

    template <typename Arg>
    inline bool lessThan(const std::pair<Arg, Arg> &pair)
    {
        return pair.first < pair.second;
    }

    template <typename Arg0, typename ...Arg>
    inline bool lessThan(const std::pair<Arg0, Arg0> &pair, const std::pair<Arg, Arg>&... pairs)
    {
        return pair.first < pair.second || (pair.first == pair.second && lessThan(pairs...));
    }

    template <typename _Type>
    class SmartSUPtr
    {
        private:
            using Type = _Type;
            CHILA_LIB_MISC__FWDEC_SPTR(Type);

            TypeSPtr shared;
            TypeUPtr unique;

        public:
            SmartSUPtr(const TypeSPtr &ptr) : shared(ptr) {}
            SmartSUPtr(const TypeUPtr &ptr) : unique(ptr) {}

            SmartSUPtr() = default;
            SmartSUPtr(SmartSUPtr &&rhs) = default;
            SmartSUPtr &operator=(SmartSUPtr &&rhs) = default;

            Type &operator*()               { return shared ? *shared : *unique; }
            const Type &operator*() const   { return shared ? *shared : *unique; }
            Type *operator->()              { return shared ? shared.get() : unique->get(); }
            const Type *operator->() const  { return shared ? shared.get() : unique->get(); }
    };

    template <typename Type, typename Fun>
    class Capture
    {
        private:
            Type val;
            Fun fun;

        public:
            Capture(Type &&val, Fun &&fun) : val{std::forward<Type>(val)}, fun{std::forward<Fun>(fun)} {}

            template <typename ...Types>
            auto operator()(Types&&... args) -> decltype(fun(val, std::forward<Types>(args)...))
            {
                return fun(val, std::forward<Types>(args)...);
            }

            template <typename ...Types>
            auto operator()( Types&&... args) const -> decltype(fun(val, std::forward<Types>(args)...))
            {
                return fun(val, std::forward<Types>(args)...);
            }
    };

    template <typename Type, typename Fun>
    Capture<Type, Fun> capture(Type &&val, Fun &&fun )
    {
        return Capture<Type, Fun>(std::forward<Type>(val), std::forward<Fun>(fun));
    }

    template <typename Fun>
    bool tokenize(const std::string &text, const std::string &seps, const Fun &fun)
    {
        using Sep = boost::char_separator<char>;
        using Tokenizer = boost::tokenizer<Sep>;

        Tokenizer tokens(text, Sep(seps.c_str()));

        for (auto token : tokens)
            if (!executeVoidBoolFun([&] { return fun(token); }))
                return true;

        return false;
    }

    template <typename Type>
    Type absDiff(const Type &val0, const Type &val1)
    {
        return val0 > val1 ? val0 - val1 : val1 - val0;
    }

    template <typename Type>
    struct RefValHolder
    {
        using type = Type;
    };

    template <typename Type>
    struct RefValHolder<Type&>
    {
        using type = boost::reference_wrapper<Type>;
    };

    template <typename Type>
    inline typename RefValHolder<Type>::type refValHolder(Type val)
    {
        return typename RefValHolder<Type>::type(val);
    }

    std::string escapeText(const std::string &text);
    std::string unescapeText(const std::string &text);

    const char *getEscapeChar(char c);

    template <typename Type>
    inline std::shared_ptr<Type> toSharedPtr(std::unique_ptr<Type> value)
    {
        return std::shared_ptr<Type>{rvalue_cast(value)};
    }

    void removeTrailingWSpace(std::string &text);

    struct timeInserter final: public chila::lib::misc::SinkInserter<timeInserter>
    {
        boost::posix_time::time_duration td;
        std::string sep;

        timeInserter(const boost::posix_time::time_duration &td, const std::string &sep = "") : td(td), sep(sep) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            out << std::setfill('0') << (td.is_negative() ? "-" : "")
                                     << std::setw(2) << abs(td.hours()) << sep
                                     << std::setw(2) << abs(td.minutes()) << sep
                                     << std::setw(2) << abs(td.seconds());
        }
    };

    struct dateInserter final: public chila::lib::misc::SinkInserter<dateInserter>
    {
        boost::gregorian::date date;
        std::string sep;

        dateInserter(const boost::gregorian::date &date, const std::string &sep = "") : date(date), sep(sep) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            out << std::setfill('0') << std::setw(4) << unsigned(date.year()) << sep
                                        << std::setw(2) << unsigned(date.month()) << sep
                                        << std::setw(2) << unsigned(date.day());
        }
    };

    struct dateTimeInserter final: public chila::lib::misc::SinkInserter<dateTimeInserter>
    {
        boost::posix_time::ptime time;
        std::string dSep, tSep, innerSep;

        dateTimeInserter(
                const boost::posix_time::ptime &time,
                const std::string &dSep = "",
                const std::string &tSep = "",
                const std::string &innerSep = "") :
            time(time), dSep(dSep), tSep(tSep),innerSep(innerSep) {}

        template <typename Sink>
        void write(Sink &out) const
        {
            out << dateInserter(time.date(), dSep) << innerSep << timeInserter(time.time_of_day(), tSep);
        }
    };

    bool wildMatch(const char *pat, const char *str);

    template <typename Range>
    void parseNumbers(const std::string &text, Range &range)
    {
        std::size_t start = 0, cur = 0;
        typename boost::range_iterator<Range>::type it = boost::begin(range);

        while (cur != std::string::npos)
        {
            struct tag_text_info {};

            if (it == boost::end(range))
                BOOST_THROW_EXCEPTION(std::range_error("range"));

            cur = text.find('.', start);
            *it++ = boost::lexical_cast<unsigned>(text.substr(start,
                cur == std::string::npos ? std::string::npos : cur - start));

            start = cur + 1;
        }
    }

}
MY_NSP_END

using chila::lib::misc::rvalue_cast;

#include "macros.fgen.hpp"

#endif

