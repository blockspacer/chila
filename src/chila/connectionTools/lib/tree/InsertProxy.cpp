/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "InsertProxy.hpp"

#define ins_first(what) \
        if (first) first = false; \
        else out << what;

#define INDENT repeatText(indent, "    ")

#include "nspDef.hpp"

MY_NSP_START
{
//     InsertProxy &InsertProxy::operator=(const InsertProxy &rhs)
//    {
//        this->container = rhs.container; rhs.container = nullptr;
//        this->node = rhs.node;
//        this->pos = rhs.pos; rhs.pos = 0;
//        return *this;
//    }
//
//    void InsertProxy::operator()()
//    {
//        my_assert(container);
//        container->insert(node, pos);
//    }
//
//    InsertProxy NodeMap::remove(const std::string &id)
//    {
//        NodeAPtr node;
//        unsigned pos;
//
//        auto it = map.find(id);
//        if (it == map.end())
//            BOOST_THROW_EXCEPTION(NodeNotFound() << ErrorInfo::Path(path() + id));
//
//        node = NodeAPtr(map.release(it).release());
//
//        auto vecIt = boost::find(vec, it);
//
//        pos = std::distance(vec.begin(), vecIt);
//
//        vec.erase(vecIt);
//
//        InsertProxy ret(this, node, pos);
//        return ret;
//    }
//
//    InsertProxy NodeVector::remove(const std::string &id)
//    {
//        return chila::lib::misc::removeConst(remove(boost::lexical_cast<unsigned>(id)));
//    }
//
//    InsertProxy NodeVector::remove(unsigned index)
//    {
//        NodeAPtr node(vector.release(vector.begin() + index).release());
//        InsertProxy ret(this, node, index);
//        updateIndexes();
//        return ret;
//    }
//    InsertProxy &InsertProxy::operator=(const InsertProxy &rhs)
//    {
//        this->container = rhs.container; rhs.container = nullptr;
//        this->node = rhs.node;
//        this->pos = rhs.pos; rhs.pos = 0;
//        return *this;
//    }
//
//    void InsertProxy::operator()()
//    {
//        my_assert(container);
//        container->insert(node, pos);
//    }
//
//    InsertProxy NodeMap::remove(const std::string &id)
//    {
//        NodeAPtr node;
//        unsigned pos;
//
//        auto it = map.find(id);
//        if (it == map.end())
//            BOOST_THROW_EXCEPTION(NodeNotFound() << ErrorInfo::Path(path() + id));
//
//        node = NodeAPtr(map.release(it).release());
//
//        auto vecIt = boost::find(vec, it);
//
//        pos = std::distance(vec.begin(), vecIt);
//
//        vec.erase(vecIt);
//
//        InsertProxy ret(this, node, pos);
//        return ret;
//    }

}
MY_NSP_END
