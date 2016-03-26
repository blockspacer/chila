/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_EXPRESSION__EXPRESSION_HPP
#define CHILA_LIB_EVALUATOR_EXPRESSION__EXPRESSION_HPP

#include "util.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <assert.h>
#include "fwd.hpp"
#include "ValueMap.hpp"
#include <boost/make_shared.hpp>
#include "ValueMap.hpp"

#include "defMacros.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    struct Expression
    {
        virtual void print(std::ostream &out, std::vector<bool> &prefixList) const = 0;
        void print(std::ostream &out) const
        {
            std::vector<bool> prefixList;
            print(out, prefixList);
        }
    };

    template <typename _Type>
    struct Evaluable
    {
        typedef _Type Type;
        virtual Type evaluate(const ValueMap &valueMap) const  = 0;
    };

    struct Variable: public Expression
    {
        std::string name;

        Variable(const std::string &name) : name(name) {}

        const std::string &getName() const { return  name; }

        void print(std::ostream &out, std::vector<bool> &prefixList) const
        {
            printPrefix(prefixList);
            out << "[var: " << name << "]" << std::endl;;
        }
    };

    template <typename _Type>
    struct VariableBase: public Variable, public Evaluable<_Type>
    {
        typedef _Type Type;

        VariableBase(const std::string &name) : Variable(name) {}

        Type evaluate(const ValueMap &valueMap) const
        {
            typedef Evaluable<Type> EvType;
            std::shared_ptr<const EvType> ev =
                std::dynamic_pointer_cast<const EvType>(valueMap.getValue(name));

            if (!ev) throw InvalidValue();

            return ev->evaluate(valueMap);
        }
    };

    struct Value: public Expression
    {
        virtual VariableSCPtr createVariable(const std::string &name) const = 0;
    };

    template <typename _Type>
    struct ValueBase final: public Value, public Evaluable<_Type>
    {
        typedef _Type Type;
        Type val;

        ValueBase(const Type &val) : val(val) {}

        Type evaluate(const ValueMap &valueMap) const
        {
            return val;
        };

        VariableSCPtr createVariable(const std::string &name) const
        {
            return std::make_shared< VariableBase<Type> >(name);
        }

        void print(std::ostream &out, std::vector<bool> &prefixList) const
        {
            printPrefix(prefixList);
            out << "[lit: " << val << "]" << std::endl;;
        }
    };

    struct Operation: public Expression
    {
        ArgumentListSCPtr argList;
        std::string name;

        Operation(const std::string &name, const ArgumentListSCPtr &argList) : name(name), argList(argList) {}

        const std::string &getName() const { return name; }

        const ArgumentListSCPtr &getArgumentList() const { return argList; }

        virtual ValueSCPtr evaluateOnValue(const ValueMap &valueMap) const = 0;

        virtual bool isConstant() const = 0;

        void print(std::ostream &out, std::vector<bool> &prefixList) const
        {
            printPrefix(prefixList);
            out << "[" << getName() << "]" << std::endl;

            if (argList)
            {
                ArgumentList::const_iterator it;
                for (it = argList->begin(); it != argList->end(); ++it)
                {
                    prefixList.push_back(it == argList->end() - 1 ? 0 : 1);
                    (*it)->print(out, prefixList);
                    prefixList.pop_back();
                }
            }
        }

        void print(std::ostream &out)
        {
            Expression::print(out);
        }
    };

}
MY_NSP_END

#include "nspUndef.hpp"
#endif

