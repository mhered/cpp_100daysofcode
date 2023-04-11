#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// the code to test
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

// A parametrized test

// a struct to hold the parametrized test cases, a constructor and a streamer
struct Sample
{
    int input;
    std::string expected;

    // constructor
    Sample(int input, std::string expected) : input(input), expected(expected){};

    // we override the << operator to have a stream method for Sample
    friend std::ostream &operator<<(std::ostream &os, const Sample &obj)
    {
        return os
               << "input: " << obj.input
               << " expected: " << obj.expected;
    }
};

// create a fixture class derived from the struct of parametrized test cases
struct EasterDateTest : testing::Test, testing::WithParamInterface<Sample>
{
};

// the parametric test
TEST_P(EasterDateTest, ParametricTest)
{
    // get parameters
    auto sample = GetParam();
    // call the function with the input to calculate the actual result
    std::string output = easterDate(sample.input);
    // assert result matches expected
    EXPECT_EQ(sample.expected, output);
}

INSTANTIATE_TEST_CASE_P(Default, EasterDateTest,
                        testing::Values(
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
                            Sample(3535, "April 14th")));

// invoking the tests
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
