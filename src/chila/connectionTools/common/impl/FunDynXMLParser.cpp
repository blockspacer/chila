/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FunDynXMLParser.hpp"
#include "../../dynFunExecuter/util.hpp"
#include <sstream>

#include <chila/lib/misc/macrosExp.hpp>


#include "macros.fgen.hpp"

#define MODULE_NAME FunDynXMLParser


MY_NSP_START
{
    void FunDynXMLParser::MOD_ACTION_SIG(take)
    {
        xmlpp::DomParser parser;
        std::stringstream str(text);

        parser.parse_stream(str);

        auto ret = dynFunExecuter::parseXML(chila::lib::misc::deref(parser.get_document()->get_root_node()));

        execute_event(parsed)(ret.path, ret.arguments);
    }

    connection::FunDynXMLParser::CProviderUPtr connection::FunDynXMLParser::create(const std::string &instanceName)
    {
        return boost::make_unique<impl::FunDynXMLParser>(instanceName);
    }
}
MY_NSP_END


