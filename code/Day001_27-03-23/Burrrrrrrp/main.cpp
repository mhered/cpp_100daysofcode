#include <string>
#include <iostream>

std::string longBurp(uint num)
{
    std::string rs(num, 'r');
    std::string burp = "Bu" + rs + "p";
    return burp;
}

int main()
{
    std::cout << longBurp(3) << std::endl;
    std::cout << longBurp(5) << std::endl;
    std::cout << longBurp(9) << std::endl;
}