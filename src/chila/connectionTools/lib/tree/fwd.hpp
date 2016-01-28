/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__FWD_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__FWD_HPP

#include <chila/lib/misc/Path.hpp>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/integer_traits.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>
#include <boost/exception/error_info.hpp>

#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

#define DEF_VECTYPE(Type)                               \
    using Type##Vec = std::vector<Type*>;               \
    using Type##CVec= std::vector<const Type*>

#define FWDEC_NTYPE(Type)                               \
    struct Type;                                        \
    DEF_VECTYPE(Type);




#define PATH_PROVIDER(Name, path)       \
        struct Name##PathProvider       \
        {                               \
            static chila::lib::misc::Path get() { return path; }  \
        }

#define DEF_BASIC_REF(Name, Type, RefType, parentCount, path)                               \
        PATH_PROVIDER(Name, path);                                                      \
        using Name = BasicReference<Type, RefType, parentCount, Name##PathProvider>;       \
        DEF_VECTYPE(Name)

#define DEF_STRING_REF(Name, RefType, parentCount, path)                               \
        PATH_PROVIDER(Name, path);                                                      \
        using Name = StringReference<RefType, parentCount, Name##PathProvider>;       \
        DEF_VECTYPE(Name)

#define BASE_PARENT boost::integer_traits<unsigned>::const_max

#define FWDEC_TYPE CHILA_LIB_MISC__FWDEC_TYPE

#include "nspDef.hpp"

MY_NSP_START
{
    namespace clMisc = chila::lib::misc;

    FWDEC_TYPE(Exception);

    using StringVec =  std::vector<std::string>;
    using PathSet =  std::set<chila::lib::misc::Path>;

    boost::uint32_t crc(boost::uint32_t val1, boost::uint32_t val2);

    boost::uint32_t crc(const std::string &value);

    inline boost::uint32_t crc(const chila::lib::misc::Path &value)
    {
        return crc(value.getStringRep());
    }

    struct ReqProv
    {
        chila::lib::misc::Path path, apcName;
        PathSet requires, provides;

        ReqProv(chila::lib::misc::Path path, chila::lib::misc::Path apcName) :
            path(rvalue_cast(path)), apcName(rvalue_cast(apcName)) {}
    };

    using ReqProvVector = std::vector<ReqProv>;

    FWDEC_TYPE(Namespace);
    FWDEC_TYPE(Description);

    namespace connector
    {
        FWDEC_TYPE(ArgumentBase);
        FWDEC_TYPE(Argument);
        FWDEC_TYPE(ArgumentMap);
        FWDEC_TYPE(ArgumentGroup);
        FWDEC_TYPE(ArgRef);
        FWDEC_TYPE(ArgRefMap);
        FWDEC_TYPE(Function);

        FWDEC_TYPE(EventBase);
        FWDEC_TYPE(EventMap);
        FWDEC_TYPE(EventGroup);
        FWDEC_TYPE(Event);

        FWDEC_TYPE(ActionBase);
        FWDEC_TYPE(ActionMap);
        FWDEC_TYPE(ActionGroup);
        FWDEC_TYPE(Action);

        FWDEC_TYPE(EventRef);
        FWDEC_TYPE(EventRefMap);
        FWDEC_TYPE(Connector);
    }

    namespace cPerformer
    {
        FWDEC_TYPE(ArgumentBase);
        FWDEC_TYPE(Argument);
        FWDEC_TYPE(ArgumentGroup);
        FWDEC_TYPE(ArgumentMap);

        FWDEC_TYPE(CArgRef);
        FWDEC_TYPE(ArgRefV);
        FWDEC_TYPE(ArgRefT);
        FWDEC_TYPE(CAArgAlias);
        FWDEC_TYPE(ConnectorRef);
        FWDEC_TYPE(CAArgAliasMap);
        FWDEC_TYPE(ConnectorAlias);
        FWDEC_TYPE(ConnectorAliasRef);
        FWDEC_TYPE(ConnectorAliasMap);
        FWDEC_TYPE(ArgRefTMap);
        FWDEC_TYPE(ArgRefVMap);
        FWDEC_TYPE(AProviderCreatorBase);
        FWDEC_TYPE(AProviderCreator);
        FWDEC_TYPE(AProviderCreatorGroup);
        FWDEC_TYPE(AProviderCreatorMap);
        FWDEC_TYPE(APCRef);
        FWDEC_TYPE(APCRefMap);
        FWDEC_TYPE(FunctionRef);
        FWDEC_TYPE(ActionInstance);
        FWDEC_TYPE(CAEventRef);
        FWDEC_TYPE(CAActionRef);
        FWDEC_TYPE(EventAlias);
        FWDEC_TYPE(EventAliasBase);
        FWDEC_TYPE(EventAliasGroup);
        FWDEC_TYPE(EventAliasMap);
        FWDEC_TYPE(ActionAlias);
        FWDEC_TYPE(ActionAliasBase);
        FWDEC_TYPE(ActionAliasGroup);
        FWDEC_TYPE(ActionAliasMap);
        FWDEC_TYPE(EventCall);
        FWDEC_TYPE(EventCallMap);
        FWDEC_TYPE(ConnectorInstanceBase);
        FWDEC_TYPE(ConnectorInstanceMap);
        FWDEC_TYPE(ConnectorInstanceGroup);
        FWDEC_TYPE(ConnectorInstance);
        FWDEC_TYPE(ConnectionPerformer);
    }

    using InsertProxy = int;

    using CInsVec = std::vector<const cPerformer::ConnectorInstance*>;
    using AInsVec = std::vector<const cPerformer::ActionInstance*>;

    CHILA_LIB_MISC__FWDEC_TYPE(ValueEntry);
    using ValueVec = std::vector<ValueEntry>;

    struct ValueEntry
    {
        std::string value;
        ValueVec subValues;

        ValueEntry(std::string value) : value(rvalue_cast(value)) {}
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#undef DEF_VECTYPE
#undef FWDEC_NTYPE
#undef FWDEC_TYPE

#undef DEF_MAP_TYPE
#undef DEF_VEC_TYPE
#undef PATH_PROVIDER
#undef DEF_BASIC_REF
#undef BASE_PARENT
#undef DEF_STRING_REF


#endif

