#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

#define M_PI 3.14159265358979323846 /* pi */
#define G 9.81                      /* g m/s2 */

std::string javelinThrow(float v, int a)
{

    double max_height, max_range;
    double a_rad = a * (M_PI / 180.0);

    double t_0 = v * sin(a_rad) / G;
    max_range = 2 * v * cos(a_rad) * t_0;
    max_height = v * sin(a_rad) * t_0 - (G / 2.0 * t_0 * t_0);

    std::stringstream ss;
    ss << "Ymax=" << round(max_height) << "m, Xmax=" << round(max_range) << "m";
    std::string result = ss.str();
    return result;
}

int main()
{
    std::cout << javelinThrow(100.0, 37) << std::endl; // ➞ "Ymax=185m, Xmax=980m"
    std::cout << javelinThrow(36.7, 45) << std::endl;  // ➞ "Ymax=34m, Xmax=137m"
    std::cout << javelinThrow(51.3, 20) << std::endl;  // ➞ "Ymax=16m, Xmax=172m"
    std::cout << javelinThrow(11.1, 25) << std::endl;  // ➞ "Ymax=1m, Xmax=10m"
    std::cout << javelinThrow(75.5, 40) << std::endl;  // ➞ "Ymax=120m, Xmax=572m"
    std::cout << javelinThrow(250.0, 42) << std::endl; // ➞ "Ymax=1426m, Xmax=6336m"
    std::cout << javelinThrow(100.1, 89) << std::endl; // ➞" Ymax=511m, Xmax=36m"

    return 0;
}