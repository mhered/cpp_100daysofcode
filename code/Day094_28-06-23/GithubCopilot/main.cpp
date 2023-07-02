#include <iostream>
#include "Date.h"

// main function

int main()
{
    // check dayOfWeek() function
    std::cout << "09/04/1975 Should be Wednesday: " << Date::dayOfWeekNames[Date("09/04/1975").dayOfWeek()] << std::endl;
    std::cout << "02/07/2023 Should be Sunday: " << Date::dayOfWeekNames[Date("02/07/2023").dayOfWeek()] << std::endl;
    std::cout << "26/02/2024 Should be Monday: " << Date::dayOfWeekNames[Date("26/02/2024").dayOfWeek()] << std::endl;


    int nWorkingDays;

    // basic check of workingDays() function
    nWorkingDays = workingDays(Date("03/07/2023"), Date("07/07/2023"));

    // print the number of working days
    std::cout << "Should be 4 working days: " << nWorkingDays << std::endl;

    // check edge case
    nWorkingDays = workingDays(Date("03/07/2023"), Date("04/07/2023"));

    // print the number of working days
    std::cout << "Should be 1 working day: " << nWorkingDays << std::endl;

    // check weekends are discounted
    nWorkingDays = workingDays(Date("01/07/2023"), Date("09/07/2023"));

    // print the number of working days
    std::cout << "Should be 5 working days: " << nWorkingDays << std::endl;

    // check bank holiday on 15/08 is considered
    nWorkingDays = workingDays(Date("07/08/2023"), Date("18/08/2023"));

    // print the number of working days
    std::cout << "Should be 8 working days: " << nWorkingDays << std::endl;

    // check on normal year (2023) Feb has 28 days
    nWorkingDays = workingDays(Date("27/02/2023"), Date("01/03/2023"));

    // print the number of working days
    std::cout << "Should be 2 working days: " << nWorkingDays << std::endl;

    // check on leap year (2024) Feb has 29 days
    nWorkingDays = workingDays(Date("27/02/2024"), Date("01/03/2024"));

    // print the number of working days
    std::cout << "Should be 3 working days: " << nWorkingDays << std::endl;

    // return 0 to indicate successful completion
    return 0;
}