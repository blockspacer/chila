/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNMDATA_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNMDATA_HPP

#include "exceptions.hpp"
#include <chila/lib/misc/exceptions.hpp>
#include "FunctionSigCreator.hpp"
#include <chila/connectionTools/lib/other/FunExecSequence.hpp>

#include "macros.fgen.hpp"

#define FWDEC_TYPE  CHILA_LIB_MISC__FWDEC_TYPE

MY_NSP_START
{
    template <typename Derived, typename Connector, typename _Arguments>
    class FunMData: public boost::noncopyable
    {
        public:
            using ConnectorType = Connector;
            using result_type = void;
            using Arguments = _Arguments;
            using Signature = typename chila::connectionTools::lib::codegen::FunctionSigCreator<Arguments>::Type;
            using Function = boost::function<Signature>;

            template <typename Fun>
            void passFunAndSet(const Fun &fun)
            {
                if (!this->function)
                    BOOST_THROW_EXCEPTION(FunctionNotSet() << chila::lib::misc::ExceptionInfo::Path(Derived::path()));

                this->function = fun(static_cast<const Function&>(this->function));
            }

            template <typename Fun>
            void addFun(const Fun &fun)
            {
                if (this->function)
                    passFunAndSet(chila::connectionTools::lib::other::funExecSequence(fun));
                else
                    assign(fun);
            }

            operator bool() const { return function; }

        protected:
            Function function;

            template <typename Fun>
            void assign(const Fun &fun)
            {
                if (this->function)
                    BOOST_THROW_EXCEPTION(FunctionAlreadySet() << chila::lib::misc::ExceptionInfo::Path(Derived::path()));

                this->function = fun;
            }
    };
}
MY_NSP_END

#include "macros.fgen.hpp"
#undef FWDEC_TYPE

#endif
