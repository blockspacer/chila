#ifndef CHILA_TOOLS_LICENSEADDER__FWD_HPP
#define CHILA_TOOLS_LICENSEADDER__FWD_HPP

#include <chila/lib/misc/fwd.hpp>
#include <chila/lib/xmlppUtils/fwd.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <iterator>

#include "macros.fgen.hpp"

CHILA_LIB_MISC__DEC_NAMESPACE_VAR(boost, filesystem)

MY_NSP_START
{
    namespace bfs = boost::filesystem;
    namespace clMisc = chila::lib::misc;
    namespace clXmlppUtils = chila::lib::xmlppUtils;

    using chila::lib::misc::rvalue_cast;

    using ISIterator = std::istream_iterator<char>;
    using MPIterator = boost::spirit::multi_pass<ISIterator>;

    CHILA_LIB_MISC__NAMED_TUPLE
    (
        Format, 0,

            ((std::string)(header))
            ((std::string)(start))
            ((std::string)(lineStart))
            ((std::string)(emptyLineStart))
            ((std::string)(end))
            ((clMisc::StringSet)(patterns))
    );


}
MY_NSP_END



#include "macros.fgen.hpp"
#endif
