#include "Connect4.h"
#include <iostream>
#include <vector>

Connect4::Connect4() // ok
{
    char c = Connect4::EMPTY;
    for (int i = 0; i < (Connect4::NCOLS * Connect4::NROWS); i++)
        board.push_back(c);

    normalize_board();
    find_diagonals();
    find_back_diagonals();
}

Connect4::~Connect4() // ok
{
}

void Connect4::normalize_board() // ok
{
    for (int i = 0; i < board.size(); i++)
        board[i] = toupper(board[i]);
}

bool Connect4::check_for_win(bool bool_board[], char player)
{
    bool verbose = false;

    // check 4 consecutive horizontals in a Connect4::NROWS x Connect4::NCOLS array
    for (size_t i = 0; i < Connect4::NROWS; i++) // for each row starting at bottom
    {
        size_t row = Connect4::NROWS - i - 1;
        size_t NCOLS_x_row = Connect4::NCOLS * row;

        int count = 0;
        for (size_t col = 0; col < Connect4::NCOLS; col++) // for each column
        {
            if (bool_board[NCOLS_x_row + col])
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in horizontal: " << row << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0; // if interrupted, restart counter

            if (count + Connect4::NCOLS - col < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive verticals in a Connect4::NROWS x Connect4::NCOLS array
    for (size_t col = 0; col < Connect4::NCOLS; col++) // for each column
    {
        int count = 0;

        for (size_t row = 0; row < Connect4::NROWS; row++) // for each row
        {
            if (bool_board[Connect4::NCOLS * row + col])
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in vertical: " << col << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                                // if interrupted, restart counter
            if (count + Connect4::NROWS - row < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (int i = 0; i < diagonals.size(); i++)
    {
        int count = 0;
        size_t diagonal_size = diagonals[i].size();
        for (size_t j = 0; j < diagonal_size; j++)
        {
            size_t row = diagonals[i][j].first;
            size_t col = diagonals[i][j].second;
            if (bool_board[Connect4::NCOLS * row + col])
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    // diagonals are k=j-i
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in diagonal j-i = " << col - row << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                            // if interrupted, restart counter
            if (count + diagonal_size - j < MIN_DIAG) // skip to next diagonal if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive backward diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (size_t i = 0; i < back_diagonals.size(); i++) // for each back_diagonal
    {
        int count = 0;
        size_t back_diagonal_size = back_diagonals[i].size();
        for (size_t j = 0; j < back_diagonal_size; j++) // for each element in back_diagonal
        {
            size_t row = back_diagonals[i][j].first;
            size_t col = back_diagonals[i][j].second;

            if (bool_board[Connect4::NCOLS * row + col])
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    // backward diagonals are k=i+j
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in back diagonal i+j = " << row + col << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                                 // if interrupted, restart counter
            if (count + back_diagonal_size - j < MIN_DIAG) // skip to next diagonal if there is not enough elements left
                break;
        }
    }

    return false;
}

bool Connect4::check_for_win(char player)
{
    bool verbose = false;

    // check 4 consecutive horizontals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint i = 0; i < Connect4::NROWS; i++) // for each row starting at bottom
    {
        uint row = Connect4::NROWS - i - 1;
        uint NCOLS_x_row = Connect4::NCOLS * row;

        int count = 0;
        for (uint col = 0; col < Connect4::NCOLS; col++) // for each column
        {
            if (board[NCOLS_x_row + col] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in horizontal: " << row << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0; // if interrupted, restart counter

            if (count + Connect4::NCOLS - col < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive verticals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint col = 0; col < Connect4::NCOLS; col++) // for each column
    {
        int count = 0;

        for (uint row = 0; row < Connect4::NROWS; row++) // for each row
        {
            if (board[Connect4::NCOLS * row + col] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in vertical: " << col << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                                // if interrupted, restart counter
            if (count + Connect4::NROWS - row < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (int i = 0; i < diagonals.size(); i++)
    {
        int count = 0;
        uint diagonal_size = diagonals[i].size();
        for (int j = 0; j < diagonal_size; j++)
        {
            uint row = diagonals[i][j].first;
            uint col = diagonals[i][j].second;
            if (board[Connect4::NCOLS * row + col] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    // diagonals are k=j-i
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in diagonal j-i = " << col - row << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                            // if interrupted, restart counter
            if (count + diagonal_size - j < MIN_DIAG) // skip to next diagonal if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive backward diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (int i = 0; i < back_diagonals.size(); i++) // for each back_diagonal
    {
        int count = 0;
        uint back_diagonal_size = back_diagonals[i].size();
        for (int j = 0; j < back_diagonal_size; j++) // for each element in back_diagonal
        {
            uint row = back_diagonals[i][j].first;
            uint col = back_diagonals[i][j].second;

            if (board[Connect4::NCOLS * row + col] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    // backward diagonals are k=i+j
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in back diagonal i+j = " << row + col << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                                 // if interrupted, restart counter
            if (count + back_diagonal_size - j < MIN_DIAG) // skip to next diagonal if there is not enough elements left
                break;
        }
    }

    return false;
}

void Connect4::set_board(std::vector<char> board) // ok
{
    this->board = board;
    normalize_board();
}

// receive a column, check next empty position in vertical from bottom to top
// if found modify &row and return true, otherwise return false
bool Connect4::empty_row_in_column(uint col, uint &row) // ok
{
    for (int i = Connect4::NROWS; i >= 0; --i)
    {
        if (board[NCOLS * i + col] == Connect4::EMPTY)
        {
            row = i;
            return true;
        }
    }
    return false;
}

void Connect4::find_diagonals()
{
    for (size_t k = -NROWS; k < NCOLS; k++)
    {
        std::vector<std::pair<uint, uint>> diag_tmp;
        for (size_t i = 0; i < NROWS; i++)
        {
            for (size_t j = 0; j < NCOLS; j++)
            {
                if (j - i == k)
                {
                    std::pair elem(i, j);
                    diag_tmp.push_back(elem);
                }
            }
        }
        if (diag_tmp.size() >= MIN_DIAG)
            diagonals.push_back(diag_tmp);
    }
}

// find backwards diagonals
void Connect4::find_back_diagonals()
{
    for (int k = 0; k < NCOLS + NROWS; k++)
    {
        std::vector<std::pair<uint, uint>> diag_tmp;
        for (uint i = 0; i < NROWS; i++)
        {
            for (uint j = 0; j < NCOLS; j++)
            {
                if (i + j == k)
                {
                    std::pair elem(i, j);
                    diag_tmp.push_back(elem);
                }
            }
        }
        if (diag_tmp.size() >= MIN_DIAG)
            back_diagonals.push_back(diag_tmp);
    }
}

// receive a column, check next empty position in vertical from bottom to top
// if found modifies board and returns true, otherwise returns false
bool Connect4::MakeMove(uint col, char player) // ok
{
    uint row;
    if (col >= 0 && col < Connect4::NCOLS && empty_row_in_column(col, row))
    {
        board[NCOLS * row + col] = player;
        return true;
    }
    return false;
}

int Connect4::Evaluate() // ok
{
    bool *bool_board_X = new bool[Connect4::NCOLS * Connect4::NROWS];
    bool *bool_board_O = new bool[Connect4::NCOLS * Connect4::NROWS];
    for (uint i = 0; i < Connect4::NROWS; i++)
    {
        for (uint j = 0; j < Connect4::NCOLS; j++)
        {
            char player = board[Connect4::NCOLS * i + j];
            bool_board_X[Connect4::NROWS * i + j] = (player == Connect4::X);
            bool_board_O[Connect4::NROWS * i + j] = (player == Connect4::O);
        }
    }

    if (check_for_win(bool_board_X, Connect4::X))
        return 10;
    if (check_for_win(bool_board_O, Connect4::O))
        return -10;

    delete[] bool_board_X;
    delete[] bool_board_O;
    return 0;
}

uint Connect4::FindBestMove() // ok
{
    int BestMoveValue = -1000;
    uint BestMove = Connect4::NCOLS;

    for (uint col = 0; col < Connect4::NCOLS; col++)
    {
        uint row;
        if (empty_row_in_column(col, row)) // if empty cell in this column
        {
            board[NCOLS * row + col] = Connect4::X;     // make a move
            int MoveValue = MiniMax(0, false);          // compute evaluation function for this move
            board[NCOLS * row + col] = Connect4::EMPTY; // undo the move
            if (MoveValue > BestMoveValue)
            {
                // update BestMove
                BestMoveValue = MoveValue;
                BestMove = col;
            }
        }
    }
    return BestMove;
}

bool Connect4::IsGameOver() // ok
{
    for (int i = 0; i < Connect4::NROWS * Connect4::NCOLS; i++)
        if (board[i] == Connect4::EMPTY)
            return false;
    return true;
}

int Connect4::MiniMax(int depth, bool isMax) // ok
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

    // If this is maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all columns
        for (int col = 0; col < Connect4::NCOLS; col++)
        {
            // Check if there is an empty cell in column
            uint row;
            if (empty_row_in_column(col, row))
            {
                // Make the move
                board[NCOLS * row + col] = Connect4::X;

                // Call minimax recursively and choose
                // the maximum value
                best = std::max(best, MiniMax(depth + 1, !isMax));

                // Undo the move
                board[NCOLS * row + col] = Connect4::EMPTY; // undo the move
            }
        }
        return best;
    }

    // If this is minimizer's move
    else
    {
        int best = 1000;

        // Traverse all columns
        for (int col = 0; col < Connect4::NCOLS; col++)
        {

            // Check if there is an empty cell in column
            uint row;
            if (empty_row_in_column(col, row))
            {
                // Make the move
                board[NCOLS * row + col] = Connect4::O;

                // Call minimax recursively and choose
                // the minimum value
                best = std::min(best, MiniMax(depth + 1, !isMax)); // should this be isMax??

                // Undo the move
                board[NCOLS * row + col] = Connect4::EMPTY; // undo the move
            }
        }
        return best;
    }
}

/*
_______________
|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|
|_|_|_|_|_|_|_|
|O|_|_|_|_|_|_|
|O|_|_|_|_|_|_|
|O|X|X|X|O|_|_|
 1 2 3 4 5 6 7

 */

void Connect4::Display() // ok
{
    std::cout << std::string(2 * NCOLS + 1, '_') << std::endl;

    for (int i = 0; i < Connect4::NROWS; i++)
    {

        for (int j = 0; j < Connect4::NCOLS; j++)
        {
            std::cout << "|" << board[i * NCOLS + j] << std::flush;
        }
        std::cout << "|" << std::endl;
    }
    std::string legend = " ";
    for (int i = 0; i < Connect4::NCOLS; i++)
        legend += (std::to_string(i + 1) + " ");
    std::cout << legend << std::endl;
}