/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_EVALUATOR_COMMON__DATE_TIME_HPP
#define CHILA_LIB_EVALUATOR_COMMON__DATE_TIME_HPP

#include "util.hpp"
#include "defMacros.hpp"


#include "nspDef.hpp"

MY_NSP_START
{

    struct GetCurrentTime
    {
        typedef boost::posix_time::ptime result_type;
        typedef boost::mpl::vector<> argument_types;

        result_type operator()() const { return boost::posix_time::second_clock::local_time(); }
    };

    template <typename Boolean, typename Numeric, typename String, typename Days, typename Date,
            typename Time, typename DateTime>
    void addDateTimeOperations(expNSP::OperationProviderMap &providerMap)
    {
//        typedef boost::gregorian::date Date;
//        typedef boost::gregorian::date_duration Days;
//        typedef boost::posix_time::time_duration Time;
//        typedef boost::posix_time::ptime DateTime;
        using boost::posix_time::hours;
        using boost::posix_time::minutes;
        using boost::posix_time::seconds;

        // ---------------------------------------- Days ----------------------------------------------------
        // From a number
        addConstructProvider<true, Days, Days, Numeric>(providerMap, "days");

        // From a Date range
        addProvider<true>(providerMap, "-", Substraction<Days, Date, Date>());

        // Relational operators
        addRelational<Boolean, Days>(providerMap);

        // ---------------------------------------- Date ----------------------------------------------------
        // From String
        addProvider<true>(providerMap, "date", unary_bind(
                Date, &boost::gregorian::from_string, String));

        // From 3 numbers
        addConstructProvider<true, Date, Date, Numeric, Numeric, Numeric>(providerMap, "date");

        // Adition to Days
        addAdditionAndSubstraction<Date, Date, Days>(providerMap);

        // Day, month and year of a date
        addProvider<true>(providerMap, "day_if", nullary_member_bind(double, Date, day));
        addProvider<true>(providerMap, "month_of", nullary_member_bind(double, Date, month));
        addProvider<true>(providerMap, "year_of", nullary_member_bind(double, Date, year));


        // Relational operators
        addRelational<Boolean, Date>(providerMap);

        // ---------------------------------------- Time ----------------------------------------------------
        // From String
        addProvider<true>(providerMap, "time", unary_bind(
                Time, &boost::posix_time::duration_from_string, String));

        // From hours, minutes, seconds
        addConstructProvider<true, Time, hours,   Numeric>(providerMap, "hours");
        addConstructProvider<true, Time, minutes, Numeric>(providerMap, "minutes");
        addConstructProvider<true, Time, seconds, Numeric>(providerMap, "seconds");

        // Adition to some time
        addAdditionAndSubstraction<Time, Time, Time>(providerMap);

        // Hours, minutes, seconds of a time
        addProvider<true>(providerMap, "hours_of", nullary_member_bind(double, Time, hours));
        addProvider<true>(providerMap, "minutes_of", nullary_member_bind(double, Time, minutes));
        addProvider<true>(providerMap, "seconds_of", nullary_member_bind(double, Time, seconds));

        // Relational operators
        addRelational<Boolean, Time>(providerMap);

        // -------------------------------------- Date-Time -------------------------------------------------
        // From String
        addProvider<true>(providerMap, "date_time", unary_bind(
                DateTime, &boost::posix_time::time_from_string, String));

        // Fron Now
        addProvider<false>(providerMap, "now", GetCurrentTime());

        // Adition to a Date
        addConstructProvider<true, DateTime, DateTime, Date, Time>(providerMap, "+");

        // Adition to some days
        addAdditionAndSubstraction<DateTime, DateTime, Days>(providerMap);

        // Date of a Date-Time
        addProvider<true>(providerMap, "date_of", nullary_member_bind(Date, DateTime, date));

        // Time of a Date-Time
        addProvider<true>(providerMap, "time_of", nullary_member_bind(Time, DateTime, time_of_day));

        // Relational operators
        addRelational<Boolean, DateTime>(providerMap);
    }

}
MY_NSP_END

#include "nspUndef.hpp"

#endif

