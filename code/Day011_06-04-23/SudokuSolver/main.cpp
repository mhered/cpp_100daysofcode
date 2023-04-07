#include <iostream>
#include "Sudoku.h"

int main()
{
    /*
    int blank[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int grid[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}};

// An Intermediate puzzle
// from https://sandiway.arizona.edu/sudoku/examples.html :
// Daily Telegraph January 19th "Diabolical"


    int diabolical[9][9] = {
        {0, 2, 0, 6, 0, 8, 0, 0, 0},
        {5, 8, 0, 0, 0, 9, 7, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 0},
        {3, 7, 0, 0, 0, 0, 5, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 8, 0, 0, 0, 0, 1, 3},
        {0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 9, 8, 0, 0, 0, 3, 6},
        {0, 0, 0, 3, 0, 6, 0, 9, 0}};*/

// A Difficult puzzle
// from https://sandiway.arizona.edu/sudoku/examples.html :
// This is puzzle number 2155141, the highest-rated 
// (as of Jan 19th 2006) on Vegard Hanssen's Top 10 list

    int vh_2155141[9][9] = {{0, 0, 0, 6, 0, 0, 4, 0, 0},
                            {7, 0, 0, 0, 0, 3, 6, 0, 0},
                            {0, 0, 0, 0, 9, 1, 0, 8, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 5, 0, 1, 8, 0, 0, 0, 3},
                            {0, 0, 0, 3, 0, 6, 0, 4, 5},
                            {0, 4, 0, 2, 0, 0, 0, 6, 0},
                            {9, 0, 3, 0, 0, 0, 0, 0, 0},
                            {0, 2, 0, 0, 0, 0, 1, 0, 0}};

    Sudoku sudoku(vh_2155141);
    std::cout << "Input:" << std::endl;
    sudoku.show_grid();
    sudoku.solve();
    std::cout << "Solution:" << std::endl;
    sudoku.show_grid();

    return 0;
}