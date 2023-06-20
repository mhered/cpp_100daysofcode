#include <ncurses.h>

int main(int argc, char **argv)
{
    // initialize screen
    // set up memory and clear screen
    initscr();

    // print a string (const char *) to a window
    printw("Press any key (ESC to quit)\n");

    // refresh screen to match what is in memory
    refresh();

    while (true)
    {
        // wait for user input, return int value of key pressed
        int c = getch();
        if (c == 27)
            break;
        printw("  You pressed %c (%d)\n", c, c);
    }
    // deallocate memory and end ncurses
    endwin();

    return 0;
}