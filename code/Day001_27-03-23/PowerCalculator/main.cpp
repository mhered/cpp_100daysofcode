#include <iostream>

int circuitPower(int voltage, int current)
{
    return voltage * current;
}

int main()
{
    std::cout << circuitPower(230, 10) << std::endl;
    std::cout << circuitPower(110, 3) << std::endl;
    std::cout << circuitPower(480, 20) << std::endl;
}