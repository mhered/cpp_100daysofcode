#include <iostream>
#include <vector>
#include <cmath>   //pow
#include <iomanip> // setprecision
#include <sstream>

struct Code // struct to make CODES table
{
public:
    std::string color;
    int digit;
    int magnitude;
    std::string tolerance;
    std::string TCR;

    Code(std::string color,
         int digit,
         int magnitude,
         std::string tolerance,
         std::string TCR) : color(color),
                            digit(digit),
                            magnitude(magnitude),
                            tolerance(tolerance),
                            TCR(TCR){};
};

Code CODES[12] = {
    {"black", 0, 0, "NA", "NA"},
    {"brown", 1, 1, "±1%", "100ppm/k"},
    {"red", 2, 2, "±2%", "50ppm/k"},
    {"orange", 3, 3, "NA", "15ppm/k"},
    {"yellow", 4, 4, "NA", "25ppm/k"},
    {"green", 5, 5, "±0.5%", "NA"},
    {"blue", 6, 6, "±0.25%", "10ppm/k"},
    {"violet", 7, 7, "±0.1%", "5ppm/k"},
    {"gray", 8, 8, "±0.05%", "NA"},
    {"white", 9, 9, "NA", "NA"},
    {"gold", -1, -1, "±5%", "NA"},
    {"silver", -1, -2, "±10%", "NA"}};

// auxiliary function to make string lowercase
std::string lowercase(std::string str)
{
    std::string result;
    for (int i = 0; i < str.size(); i++)
        result.push_back(tolower(str[i]));
    return result;
}

// receives a std::string with a color and finds its index in the CODES table
int find_color(std::string color)
{
    std::string color_lower = lowercase(color);
    for (int i = 0; i < 12; i++)
    {
        if (CODES[i].color == color_lower)
            return i;
    }
    return -1;
}

// main function
std::string resistorCode(std::vector<std::string> colors)
{

    std::vector<int> indexes;
    int codelen = colors.size();
    for (int i = 0; i < codelen; i++)
    {
        int k = find_color(colors[i]);
        indexes.push_back(k);
    }
    double digit;
    int magnitude;
    int precision;
    std::string tolerance, TCR;
    switch (indexes.size())
    {
    case 4:
        precision = 2;
        digit = 10 * CODES[indexes[0]].digit + CODES[indexes[1]].digit;
        magnitude = CODES[indexes[2]].magnitude;
        digit *= pow(10, magnitude);
        tolerance = CODES[indexes[3]].tolerance;
        break;
    case 5:
        precision = 3;
        digit = 100 * CODES[indexes[0]].digit + 10 * CODES[indexes[1]].digit + CODES[indexes[2]].digit;
        magnitude = CODES[indexes[3]].magnitude;
        digit *= pow(10, magnitude);
        tolerance = CODES[indexes[4]].tolerance;
        break;

    case 6:
        precision = 3;
        digit = 100 * CODES[indexes[0]].digit + 10 * CODES[indexes[1]].digit + CODES[indexes[2]].digit;
        magnitude = CODES[indexes[3]].magnitude;
        digit *= pow(10, magnitude);
        tolerance = CODES[indexes[4]].tolerance;

        TCR = CODES[indexes[5]].TCR;
    }

    std::string units, tol;
    if (digit >= pow(10, 9))
    {
        digit /= pow(10, 9);
        units = "GΩ";
    }
    else if (digit >= pow(10, 6))
    {
        digit /= pow(10, 6);
        units = "MΩ";
    }
    else if (digit >= pow(10, 3))

    {
        digit /= pow(10, 3);
        units = "kΩ";
    }
    else
    {
        units = "Ω";
    }

    std::stringstream ss;
    ss << std::setprecision(precision) << digit
       << units << " " << tolerance;
    if (indexes.size() > 5)
        ss << " " + TCR;

    return ss.str();
}
int main()
{

    std::cout << resistorCode({"red", "yellow", "blue", "green"}) << std::endl; // ➞ "24MΩ ±0.5%"
    // red + yellow = 24; blue = 10^6, green = ±0.5%
    // resistance * magnitude = 24000000 (24M)

    std::cout << resistorCode({"white", "black", "white", "blue", "gold"}) << std::endl; // ➞ "909MΩ ±5%"
    // white + black + white = 909

    std::cout << resistorCode({"black", "white", "black", "orange", "red", "yellow"}) << std::endl; // ➞ "90kΩ ±2% 25ppm/k"
    // black + white + black = 090 = 90; orange = 10^3
    // resistance * magnitude = 90000 (90k)

    std::cout << resistorCode({"black", "blue", "black", "brown"}) << std::endl;                      // "6Ω ±1%"
    std::cout << resistorCode({"orange", "yellow", "white", "gold", "gray"}) << std::endl;            // "34.9Ω ±0.05%"
    std::cout << resistorCode({"yellow", "brown", "green", "black", "green", "orange"}) << std::endl; // "415Ω ±0.5% 15ppm/k"
    std::cout << resistorCode({"brown", "violet", "red", "silver"}) << std::endl;                     // "1.7kΩ ±10%"
    std::cout << resistorCode({"green", "gray", "black", "silver", "blue"}) << std::endl;             // "5.8Ω ±0.25%"
    std::cout << resistorCode({"white", "white", "white", "white", "silver", "violet"}) << std::endl; // "999GΩ ±10% 5ppm/k"

    return 0;
}