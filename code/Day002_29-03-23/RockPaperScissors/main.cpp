#include <iostream>

std::string rps(std::string s1, std::string s2)
{
    std::string winner;
    std::string msg;

    if ((s1 == "scissors" || s1 == "paper" || s1 == "rock") &&
        (s2 == "scissors" || s2 == "paper" || s2 == "rock"))
    {
        if (s1 == s2)
        {
            return "TIE";
        }
        else if ((s1 == "rock" && s2 == "scissors") ||
                 (s1 == "paper" && s2 == "rock") ||
                 (s1 == "scissors" && s2 == "paper"))
        {
            winner = "1";
        }
        else if ((s2 == "rock" && s1 == "scissors") ||
                 (s2 == "paper" && s1 == "rock") ||
                 (s2 == "scissors" && s1 == "paper"))
        {
            winner = "2";
        }
        msg = "Player " + winner + " wins";
    }
    else
        msg = "Invalid input";
    return msg;
}

int main()
{

    std::cout << rps("rock", "paper") << std::endl;        // "Player 2 wins"
    std::cout << rps("paper", "rock") << std::endl;        // "Player 1 wins"
    std::cout << rps("paper", "scissors") << std::endl;    // "Player 2 wins"
    std::cout << rps("scissors", "scissors") << std::endl; // "TIE"
    std::cout << rps("scissors", "paper") << std::endl;    // "Player 1 wins"

    return 0;
}
