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

//@TODO Que al llamara al event se llame con el operador() y no entrando en .function(...)
//@TODO Manejar los asserts
//@TODO Categorizar events y functions, o sea, agruparlos
//@TODO Hay que crear el linkeador automatico de modulos (start-->start-->start, finish<--finish<--finish)
//@TODO Podrias ser bueno que al especificar los tipos, se especificque el unqualified, y que siempre se lo use con const&


#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__FWD_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_TREE__FWD_HPP

#include <vector>
#include <string>
#include <set>
#include <chila/lib/misc/Path.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/exception/error_info.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    template <typename Container>
    struct Object;

    template <typename Derived>
    struct Arguments;

    template <typename Derived>
    struct ArgumentAliases;

    template <typename Derived>
    struct ArgProviderCreators;

    template <typename Derived>
    struct ConnectorAliases;

    template <typename Derived>
    struct ConnectorInstances;

    struct ObjectContainer;
    struct Connector;
    struct Function;
    struct Functions;
    struct Signature;
    struct Argument;
    struct FunctionArgument;
    struct Namespace;
    struct NspBase;
    struct GlobalNsp;
    struct ArgumentGenerator;
    struct ArgumentGenerators;
    struct Application;
    struct ConnectorEventConnection;
    struct ConnectorEventConnections;
    struct ArgumentAlias;
    struct ArgumentAliasLink;
    struct ArgProviderCreator;
    struct ArgumentGetterProv;
    struct ArgumentSetterReq;
    struct ConnectorAlias;
    struct FunctionConnection;
    struct ConnectorInstance;
    struct APCArguments;
    struct APCArgument;
    struct FunConnDestination;
    struct FunConnArgProvCreator;
    struct FunConnArgProvCreators;

    struct TreeElement
    {
        virtual GlobalNsp &getGlobalNsp() = 0;
        virtual const GlobalNsp &getGlobalNsp() const = 0;
        virtual void check() const {}
    };

    typedef std::vector<std::string> StringVec;
    typedef std::set<std::string> StringSet;

    FWDEC_TYPE(IArgNamesReqOrProv);
    FWDEC_TYPE(IArgumentNamesRequirer);
    FWDEC_TYPE(IArgumentNamesProvider);

#define DEF_VECTOR(Type)                                    \
        typedef std::vector<Type*> Type##Vec;               \
        typedef std::vector<const Type*> Type##CVec;

    DEF_VECTOR(Namespace);
    DEF_VECTOR(Argument);
    DEF_VECTOR(Function);
    DEF_VECTOR(FunctionArgument);
    DEF_VECTOR(Connector);
    DEF_VECTOR(Application);
    DEF_VECTOR(ArgumentAlias);
    DEF_VECTOR(ArgumentAliasLink);
    DEF_VECTOR(ConnectorAlias);
    DEF_VECTOR(ArgProviderCreator);
    DEF_VECTOR(FunctionConnection);
    DEF_VECTOR(ConnectorInstance);
    DEF_VECTOR(APCArgument);
    DEF_VECTOR(FunConnDestination);
    DEF_VECTOR(FunConnArgProvCreator);


#undef DEF_VECTOR

    StringSet getAliasesOfFunction(const ConnectorAlias &connAlias, const Function &function);

    struct IArgNamesReqOrProv
    {
        virtual const libMisc::Path &getPath() const = 0;
        virtual ~IArgNamesReqOrProv() {}
    };

    struct IArgumentNamesRequirer : public virtual IArgNamesReqOrProv
    {
        virtual const StringSet &getRequiredArgNames() const = 0;
    };

    struct IArgumentNamesProvider : public virtual IArgNamesReqOrProv
    {
        virtual const StringSet &getProvidedArgNames() const = 0;
    };

    typedef std::vector<IArgNamesReqOrProvSCPtr> IArgNamesReqOrProvVec;




}}}}

#undef libMisc
#undef DEF_NAMESPACE
#undef FWDEC_TYPE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

