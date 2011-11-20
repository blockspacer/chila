/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_LIB_MISC_FUSION_FUNSEQEXECUTER_H
#define CHILA_LIB_MISC_FUSION_FUNSEQEXECUTER_H

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/invoke_function_object.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/preprocessor.hpp>
#include <boost/mpl/set.hpp>


#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

DEF_NAMESPACE(4, (chila,lib,misc,fusion))
{
    template <typename FunFSeq>
    struct FunSeqExecuter
    {
        typedef void result_type;

        template <typename ArgFSeq>
        struct Executer
        {
            ArgFSeq args;
            Executer(const ArgFSeq &args) : args(args) {}

            template <typename Fun>
            void operator()(const Fun &fun) const
            {
                boost::fusion::invoke_function_object(fun, args);
            }
        };

        template <typename ArgFSeq>
        Executer<ArgFSeq> executer(const ArgFSeq &args) const
        {
            return Executer<ArgFSeq>(args);
        }

        FunFSeq seq;
        FunSeqExecuter(const FunFSeq &seq) : seq(seq) {}

        void operator()() const
        {
            boost::fusion::for_each(seq, executer(boost::fusion::make_vector()));
        }

        #define DEF_OPERATOR(z, argCount, data) \
            template <BOOST_PP_ENUM_PARAMS(argCount, typename Arg)>                                     \
            void operator()(BOOST_PP_ENUM_BINARY_PARAMS(argCount, const Arg, &arg)) const               \
            {                                                                                           \
                boost::fusion::for_each(seq,                                                            \
                        executer(boost::fusion::make_vector(BOOST_PP_ENUM_PARAMS(argCount, arg))));     \
            }


        BOOST_PP_REPEAT_FROM_TO(1, 49, DEF_OPERATOR, )
    };

    template <typename FunFSeq>
    inline FunSeqExecuter<FunFSeq> funSeqExecuter(const FunFSeq &functions)
    {
        return FunSeqExecuter<FunFSeq>(functions);
    }

}}}}

#undef DEF_NAMESPACE
#undef DEF_OPERATOR

#include <chila/lib/misc/macrosUndef.hpp>
#endif