/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 *
 * This file is part of 'chila.connectionTools.lib.codegen'
 *
 * 'chila.connectionTools.lib.codegen' is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 'chila.connectionTools.lib.codegen' is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'chila.connectionTools.lib.codegen'. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNMDATA_HPP
#define CHILA_CONNECTIONTOOLS_LIB_CODEGEN__FUNMDATA_HPP

#include <boost/mpl/vector.hpp>
#include "exceptions.hpp"
#include <chila/lib/misc/exceptions.hpp>
#include "FunctionSigCreator.hpp"
#include <chila/connectionTools/lib/other/util.hpp>

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
            using Function = std::function<Signature>;

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

            operator bool() const { return bool(function); }

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
