#ifndef CONNECT4_H
#define CONNECT4_H

#include <vector>
#include <iostream>

#pragma once

class Connect4
{
public:
    const static char X = 'X';
    const static char O = 'O';
    const static char EMPTY = '_';
    const static size_t NROWS = 4; // standard board 6x7 but works max with 4x4
    const static size_t NCOLS = 4;
    const static size_t MIN_DIAG = 4;

public:
    Connect4();
    Connect4(std::vector<char> board) : board(board)
    {
        normalize_board();
        find_back_diagonals();
        find_diagonals();
    };
    Connect4(const Connect4 &other) : board(other.board){}; // copy constructor

    ~Connect4();
    int Evaluate();
    void set_board(std::vector<char> board);
    uint FindBestMove();
    bool MakeMove(uint pos, char player);
    bool IsGameOver();
    int MiniMax(int depth, bool isMax);
    void Display();

public: // change to private
    void normalize_board();
    bool check_for_win(char player);
    bool check_for_win(bool *bool_board, char player);
    bool empty_row_in_column(uint col, uint &row);
    void find_back_diagonals();
    void find_diagonals();

private:
    std::vector<char> board;
    std::vector<std::vector<std::pair<uint, uint>>> diagonals;
    std::vector<std::vector<std::pair<uint, uint>>> back_diagonals;
};

#endif