#include <iostream>
#include "kbhit.h"
#include <chrono>
#include <thread>
#include <vector>

const int HEIGHT = 15;
const int WIDTH = 50;
int delay = 200;


std::string EDGE_FORMAT = "\033[36m"; // cyan
std::string SNAKE_FORMAT = "\033[32m"; // green
std::string FRUIT_FORMAT = "\033[31m"; // red
std::string RESET_FORMAT = "\033[0m";

/*
std::string NOKIA = "\033[1;42;30m";

std::string EDGE_FORMAT = NOKIA;
std::string SNAKE_FORMAT = NOKIA;
std::string FRUIT_FORMAT = NOKIA;
std::string RESET_FORMAT = NOKIA;
*/

char FRUIT = '@'; // red
char SNAKE = 'O'; // green
char EDGE = '#';  // cyan

bool game_over;
int fruit_x, fruit_y;
std::vector<int> x, y;

int score = 1;
enum Direction
{
    STOP,
    RIGHT,
    LEFT,
    UP,
    DOWN
};
Direction dir;

void setup()
{
    game_over = false;
    dir = STOP;
    x.push_back(WIDTH / 2 - 1);
    y.push_back(HEIGHT / 2 - 1);
    fruit_x = rand() % (WIDTH - 2) + 1; // spawn new fruit
    fruit_y = rand() % (HEIGHT - 2) + 1;
}

void draw()
{
    system("clear");

    std::cout << EDGE_FORMAT << std::string(WIDTH, EDGE) << RESET_FORMAT << "  SCORE:" << score << std::endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            std::string str = RESET_FORMAT + " " + RESET_FORMAT;
            for (int k = 0; k < score; k++)
            {
                if (i == y[k] && j == x[k])
                {
                    str = SNAKE_FORMAT + std::string(1, SNAKE) + RESET_FORMAT; // snake
                }
                else if (j == 0 || j == WIDTH - 1)
                {
                    str = EDGE_FORMAT + std::string(1, EDGE) + RESET_FORMAT; // edge
                }
                else if (i == fruit_y && j == fruit_x)
                {
                    str = FRUIT_FORMAT + std::string(1, FRUIT) + RESET_FORMAT; // fruit
                }
            }
            std::cout << str; // print
        }
        std::cout << std::endl;
    }

    std::cout << EDGE_FORMAT;
    for (int i = 0; i < WIDTH; i++)
    {
        std::cout << EDGE;
    }
    std::cout << RESET_FORMAT << std::endl;
}

void input(keyboard keyboard)
{

    if (keyboard.kbhit())
    {
        switch ((char)keyboard.getch())
        {
        case 'o':
            dir = LEFT;
            break;
        case 'p':
            dir = RIGHT;
            break;
        case 'q':
            dir = UP;
            break;
        case 'a':
            dir = DOWN;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void logic()
{
    int new_x = x.back();
    int new_y = y.back();

    switch (dir)
    {
    case LEFT:
        // if (new_x > 1)
        new_x--;
        break;
    case RIGHT:
        // if (new_x < WIDTH - 2)
        new_x++;
        break;
    case UP:
        // if (new_y > 0)
        new_y--;
        break;
    case DOWN:
        // if (new_y < HEIGHT - 1)
        new_y++;
        break;
    }
    if (new_x != x.back() || new_y != y.back()) // update needed
    {
        // check collision with borders
        if (new_x < 0 || new_x >= WIDTH - 1 || new_y < 0 || new_y >= HEIGHT)
            game_over = true;

        // check collision with snake
        for (int k = 0; k < score; k++)
        {
            if (new_x == x[k] && new_y == y[k])
            {
                game_over = true;
            }
        }
        // check eaten fruit
        if (new_x == fruit_x && new_y == fruit_y)
        {
            score++;                            // grow snake
            fruit_x = rand() % (WIDTH - 2) + 1; // spawn new fruit
            fruit_y = rand() % (HEIGHT - 2) + 1;
            delay -= 5; // increase game speed
        }
        else
        {
            x.erase(x.begin());
            y.erase(y.begin());
        }
        // Update position
        x.push_back(new_x);
        y.push_back(new_y);
    }
}

int main()
{
    setup();
    keyboard my_keyboard;
    while (!game_over)
    {
        draw();
        input(my_keyboard);
        logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // regulate speed
    }
}
