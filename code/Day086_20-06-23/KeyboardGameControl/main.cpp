#include <ncurses.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
const int HEIGHT = 30;
const int WIDTH = 60;

struct Pos
{
    int x;
    int y;
    int angle; // angle in 45deg multiples: 0 - 7
};

void draw_character(Pos pos0, Pos pos)
{
    mvprintw(pos0.y, pos0.x, " ");
    mvprintw(pos.y, pos.x, "%i", pos.angle);
}

void move_up(Pos &pos)
{
    if (pos.y > 2)
        pos.y--;
}

void move_down(Pos &pos)
{
    if (pos.y < (HEIGHT - 1))
        pos.y++;
}

void move_left(Pos &pos)
{
    if (pos.x > 2)
        pos.x--;
}

void move_right(Pos &pos)
{
    if (pos.x < (WIDTH - 1))
        pos.x++;
}

void rotate_ccwise(Pos &pos)
{
    pos.angle = (pos.angle + 1) % 8;
}

void rotate_cwise(Pos &pos)
{
    pos.angle = (pos.angle - 1) % 8;
}

int main(int argc, char **argv)
{
    /* NCURSES START*/
    // initialize screen
    // set up memory and clear screen
    initscr();
    timeout(60);

    cbreak(); // Ctrl+C will exit
    raw();    // do not accept special characters
    noecho(); // avoid showing input to the screen

    int start_y = 5;
    int start_x = 10;

    // create a window pointer
    WINDOW *win = newwin(HEIGHT, WIDTH, start_y, start_x);

    Pos pos0, pos;
    pos = {WIDTH / 2, HEIGHT / 2, 0};

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        pos0 = pos;
        std::vector<int> pressed_keys;
        int c = getch();
        while (c != ERR)
        {
            if (std::find(pressed_keys.begin(), pressed_keys.end(), c) == pressed_keys.end()) // add char only once per frame
                pressed_keys.push_back(c);
            c = getch();
        }

        if (!pressed_keys.empty())
        {
            mvprintw(2, 1, "Pressed: ");

            for (int i = 0; i < pressed_keys.size(); i++)
            {
                printw("%c ", char(pressed_keys[i]));
                switch (char(pressed_keys[i]))
                {
                case 'q':
                    move_up(pos);
                    break;
                case 'a':
                    move_down(pos);
                    break;
                case 'o':
                    move_left(pos);
                    break;
                case 'p':
                    move_right(pos);
                    break;
                case 'n':
                    rotate_ccwise(pos);
                    break;
                case 'm':
                    rotate_cwise(pos);
                    break;
                }
            }
        }

        mvprintw(1, 1, "x:%i y:%i angle:%i", pos.x, pos.y, pos.angle);

        if (pos.x != pos0.x || pos.y != pos0.y || pos.angle != pos0.angle)
        {
            draw_character(pos0, pos);
            refresh();
        }
    }

    // deallocate memory and end ncurses
    endwin();
    /* NCURSES END*/

    return 0;
}