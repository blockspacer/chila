/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define CHILA_LIB_DSV__SAVE_FIELD(r, fieldPos, elem) \
    BOOST_PP_IF(BOOST_PP_SUB(r, 2), out << delim;,) \
    chila::lib::dsv::save(out, data.BOOST_PP_SEQ_ELEM(fieldPos, elem), delim);

#define CHILA_LIB_DSV__LOAD_FIELD(r, fieldPos, elem) \
    chila::lib::dsv::load(in, data.BOOST_PP_SEQ_ELEM(fieldPos, elem), delim);

#define CHILA_LIB_DSV__DEC_SAVE_LOAD(Name)                    \
        template<>                                                      \
        void save(std::ostream &out, const Name &data, char delim);     \
        template<>                                                      \
        void load(std::istream &in, Name &data, char delim);


#define CHILA_LIB_DSV__DEF_SAVE_LOAD(Name, fields, fieldPos) \
        template<>                                                      \
        void save(std::ostream &out, const Name &data, char delim)      \
        {                                                               \
            BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DSV__SAVE_FIELD, fieldPos, fields)   \
        }                                                       \
        template<>                                              \
        void load(std::istream &in, Name &data, char delim)     \
        {                                                       \
            BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DSV__LOAD_FIELD, fieldPos, fields)   \
        }
