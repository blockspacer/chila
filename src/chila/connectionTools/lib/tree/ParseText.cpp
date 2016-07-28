/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "ParseText.hpp"
#include <chila/connectionTools/lib/tree/types.hpp>
#include <boost/range/algorithm/find_first_of.hpp>
#include <boost/range/algorithm/find.hpp>
#include "exceptions.hpp"
#include "util.hpp"

#include "nspDef.hpp"

MY_NSP_START
{


#define my_text_case(Type) \
    if (auto *typed = dynamic_cast<const Type*>(&node)) \
        return parse(*typed);

    bool ParseText::parse()
    {
        my_text_case(connector::Connector)
        my_text_case(connector::ArgumentBase)
        my_text_case(connector::EventBase)
        my_text_case(connector::ActionBase)
        my_text_case(cPerformer::ArgumentBase)
        my_text_case(cPerformer::AProviderCreatorBase)
        my_text_case(cPerformer::ConnectorAlias)
        my_text_case(cPerformer::ConnectorInstance)
        my_text_case(cPerformer::ConnectorInstanceGroup)
        my_text_case(cPerformer::ActionInstance)
        my_text_case(cPerformer::EventCall)
        my_text_case(cPerformer::CAArgAlias)
        my_text_case(cPerformer::EventAlias)
        my_text_case(cPerformer::ActionAlias)
        my_text_case(cPerformer::ConnectionPerformer)

        CHILA_LIB_MISC__SHOW(40, boost::typeindex::type_id_runtime(node).pretty_name());
        abort();

//        if (_range.empty())
//            return false;
//
//        _token = _range;
//        _range = boost::make_iterator_range(_range.end(), _range.end());
        return true;
    }

    template <typename CastFun>
    bool ParseText::parseEx(const CastFun &castFun)
    {
        //CHILA_LIB_MISC__SHOW(40, tokenStr());
        if (outside)
        {
            auto end = boost::find(_range,  '\'');
            _token = boost::make_iterator_range(_range.begin(), end);


            //CHILA_LIB_MISC__SHOW(40, "here");
            outside = end == _range.end();

            if (_range.empty())
                return false;

            //CHILA_LIB_MISC__SHOW(40, "here");
            _range = boost::make_iterator_range(end == _range.end() ? end : end + 1, _range.end());
            _foundNode = nullptr;
        }
        else
        {
            auto end = boost::find_first_of(_range, std::array<char, 3>{{'\'', '\n', ' '}});
            _token = boost::make_iterator_range(_range.begin(), end);

            //CHILA_LIB_MISC__SHOW(40, "here");
            outside = true;

            if (_range.empty())
                BOOST_THROW_EXCEPTION(DescriptionParseError());

            if (end == _range.end() || *end == ' ' || *end == '\n')
            {
                _range = boost::make_iterator_range(end, _range.end());
                _token = boost::make_iterator_range(_token.begin() - 1, _token.end());
                //CHILA_LIB_MISC__SHOW(40, "here");
                return end != _range.end();
            }

            //CHILA_LIB_MISC__SHOW(40, "here");
            _range = boost::make_iterator_range(end + 1, _range.end());

            //CHILA_LIB_MISC__SHOW(40, "here");
            auto path = clMisc::Path(tokenStr());

            //CHILA_LIB_MISC__SHOW(40, "here");
            if (path.size() != 2)
//                abort();
                BOOST_THROW_EXCEPTION(DescriptionParseInvalidReference() << ErrorInfo::DescToken(tokenStr()));

            auto typeStr = *path.begin();
            auto name = *(path.begin() + 1);

            //CHILA_LIB_MISC__SHOW(40, "here");
            _foundNode = castFun(typeStr, name);

            //CHILA_LIB_MISC__SHOW(40, "here");
            if (!_foundNode)
                BOOST_THROW_EXCEPTION(DescriptionParseInvalidReference() << ErrorInfo::DescToken(tokenStr()));
        }

        return true;
    }

#define my_parse_text_case_grouped(elementsStr, elements, Element) \
    if (typeStr == elementsStr) \
    { \
        return getGroupedElementPtr<const Element##Group, \
                                             const Element>(elements, clMisc::Path(elemName, ":")); \
    }

#define my_parse_text_case(elementsStr, elements) \
    if (typeStr == elementsStr) \
        return elements.getPtr(elemName); \

#define my_parse_text_case_walias(elementsStr, aliasElements, elements) \
    if (typeStr == elementsStr) \
    { \
        if (auto ret = aliasElements.getPtr(elemName)) \
            return ret; \
        else \
            return elements.getPtr(elemName); \
    }

    bool ParseText::parseDefault()
    {
        if (_range.empty())
            return false;

        _token = _range;
        _range = boost::make_iterator_range(_range.end(), _range.end());
        return true;
    }


    bool ParseText::parse(const connector::Connector &typedNode)
    {
        return parseEx([&](const std::string &typeStr, const std::string &elemName) -> Node*
        {
            my_parse_text_case_grouped("arguments", typedNode.arguments(), connector::Argument)
            my_parse_text_case_grouped("events", typedNode.events(), connector::Event)
            my_parse_text_case_grouped("actions", typedNode.actions(), connector::Action)

            return  nullptr;
        });
    }

    bool ParseText::parse(const connector::ArgumentBase &typedNode)
    {
        auto &parent = typedNode.parent<connector::ArgumentMap>();
        auto &connector = getGroupParent<connector::Connector, connector::ArgumentGroup>(parent);
        return parse(connector);
    }

    bool ParseText::parse(const connector::EventBase &typedNode)
    {
        auto &parent = typedNode.parent<connector::EventMap>();
        auto &connector = getGroupParent<connector::Connector, connector::EventGroup>(parent);
        return parse(connector);
    }


    bool ParseText::parse(const connector::ActionBase &typedNode)
    {
        auto &parent = typedNode.parent<connector::ActionMap>();
        auto &connector = getGroupParent<connector::Connector, connector::ActionGroup>(parent);
        return parse(connector);
    }

    bool ParseText::parse(const cPerformer::ConnectionPerformer &typedNode)
    {
        return parseEx([&](const std::string &typeStr, const std::string &elemName) -> Node*
        {
            my_parse_text_case_grouped("arguments", typedNode.arguments(), cPerformer::Argument)
            my_parse_text_case_grouped("apcs", typedNode.aProvCreators(), cPerformer::AProviderCreator)
            my_parse_text_case("connAliases", typedNode.connectorAliases())
            my_parse_text_case_grouped("connInstances", typedNode.connInstances(), cPerformer::ConnectorInstance)

            return nullptr;
        });
    }

    bool ParseText::parse(const cPerformer::ArgumentBase &typedNode)
    {
        auto &parent = typedNode.parent<cPerformer::ArgumentMap>();
        auto &cPerformer = getGroupParent<cPerformer::ConnectionPerformer, cPerformer::ArgumentGroup>(parent);
        return parse(cPerformer);
    }

    bool ParseText::parse(const cPerformer::AProviderCreatorBase &typedNode)
    {
        auto &parent = typedNode.parent<cPerformer::AProviderCreatorMap>();
        auto &cPerformer = getGroupParent<cPerformer::ConnectionPerformer, cPerformer::AProviderCreatorGroup>(parent);
        return parse(cPerformer);
    }


    bool ParseText::parse(const cPerformer::ConnectorAlias &typedNode)
    {
        auto &connector = typedNode.connector().referenced();
        return parseEx([&](const std::string &typeStr, const std::string &elemName) -> Node*
        {
            my_parse_text_case("arguments", typedNode.arguments())
            my_parse_text_case_walias("events", typedNode.events(), connector.events())
            my_parse_text_case_walias("actions", typedNode.actions(), connector.actions())

            return nullptr;
        });
    }

    bool ParseText::parse(const cPerformer::CAArgAlias &typedNode)
    {
        auto &connAlias = typedNode.parent().parent<cPerformer::ConnectorAlias>();
        return parse(connAlias);
    }

    bool ParseText::parse(const cPerformer::EventAlias &typedNode)
    {
        auto &connAlias = typedNode.parent().parent<cPerformer::ConnectorAlias>();
        return parse(connAlias);
    }

    bool ParseText::parse(const cPerformer::ActionAlias &typedNode)
    {
        auto &connAlias = typedNode.parent().parent<cPerformer::ConnectorAlias>();
        return parse(connAlias);
    }

    bool ParseText::parse(const cPerformer::ConnectorInstance &typedNode)
    {
        auto &connAlias = typedNode.connAlias().referenced();
        return parse(connAlias);
    }

    bool ParseText::parse(const cPerformer::ConnectorInstanceGroup &typedNode)
    {
        auto &parent = typedNode.parent<cPerformer::ConnectorInstanceMap>();
        auto &cPerformer = getGroupParent<cPerformer::ConnectionPerformer, cPerformer::ConnectorInstanceGroup>(parent);
        return parse(cPerformer);
    }

    bool ParseText::parse(const cPerformer::EventCall &typedNode)
    {
        auto &connAlias = typedNode.parent<cPerformer::EventCallMap>()
                                   .parent<cPerformer::ConnectorInstance>().connAlias().referenced();
        return parse(connAlias);
    }

    bool ParseText::parse(const cPerformer::ActionInstance &typedNode)
    {
        // Fix: must contemplate the event-call's and the action-instance's connector-alias
        auto &connAlias = typedNode.connInstance().referenced().connAlias().referenced();

        return parse(connAlias);
    }


}
MY_NSP_END
