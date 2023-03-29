#include <iostream>
#include <string>

std::string fizzBuzz(int num)
{
    std::string output;
    if (num % 3 == 0 && num % 5 == 0)
    {
        output = "FizzBuzz";
    }
    else if (num % 3 == 0)
    {
        output = "Fizz";
    }
    else if (num % 5 == 0)
    {
        output = "Buzz";
    }
    else
    {
        output = std::to_string(num);
    }

    return output;
}

int main()
{

    std::cout << fizzBuzz(3) << std::endl;  // "Fizz"
    std::cout << fizzBuzz(5) << std::endl;  // "Buzz"
    std::cout << fizzBuzz(15) << std::endl; //"FizzBuzz"
    std::cout << fizzBuzz(4) << std::endl;  // "4"

    return 0;
}