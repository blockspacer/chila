/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_COMMON_IMPL_CONNECTION__FORWARDER_HPP
#define CHILA_CONNECTIONTOOLS_COMMON_IMPL_CONNECTION__FORWARDER_HPP

#include "fwd.hpp"
#include <chila/connectionTools/lib/other/Module.hpp>
#include "../../connectors/gen/Forwarder.hpp"

#include <chila/lib/misc/macrosExp.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct Forwarder
    {
        struct Object: public virtual chila::lib::misc::Streamable
        {
            virtual ~Object() {}
        };

        CHILA_LIB_MISC__FWDEC_SPTR(Object);

        struct ArgTypes
        {
            typedef std::string     errorMsg;
            typedef ObjectSCPtr     object;
        };

        DEF_CPROVIDER(Forwarder);

        using ExecuterFun = boost::function<void(
                const CProvider::Connector::Actions::MData_take::EventExecuter &eventExecuter,
                const ObjectSCPtr &object)>;

        static CProviderUPtr create(const std::string &instanceName, const ExecuterFun &executer = ExecuterFun());
    };

}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
