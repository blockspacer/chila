/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_TREE__CONNECTORCREATOR_HPP
#define CHILA_CONNECTIONTOOLS_LIB_TREE__CONNECTORCREATOR_HPP

#include "types.hpp"
#include "CreatorBase.hpp"
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/misc/Path.hpp>
#include <vector>
#include <libxml++/libxml++.h>


#include "nspDef.hpp"

MY_NSP_START
{
    class ConnectorCreator final: public CreatorBase
    {
        private:
            using AddFunction = boost::function<void(const std::string &name, const StringVec &argNames,
                    const std::string &description)>;

            void getSignature(const xmlpp::Element &root, StringVec &argNames);

            template <typename Function, typename FunctionGroup, typename FunctionMap>
            void loadFunctions(const xmlpp::Element &root, FunctionMap &functions);

            void loadArguments(const xmlpp::Element &root, connector::Connector &connector);

        public:
            ConnectorCreator(Namespace &nspBase, const boost::filesystem::path &file) :
                CreatorBase(nspBase, file) {}

            connector::Connector &create();
    };
}
MY_NSP_END

#include "nspUndef.hpp"

#endif


