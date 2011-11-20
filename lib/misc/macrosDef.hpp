/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/preprocessor.hpp>

#define CHILA_LIB_MISC__NSP_FOR(index, data, nspName) \
        BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_DEC(index)), {,) namespace nspName

#define CHILA_LIB_MISC__DEF_NAMESPACE(deep, nspTuple) \
        BOOST_PP_LIST_FOR_EACH(CHILA_LIB_MISC__NSP_FOR, , BOOST_PP_TUPLE_TO_LIST(deep, nspTuple))

#define CHILA_LIB_MISC__DEF_EXCEPTION(Name, whatTxt) \
    struct Name : public std::exception, public boost::exception    \
    {                                                               \
        Name() {}                                                   \
        const char *what() const throw() { return whatTxt; }        \
        ~Name() throw() {}                                          \
    }

#define CHILA_LIB_MISC__SHOW(x) std::cout << "<" << __FILE__ << ":" << __LINE__ << ">: [" << x << "]" << std::endl

#define CHILA_LIB_MISC__FWDEC_SPTR(Type)                            \
    typedef boost::shared_ptr<Type> Type##SPtr;            \
    typedef boost::shared_ptr<const Type> Type##SCPtr;     \
    typedef boost::weak_ptr<Type> Type##WPtr;              \
    typedef boost::weak_ptr<const Type> Type##WCPtr

#define CHILA_LIB_MISC__FWDEC_APTR(Type)                                \
    typedef std::auto_ptr<Type> Type##APtr;             \
    typedef std::auto_ptr<const Type> Type##ACPtr;

#define CHILA_LIB_MISC__FWDEC_TYPE(Type)                            \
    class Type;                                     \
    CHILA_LIB_MISC__FWDEC_SPTR(Type)

#define CHILA_LIB_MISC__DEF_RUNTIME_ERROR(Name) \
    struct Name : public std::runtime_error, public boost::exception     \
    {                                           \
        Name(const std::string &msg) : std::runtime_error(msg) {}   \
        ~Name() throw() {}                      \
    }

