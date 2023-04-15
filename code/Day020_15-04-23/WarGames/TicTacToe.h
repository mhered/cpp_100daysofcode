#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <iostream>

#pragma once

class TicTacToe
{
public:
    const static char X = 'x';
    const static char O = 'o';
    const static char EMPTY = ' ';

public:
    TicTacToe();
    TicTacToe(std::vector<char> board) : board(board) { normalize_board(); };
    TicTacToe(const TicTacToe &other) : board(other.board){}; // copy constructor

    ~TicTacToe();
    int Evaluate();
    void set_board(std::vector<char> board);
    uint FindBestMove();
    bool MakeMove(uint pos, char player);
    bool IsGameOver();
    int MiniMax(int depth, bool isMax);
    void Display();

private:
    void normalize_board();
    bool check_for_win(char player);

private:
    std::vector<char> board;
};

#endif