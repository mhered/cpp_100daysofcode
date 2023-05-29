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
    /*
    find_horizontals();
    find_verticals();
    */
}

Connect4::~Connect4() // ok
{
}

void Connect4::normalize_board() // ok
{
    for (int i = 0; i < board.size(); i++)
        board[i] = toupper(board[i]);
}
/*
bool Connect4::check_for_win(char player)
{
    bool verbose = false;

    // check 4 consecutive horizontals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint i = 0; i < Connect4::NROWS; i++)
    {

        // for each row starting at bottom
        uint row = Connect4::NROWS - i - 1;
        uint NCOLS_x_row = Connect4::NCOLS * row;

        int count = 0;
        for (uint j = 0; j < Connect4::NCOLS; j++) // for each column
        {
            if (board[NCOLS_x_row + j] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in horizontal #" << i << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0; // if interrupted, restart counter

            if (count + Connect4::NCOLS - j < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive verticals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint j = 0; j < Connect4::NCOLS; j++) // for each column
    {
        int count = 0;

        for (uint i = 0; i < Connect4::NROWS; i++) // for each row
        {
            if (board[Connect4::NCOLS * i + j] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in vertical: " << j << std::endl;
                        Display();
                    }
                    return true;
                }
            }
            else
                count = 0;                              // if interrupted, restart counter
            if (count + Connect4::NROWS - i < MIN_DIAG) // skip to next column if there is not enough elements left
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
            if (board[diagonals[i][j]] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in diagonal #" << i << std::endl;
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
            if (board[back_diagonals[i][j]] == player)
            {
                count++;
                if (count >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << player << " wins in back diagonal #" << i << std::endl;
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
*/
int Connect4::Evaluate()
{
    bool verbose = false;

    // check 4 consecutive horizontals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint i = 0; i < Connect4::NROWS; i++)
    {

        // for each row starting at bottom
        uint row = Connect4::NROWS - i - 1;
        uint NCOLS_x_row = Connect4::NCOLS * row;

        int count_X = 0;
        int count_O = 0;

        for (uint j = 0; j < Connect4::NCOLS; j++) // for each column
        {
            char val = board[NCOLS_x_row + j];
            if (val == Connect4::X)
            {
                count_X++;
                count_O = 0;
                if (count_X >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::X << " wins in horizontal #" << i << std::endl;
                        Display();
                    }
                    return 10;
                }
            }
            else if (val == Connect4::O)
            {
                count_O++;
                count_X = 0;
                if (count_O >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::O << " wins in horizontal #" << i << std::endl;
                        Display();
                    }
                    return -10;
                }
            }
            else
            {
                count_X = 0; // if empty, restart counters
                count_O = 0;
            }

            if (count_X + Connect4::NCOLS - j < MIN_DIAG &&
                count_O + Connect4::NCOLS - j < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive verticals in a Connect4::NROWS x Connect4::NCOLS array
    for (uint j = 0; j < Connect4::NCOLS; j++) // for each column
    {
        int count_X = 0;
        int count_O = 0;

        for (uint i = 0; i < Connect4::NROWS; i++) // for each row
        {
            char val = board[Connect4::NCOLS * i + j];
            if (val == Connect4::X)
            {
                count_X++;
                count_O = 0;

                if (count_X >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::X << " wins in vertical: " << j << std::endl;
                        Display();
                    }
                    return 10;
                }
            }
            else if (val == Connect4::O)
            {
                count_O++;
                count_X = 0;

                if (count_O >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::O << " wins in vertical: " << j << std::endl;
                        Display();
                    }
                    return -10;
                }
            }
            else
            {
                count_X = 0; // scanning upwards, so if empty found, skip to next
                count_O = 0;
                break;
            }

            if (count_X + Connect4::NROWS - i < MIN_DIAG &&
                count_O + Connect4::NROWS - i < MIN_DIAG) // skip to next column if there is not enough elements left
                break;
        }
    }

    // check 4 consecutive diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (int i = 0; i < diagonals.size(); i++)
    {
        int count_X = 0;
        int count_O = 0;

        uint diagonal_size = diagonals[i].size();
        for (int j = 0; j < diagonal_size; j++)
        {
            char val = board[diagonals[i][j]];
            if (val == Connect4::X)
            {
                count_X++;
                count_O = 0;
                if (count_X >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::X << " wins in diagonal #" << i << std::endl;
                        Display();
                    }
                    return 10;
                }
            }
            else if (val == Connect4::O)
            {
                count_O++;
                count_X = 0;
                if (count_O >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::O << " wins in diagonal #" << i << std::endl;
                        Display();
                    }
                    return -10;
                }
            }
            else
            {
                count_X = 0; // if empty, restart counters
                count_O = 0;
            }

            // skip to next diagonal if there is not enough elements left

            if (count_X + diagonal_size - j < MIN_DIAG &&
                count_O + diagonal_size - j < MIN_DIAG)
                break;
        }
    }

    // check 4 consecutive backward diagonals in a Connect4::NROWS x Connect4::NCOLS array
    for (int i = 0; i < back_diagonals.size(); i++) // for each back_diagonal
    {
        int count_X = 0;
        int count_O = 0;

        uint back_diagonal_size = back_diagonals[i].size();
        for (int j = 0; j < back_diagonal_size; j++) // for each element in back_diagonal
        {
            char val = board[back_diagonals[i][j]];
            if (val == Connect4::X)
            {
                count_X++;
                count_O = 0;
                if (count_X >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::X << " wins in back diagonal #" << i << std::endl;
                        Display();
                    }
                    return 10;
                }
            }
            else if (val == Connect4::O)
            {
                count_O++;
                count_X = 0;
                if (count_O >= MIN_DIAG) // MIN_DIAG is 4 in Connect4
                {
                    if (verbose)
                    {
                        std::cout << std::endl
                                  << Connect4::O << " wins in back diagonal #" << i << std::endl;
                        Display();
                    }
                    return -10;
                }
            }
            else
            {
                count_X = 0; // if empty found, restart both counters
                count_O = 0;
            }
            if (count_X + back_diagonal_size - j < MIN_DIAG &&
                count_O + back_diagonal_size - j < MIN_DIAG) // skip to next diagonal if there is not enough elements left
                break;
        }
    }

    return 0; // no one wins
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

