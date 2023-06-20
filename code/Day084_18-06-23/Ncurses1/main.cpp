#include <ncurses.h>

int main(int argc, char **argv)
{
    // initialize screen
    // set up memory and clear screen
    initscr();

    int columns, rows;
    columns = 4;
    rows = 7;

    // note it is y, x with origin in top left ocrner
    move(rows, columns);

    // print a string (const char *) to a window
    printw("Press any key (ESC to quit):");

    // refresh screen to match what is in memory
    refresh();

    while (true)
    {
        // wait for user input, return int value of key pressed
        move(7, columns + 32);

        int c = getch();
        if (c == 27)
            break;

        // mvprintw() condenses move() and printw()
        // in a single instruction

        mvprintw(4, columns + 20, "You pressed %c (%d)\n", c, c);

        mvprintw(5, columns + 32, "|");

        mvprintw(6, columns + 32, "V");
    }

    // clear the screen
    clear();

    // wait for user input
    getch();

    // deallocate memory and end ncurses
    endwin();

    return 0;
}