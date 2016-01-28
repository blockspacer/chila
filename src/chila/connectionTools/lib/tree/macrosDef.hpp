/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define def_getall_getters(Type, types) \
        Type##Vec types()        { return elementsOf<Type>(); }   \
        Type##CVec types() const { return elementsOf<Type>(); }



#define def_map_getters(Type, type)     \
        Type &type(const std::string &name)             { return get(name).cast<Type>(); }     \
        const Type &type(const std::string &name) const { return get(name).cast<Type>(); }

#define def_map_getall_getters(Type, type)      \
        def_map_getters(Type, type)             \
        def_getall_getters(Type, type##s)

#define def_map_setter(Type, type)     \
        Type &type(const std::string &name)      \
        {                                                       \
            Type *ret;                                          \
            NodeAPtr aptr(ret = new Type(*this, name));         \
            append(aptr);                                       \
            return *ret;                                        \
        }

#define def_map_getall_getters_setter(Type, type)   \
        def_map_getall_getters(Type, type)           \
        def_map_setter(Type, set##Type)


#define def_vec_getters(Type)     \
        Type &operator[](unsigned index)             { return get(index).cast<Type>(); }      \
        const Type &operator[](unsigned index) const { return get(index).cast<Type>(); }

#define def_vec_adder(Type)     \
        Type &add()                                             \
        {                                                       \
            Type *ret;                                          \
            NodeAPtr aptr(ret = new Type(*this));               \
            NodeVector::add(aptr);                              \
            return *ret;                                        \
        }

#define def_vec_getall_getters(Type)      \
        def_vec_getters(Type)             \
        def_getall_getters(Type, elements)


#define def_vec_getall_getters_adder(Type)  \
        def_vec_getall_getters(Type)            \
        def_vec_adder(Type)


#define def_map_attribute(Type, name)                           \
        const Value<Type> &name() const                         \
        {                                                       \
            return get(#name).cast< Value<Type> >();            \
        }                                                       \
        Value<Type> &name()                                     \
        {                                                       \
            return get(#name).cast< Value<Type> >();            \
        }

#define def_map_field(Type, name)                               \
        const Type &name() const                                \
        {                                                       \
            return get(#name).cast<Type>();                     \
        }                                                       \
        Type &name()                                            \
        {                                                       \
            return get(#name).cast<Type>();                     \
        }
