/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "Parser.hpp"
#include <boost/make_shared.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    #define def_create(name, Iterator)  \
        boost::shared_ptr< IParser<Iterator> >  name(                               \
            const IExpressionProviderSCPtr &expProvider, bool optimize)             \
        {                                                                           \
            return boost::make_shared< Parser<Iterator> >(expProvider, optimize);   \
        }

    def_create(createStrItParser, std::string::const_iterator)
//    def_create(createCCharParser, const char*)

    #undef def_create


}
MY_NSP_END