/*
void Connect4::find_horizontals()
{
    for (uint i = 0; i < NROWS; i++)
    {
        // for each row starting at bottom
        uint row = Connect4::NROWS - i - 1;
        uint NCOLS_x_row = Connect4::NCOLS * row;

        std::vector<uint> horiz_tmp;
        for (uint j = 0; j < NCOLS; j++)
        {
            horiz_tmp.push_back(NCOLS_x_row + j);
        }
        horizontals.push_back(horiz_tmp);
    }
}

void Connect4::find_verticals()
{
    for (uint j = 0; j < NCOLS; j++)
    {
        std::vector<uint> vert_tmp;
        for (uint i = 0; i < NROWS; i++)
        {
            vert_tmp.push_back(Connect4::NCOLS * i + j);
        }
        verticals.push_back(vert_tmp);
    }
}
*/

void Connect4::find_diagonals()
{
    for (int k = -NROWS; k < NCOLS; k++)
    {
        std::vector<uint> diag_tmp;
        for (uint i = 0; i < NROWS; i++)
        {
            for (uint j = 0; j < NCOLS; j++)
            {
                if (j - i == k)
                {
                    diag_tmp.push_back(Connect4::NCOLS * i + j);
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
        std::vector<uint> diag_tmp;
        for (uint i = 0; i < NROWS; i++)
        {
            for (uint j = 0; j < NCOLS; j++)
            {
                if (i + j == k)
                {
                    diag_tmp.push_back(Connect4::NCOLS * i + j);
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

/*
int Connect4::Evaluate() // ok
{
    if (check_for_win(Connect4::X))
        return 10;
    if (check_for_win(Connect4::O))
        return -10;
    return 0;
}
*/

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