#include <iostream>
#include <vector>

class Grid
{
private:
    std::vector<std::vector<bool>> board;

public:
    Grid(std::vector<std::vector<bool>> board) : board(board){};
    Grid(int N);
    int numCols() { return board[0].size(); };
    int numRows() { return board.size(); };
    bool IsSafe(int row, int col);
    void PlaceQueen(int row, int col);
    void RemoveQueen(int row, int col);
    bool Solve(int col);
    void showGrid();
};

Grid::Grid(int N) // Constructor of an empty N by N board
{ 
    std::vector<std::vector<bool>> empty_board(N, std::vector<bool>(N));
    board = empty_board;
};

void Grid::showGrid()
{

    for (int i = 0; i < numCols(); i++)
    {
        std::cout << " _";
    }
    std::cout << " " << std::endl;
    for (int i = 0; i < numRows(); i++)
    {
        for (int j = 0; j < numCols(); j++)
        {
            std::string pos = board[i][j] ? "Q" : "_";
            std::cout << "|" << pos;
        }
        std::cout << "|" << std::endl;
    }
}

bool Grid::IsSafe(int row, int col)
{
    // check no Queens in row
    for (int i = 0; i < numCols(); i++)
    {
        if (board[row][i])
            return false;
    }
    // check no Quees in column
    for (int i = 0; i < numRows(); i++)
    {
        if (board[i][col])
            return false;
    }
    // check no Queens in diagonals
    for (int i = 0; i < numRows(); i++)
    {
        for (int j = 0; j < numCols(); j++)
        {
            if (((i + j) == (row + col)) && board[i][j])
                return false;
            if (((j - i) == (col - row)) && board[i][j])
                return false;
        }
    }
    return true;
}
void Grid::PlaceQueen(int row, int col)
{
    board[row][col] = true;
}

void Grid::RemoveQueen(int row, int col)
{

    board[row][col] = false;
}

// 8 Queens Backtracking Algorithm
bool Grid::Solve(int col = 0)
{
    if (col >= numCols()) // base case
        return true;
    for (int rowToTry = 0; rowToTry < numRows(); rowToTry++)
    {
        // for all choices available
        if (IsSafe(rowToTry, col))
        {
            // make the choice
            PlaceQueen(rowToTry, col);
            showGrid();
            // try to solve from here, if works out, you're done
            if (Solve(col + 1))
            {
                return true;
            }
            // if not, unmake the choice and keep looking
            RemoveQueen(rowToTry, col);
        }
    }
    // tried all choices, no solution found
    return false;
}

int main()
{

    Grid empty(8);
    empty.showGrid();
    empty.Solve();
    return 0;
}