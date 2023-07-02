#ifndef DATE_H
#define DATE_H

#pragma once

#include <string>
#include <vector>
#include <iostream>

// a class Date with day, month and year
// a Date constructor that receives a string in the format "dd/mm/yyyy"
// a static list of bank holidays
// a static list of day of week names
// 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday, 5 = Saturday, 6 = Sunday

// a function to calculate the number of working days between two dates
class Date
{
    int day;
    int month;
    int year;

public:
    const static std::vector<std::string> bankHolidays;
    const static std::vector<std::string> dayOfWeekNames;
    Date(int day, int month, int year) : day(day), month(month), year(year){};
    Date(std::string);
    int dayOfWeek();
    bool isBankHoliday();
    std::string to_str();

    // overloading the < operator
    friend bool operator<(const Date &d1, const Date &d2);
    // overloading the = operator
    friend bool operator==(const Date &d1, const Date &d2);
    // overloading the <= operator
    friend bool operator<=(const Date &d1, const Date &d2);
    // overloading the ++ operator
    friend void operator++(Date &d1, int);

    friend int workingDays(Date startDate, Date endDate);
};

#endif