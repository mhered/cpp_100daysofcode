#include <iostream>
#include <sstream>
#include <ctime>
#include <string>

std::tm make_tm(int year, int month, int day)
{
    std::tm tm{};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    tm.tm_isdst = -1;          // data saving time set to "No info"
    return tm;
}

bool extractDate(const std::string &date, int &day, int &month, int &year, struct tm &t)
{
    std::istringstream is(date);
    char delimiter;
    // function expects the string in format mm/dd/yyyy
    if (is >> month >> delimiter >> day >> delimiter >> year)
    {

        t = make_tm(year, month, day);

        // normalize:
        time_t when = mktime(&t);
        const struct tm *norm = localtime(&when);
        // the actual date would be:
        // month = norm->tm_mon + 1;
        // d = norm->tm_mday;
        // year = norm->tm_year;
        // e.g. 29/02/2013 would become 01/03/2013

        // validate (is the normalized date still the same?):
        return (norm->tm_mday == day &&
                norm->tm_mon == month - 1 &&
                norm->tm_year == year - 1900);
    }
    return false;
}

std::string daysUntil2021(std::string date)
{
    std::tm year2021 = make_tm(2021, 1, 1);
    int day, month, year;
    std::tm tm{};

    if (!extractDate(date, day, month, year, tm))
        return "invalid date";

    // Arithmetic time values.
    // On a posix system, these are seconds since 1970-01-01 00:00:00 UTC
    time_t tval_2021 = mktime(&year2021);
    time_t tval_tm = mktime(&tm);

    // Calculate difference in seconds and divide by number of seconds in a day to get days
    const int seconds_per_day = 60 * 60 * 24;

    // To be fully portable, we use "difftime" to give the difference in seconds:
    int portable_difference = (int)std::difftime(tval_2021, tval_tm) / seconds_per_day;

    std::string day_s;
    if (portable_difference == 1)
        day_s = " day";
    else
        day_s = " days";

    return std::to_string(portable_difference) + day_s;
}

int main()
{
    // mm/dd/yyyy format!
    std::cout << daysUntil2021("1/1/2020") << std::endl;   // "366 days"
    std::cout << daysUntil2021("2/28/2020") << std::endl;  // "308 days"
    std::cout << daysUntil2021("12/28/2020") << std::endl; // "3 days"
    std::cout << daysUntil2021("2/29/2019") << std::endl;  // "invalid date" because 2019 was not a leap year
    std::cout << daysUntil2021("4/31/2020") << std::endl;  // "invalid date" no 31st in April!
    std::cout << daysUntil2021("12/31/2020") << std::endl; // "1 day" edge case

    return 0;
}