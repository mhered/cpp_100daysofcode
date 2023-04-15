#include "TicTacToe.h"
#include <iostream>
#include <vector>

TicTacToe::TicTacToe()
{
    char c = TicTacToe::EMPTY;
    board = {c, c, c,
             c, c, c,
             c, c, c};
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::normalize_board()
{
    for (int i = 0; i < board.size(); i++)
        board[i] = tolower(board[i]);
}

bool TicTacToe::check_for_win(char player)
{

    for (uint i = 0; i < 3; i++)
    {
        // check horizontals
        if (board[3 * i] == player && board[3 * i + 1] == player && board[3 * i + 2] == player)
        {
            // std::cout << player << " wins in horizontal " << i << std::endl;
            return true;
        }
        // check horizontals
        if (board[i] == player && board[3 + i] == player && board[6 + i] == player)
        {
            // std::cout << player << " wins in vertical " << i << std::endl;
            return true;
        }
    }
    // check diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
    {
        // std::cout << player << " wins in a diagonal " << std::endl;
        return true;
    }

    return false;
}

void TicTacToe::set_board(std::vector<char> board)
{
    this->board = board;
    normalize_board();
}

bool TicTacToe::MakeMove(uint pos, char player)
{
    if (board[pos] == TicTacToe::EMPTY)
    {
        board[pos] = player;
        return true;
    }
    return false;
}

int TicTacToe::Evaluate()
{
    if (check_for_win(TicTacToe::X))
        return 10;
    if (check_for_win(TicTacToe::O))
        return -10;
    return 0;
}

uint TicTacToe::FindBestMove()
{
    int BestMoveValue = -1000;
    uint BestMove = 9;

    for (uint i = 0; i < 9; i++)
    {
        if (board[i] == TicTacToe::EMPTY) // if cell is empty
        {
            board[i] = TicTacToe::X;           // make a move
            int MoveValue = MiniMax(0, false); // compute evaluation function for this move
            board[i] = TicTacToe::EMPTY;       // undo the move
            if (MoveValue > BestMoveValue)
            { // update BestMove
                BestMoveValue = MoveValue;
                BestMove = i;
            }
        }
    }
    return BestMove;
}

bool TicTacToe::IsGameOver()
{
    for (int i = 0; i < 9; i++)
        if (board[i] == TicTacToe::EMPTY)
            return false;
    return true;
}

int TicTacToe::MiniMax(int depth, bool isMax)
{
    int score = Evaluate();

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (IsGameOver())
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 9; i++)
        {
            // Check if cell is empty
            if (board[i] == TicTacToe::EMPTY)
            {
                // Make the move
                board[i] = TicTacToe::X;

                // Call minimax recursively and choose
                // the maximum value
                best = std::max(best, MiniMax(depth + 1, !isMax));

                // Undo the move
                board[i] = TicTacToe::EMPTY;
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 9; i++)
        {

            // Check if cell is empty
            if (board[i] == TicTacToe::EMPTY)
            {
                // Make the move
                board[i] = TicTacToe::O;

                // Call minimax recursively and choose
                // the minimum value
                best = std::min(best, MiniMax(depth + 1, !isMax));

                // Undo the move
                board[i] = TicTacToe::EMPTY;
            }
        }
        return best;
    }
}

void TicTacToe::Display()
{
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            std::cout << board[3 * i + j] << " | " << std::flush;
        }
        std::cout << board[3 * i + 2] << std::endl;
        if (i < 2)
            std::cout << "---------" << std::endl;
    }
    std::cout << std::endl;
}