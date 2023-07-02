#include "Date.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// initialize the static list of bank holidays
const std::vector<std::string> Date::bankHolidays = {
    "01/01",
    "06/01",
    "19/03",
    "01/05",
    "15/08",
    "12/10",
    "01/11",
    "25/12"};

// initialize the static list of day of week names
const std::vector<std::string> Date::dayOfWeekNames = {"Monday",
                                                       "Tuesday",
                                                       "Wednesday",
                                                       "Thursday",
                                                       "Friday",
                                                       "Saturday",
                                                       "Sunday"};

// Date constructor that receives a string in the format "dd/mm/yyyy" and converts it to a Date
Date::Date(std::string date)
{
    // get the day, month and year from the string
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    // set the day, month and year
    this->day = day;
    this->month = month;
    this->year = year;
}

// function to determine which day of the week a date falls on
// dates are passed as Date objects
// returns an int 0-6 for the day of the week
// 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday, 5 = Saturday, 6 = Sunday
int Date::dayOfWeek()
{
    // calculate the day of the week
    // int dayOfWeek = (day + (2 * month) + (3 * (month + 1) / 5) + year + (year / 4) - (year / 100) + (year / 400)) % 7;

    //int m = (month + 9) % 12;
    //int y = year - m / 10;
    //int dn = 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (day - 1);

    // return the day of the week
    //return (dn % 7);


    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };  
    int y = year - (month < 3);  
    return ( y + y / 4 - y / 100 + y / 400 + t[month - 1] + day -1) % 7;  
}



// function to determine if a date is Bank Holiday
bool Date::isBankHoliday()
{
    // build a dd/mm string with day and month
    std::string dayMonth = to_str().substr(0, 5);

    // check if the dayMonth string is in the bankHolidays list
    if (std::find(bankHolidays.begin(), bankHolidays.end(), dayMonth) != bankHolidays.end())
    {
        // dayMonth is in the bankHolidays list
        return true;
    }
    else
    {
        // dayMonth is not in the bankHolidays list
        return false;
    }
}

bool operator<(const Date &d1, const Date &d2)
{
    if (d1.year < d2.year)
    {
        return true;
    }
    else if (d1.year == d2.year)
    {
        if (d1.month < d2.month)
        {
            return true;
        }
        else if (d1.month == d2.month)
        {
            if (d1.day < d2.day)
            {
                return true;
            }
        }
    }
    return false;
}

bool operator==(const Date &d1, const Date &d2)
{
    if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
    {
        return true;
    }
    return false;
}

bool operator<=(const Date &d1, const Date &d2)
{
    if (d1 == d2 || d1 < d2)
    {
        return true;
    }
    return false;
}

void operator++(Date &d1, int)
{
    // a vector of pairs with number of days per month
    std::vector<std::pair<int, int>> daysPerMonth = {
        {1, 31},
        {2, 28},
        {3, 31},
        {4, 30},
        {5, 31},
        {6, 30},
        {7, 31},
        {8, 31},
        {9, 30},
        {10, 31},
        {11, 30},
        {12, 31}};

    // check if the year is a leap year
    if (d1.year % 4 == 0)
    {
        // year is a leap year
        daysPerMonth[1].second = 29;
    }

    d1.day++;
    // check if the day is greater than the number of days in the month
    if (d1.day > daysPerMonth[d1.month - 1].second)
    {
        // day is greater than the number of days in the month
        d1.day = 1;
        d1.month++;
        // check if the month is greater than 12
        if (d1.month > 12)
        {
            // month is greater than 12
            d1.month = 1;
            d1.year++;
        }
    }
}

std::string Date::to_str()
{
    // return a string in the format "dd/mm/yyyy"
    // use leading zeroes for day and month
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "/" << std::setw(2) << std::setfill('0') << month << "/" << year;
    return oss.str();
}

// function to calculate the number of working days between two dates
// dates are passed as Date objects
// working days do not include weekends or bank holidays
// uses Date::dayOfWeek() function and Date::bankHolidays static list
// does not consider leap years

int workingDays(Date date1, Date date2)
{
    // initialize the number of working days
    int workingDays = 0;

    // loop through the dates between date1 and date2
    for (Date date = date1; date < date2; date++)
    {
        // check if the date is a weekend
        if (date.dayOfWeek() == 5 || date.dayOfWeek() == 6)
        {
            // date is a weekend
            // print the day of the week
            std::cout << date.to_str() << " is a weekend: " << Date::dayOfWeekNames[date.dayOfWeek()] << std::endl;

            continue;
        }

        // check if the date is a bank holiday
        if (date.isBankHoliday())
        {
            // date is a bank holiday

            std::cout << date.to_str() << " is a Bank holiday" << std::endl;

            continue;
        }

        // date is a working day
        workingDays++;
    }

    // return the number of working days
    return workingDays;
}