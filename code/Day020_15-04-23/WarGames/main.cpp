#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "TicTacToe.h"

int main()
{
    std::cout << "GREETINGS PROFESSOR FALKEN." << std::endl;
    std::cout << "SHALL WE PLAY A GAME?" << std::endl;

    TicTacToe game;
    game.Display();

    do
    {
        int your_move;
        do
        {
            std::cout << "YOU PLAY WITH 'o'S. PLEASE ENTER YOUR MOVE [0-8]:";
            std::cin >> your_move;
            if (game.MakeMove(your_move, TicTacToe::O))
            {
                game.Display();
                break;
            }
            else
                std::cout << "INVALID MOVE, PLEASE TRY AGAIN." << std::endl;
        } while (true);
        int my_move = game.FindBestMove();
        if (0 <= my_move && my_move < 9)
        {
            std::cout << "I PLAY WITH 'x'S. MY MOVE IS: " << my_move << std::endl;
            game.MakeMove(my_move, TicTacToe::X);
            game.Display();
        }
        else
            break;
        if (game.Evaluate())
            break;
    } while (!game.IsGameOver());
    if (game.Evaluate() == 0)
    {
        std::cout << std::endl
                  << "A STRANGE GAME." << std::endl;
        std::cout << "THE ONLY WINNING MOVE IS" << std::endl;
        std::cout << "NOT TO PLAY." << std::endl;
        std::cout << std::endl
                  << "HOW ABOUT A NICE GAME OF CHESS?" << std::endl
                  << std::endl;
    }
    else if (game.Evaluate() > 0)
        std::cout << "I WIN!" << std::endl
                  << std::endl;
}
