#include "kbhit.h"
#include <iostream>

int main()
{
    int key_nr;
    char key;
    keyboard keyboard;
    while (true)
    {
        if (keyboard.kbhit())
        {
            key_nr = keyboard.getch(); // return int
            key = key_nr;              // get ascii char

            std::cout << "You pressed:  " << key << " (" << key_nr << ")" << std::endl;
        }
    }
    return 0;
}
