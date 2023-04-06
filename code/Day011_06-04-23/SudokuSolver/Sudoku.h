#ifndef SUDOKU_H
#define SUDOKU_H

#pragma once

class Sudoku
{
    const static int N = 9;

public:
    Sudoku();
    Sudoku(int grid[N][N]);
    ~Sudoku();

    bool solve();
    void show_grid();

private:
    bool is_in_col(int n, int col);
    bool is_in_row(int n, int row);
    bool is_in_block(int n, int row, int col);
    bool find_empty(int &row, int &col);
    bool is_valid(int row, int col, int n);

private:
    int grid[N][N];
};

#endif