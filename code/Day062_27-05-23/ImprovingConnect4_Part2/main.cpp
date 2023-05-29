#include <iostream>
#include <vector>
#include "Connect4.h"

#include <chrono>

template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int main()
{

    // debug
    /*
    Connect4 game(
        {'x', '_', 'o', '_',
         'x', 'o', 'o', '_',
         'x', 'x', 'o', 'o',
         'o', 'o', 'o', 'x'});

    Connect4 game(
        {'_', '_', '_', '_', '_', '_', '_',
         'o', '_', '_', '_', '_', '_', '_',
         'x', '_', '_', '_', '_', '_', '_',
         'x', 'o', 'x', '_', '_', 'o', '_',
         'x', 'x', 'x', 'o', 'x', 'o', '_',
         'o', 'o', 'o', 'x', 'x', 'o', 'o'});

    game.Display();

    std::string str = game.IsGameOver() ? "yes" : "no";
    std::cout << "Is game over? " << str << std::endl;
    str = game.check_for_win(Connect4::X) ? "yes" : "no";
    std::cout << "Did X win? " << str << std::endl;
    str = game.check_for_win(Connect4::O) ? "yes" : "no";
    std::cout << "Did O win? " << str << std::endl;
    */

    Connect4 game;
    game.Display();

    do
    {
        int your_move;
        do
        {
            std::cout << "YOU PLAY WITH 'o'S. PLEASE ENTER YOUR MOVE [1-7]:";
            std::cin >> your_move;
            if (game.MakeMove(your_move - 1, Connect4::O)) // from 1-NCOLS to (0-NCOLS-1) for processing
            {
                game.Display();
                break;
            }
            else
                std::cout << "INVALID MOVE, PLEASE TRY AGAIN." << std::endl;
        } while (true);

        // Timestamp the start of the code
        auto beg = std::chrono::high_resolution_clock::now();

        int my_move = game.FindBestMove();

        // Timestamp after the code is ran
        auto end = std::chrono::high_resolution_clock::now();

        // Subtract the timestamps and cast the differenc to microseconds
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

        // Display the elapsed time
        std::cout << "(Elapsed Time: " << duration.count()/1000000.0 << " seconds)" << std::endl;

        if (0 <= my_move && my_move < Connect4::NROWS)
        {
            std::cout << "I PLAY WITH 'x'S. MY MOVE IS: " << my_move + 1 << std::endl; // display 1-NCOLS
            game.MakeMove(my_move, Connect4::X);
            game.Display();
        }
        else
            break;
        if (game.Evaluate() != 0)
            break;
    } while (!game.IsGameOver());
    if (game.Evaluate() == 0)
    {
        std::cout << std::endl
                  << "THAT WAS A DRAW" << std::endl;
    }
    else if (game.Evaluate() > 0)
        std::cout << "I WIN!" << std::endl
                  << std::endl;
    else if (game.Evaluate() < 0)
        std::cout << "CONGRATS, YOU WIN!" << std::endl
                  << std::endl;
}
