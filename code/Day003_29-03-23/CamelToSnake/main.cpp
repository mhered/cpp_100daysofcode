#include <iostream>
#include <cctype>

std::string toSnakeCase(std::string str)
{
    for (uint i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
        {
            std::string lowercase(1, (char)std::tolower(str[i]));
            str.replace(i, 1, "_" + lowercase);
        }
    }
    return str;
}

std::string toCamelCase(std::string str)
{
    for (uint i = 0; i < str.length(); i++)
    {
        if (str[i] == '_')
        {
            char uppercase = (char)std::toupper(str[i + 1]);
            std::string replacestr(1, uppercase);
            str.replace(i, 2, replacestr);
        }
    }
    return str;
}

int main()
{
    std::cout << toCamelCase("hello_edabit") << std::endl;  // "helloEdabit"
    std::cout << toSnakeCase("helloEdabit") << std::endl;   // "hello_edabit"
    std::cout << toCamelCase("is_modal_open") << std::endl; // "isModalOpen"
    std::cout << toSnakeCase("getColor") << std::endl;      // "get_color"
    return 0;
}