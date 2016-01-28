/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__EXCEPTIONS_HPP
#define CHILA_LIB_MISC__EXCEPTIONS_HPP

#include <chila/lib/misc/fwd.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/type_index.hpp>
#include "fwd.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Exception: public std::exception, boost::exception
    {
        virtual std::string message() const { return what(); }
        ~Exception() throw() {}
    };

    template <typename Type>
    void printExDetail(const boost::exception &ex, const std::string &desc)
    {
        if (auto *info = boost::get_error_info<Type>(ex))
        {
            std::cerr << "- " << desc << ": [" << *info << "]" << std::endl;
        }
    }

    DEF_EXCEPTION(ElementNotFound, "element not found");
    DEF_EXCEPTION(ElementAlreadyExists, "element already exists");
    DEF_EXCEPTION(ManyXMLElementsFound, "many xml nodes found");
    DEF_EXCEPTION(XMLElementNotFound, "xml element not found");
    DEF_EXCEPTION(XMLNodeIsNotElement, "xml node is not element");
    DEF_EXCEPTION(XMLNodeIsNotAttribute, "xml node is not attribute");
    DEF_EXCEPTION(InvalidXMLAttribute, "invalid xml attribute");
    DEF_EXCEPTION(InvalidArgument, "invalid argument value");
    DEF_EXCEPTION(ValueNotSet, "value not set");
    DEF_RUNTIME_ERROR(ApplicationError);
    DEF_RUNTIME_ERROR_WT(InvalidPath, "invalid path");

    CHILA_LIB_MISC__DEC_ERROR_INFO_STRUCT
    (
        ((Description)(std::string)("description"))
        ((Row)(unsigned)("row"))
        ((Column)(unsigned)("column"))
        ((XPath)(std::string)("xpath"))
        ((FilePath)(boost::filesystem::path)("file path"))
        ((Path)(chila::lib::misc::Path)("path"))
        ((TypeFrom)(boost::typeindex::type_index)("type from"))
        ((TypeTo)(boost::typeindex::type_index)("type to"))
        ((ActualType)(boost::typeindex::type_index)("actual type"))
    )

    struct AssertionFailed: public chila::lib::misc::Exception
    {
        std::string msg;
        AssertionFailed(const std::string &msg) : msg(msg) {}

        const char *what() const throw() { return msg.c_str(); }

        ~AssertionFailed() throw() {}
    };

    struct DynamicLibraryError: public boost::exception, public std::runtime_error
    {
        DynamicLibraryError(const std::string &cause) : std::runtime_error(cause) {}
        ~DynamicLibraryError() throw() {}
    };

    struct DynamicLibraryOpenError: public DynamicLibraryError
    {
        boost::filesystem::path file;
        DynamicLibraryOpenError(const boost::filesystem::path &file, const std::string &cause) :
            DynamicLibraryError(cause), file(file) {}
        ~DynamicLibraryOpenError() throw() {}
    };

    struct DynamicLibrarySymbolError: public DynamicLibraryError
    {
        std::string symbol;
        DynamicLibrarySymbolError(const std::string &symbol, const std::string &cause) :
            DynamicLibraryError(cause), symbol(symbol) {}
        ~DynamicLibrarySymbolError() throw() {}
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef DEF_EXCEPTION


#endif
