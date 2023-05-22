#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

std::string color_text(int number, int color_key)
{
    std::stringstream ss;
    ss << "\033[48;5;" << color_key << "m " << std::setfill('0') << std::setw(2) << std::to_string(number); // format
    ss << "\033[0m";                                                                                        // reset
    return ss.str();
}

std::vector<std::vector<std::pair<int, int>>> find_diagonals(int NROWS, int NCOLS, int MIN_DIAG)
{
    std::vector<std::vector<std::pair<int, int>>> diagonals;

    for (int k = -NROWS; k < NCOLS; k++)
    {
        std::vector<std::pair<int, int>> diag_tmp;
        for (int i = 0; i < NROWS; i++)
        {
            for (int j = 0; j < NCOLS; j++)
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
    return diagonals;
}

// find backwards diagonals
std::vector<std::vector<std::pair<int, int>>> find_back_diagonals(int NROWS, int NCOLS, int MIN_DIAG)
{
    std::vector<std::vector<std::pair<int, int>>> back_diagonals;

    for (int k = 0; k < NCOLS + NROWS; k++)
    {
        std::vector<std::pair<int, int>> diag_tmp;
        for (int i = 0; i < NROWS; i++)
        {
            for (int j = 0; j < NCOLS; j++)
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
    return back_diagonals;
}

int main()
{
    int NCOLS = 7;
    int NROWS = 6;
    int MIN_DIAG = 4;

    // initialize
    std::vector<int> board;

    // populate with indexes for easier display
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            board.push_back((10 * i) + j);
        }
    }

    // display array
    std::cout << "Array  of " << NROWS << " x " << NCOLS << " elements:" << std::endl
              << std::endl;
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            std::cout << std::setfill('0') << std::setw(2) << board[NCOLS * i + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // find diagonals
    std::vector<std::vector<std::pair<int, int>>> diagonals = find_diagonals(NROWS, NCOLS, MIN_DIAG);

    // print message
    std::cout << "Found " << diagonals.size() << " diagonals with at least " << MIN_DIAG << " elements:" << std::endl;

    // print elements
    for (auto diagonal : diagonals)
    {
        for (auto item : diagonal)
        {
            std::cout << " [" << item.first << "," << item.second << "]: " << board[item.first * NCOLS + item.second];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // print illustration
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            std::cout << color_text(board[NCOLS * i + j], abs(j - i)) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // find backwards diagonals
    std::vector<std::vector<std::pair<int, int>>> back_diagonals = find_back_diagonals(NROWS, NCOLS, MIN_DIAG);

    // print message
    std::cout << "Found " << back_diagonals.size() << " backwards diagonals with at least " << MIN_DIAG << " elements:" << std::endl;

    // print elements
    for (auto back_diagonal : back_diagonals)
    {
        for (auto item : back_diagonal)
        {
            std::cout << " [" << item.first << "," << item.second << "]: " << board[item.first * NCOLS + item.second];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // print illustration
    for (int i = 0; i < NROWS; i++)
    {
        for (int j = 0; j < NCOLS; j++)
        {
            std::cout << color_text(board[NCOLS * i + j], i + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}