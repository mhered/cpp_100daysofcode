#include <ncurses.h>

int main(int argc, char **argv)
{

    /* NCURSES START*/
    // initialize screen
    // set up memory and clear screen
    initscr();

    cbreak(); // Ctrl+C will exit
    // raw();    // do not accept special characters
    noecho(); // avoid showing input to the screen

    int height, width, start_y, start_x;
    height = 10;
    width = 20;
    start_y = 5;
    start_x = 10;

    // create a window pointer
    WINDOW *win = newwin(height, width, start_y, start_x);

    // must refresh screen to match what is in memory
    refresh();

    // add a box
    // Can provide ASCII value for the symbol to use
    // on top-bottom, and left-right borders
    // 0, 0 is default: a simple single line
    int top_bottom = (int)'='; // this casts char to int
    int left_right = (int)'I';

    // box(win, left_right, top_bottom);

    // wborder works the same and gives full control
    int left, right, top, bottom, tlc, trc, blc, brc;
    left = (int)'|';
    right = (int)'#';
    top = (int)'-';
    bottom = (int)'#';
    tlc = trc = blc = brc = (int)'+';
    wborder(win, left, right, top, bottom, tlc, trc, blc, brc);

    // add output to the window
    // move relative to top right corner of window then print
    mvwprintw(win, 1, 2, "This is a box");

    // refresh the window in which box was created
    wrefresh(win);

    // wait for user input
    while (true)
        getch();

    // deallocate memory and end ncurses
    endwin();
    /* NCURSES END*/

    return 0;
}