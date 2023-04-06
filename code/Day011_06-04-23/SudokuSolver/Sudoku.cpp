#include "Sudoku.h"
#include <iostream>
Sudoku::Sudoku(int grid[N][N])
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            this->grid[i][j] = grid[i][j];
        }
    }
}

Sudoku::Sudoku() {}
Sudoku::~Sudoku() {}

bool Sudoku::is_in_col(int n, int col)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[i][col] == n)
            return true;
    }
    return false;
}

bool Sudoku::find_empty(int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

bool Sudoku::is_valid(int row, int col, int n)
{

    return !(is_in_col(n, col)) &&
           !(is_in_row(n, row)) &&
           !(is_in_block(n, 3 * (row / 3), 3 * (col / 3)));
}

bool Sudoku::is_in_row(int n, int row)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == n)
            return true;
    }
    return false;
}

bool Sudoku::is_in_block(int n, int row, int col)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[row + i][col + j] == n)
                return true;
        }
    }
    return false;
}

bool Sudoku::solve()
{
    int row;
    int col;
    if (!find_empty(row, col))
        return true;

    for (int n = 1; n <= N; n++)
    {
        if (is_valid(row, col, n))
        {
            grid[row][col] = n;
            if (solve())
                return true;
            grid[row][col] = 0;
        }
    }
    return false; // no solution
}

void Sudoku::show_grid()
{
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char show_number = grid[i][j] + '0';
            if (show_number == '0')
                show_number = '_';
            if (j < (N - 1) && (j + 1) % 3 == 0)
                std::cout << show_number << " | " << std::flush;
            else
                std::cout << show_number << " " << std::flush;
        }
        std::cout << std::endl;
        if (i < (N - 1) && (i + 1) % 3 == 0)
            std::cout << std::string(22, '-') << std::endl;
    }
    std::cout << std::endl;
}
