#include <iostream>
#include <string>
#include <vector>

std::string maskify(std::string str)
{
    if (str.size() < 4)
        return str;
    else
        return str.replace(str.begin(), str.end() - 4, std::string(str.size() - 4, '#'));
}

void test_maskify(std::string input, std::string expected)
{
    std::string output = maskify(input);
    if (output == expected)
        std::cout << "  OK: maskify(\"" << input << "\") = \"" << expected << "\"" << std::endl;
    else
        std::cout << "* KO: maskify(\"" << input << "\") = \"" << output << "\" != \"" << expected << "\"" << std::endl;
}

int main()
{
    std::vector<std::vector<std::string>> samples = {
        {"4556364607935616", "############5616"},
        {"64607935616", "#######5616"},
        {"1", "1"},
        {"", ""},
        {"tBy>L/cMe+?<j:6n;C~H", "################;C~H"},
        {"12", "12"},
        {"8Ikhlf6yoxPOwi5cB014eWbRumj7vJ", "##########################j7vJ"},
        {"123", "123"},
        {")E$aCU=e\"_", "######=e\"_"},
        {"2673951408", "######1408"},
        {"1234", "#234"}};

    for (auto item : samples)
    {
        std::string input = item[0];
        std::string expected = item[1];
        test_maskify(input, expected);
    }

    return 0;
}
