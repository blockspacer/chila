/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_NODE__UTIL_HPP
#define CHILA_LIB_NODE__UTIL_HPP

#include <chila/lib/misc/util.hpp>
#include "exceptions.hpp"

#define my_assert CHILA_LIB_MISC__ASSERT

#define CHILA_META_NODE__DEF_CHECK_BASES_ELEM(n, data, elem) \
        chila::lib::node::checkAndAdd(list, [&]{ elem::check(newData.get()); });


#define CHILA_META_NODE__DEF_CHECK_BASES(Bases, defMyCheck) \
        BOOST_PP_IF(defMyCheck, chila::lib::node::CheckDataUPtr createCheckData(chila::lib::node::CheckData *data) const;, ); \
        BOOST_PP_IF(defMyCheck, void myCheck(chila::lib::node::CheckData *data = nullptr) const;, ); \
        void check(chila::lib::node::CheckData *data = nullptr) const override \
        { \
            chila::lib::node::CheckExceptionList list; \
            auto newData = BOOST_PP_IF(defMyCheck, createCheckData(data), chila::lib::node::CheckDataUPtr()); \
            BOOST_PP_SEQ_FOR_EACH(CHILA_META_NODE__DEF_CHECK_BASES_ELEM,,Bases) \
            BOOST_PP_IF(defMyCheck, BOOST_PP_IDENTITY(\
                chila::lib::node::checkAndAdd(list, [&]{ myCheck(newData.get()); }); \
            ), BOOST_PP_EMPTY)(); \
            if (!list.exceptions.empty()) throw list; \
        }

#define CHILA_META_NODE__DEF_CHECK \
        void check(chila::lib::node::CheckData *data = nullptr) const override;

#include "nspDef.hpp"

MY_NSP_START
{
    template <typename CheckFun>
    void checkAndAdd(chila::lib::node::CheckExceptionList &list, const CheckFun &checkFun) try
    {
        checkFun();
    }
    catch (ExceptionWrapper &ex)
    {
        list.add(ex.ex);
    }
    catch (CheckExceptionList &ex)
    {
        list.add(ex);
    }
    catch (Exception &ex)
    {
        list.add(ex);
    }

    chila::lib::misc::Path getNodePath(const Node &node); // to avoid cyclical dependency

    template <typename Fun>
    inline auto catchThrow(const Node &node, const Fun &fun) -> decltype(fun()) try
    {
        return fun();
    }
    catch (const boost::exception &ex)
    {
        ex << chila::lib::misc::ExceptionInfo::Path(getNodePath(node));
        throw;
    }

    template <typename ToType, typename Node>
    inline const ToType &castNode(const Node &node) try
    {
        return catchThrow(node, [&]() -> const ToType& { return chila::lib::misc::dynamicCast<ToType>(node); });
    }
    catch (const boost::exception &ex)
    {
        InvalidNode exx;
        insert_error_info(chila::lib::misc::ExceptionInfo::TypeFrom)
        insert_error_info(chila::lib::misc::ExceptionInfo::TypeTo)
        insert_error_info(chila::lib::misc::ExceptionInfo::ActualType)
        insert_error_info(chila::lib::misc::ExceptionInfo::Path)

        BOOST_THROW_EXCEPTION(exx);
    }

    template <typename ToType, typename Node>
    inline ToType &castNode(Node &node) try
    {
        return catchThrow(node, [&]() -> ToType& { return chila::lib::misc::dynamicCast<ToType>(node); });
    }
    catch (const boost::exception &ex)
    {
        InvalidNode exx;
        insert_error_info(chila::lib::misc::ExceptionInfo::TypeFrom)
        insert_error_info(chila::lib::misc::ExceptionInfo::TypeTo)
        insert_error_info(chila::lib::misc::ExceptionInfo::ActualType)
        insert_error_info(chila::lib::misc::ExceptionInfo::Path)

        BOOST_THROW_EXCEPTION(exx);
    }

    NodeWithChildren &mainParent(NodeWithChildren &node);

    PathVec getReferences(
        NodeWithChildren &node,
        const chila::lib::misc::Path &path);

    void replaceReferences(NodeWithChildren &node, const PathVec &paths, const Node &newRefNode);

}
MY_NSP_END

#include "nspUndef.hpp"

#endif
