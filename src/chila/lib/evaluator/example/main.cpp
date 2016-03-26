/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/evaluator/common/basic.hpp>
#include <chila/lib/evaluator/common/date_time.hpp>
#include <chila/lib/evaluator/common/set.hpp>
#include <iostream>
#include <chila/lib/evaluator/common/util.hpp>
#include <chila/lib/evaluator/expression/VariableProviderMap.hpp>
#include <chila/lib/evaluator/expression/OperationProviderMap.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chila/lib/evaluator/parser/util.hpp>
#include <chila/lib/evaluator/parser/interfaces.hpp>
#include <boost/foreach.hpp>

using namespace chila::lib::evaluator::common;
using namespace chila::lib::evaluator::expression;

typedef bool Boolean;
typedef double Numeric;
typedef std::string String;
typedef boost::gregorian::date Date;
typedef boost::gregorian::date_duration Days;
typedef boost::posix_time::time_duration Time;
typedef boost::posix_time::ptime DateTime;
typedef std::shared_ptr< const std::set<Numeric> > NumericSetSCPtr;
typedef std::shared_ptr< const std::set<String> > StringSetSCPtr;

struct ExpressionProvider final: public chila::lib::evaluator::parser::IExpressionProvider
{
    OperationProviderMap opProviders;

    ExpressionProvider()
    {
        addBooleanOperations<Boolean>(opProviders);
        addNumericOperations<Boolean, Numeric>(opProviders);
        addStringOperations<Boolean, Numeric, String>(opProviders);
        addDateTimeOperations<Boolean, Numeric, String, Days, Date, Time, DateTime>(opProviders);

        addSetOperations<Boolean, Numeric>(opProviders);
        addSetOperations<Boolean, String>(opProviders);
    }

    ValueSCPtr createNumericValue(double val) const
    {
        return std::make_shared< ValueBase<Numeric> >(val);
    }

    ValueSCPtr createBooleanValue(bool val) const
    {
        return std::make_shared< ValueBase<Boolean> >(val); ;
    }

    ValueSCPtr createStringValue(const std::string &val) const
    {
        return std::make_shared< ValueBase<String> >(val); ;
    }

    OperationSCPtr createOperation(const std::string &name, const ArgumentListSCPtr &aList) const
    {
        return opProviders.create(name, aList);
    }
};

typedef std::shared_ptr<ExpressionProvider> ExpressionProviderSCPtr;



#include <set>
#include <iostream>
#include <typeinfo>
#include <chila/lib/evaluator/expression/FunctorExecuterOperation.hpp>

template <typename Type>
std::ostream &operator<<(std::ostream &out, const std::shared_ptr< const std::set<Type> > &set)
{
    out << "set<";
    bool first = true;
    for (const auto &element : *set)
    {
        if (first) first = false;
        else out << ", ";
        out << element;
    }

    return out << ">";
}

template <typename Type>
inline void printResultIf(const ExpressionSCPtr &exp, const ValueMap &vMap)
{
    if (std::shared_ptr< const Evaluable<Type> > ev =
            std::dynamic_pointer_cast< const Evaluable<Type> >(exp))
    {
        unsigned rep = 10000;
        Type ret;
        DateTime startTime = boost::posix_time::microsec_clock::local_time();
        for (unsigned i = 0; i < rep; ++i)
        {
            ret = ev->evaluate(vMap);
        }
        DateTime endTime = boost::posix_time::microsec_clock::local_time();
        Time avTime = (endTime - startTime) / rep;

        std::cout << "Result: " << ret << std::endl;
        std::cout << "Av. time: " << avTime << std::endl;
    }
}

int main()
{

    ExpressionProviderSCPtr eProv = std::make_shared<ExpressionProvider>();

    std::string text;// = "5 *";

    ValueMap vMap;

    vMap.setValue("alpha", double(6));
    vMap.setValue("beta", double(8.7));
    vMap.setValue("gamma", false);

    typedef std::string::const_iterator Iterator;

    typedef chila::lib::evaluator::parser::IParser<Iterator> IParser;
    typedef std::shared_ptr<const IParser> IParserSCPtr;

    IParserSCPtr parser = chila::lib::evaluator::parser::createStrItParser(eProv, false);
//            std::make_shared< chila::lib::evaluator::parser::Parser<Iterator> >(eProv, false);

    while (getline(std::cin, text)) try
    {
        Iterator begin = text.begin(), end = text.end();

        ExpressionSCPtr exp = parser->parse(begin, end, vMap);

        exp->print(std::cout);

        printResultIf<Boolean>(exp, vMap);
        printResultIf<Numeric>(exp, vMap);
        printResultIf<String>(exp, vMap);
        printResultIf<Days>(exp, vMap);
        printResultIf<Date>(exp, vMap);
        printResultIf<Time>(exp, vMap);
        printResultIf<DateTime>(exp, vMap);
        printResultIf<NumericSetSCPtr>(exp, vMap);
        printResultIf<StringSetSCPtr>(exp, vMap);

        std::cout << "\n--------------------------------------------------------------" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}


