#include <iostream>
#include <algorithm>
int cars(int wheels, int bodies, int figures)
{
    const int NUM_WHEELS = 4;
    const int NUM_BODIES = 1;
    const int NUM_FIGURES = 2;

    return std::min({wheels / NUM_WHEELS, bodies / NUM_BODIES, figures / NUM_FIGURES});
}

int main()
{
    std::cout << cars(2, 48, 76) << std::endl;  // 0 // 2 wheels, 48 car bodies, 76 figures
    std::cout << cars(43, 15, 87) << std::endl; // 10
    std::cout << cars(88, 37, 17) << std::endl; // 8

    std::cout << cars(37, 15, 20) << std::endl;    // 9
    std::cout << cars(72, 7, 21) << std::endl;     // 7
    std::cout << cars(9, 44, 34) << std::endl;     // 2
    std::cout << cars(50, 38, 7) << std::endl;     // 3
    std::cout << cars(68, 9, 44) << std::endl;     // 9
    std::cout << cars(3, 29, 54) << std::endl;     // 0
    std::cout << cars(28, 34, 80) << std::endl;    // 7
    std::cout << cars(88, 50, 83) << std::endl;    // 22
    std::cout << cars(66, 18, 21) << std::endl;    // 10
    std::cout << cars(97, 6, 10) << std::endl;     // 5
    std::cout << cars(921, 310, 350) << std::endl; // 175
    std::cout << cars(736, 430, 851) << std::endl; // 184
    std::cout << cars(405, 379, 740) << std::endl; // 101
    std::cout << cars(593, 78, 389) << std::endl;  // 78
    std::cout << cars(875, 370, 675) << std::endl; // 218
    std::cout << cars(863, 274, 203) << std::endl; // 101
    std::cout << cars(959, 331, 537) << std::endl; // 239
    std::cout << cars(416, 340, 551) << std::endl; // 104
    std::cout << cars(692, 348, 543) << std::endl; // 173
    std::cout << cars(527, 412, 951) << std::endl; // 131
    return 0;
}