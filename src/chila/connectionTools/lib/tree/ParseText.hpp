/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__PARSETEXT_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__PARSETEXT_HPP

#include "fwd.hpp"
#include <chila/lib/misc/SinkInserter.hpp>
#include <chila/lib/misc/Path.hpp>
#include <chila/lib/node/fwd.hpp>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/node/exceptions.hpp>
#include <chila/lib/xmlppUtils/util.hpp>
#include <string>
#include <chila/lib/misc/macrosExp.hpp>
#include <boost/range.hpp>
#include <chila/connectionTools/lib/tree/fwd.hpp>

#include "nspDef.hpp"

MY_NSP_START
{
    class ParseText
    {
        public:
            using Range = boost::iterator_range<std::string::const_iterator>;
            using Node = const chila::lib::node::Node;

            const chila::lib::node::Node &node;

            ParseText(const std::string &text, const chila::lib::node::Node &node) :
                _range(boost::make_iterator_range(text)), node(node) {}

            bool parse();

            Range token() const { return _token; }
            std::string tokenStr() const { return std::string{_token.begin(), _token.end()}; }
            const Node *foundNode() const { return _foundNode; }

        private:
            Range _range, _token;
            Node *_foundNode = nullptr;
            bool outside = true;

            template <typename CastFun>
            bool parseEx(const CastFun &castFun);

            bool parseDefault();
            bool parse(const connector::Connector &node);
            bool parse(const connector::ArgumentBase &node);
            bool parse(const connector::EventBase &node);
            bool parse(const connector::ActionBase &node);
            bool parse(const cPerformer::ConnectionPerformer &node);
            bool parse(const cPerformer::ArgumentBase &node);
            bool parse(const cPerformer::AProviderCreatorBase &node);
            bool parse(const cPerformer::ConnectorAlias &node);
            bool parse(const cPerformer::ConnectorInstance &node);
            bool parse(const cPerformer::ConnectorInstanceGroup &node);
            bool parse(const cPerformer::ActionInstance &node);
            bool parse(const cPerformer::EventCall &node);
            bool parse(const cPerformer::CAArgAlias &node);
            bool parse(const cPerformer::EventAlias &node);
            bool parse(const cPerformer::ActionAlias &node);
    };
}
MY_NSP_END

#include "nspUndef.hpp"



#endif

