#include <iostream>
#include <vector>

std::string easterDate(int y)
{
    int a = y % 19;
    int b = y / 100;
    int c = y % 100;
    int d = b / 4;
    int e = b % 4;
    int g = (8 * b + 13) / 25;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 19 * l) / 433;
    int n = (h + l - 7 * m + 90) / 25;
    int p = (h + l - 7 * m + 33 * n + 19) % 32;
    std::string month;
    if (n == 3)
        month = "March";
    else
        month = "April";

    std::string ending = "th";

    if (p == 1 || p == 21 || p == 31)
        ending = "st";
    if (p == 2 || p == 22)
        ending = "nd";
    if (p == 3 || p == 23)
        ending = "rd";

    return month + " " + std::to_string(p) + ending;
}

// a struct with the input data, the expected result and a constructor
struct Sample
{
    int input;
    std::string expected;
    Sample(int input, std::string expected) : input(input), expected(expected){};
};

// a testing function
bool test_function(Sample sample)
{
    // function name (for display only)
    std::string function_name = "easterDate";
    // call the function with the input to calculate the actual result
    std::string output = easterDate(sample.input);

    if (output == sample.expected)
        std::cout << ".   " << function_name << "( " << sample.input << " ) = \"" << sample.expected << "\"" << std::endl;
    else
        std::cout << "X   " << function_name << "( "
                  << sample.input << " ) = \""
                  << output << "\" != \""
                  << sample.expected << "\" (expected)" << std::endl;

    return output == sample.expected;
}

int main()
{
    // define a vector of testing cases
    // unsing the struct Sample constructor
    std::vector<Sample> samples = {
        Sample(1600, "April 2nd"),  // start of Gregorian calendar
        Sample(1611, "April 3rd"),  // a year where it falls on a 3rd
        Sample(1636, "March 23rd"), // a year where it falls on a 23rd
        Sample(1653, "April 13th"), // a year where it falls on 13th
        Sample(1722, "April 5th"),  // Easter Island discovered https://www.rappler.com/newsbreak/iq/55843-easter-sunday-in-history/
        Sample(1853, "March 27th"),
        Sample(1945, "April 1st"),  // Start of Battle of Okinawa in WWII https://www.rappler.com/newsbreak/iq/55843-easter-sunday-in-history/
        Sample(1990, "April 15th"), // Birthday of Emma Watson https://www.rappler.com/newsbreak/iq/55843-easter-sunday-in-history/
        Sample(2019, "April 21st"),
        Sample(2020, "April 12th"),
        Sample(2021, "April 4th"),
        Sample(2022, "April 17th"),
        Sample(2023, "April 9th"), // my birthday! Also 1939, 1944, 1950, 2034, 2045 see https://www.dr-mikes-math-games-for-kids.com/easter-date-tables.html?century=21
        Sample(2024, "March 31st"),
        Sample(2028, "April 16th"),
        Sample(3535, "April 14th")};

    // run the tests counting how many passed
    int tests_passed = 0;
    int tests_total = 0;
    for (auto sample : samples)
    {
        if (test_function(sample))
            tests_passed++;
        tests_total++;
    }
    std::cout << std::endl
              << tests_passed << "/"
              << tests_total << " tests passed successfully"
              << std::endl
              << std::endl;
    return 0;
}
