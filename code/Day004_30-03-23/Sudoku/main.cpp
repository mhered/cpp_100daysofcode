#include <iostream>
#include <vector>

void showSudoku(std::vector<std::vector<int>> square)
{

    for (auto row : square)
    {
        for (auto elem : row)
        {
            std::cout << elem << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

bool isMiniSudoku(std::vector<std::vector<int>> square)
{

    bool found[9] = {0};

    for (auto row : square)
    {
        for (auto elem : row)
        {
            if (elem < 1 || elem > 9)
            {
                return false; // out of bounds
            }

            if (found[elem - 1] == false)
            {
                found[elem - 1] = true;
            }
            else
            {
                return false; // duplicate
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (!found[i])
            return false; // redundant: check all numbers 1-9 found
    }
    return true; // valid Sudoku
}

int main()
{
    // showSudoku({{1, 3, 2}, {9, 7, 8}, {4, 5, 6}});
    std::cout << isMiniSudoku({{1, 3, 2}, {9, 7, 8}, {4, 5, 6}}) << std::endl; // true
    std::cout << isMiniSudoku({{1, 1, 3}, {6, 5, 4}, {8, 7, 9}}) << std::endl; // false
    std::cout << isMiniSudoku({{0, 1, 2}, {6, 4, 5}, {9, 8, 7}}) << std::endl; // false
    std::cout << isMiniSudoku({{8, 9, 2}, {5, 6, 1}, {3, 7, 4}}) << std::endl; // true

    return 0;
}