#include <iostream>
#include <vector>

bool check_for(std::vector<std::vector<char>> inputs, char symbol)
{

    for (uint i = 0; i < 3; i++)
    {
        // check horizontals
        if (inputs[i][0] == symbol &&
            inputs[i][1] == symbol &&
            inputs[i][2] == symbol)
        {
            // std::cout << symbol << " wins in horizontal " << i << std::endl;
            return true;
        }
        // check horizontals
        if (inputs[0][i] == symbol &&
            inputs[1][i] == symbol &&
            inputs[2][i] == symbol)
        {
            // std::cout << symbol << " wins in vertical " << i << std::endl;
            return true;
        }
    }
    // check diagonals
    if ((inputs[0][0] == symbol &&
         inputs[1][1] == symbol &&
         inputs[2][2] == symbol) ||
        (inputs[0][2] == symbol &&
         inputs[1][1] == symbol &&
         inputs[2][0] == symbol))
    {
        // std::cout << symbol << " wins in a diagonal " << std::endl;
        return true;
    }
    return false;
}

std::string ticTacToe(std::vector<std::vector<char>> inputs)
{
    for (auto row : inputs)
    {
        for (auto elem : row)
        {
            elem = tolower(elem);
        }
    }
    bool player_1 = check_for(inputs, 'X');
    bool player_2 = check_for(inputs, 'O');
    if (player_1 && !player_2)
        return "Player 1 wins";
    if (player_2 && !player_1)
        return "Player 2 wins";
    return "It's a Tie";
}

int main()
{
    std::string res;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'O', 'X', 'O'},
                     {'O', '#', 'X'}}); // "Player 1 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'O', 'X', 'O'},
                     {'X', '#', 'O'}}); // "Player 2 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'X', 'O'},
                     {'O', 'X', 'O'},
                     {'X', 'O', '#'}}); // "It's a Tie"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', '#', 'X'},
                     {'O', 'O', 'O'},
                     {'O', '#', 'X'}}); //"Player 2 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'O', 'X', 'O'},
                     {'O', '#', 'O'}}); //"Player 2 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'O', 'X', 'O'},
                     {'O', 'O', '#'}}); //"It's a Tie"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'X', 'X', 'O'},
                     {'X', 'O', '#'}}); //"Player 1 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', '#', 'O'},
                     {'X', 'X', 'O'},
                     {'#', 'O', '#'}}); //"It's a Tie"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'X', 'X'},
                     {'X', 'O', 'O'},
                     {'O', 'O', 'X'}}); //"Player 1 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'X', 'O', 'O'},
                     {'O', 'X', 'X'}}); //"Player 2 wins"
    std::cout << res << std::endl;

    res = ticTacToe({{'X', 'O', 'O'},
                     {'X', 'O', 'O'},
                     {'#', 'X', 'X'}}); //"It's a Tie"
    std::cout << res << std::endl;
    
    res = ticTacToe({{'X', 'O', 'O'},
                     {'O', 'O', 'O'},
                     {'#', 'X', 'X'}}); //"Player 2 wins"
    std::cout << res << std::endl;

    return 0;
}
