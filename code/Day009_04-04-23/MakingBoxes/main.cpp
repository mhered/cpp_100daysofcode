#include <iostream>
#include <vector>

std::vector<std::string> makeBox(uint n)
{
    char C = '#';

    if (n < 1)
        return {""};
    std::vector<std::string> arr;
    // n>=3
    for (uint i = 0; i < n; i++)
    {
        std::string row;
        if (i == 0 || i == n - 1)
        {
            row = std::string(n, C);
        }
        else
        {
            row = C + std::string(n - 2, ' ') + C;
        }
        arr.push_back(row);
    }
    return arr;
}

void display(std::vector<std::string> arr)
{
    for (auto row : arr)
    {
        std::cout << row << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    display(makeBox(5));

    // {
    //   "#####",
    //   "#   #",
    //   "#   #",
    //   "#   #",
    //   "#####"
    // }

    display(makeBox(3));

    // {
    //   "###",
    //   "# #",
    //   "###"
    // }

    display(makeBox(2));

    // {
    //   "##",
    //   "##"
    // }

    display(makeBox(1));

    // {
    //   "#"
    // }
    return 0;
}