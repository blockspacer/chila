/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define def_unary_op(Name, op)                                      \
    template <typename Ret, typename Arg>                           \
    struct Name                                                     \
    {                                                               \
        typedef Ret result_type;                                    \
        typedef boost::mpl::vector<Arg> argument_types;             \
                                                                    \
        Ret operator()(Arg val) const                               \
        {                                                           \
            return op val;                                          \
        }                                                           \
    };

#define def_binary_op(Name, op)                                     \
    template <typename Ret, typename Arg0, typename Arg1>           \
    struct Name                                                     \
    {                                                               \
        typedef Ret result_type;                                    \
        typedef boost::mpl::vector<Arg0, Arg1> argument_types;      \
                                                                    \
        Ret operator()(Arg0 val0, Arg1 val1) const                  \
        {                                                           \
            return val0 op val1;                                    \
        }                                                           \
    };
