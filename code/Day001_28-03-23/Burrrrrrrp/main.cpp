#include <string>
#include <iostream>

std::string longBurp(int num)
{
    if (num < 1)
    {
        return "Error";
    }

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