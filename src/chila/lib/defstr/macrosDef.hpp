/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#define CHILA_LIB_DEFSTR__ELEM(index, fieldInds, elem)  \
    BOOST_PP_SEQ_ELEM(BOOST_PP_SEQ_ELEM(index, fieldInds), elem)


#define CHILA_LIB_DEFSTR__DEF_FIELD(r, fieldInds, elem) \
        CHILA_LIB_DEFSTR__ELEM(0, fieldInds, elem)     \
        CHILA_LIB_DEFSTR__ELEM(1, fieldInds, elem);

#define CHILA_LIB_DEFSTR__PRINT_FIELD(r, fieldInds, elem) \
        chila::lib::defstr::printField(printer,                         \
        CHILA_LIB_DEFSTR__ELEM(0, fieldInds, elem),                       \
        BOOST_PP_STRINGIZE(CHILA_LIB_DEFSTR__ELEM(1, fieldInds, elem)),   \
        data.CHILA_LIB_DEFSTR__ELEM(1, fieldInds, elem));


/**
 * - Name:      Structure name.
 * - fields:    Sequence of field sequences.
 * - fieldInds: Field indexes to take (0 = type, 1 = name).
 */
#define CHILA_LIB_DEFSTR__DEF_STRUCT(Name, fields, fieldInds)    \
        struct Name                 \
        {                           \
            BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DEFSTR__DEF_FIELD, fieldInds, fields)    \
        };

#define CHILA_LIB_DEFSTR__DEC_PRINT(Name)    \
        template <>                                     \
        void print(chila::lib::misc::Printer &printer, const Name &data);

/**
 * - Name:      Structure name.
 * - fields:    Sequence of field sequences.
 * - fieldInd:  Field index or the field name.
 */
#define CHILA_LIB_DEFSTR__DEF_PRINT(Name, fields, fieldInds)    \
        template <>                                     \
        void print(chila::lib::misc::Printer &printer, const Name &data)  \
        {                                                                                               \
            BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DEFSTR__PRINT_FIELD, fieldInds, fields)                      \
        }

#define CHILA_LIB_DEFSTR__EQ_FIELD(r, fieldInd, elem) \
        && lhs.BOOST_PP_SEQ_ELEM(fieldInd, elem) == rhs.BOOST_PP_SEQ_ELEM(fieldInd, elem)

#define CHILA_LIB_DEFSTR__NEQ_FIELD(r, fieldInd, elem) \
        || lhs.BOOST_PP_SEQ_ELEM(fieldInd, elem) != rhs.BOOST_PP_SEQ_ELEM(fieldInd, elem)

#define CHILA_LIB_DEFSTR__DEC_COMP(Name)    \
        bool operator==(const Name &lhs, const Name &rhs);  \
        bool operator!=(const Name &lhs, const Name &rhs);

#define CHILA_LIB_DEFSTR__DEF_COMP(Name, fields, fieldInd)    \
        bool operator==(const Name &lhs, const Name &rhs)                                                   \
        {                                                                                                   \
            return true BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DEFSTR__EQ_FIELD, fieldInd, fields);       \
        }                                                                                                   \
        bool operator!=(const Name &lhs, const Name &rhs)                                                   \
        {                                                                                                   \
            return false BOOST_PP_SEQ_FOR_EACH(CHILA_LIB_DEFSTR__NEQ_FIELD, fieldInd, fields);     \
        }

