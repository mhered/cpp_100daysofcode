#include <iostream>

// ask user for name and greet them

int main()
{
    // ask for the person's name
    std::cout << "Please enter your first name: ";

    // read the name
    std::string name; // define name
    std::cin >> name; // read into

    // write a greeting
    std::cout << "Hello, " << name << "!" << std::endl;
    return 0;
}
