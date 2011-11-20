/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_EXCEPTIONS_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_EXCEPTIONS_HPP

#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <stdexcept>
#include <string>
#include <boost/make_shared.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE           CHILA_LIB_MISC__DEF_NAMESPACE
#define DEF_RUNTIME_ERROR       CHILA_LIB_MISC__DEF_RUNTIME_ERROR
#define DEF_EXCEPTION           CHILA_LIB_MISC__DEF_EXCEPTION

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    DEF_RUNTIME_ERROR(ConnectorCreationError);
    DEF_EXCEPTION(ArgumentConnectorAlreadyExistsError, "argument's connector already exists");
    DEF_EXCEPTION(ArgumentConnectorIsSameAsSourceError, "argument's connector is the same as the source's");

    DEF_EXCEPTION(TypeConversionAlreadyExistsError, "type conversion already exists");
    DEF_EXCEPTION(TypeInheritanceAlreadyExistsError, "type inheritance already exists");
    DEF_EXCEPTION(InvalidTypeError, "invalid type");
    DEF_EXCEPTION(ArgumentCannotBePassedError, "argument cannot be passed");
    DEF_EXCEPTION(ForwarderAlreadyExistsError, "forwarder already exists");
    DEF_EXCEPTION(ConnectorInstanceAlreadyExists, "connector instance already exists");

    struct ErrorInfo
    {
        typedef boost::error_info<struct tag_msg, std::string> Message;
        typedef boost::error_info<struct tag_path, libMisc::Path> Path;
    };


    struct IdentifierNotFound : public std::exception, public boost::exception
    {
        libMisc::Path path;
        IdentifierNotFound(const libMisc::Path &path) : path(path) {}
        ~IdentifierNotFound() throw() {}
    };

    struct ArgumentNotFound : public IdentifierNotFound
    {
        ArgumentNotFound(const libMisc::Path &path) : IdentifierNotFound(path) {}
        const char *what() const throw() { return "argument not found"; }
        ~ArgumentNotFound() throw() {}
    };

//    struct ArgumentAlreadyLinked : public std::exception, public boost::exception
//    {
//        ArgumentSCPtr arg;
//        ArgumentAlreadyLinked(const ArgumentSCPtr &arg) : arg(arg) {}
//        const char *what() const throw() { return "argument already linked"; }
//        ~ArgumentAlreadyLinked() throw() {}
//    };

    struct ArgumentsNotLinkedError : public std::exception, public boost::exception
    {
        libMisc::Path srcArg, dstArg;
        ArgumentsNotLinkedError(const libMisc::Path &srcArg, const libMisc::Path &dstArg) : srcArg(srcArg), dstArg(dstArg) {}
        const char *what() const throw() { return "arguments are not linked"; }
        ~ArgumentsNotLinkedError() throw() {}
    };

    struct AliasNameDoesNotExistError : public std::exception, public boost::exception
    {
        std::string aliasName;
        AliasNameDoesNotExistError(const std::string &aliasName) : aliasName(aliasName) {}
        const char *what() const throw() { return "alias name does not exist"; }
        ~AliasNameDoesNotExistError() throw() {}
    };

    struct CheckError;
    struct CheckErrorGroup;
    struct CheckErrorElement;
    typedef boost::shared_ptr<const CheckError> CheckErrorSCPtr;
    typedef boost::shared_ptr<const CheckErrorElement> CheckErrorElementSCPtr;
    typedef boost::shared_ptr<const CheckErrorGroup> CheckErrorGroupSCPtr;

    struct CheckError : public std::exception
    {
        virtual CheckErrorSCPtr clone() const = 0;
        virtual std::ostream &write(std::ostream &out) const = 0;
        ~CheckError() throw() {}
    };

    class CheckErrorElement : public CheckError
    {
        protected:
            libMisc::Path path;
            std::string error;

        public:
            CheckErrorElement(const libMisc::Path &path, const std::string &error) : path(path), error(error) {}
            CheckErrorElement(const CheckErrorElement &rhs) : path(rhs.path), error(rhs.error) {}
            ~CheckErrorElement() throw() {}

            const libMisc::Path &getPath() const { return path; }
            const std::string &getError() const { return error; }

            virtual CheckErrorSCPtr clone() const { return boost::make_shared<CheckErrorElement>(*this); }

            virtual std::ostream &write(std::ostream &out) const
            {
                return out << "- " << path.getStringRep() << ": " << error << "\n";
            }
    };

    class CheckFunConnError : public CheckErrorElement
    {
        private:
            IArgNamesReqOrProvVec vec;

        public:
            CheckFunConnError(const libMisc::Path &path, const std::string &error,
                    const IArgNamesReqOrProvVec &vec) : CheckErrorElement(path, error), vec(vec) {}
            CheckFunConnError(const CheckFunConnError &rhs) : CheckErrorElement(rhs.path, rhs.error), vec(rhs.vec) {}
            ~CheckFunConnError() throw() {}

            CheckErrorSCPtr clone() const  { return boost::make_shared<CheckFunConnError>(*this); }

            std::ostream &write(std::ostream &out) const
            {
                CheckErrorElement::write(out);
                out << "  vector is:\n";

                BOOST_FOREACH(const IArgNamesReqOrProvSCPtr &elem, vec)
                {
                    out << "   - " << elem->getPath().getStringRep() << ":";
                    if (IArgumentNamesRequirerSCPtr req = boost::dynamic_pointer_cast<const IArgumentNamesRequirer>(elem))
                    {
                        out << " (req: ";
                        printArgSet(out, req->getRequiredArgNames());
                        out << ")";
                    }

                    if (IArgumentNamesProviderSCPtr prov = boost::dynamic_pointer_cast<const IArgumentNamesProvider>(elem))
                    {
                        out << " (prov: ";
                        printArgSet(out, prov->getProvidedArgNames());
                        out << ")";
                    }
                    out << "\n";
                }

                return out;
            }

            void printArgSet(std::ostream &out, const StringSet &args) const
            {
                bool first = true;
                BOOST_FOREACH(const std::string &arg, args)
                {
                    if (first) first = false;
                    else out << ", ";

                    out << arg;
                }
            }

    };

    class CheckErrorGroup : public CheckError
    {
        private:
            typedef std::vector<CheckErrorSCPtr> ErrorVec;
            ErrorVec errors;

        public:
            CheckErrorGroup(const CheckErrorGroup &rhs) : errors(rhs.errors) {}
            CheckErrorGroup() {}
            ~CheckErrorGroup() throw() {}


            void addError(const CheckErrorSCPtr &error)
            {
                errors.push_back(error);
            }

            void addError(const CheckError &error)
            {
                errors.push_back(error.clone());
            }

            const ErrorVec &getErrors() const { return errors; }

            CheckErrorSCPtr clone() const { return boost::make_shared<CheckErrorGroup>(*this); }

            std::ostream &write(std::ostream &out) const
            {
                BOOST_FOREACH(const CheckErrorSCPtr &cError, errors)
                {
                    cError->write(out);
                }

                return out;
            }
    };

}}}}

#undef DEF_NAMESPACE
#undef libMisc
#undef DEF_RUNTIME_ERROR
#undef DEF_EXCEPTION

#include <chila/lib/misc/macrosUndef.hpp>
#endif

