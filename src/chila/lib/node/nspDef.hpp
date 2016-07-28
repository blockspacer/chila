/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/misc/macrosExp.hpp>

#define MY_NSP chila,lib,node

#define MY_NSP_START      CHILA_LIB_MISC__DEF_NAMESPACE_VAR(MY_NSP)
#define MY_NSP_END    CHILA_LIB_MISC__CLOSE_DEF_NAMESPACE_VAR(MY_NSP)

#define my_assert       CHILA_LIB_MISC__ASSERT

#define insert_error_info(Type) \
    if (auto *info = boost::get_error_info<Type>(ex)) \
        exx << Type(*info);

#define ADD_CONST_IF(InType, Type)  CHILA_LIB_MISC__ADD_CONST_IF_TN(Type, boost::is_const<InType>::value)

#define CHILA_LIB_NODE__FRIEND_MAKE_SHARED_DEC(Name) \
    std::shared_ptr<class Name> make##Name(); \
    std::shared_ptr<class Name> make##Name(const Name &name); \

#define CHILA_LIB_NODE__FRIEND_MAKE_SHARED_DEF(Name) \
    namespace \
    { \
        struct concrete_##Name: public Name \
        { \
            concrete_##Name() = default; \
            concrete_##Name(const Name &name) : Name(name) {} \
        }; \
    } \
    inline std::shared_ptr<Name> make##Name() \
    { \
        return std::make_shared<concrete_##Name>(); \
    } \
    inline std::shared_ptr<Name> make##Name(const Name &name) \
    { \
        return std::make_shared<concrete_##Name>(); \
    }
